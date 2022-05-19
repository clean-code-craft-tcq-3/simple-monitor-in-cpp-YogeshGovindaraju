#ifndef TEMPERATUREMANAGER
#define TEMPERATUREMANAGER

class TemperatureManager : public BatteryManagementSystem
{
    std::vector<Range> temperatureRange;
    std::vector<float> temperatureLimit;
    std::vector<std::string> messages;
    
    public:
    TemperatureManager(bool withWarningLevel, Language messageLanguage)
    {
        populateTemperatureValues(withWarningLevel);
        populateTemperatureMessages(messageLanguage, messages);
    }
    
    void populateTemperatureValues(bool withWarningLevel)
    {
        if(withWarningLevel)
        {
            temperatureRange.push_back(LOW_BREACH);
            temperatureLimit.push_back(MINIMUMTEMPERATURE);
            temperatureRange.push_back(LOW_WARNING);
            temperatureLimit.push_back(MINIMUMTEMPERATURE+(MAXIMUMTEMPERATURE*TOLERANCE));
            temperatureRange.push_back(NORMAL);
            temperatureLimit.push_back(MAXIMUMTEMPERATURE-(MAXIMUMTEMPERATURE*TOLERANCE));
            temperatureRange.push_back(HIGH_WARNING);
            temperatureLimit.push_back(MAXIMUMTEMPERATURE);
            temperatureRange.push_back(HIGH_BREACH);
        }
        else
        {
            temperatureRange.push_back(LOW_BREACH);
            temperatureLimit.push_back(MINIMUMTEMPERATURE);
            temperatureRange.push_back(NORMAL);
            temperatureLimit.push_back(MAXIMUMTEMPERATURE);
            temperatureRange.push_back(HIGH_BREACH);
        }
    }
    
    bool isWithinLimit(float temperature, void (*displayTemperatureAlert)(Range,std::vector<std::string>))
    {
        bool returnStatus = true;
        Range classifiedTemperatureRange = classifyRange(temperature);
        if((classifiedTemperatureRange == LOW_BREACH) || (classifiedTemperatureRange == HIGH_BREACH))
        {
            returnStatus = false;
        }
        displayTemperatureAlert(classifiedTemperatureRange, messages);
        return returnStatus;
    }
    
    Range classifyRange(float temperature)
    {
        unsigned int i = 0;
        for(i=0; i<temperatureLimit.size(); i++)
        {
            if(temperature <= temperatureLimit.at(i))
            {
                return temperatureRange.at(i);
            }
        }
        return temperatureRange.at(i);
    }
};

#endif