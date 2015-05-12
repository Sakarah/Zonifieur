#include "actions.h"
#include "loopavoider.h"

#ifdef DEBUG
#include <cstdio>
#endif

position lastTakenPortal = INVALID_POS;

position pos = INVALID_POS;
position advPos = INVALID_POS;
int area = 0;

/**
 * Fonction de base qui correspond à toute la stratégie de l'IA
 */
void strategy()
{
    area -= currentArea(adversaire());
    LoopAvoider::instance().posReached(pos, advPos, area);

    pos = myPos();
    advPos = position_agent(adversaire());

    while(true)
    {
        if(!goToBestPortal()) return;
        if(!takePortal()) return;
        if(!fortifyPortal(2)) return;
        if(!createLinks()) return;

        // Ceci permet de conserver mieux ses positions. Si on y arrive pas tant pis on passe à la suite
        fortifyPortal(6);
    }

    area = currentArea(moi());
}

/**
 * Cette fonction envoie le joueur sur le "meilleur" portail trouvé pour continuer
 */
bool goToBestPortal()
{
#ifdef DEBUG
    std::printf("--New move (%d,%d)--\n", myPos().x, myPos().y);
    std::fflush(stdout);
#endif

    position portal;
    if(portalValue(myPos()) && !LoopAvoider::instance().checkLoop(myPos())) portal = myPos();
    else portal = bestPortal();

    position objective = portal;
    bool reached = true;

    if(myPos() != portal)
    {
        while(points_deplacement() < distance(portal, myPos()))
        {
            if(points_action() < COUT_TURBO) break;
            utiliser_turbo();
        }

        if(deplacer(portal) != OK)
        {
            objective = nearestPosReachable(myPos(), portal, points_deplacement());
            deplacer(objective);
            reached = false;
        }
    }

    LoopAvoider::instance().setNextObjective(objective);
    return reached;
}

/**
 * Cette fonction s'empare du portail sur lequel on est
 */
bool takePortal()
{
    if(portail_joueur(myPos()) == adversaire())
    {
        if(neutraliser() == PA_INSUFFISANTS) return false;
    }
    erreur e = capturer();
    if(e == PA_INSUFFISANTS) return false;
    else if(e == OK) lastTakenPortal = myPos();

    return true;
}

/**
 * Cette fonction fortifie le portail actuel en y installant des bouclier jusqu'à ce qu'il y
 * en ait objective
 */
bool fortifyPortal(int objective)
{
    while(portail_boucliers(myPos()) < objective)
    {
        if(ajouter_bouclier() != OK) return false;
    }
    return true;
}

/**
 * Cette fonction créé des liens à partir du portail actuel
 */
bool createLinks()
{
#ifdef DEBUG
    std::printf("--New links (%d,%d)--\n", myPos().x, myPos().y);
    std::fflush(stdout);
#endif

    std::vector<position> linksToCreate = computeBestLinks(myPos());
    for(uint i = 0 ; i < linksToCreate.size() ; i++)
    {
#ifdef DEBUG
        std::printf("Link to (%d,%d)\n", linksToCreate[i].x, linksToCreate[i].y);
        std::fflush(stdout);
#endif
        erreur e = lier(linksToCreate[i]);
        if(e == PA_INSUFFISANTS) return false;
    }
    return true;
}
