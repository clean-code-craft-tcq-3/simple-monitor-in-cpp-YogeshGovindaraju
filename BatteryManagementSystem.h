#ifndef BATTERYMANAGEMENTSYSTEM
#define BATTERYMANAGEMENTSYSTEM

class BatteryManagementSystem
{
    public:
    virtual bool isWithinLimit(float) = 0;
    virtual Range classifyRange(float) = 0;
};

#endif