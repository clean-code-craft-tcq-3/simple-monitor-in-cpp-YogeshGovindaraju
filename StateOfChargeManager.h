#ifndef STATEOFCHARGEMANAGER
#define STATEOFCHARGEMANAGER

class StateOfChargeManager : public BatteryManagementSystem
{
    public:
    bool checkOptimumLimit(float stateOfCharge)
    {
        bool returnStatus = true;
        if(stateOfCharge < MINIMUMSTATEOFCHARGE || stateOfCharge > MAXIMUMSTATEOFCHARGE)
        {
            displayStateOfChargeAlert();
            returnStatus = false;
        }
        return returnStatus;
    }
    
    Range getRange(float stateOfCharge)
    {
        Range rangeStatus = NORMAL;
        if(stateOfCharge < MINIMUMSTATEOFCHARGE)
        {
            rangeStatus = LOW;
        }
        else if(stateOfCharge > MAXIMUMSTATEOFCHARGE)
        {
            rangeStatus = HIGH;
        }
        return rangeStatus;
    }
    
    void displayStateOfChargeAlert()
    {
        std::cout << "State of Charge out of range!\n";
    }
};

#endif