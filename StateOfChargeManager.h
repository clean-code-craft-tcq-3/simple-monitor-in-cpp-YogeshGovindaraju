#ifndef STATEOFCHARGEMANAGER
#define STATEOFCHARGEMANAGER

class StateOfChargeManager : public BatteryManagementSystem
{
    std::vector<Range> StateOfChargeRange;
    std::vector<float> StateOfChargeLimit;
    std::vector<std::string> messages;
    typedef void (StateOfChargeManager::*updateMessages)(void);
    std::map<Language, updateMessages> languageMessagesList;
    
    public:
    StateOfChargeManager(bool withWarningLevel, Language messageLanguage)
    {
        populateStateOfChargeValues(withWarningLevel);
        populateMessages(messageLanguage);
    }
    
    void populateStateOfChargeValues(bool withWarningLevel)
    {
        if(withWarningLevel)
        {
            StateOfChargeRange.push_back(LOW_BREACH);
            StateOfChargeLimit.push_back(MINIMUMSTATEOFCHARGE);
            StateOfChargeRange.push_back(LOW_WARNING);
            StateOfChargeLimit.push_back(MINIMUMSTATEOFCHARGE+(MAXIMUMSTATEOFCHARGE*TOLERANCE));
            StateOfChargeRange.push_back(NORMAL);
            StateOfChargeLimit.push_back(MAXIMUMSTATEOFCHARGE-(MAXIMUMSTATEOFCHARGE*TOLERANCE));
            StateOfChargeRange.push_back(HIGH_WARNING);
            StateOfChargeLimit.push_back(MAXIMUMSTATEOFCHARGE);
            StateOfChargeRange.push_back(HIGH_BREACH);
        }
        else
        {
            StateOfChargeRange.push_back(LOW_BREACH);
            StateOfChargeLimit.push_back(MINIMUMSTATEOFCHARGE);
            StateOfChargeRange.push_back(NORMAL);
            StateOfChargeLimit.push_back(MAXIMUMSTATEOFCHARGE);
            StateOfChargeRange.push_back(HIGH_BREACH);
        }
    }
    
    void populateMessages(Language messageLanguage)
    {
        languageMessagesList.insert(std::pair<Language, updateMessages>(ENGLISH, &StateOfChargeManager::populateEnglishMessages));
        languageMessagesList.insert(std::pair<Language, updateMessages>(GERMAN, &StateOfChargeManager::populateGermanMessages));
        std::map<Language, updateMessages>::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
        assert(messageIterator != languageMessagesList.end());
        (this->*messageIterator->second)();
    }
    
    void populateEnglishMessages()
    {
        messages.push_back("State of Charge out of range!");
        messages.push_back("Warning: Approaching charge-peak");
        messages.push_back("Warning: Approaching discharge");
    }
    
    void populateGermanMessages()
    {
        messages.push_back("Ladezustand außerhalb des Bereichs!");
        messages.push_back("Warnung: Ladespitze nähert sich");
        messages.push_back("Warnung: Naht Entladung");
    }
    
    bool isWithinLimit(float stateOfCharge, void (*displayStateOfChargeAlert)(Range,std::vector<std::string>))
    {
        bool returnStatus = true;
        Range classifiedStateOfChargeRange = classifyRange(stateOfCharge);
        if((classifiedStateOfChargeRange == LOW_BREACH) || (classifiedStateOfChargeRange == HIGH_BREACH))
        {
            returnStatus = false;
        }
        displayStateOfChargeAlert(classifiedStateOfChargeRange, messages);
        return returnStatus;
    }
    
    Range classifyRange(float stateOfCharge)
    {
        unsigned int i = 0;
        for(i=0; i<StateOfChargeLimit.size(); i++)
        {
            if(stateOfCharge <= StateOfChargeLimit.at(i))
            {
                return StateOfChargeRange.at(i);
            }
        }
        return StateOfChargeRange.at(i);
    }
};

#endif