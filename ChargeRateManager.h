#ifndef CHARGERATEMANAGER
#define CHARGERATEMANAGER

class ChargeRateManager : public BatteryManagementSystem
{
    public:
    bool isWithinLimit(float chargeRate)
    {
        bool returnStatus = true;
        if(classifyRange(chargeRate) != NORMAL)
        {
            displayChargeRateAlert();
            returnStatus = false;
        }
        return returnStatus;
    }
    
    Range classifyRange(float chargeRate)
    {
        Range rangeStatus = NORMAL;
        if(chargeRate > MAXIMUMCHARGERATE)
        {
            rangeStatus = HIGH;
        }
        return rangeStatus;
    }
    
    void displayChargeRateAlert()
    {
        std::cout << "Charge Rate out of range!\n";
    }
};

#endif