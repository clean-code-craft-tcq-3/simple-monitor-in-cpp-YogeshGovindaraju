#ifndef CHARGERATEMANAGER
#define CHARGERATEMANAGER

class ChargeRateManager : public BatteryManagementSystem
{
    std::vector<Range> ChargeRateRange;
    std::vector<float> ChargeRateLimit;
    std::vector<std::string> messages;
    
    public:
    ChargeRateManager(bool withWarningLevel, Language messageLanguage)
    {
        populateChargeRateValues(withWarningLevel);
        populateChargeRateMessages(messageLanguage, messages);
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