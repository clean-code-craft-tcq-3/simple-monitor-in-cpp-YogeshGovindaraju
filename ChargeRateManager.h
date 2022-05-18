#ifndef CHARGERATEMANAGER
#define CHARGERATEMANAGER

class ChargeRateManager : public BatteryManagementSystem
{
    std::vector<Range> ChargeRateRange;
    std::vector<float> ChargeRateLimit;
    std::vector<std::string> messages;
    typedef void (ChargeRateManager::*updateMessages)(void);
    std::map<Language, updateMessages> languageMessagesList;
    
    public:
    ChargeRateManager(bool withWarningLevel, Language messageLanguage)
    {
        populateChargeRateValues(withWarningLevel);
        populateMessages(messageLanguage);
    }
    
    void populateChargeRateValues(bool withWarningLevel)
    {
        if(withWarningLevel)
        {
            ChargeRateRange.push_back(NORMAL);
            ChargeRateLimit.push_back(MAXIMUMCHARGERATE-(MAXIMUMCHARGERATE*TOLERANCE));
            ChargeRateRange.push_back(HIGH_WARNING);
            ChargeRateLimit.push_back(MAXIMUMCHARGERATE);
            ChargeRateRange.push_back(HIGH_BREACH);
        }
        else
        {
            ChargeRateRange.push_back(NORMAL);
            ChargeRateLimit.push_back(MAXIMUMCHARGERATE);
            ChargeRateRange.push_back(HIGH_BREACH);
        }
    }
    
    void populateMessages(Language messageLanguage)
    {
        languageMessagesList.insert(std::pair<Language, updateMessages>(ENGLISH, &ChargeRateManager::populateEnglishMessages));
        languageMessagesList.insert(std::pair<Language, updateMessages>(GERMAN, &ChargeRateManager::populateGermanMessages));
        std::map<Language, updateMessages>::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
        assert(messageIterator != languageMessagesList.end());
        (this->*messageIterator->second)();
    }
    
    void populateEnglishMessages()
    {
        messages.push_back("Charge Rate out of range!");
        messages.push_back("Warning: Approaching High Charge Rate");
    }
    
    void populateGermanMessages()
    {
        messages.push_back("Laderate außerhalb des Bereichs!");
        messages.push_back("Warnung: Annäherung an hohe Laderate");
    }
    
    bool isWithinLimit(float chargeRate, void (*displayChargeRateAlert)(Range,std::vector<std::string>))
    {
        bool returnStatus = true;
        Range classifiedChargeRateRange = classifyRange(chargeRate);
        if(classifiedChargeRateRange == HIGH_BREACH)
        {
            returnStatus = false;
        }
        displayChargeRateAlert(classifiedChargeRateRange, messages);
        return returnStatus;
    }
    
    Range classifyRange(float chargeRate)
    {
        unsigned int i = 0;
        for(i=0; i<ChargeRateLimit.size(); i++)
        {
            if(chargeRate <= ChargeRateLimit.at(i))
            {
                return ChargeRateRange.at(i);
            }
        }
        return ChargeRateRange.at(i);
    }
};

#endif