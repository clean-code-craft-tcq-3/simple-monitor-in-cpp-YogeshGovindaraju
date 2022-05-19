#ifndef LANGUAGEMESSAGE
#define LANGUAGEMESSAGE

typedef void (*UpdateMessages)(std::vector<std::string>&);
typedef std::map<Language, UpdateMessages> LanguageMessagesList;

struct LanguageMessage
{
    LanguageMessage(LanguageMessagesList::const_iterator& messageIterator)
     : language(messageIterator->first), populateLanguageMessages(messageIterator->second) {}
    Language language;
    UpdateMessages populateLanguageMessages;
};

void populateTemperatureEnglishMessages(std::vector<std::string> &messages)
{
    messages.push_back("Temperature out of range!");
    messages.push_back("Warning: Approaching High Temperature Range");
    messages.push_back("Warning: Approaching Low Temperature Range");
}

void populateTemperatureGermanMessages(std::vector<std::string> &messages)
{
    messages.push_back("Temperatur außerhalb des Bereichs!");
    messages.push_back("Warnung: Annäherung an den hohen Temperaturbereich");
    messages.push_back("Warnung: Annäherung an den niedrigen Temperaturbereich");
}

void populateTemperatureMessages(Language messageLanguage, std::vector<std::string> &messages)
{
    LanguageMessagesList languageMessagesList;
    languageMessagesList.insert({ENGLISH, populateTemperatureEnglishMessages});
    languageMessagesList.insert({GERMAN, populateTemperatureGermanMessages});
    LanguageMessagesList::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
    assert(messageIterator != languageMessagesList.end());
    LanguageMessage(messageIterator).populateLanguageMessages(messages);
}

void populateStateOfChargeEnglishMessages(std::vector<std::string> &messages)
{
    messages.push_back("State of Charge out of range!");
    messages.push_back("Warning: Approaching charge-peak");
    messages.push_back("Warning: Approaching discharge");
}

void populateStateOfChargeGermanMessages(std::vector<std::string> &messages)
{
    messages.push_back("Ladezustand außerhalb des Bereichs!");
    messages.push_back("Warnung: Ladespitze nähert sich");
    messages.push_back("Warnung: Naht Entladung");
}

void populateStateOfChargeMessages(Language messageLanguage, std::vector<std::string> &messages)
{
    LanguageMessagesList languageMessagesList;
    languageMessagesList.insert({ENGLISH, populateStateOfChargeEnglishMessages});
    languageMessagesList.insert({GERMAN, populateStateOfChargeGermanMessages});
    LanguageMessagesList::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
    assert(messageIterator != languageMessagesList.end());
    LanguageMessage(messageIterator).populateLanguageMessages(messages);
}

void populateChargeRateEnglishMessages(std::vector<std::string> &messages)
{
    messages.push_back("Charge Rate out of range!");
    messages.push_back("Warning: Approaching High Charge Rate");
}

void populateChargeRateGermanMessages(std::vector<std::string> &messages)
{
    messages.push_back("Laderate außerhalb des Bereichs!");
    messages.push_back("Warnung: Annäherung an hohe Laderate");
}

void populateChargeRateMessages(Language messageLanguage, std::vector<std::string> &messages)
{
    LanguageMessagesList languageMessagesList;
    languageMessagesList.insert({ENGLISH, populateChargeRateEnglishMessages});
    languageMessagesList.insert({GERMAN, populateChargeRateGermanMessages});
    LanguageMessagesList::const_iterator messageIterator = languageMessagesList.find(messageLanguage);
    assert(messageIterator != languageMessagesList.end());
    LanguageMessage(messageIterator).populateLanguageMessages(messages);
}

#endif