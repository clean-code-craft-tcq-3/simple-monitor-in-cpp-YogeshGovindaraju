#ifndef BATTERYMANAGEMENTSYSTEM
#define BATTERYMANAGEMENTSYSTEM

class BatteryManagementSystem
{
    public:
    virtual bool checkOptimumLimit(float) = 0;
    virtual Range getRange(float) = 0;
};

#endif