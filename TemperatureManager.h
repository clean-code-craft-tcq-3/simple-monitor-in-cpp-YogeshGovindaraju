#ifndef TEMPERATUREMANAGER
#define TEMPERATUREMANAGER

class TemperatureManager : public BatteryManagementSystem
{
    std::vector<Range> temperatureRange;
    std::vector<float> temperatureLimit;
    std::vector<std::string> messages;
    typedef void (TemperatureManager::*updateMessages)(void);
    std::map<Language, updateMessages> languageMessagesList;
    
    public:
    TemperatureManager(bool withWarningLevel, Language messageLanguage)
    {
        populateTemperatureValues(withWarningLevel);
        populateMessages(messageLanguage);
    }
    
    void populateTemperatureValues(bool withWarningLevel)
    {
        if(withWarningLevel)
        {
            temperatureRange.push_back(LOW_BREACH);
            temperatureLimit.push_back(MINIMUMTEMPERATURE);
            temperatureRange.push_back(LOW_WARNING);
            temperatureLimit.push_back(MINIMUMTEMPERATURE+(MAXIMUMTEMPERATURE*0.05));
            temperatureRange.push_back(NORMAL);
            temperatureLimit.push_back(MAXIMUMTEMPERATURE-(MAXIMUMTEMPERATURE*0.05));
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
    
    void populateMessages(Language messageLanguage)
    {
        languageMessagesList.insert(std::pair<Language, updateMessages>(ENGLISH, &TemperatureManager::populateEnglishMessages));
        languageMessagesList.insert(std::pair<Language, updateMessages>(GERMAN, &TemperatureManager::populateGermanMessages));
        std::map<Language, updateMessages>::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
        assert(messageIterator != languageMessagesList.end());
        (this->*messageIterator->second)();
    }
    
    void populateEnglishMessages()
    {
        messages.push_back("Temperature out of range!");
        messages.push_back("Warning: Approaching High Temperature Range");
        messages.push_back("Warning: Approaching Low Temperature Range");
    }
    
    void populateGermanMessages()
    {
        messages.push_back("Temperatur außerhalb des Bereichs!");
        messages.push_back("Warnung: Annäherung an den hohen Temperaturbereich");
        messages.push_back("Warnung: Annäherung an den niedrigen Temperaturbereich");
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