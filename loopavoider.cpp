#include "loopavoider.h"
#include "utils.h"

#ifdef DEBUG
#include <cstdio>
#endif

/**
 * Renvoie l'instance du LoopAvoider
 */
LoopAvoider& LoopAvoider::instance()
{
    static LoopAvoider instance;
    return instance;
}

/**
 * Initialise le LoopAvoider
 */
LoopAvoider::LoopAvoider()
{
    objective = INVALID_POS;
    lastPos = -1;
    for(int i = 0 ; i < MAX_LOOP_SIZE ; i++)
    {
        oldPos[i] = StateData(INVALID_POS, INVALID_POS, INVALID_POS, 0);
    }
}

/**
 * Définit l'objectif à la position donnée
 */
void LoopAvoider::setNextObjective(position o)
{
    if(objective == INVALID_POS) objective = o;
}

/**
 * Prévient le LoopAvoider que la position a été atteinte avec un score spécifié.
 */
void LoopAvoider::posReached(position myPos, position advPos, int score)
{
#ifdef DEBUG
    std::printf("LoopNode me(%d,%d) - adv(%d,%d) - obj(%d,%d) - score:%d\n",
                myPos.x, myPos.y, advPos.x, advPos.y, objective.x, objective.y, score);
    std::fflush(stdout);
#endif

    lastPos++;
    lastPos %= MAX_LOOP_SIZE;

    oldPos[lastPos] = StateData(objective, myPos, advPos, score);

    objective = INVALID_POS;
}

/**
 * Vérifie si il existe une boucle défavorable dans la situation actuelle si on va vers p.
 */
bool LoopAvoider::checkLoop(position p)
{
#ifdef DEBUG_HARD
    std::printf("- Check loop (%d,%d) -\n", p.x, p.y);
    std::fflush(stdout);
#endif
    int diffScore = 0;
    for(int i = 0 ; i < MAX_LOOP_SIZE ; i++)
    {
        int index = (lastPos-i+MAX_LOOP_SIZE) % MAX_LOOP_SIZE;

        position obj = oldPos[index].objective;
        position myPosition = oldPos[index].myPos;
        position advPos = oldPos[index].advPos;
        diffScore += oldPos[index].score;

#ifdef DEBUG_HARD
        std::printf("LoopNode[%d] me(%d,%d) - adv(%d,%d) - obj(%d,%d) - score:%d\n", index,
                    myPosition.x, myPosition.y, advPos.x, advPos.y, obj.x, obj.y, diffScore);
        std::fflush(stdout);
#endif

        if(obj == p && myPosition == myPos() && advPos == position_agent(adversaire()))
        {
            int loopScore = diffScore*nbTurnLeft() + score(moi()) - score(adversaire());
#ifdef DEBUG
            std::printf("LOOP DETECTED (Score : %d) !\n", loopScore);
            std::fflush(stdout);
#endif
            if(loopScore < 0)
            {
                return true;
            }
        }
    }
    return false;
}
