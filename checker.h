#ifndef CHECKER
#define CHECKER

#include <iostream>
#include <assert.h>
#include <vector>
#include <map>

#define MINIMUMTEMPERATURE 0
#define MAXIMUMTEMPERATURE 45
#define MINIMUMSTATEOFCHARGE 20
#define MAXIMUMSTATEOFCHARGE 80
#define MAXIMUMCHARGERATE 0.8f
#define WITHOUTWARNINGLEVEL 0
#define WITHWARNINGLEVEL 1
#define TOLERANCE 0.05f

enum Range {LOW_BREACH, LOW_WARNING, NORMAL, HIGH_WARNING, HIGH_BREACH};
enum Language {ENGLISH, GERMAN};
enum MessageIndex {OUT_OF_RANGE, HIGH_WARNING_RANGE, LOW_WARNING_RANGE};

struct BatterySystem
{
    float temperature;
    float stateOfCharge;
    float chargeRate;
    bool warningLevel;
    Language language;
    void (*displayAlert)(Range, std::vector<std::string>);
};

#include "BatteryManagementSystem.h"
#include "TemperatureManager.h"
#include "StateOfChargeManager.h"
#include "ChargeRateManager.h"

bool isBatteryOk(BatterySystem system);
bool getBatteryStatus(BatteryManagementSystem *batteryStatus, float value, void (*displayAlert)(Range, std::vector<std::string>));
void displayAlert(Range classifiedTemperatureRange, std::vector<std::string> messages);
void displayWarning(Range classifiedTemperatureRange, std::vector<std::string> messages);

#endif