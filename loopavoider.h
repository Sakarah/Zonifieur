#ifndef LOOPAVOIDER_H
#define LOOPAVOIDER_H

#include "prologin.hh"

struct StateData
{
    StateData() = default;
    StateData(position o, position myp, position ap, int s){ objective=o; myPos=myp; advPos=ap; score=s; }
    position objective;
    position myPos;
    position advPos;
    int score;
};

const int MAX_LOOP_SIZE = 10;
class LoopAvoider
{
public:
    static LoopAvoider& instance();
    LoopAvoider();
    void setNextObjective(position objective);
    void posReached(position myPos, position advPos, int score);
    bool checkLoop(position p);
private:
    position objective;
    int lastPos;
    StateData oldPos[MAX_LOOP_SIZE];
};

#endif // LOOPAVOIDER_H
