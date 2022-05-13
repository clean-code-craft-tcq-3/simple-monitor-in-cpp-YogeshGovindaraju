#ifndef TEMPERATUREMANAGER
#define TEMPERATUREMANAGER

class TemperatureManager : public BatteryManagementSystem
{
    public:
    bool isWithinLimit(float temperature)
    {
        bool returnStatus = true;
        if(classifyRange(temperature) != NORMAL)
        {
            displayTemperatureAlert();
            returnStatus = false;
        }
        return returnStatus;
    }
    
    Range classifyRange(float temperature)
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