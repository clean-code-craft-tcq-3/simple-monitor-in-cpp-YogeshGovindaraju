#ifndef TEMPERATUREMANAGER
#define TEMPERATUREMANAGER

class TemperatureManager : public BatteryManagementSystem
{
    public:
    bool checkOptimumLimit(float temperature)
    {
        bool returnStatus = true;
        if(temperature < MINIMUMTEMPERATURE || temperature > MAXIMUMTEMPERATURE)
        {
            displayTemperatureAlert();
            returnStatus = false;
        }
        return returnStatus;
    }
    
    Range getRange(float temperature)
    {
        Range rangeStatus = NORMAL;
        if(temperature < MINIMUMTEMPERATURE)
        {
            rangeStatus = LOW;
        }
        else if(temperature > MAXIMUMTEMPERATURE)
        {
            rangeStatus = HIGH;
        }
        return rangeStatus;
    }
    
    void displayTemperatureAlert()
    {
        std::cout << "Temperature out of range!\n";
    }
};

#endif