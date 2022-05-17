#ifndef BATTERYMANAGEMENTSYSTEM
#define BATTERYMANAGEMENTSYSTEM

class BatteryManagementSystem
{
    public:
    virtual bool isWithinLimit(float, void (*displayAlert)(Range,std::vector<std::string>)) = 0;
    virtual Range classifyRange(float) = 0;
};

#endif