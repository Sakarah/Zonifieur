#include "utils.h"
#include "actions.h"
#include "loopavoider.h"
#include <limits>
#include <algorithm>

#ifdef DEBUG
#include <cstdio>
#endif

/**
 * Renvoie le meilleur portail trouvé pour continuer à fabriquer des liens / embêter l'adversaire
 * Si aucun ne correspond, renvoie (15,15)
 */
position bestPortal()
{
    int bestValue = 0;
    position bestPos = position(15,15);
    std::vector<position> listPortal = liste_portails();
    for(position portal : listPortal)
    {
        int val = portalValue(portal);
        if(val > bestValue)
        {
            position realPos = nearestPosReachable(myPos(), portal, points_deplacement()+points_action()/6);
            if(LoopAvoider::instance().checkLoop(realPos)) continue;
            bestValue = val;
            bestPos = portal;
        }
    }

#ifdef DEBUG
    std::printf("Best portal : (%d,%d)\n", bestPos.x, bestPos.y);
    std::fflush(stdout);
#endif

    return bestPos;
}

/**
 * Fonction chargée d'évaluer la pertinence du mouvement vers un portail
 * Plus la valeur de retour est grande plus il est intéressant de prendre le portail
 */
int portalValue(position pos)
{
#ifdef DEBUG_HARD
    std::printf("(%d,%d)", pos.x, pos.y);
    std::fflush(stdout);
#endif

    if(portail_joueur(pos) == -2) return 0;
    if(distance(pos, myPos()) > 30) return 0; // On élimine les vraiment trop loin

    int score = 0;
    if(portail_joueur(pos) == adversaire())
    {
        // Bonus correspondant à la prise d'aire de l'adversaire
        for(champ c : champs_incidents_portail(pos))
        {
            score += score_triangle(c.som1, c.som2, c.som3);
        }
        score /= 10; // Constante qui aurait du être remplacée par un calcul en fonction du nombre de tours nécessaires
        score -= COUT_NEUTRALISATION/5;
        score -= (COUT_NEUTRALISATION_BOUCLIER/5) * portail_boucliers(pos);
    }

    if(portail_joueur(pos) != moi())
    {
        // On évite de compter un bonus capture pour un portail trop proche car il nous
        // désaventage pour la création de triangle par la suite
        if(distance(lastTakenPortal, pos) > 2) score += POINTS_CAPTURE;
    }
    if(!case_dans_champ(pos))
    {
        // Bonus correspondant à l'aire qu'on peux avoir en plus avec le portail
        std::vector<lien> linkList = liste_liens();
        for(lien link : linkList)
        {
            if(link.joueur_l != moi()) continue;
            if(case_dans_champ(link.extr1) || case_dans_champ(link.extr2)) continue;
            if(lien_existe(pos, link.extr1) || lien_existe(pos, link.extr2)) continue;
            if(liens_bloquants(pos, link.extr1).size() || liens_bloquants(pos, link.extr2).size()) continue;

            score += score_triangle(pos, link.extr1, link.extr2);
        }
    }

    // Pondération en fonction de la distance
    score *= 2*TAILLE_TERRAIN; // On multiplie par la distance maximale avant de diviser pour éviter d'avoir des arrondis à 0
    score /= distance(myPos(), pos)+1;

#ifdef DEBUG_HARD
    std::printf(":%d\n", score);
    std::fflush(stdout);
#endif

    return score;
}

/**
 * Renvoie la plus proche position de target accessible depuis la position actuelle en movePoints
 */
position nearestPosReachable(position start, position target, int movePoints)
{
    int horizDiff = target.x - start.x;
    if(movePoints < std::abs(horizDiff)) return position((horizDiff>0?1:-1)*movePoints+start.x, start.y);
    movePoints -= std::abs(horizDiff);

    int vertDiff = target.y - start.y;
    if(movePoints < std::abs(vertDiff)) return position(target.x, (vertDiff>0?1:-1)*movePoints+start.y);

    return target;
}

position cmpRef; // Je sais c'est moche mais je sais pas comment faire mieux en restant simple
bool areaCmp(const lien& a, const lien& b)
{
    int areaA = score_triangle(a.extr1, a.extr2, cmpRef);
    int areaB = score_triangle(b.extr1, b.extr2, cmpRef);
    return areaA > areaB;
}
bool minDistCmp(const position& a, const position& b)
{
    int distA = distance(a, cmpRef);
    int distB = distance(b, cmpRef);
    return distA < distB;
}

/**
 * Renvoie les meilleurs liens à créer depuis la position pos
 * Elles sont classées dans l'ordre "optimal" de création.
 * Note : un même lien peut être en double. Il suffit d'ignorer sa deuxième occurence.
 */
std::vector<position> computeBestLinks(position pos)
{
    if(case_dans_champ(pos)) return std::vector<position>();

    std::vector<position> linksToCreate;
    std::vector<lien> linkList = liste_liens();
    std::vector<lien> myUsableLinkList;
    for(lien link : linkList)
    {
        if(link.joueur_l != moi()) continue;
        if(lien_existe(pos, link.extr1) || lien_existe(pos, link.extr2)) continue;
        if(liens_bloquants(pos, link.extr1).size() || liens_bloquants(pos, link.extr2).size()) continue;
        myUsableLinkList.push_back(link);
    }


    if(!myUsableLinkList.empty())
    {        
        if(liste_portails().size() <= 100) // Si il y a plus que 100 portails j'utilise une version plus rapide
        {
            cmpRef = pos;
            std::sort(myUsableLinkList.begin(), myUsableLinkList.end(), areaCmp);

            for(uint i = 0 ; i < myUsableLinkList.size() ; i++)
            {
                lien link = myUsableLinkList[i];

                std::vector<champ> nearFields = champs_incidents_segment(link.extr1, link.extr2);
                for(champ c : nearFields)
                {
                    position p = c.som1;
                    if(p == link.extr1 || p == link.extr2) p = c.som2;
                    if(p == link.extr1 || p == link.extr2) p = c.som3;

                    linksToCreate.push_back(p); // Si on ne les ajoute pas maintenant il sera trop tard après
                }

                linksToCreate.push_back(link.extr1);
                linksToCreate.push_back(link.extr2);
            }
        }
        else
        {
            for(lien l : myUsableLinkList)
            {
                linksToCreate.push_back(l.extr1);
                linksToCreate.push_back(l.extr2);
            }
            cmpRef = pos;
            std::sort(linksToCreate.begin(), linksToCreate.end(), minDistCmp);
        }
    }
    else
    {
        std::vector<position> portals = liste_portails();
        for(uint i = 0 ; i < portals.size() ; i++)
        {
            position portal = portals[i];
            if(lien_existe(pos,portal)) continue;
            if(liens_bloquants(pos, portal).size()) continue;
            linksToCreate.push_back(portal);
        }
    }

    return linksToCreate;
}


/**
 * Renvoie l'aire actuelle possédée par un joueur
 */
int currentArea(int player)
{
    int score = 0;
    std::vector<champ> champs = liste_champs();
    for(champ c : champs)
    {
        if(c.joueur_c == player) score += score_triangle(c.som1, c.som2, c.som3);
    }
    return score;
}
