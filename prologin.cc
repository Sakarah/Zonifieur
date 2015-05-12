#include "prologin.hh"
#include "actions.h"
#include "loopavoider.h"

#ifdef DEBUG
#include <cstdio>
#include <ctime>
#include <chrono>
#endif

/****************************************************************************************
 * ### ZONIFIEUR ###
 *
 * Cette IA tente à chaque tour de se déplacer vers un portail estimé optimal
 * de le capturer et de créer une bonne disposition de lien à partir de là
 * Elle essaye d'éviter au possible les boucles perdantes via LoopAvoider
 *
 * Pour déterminer si un portail est intéressant on lui calcule une valeur heuristique
 * en fonction de ce qu'on pourra faire perdre ou qu'on pourra gagner avec.
 *
 * On place systématiquement 2 boucliers après capture qu'on renforce si on a des PA en
 * fin d'action.
 *
 * Pour créer les liens on s'arrange pour essayer d'avoir des patterns qui maximisent
 * la réutilisation d'une même aire.
 ***************************************************************************************/

/**
 * Fonction appelée au début de la partie.
 */
void partie_init()
{
    // Rien à initialiser
}

/**
 * Fonction appelée à chaque tour
 */
void jouer_tour()
{
#ifdef DEBUG
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    std::printf("##### DEBUT DU TOUR #%d (Player %d) #####\n", tour_actuel(), moi());
    std::printf("me(%d,%d) - adv(%d,%d)\n", myPos().x, myPos().y,
                position_agent(adversaire()).x, position_agent(adversaire()).y);
    std::fflush(stdout);
#endif

    strategy();

#ifdef DEBUG
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::printf("##### FIN DU TOUR (PA:%d/PM:%d) - %fsec #####\n", points_action(),
                points_deplacement(), elapsed_seconds.count());
    std::fflush(stdout);
#endif
}

/**
 * Fonction appelée à la fin de la partie.
 */
void partie_fin()
{
    // Rien à désallouer
}

