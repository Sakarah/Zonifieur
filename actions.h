#ifndef ACTIONS_H
#define ACTIONS_H

#include "utils.h"

extern position lastTakenPortal; // Position du dernier portail pris

void strategy();
bool goToBestPortal();
bool takePortal();
bool fortifyPortal(int objective);
bool createLinks();

#endif // ACTIONS_H

