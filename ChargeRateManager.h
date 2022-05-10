#ifndef CHARGERATEMANAGER
#define CHARGERATEMANAGER

class ChargeRateManager : public BatteryManagementSystem
{
    public:
    bool checkOptimumLimit(float chargeRate)
    {
        bool returnStatus = true;
        if(chargeRate > MAXIMUMCHARGERATE)
        {
            displayChargeRateAlert();
            returnStatus = false;
        }
        return returnStatus;
    }
    
    Range getRange(float chargeRate)
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