#ifndef UTILS_H
#define UTILS_H

#include "prologin.hh"

typedef unsigned int uint;
const position INVALID_POS = position(-100,-100);

inline position myPos() { return position_agent(moi()); } /**< Renvoie ma position */
inline int nbTurnLeft() { return NB_TOURS-tour_actuel(); } /**< Renvoie le nombre de tours restants */

position bestPortal();
int portalValue(position pos);
position nearestPosReachable(position start, position target, int movePoints);
std::vector<position> computeBestLinks(position pos);
int currentArea(int player);

#endif // UTILS_H

