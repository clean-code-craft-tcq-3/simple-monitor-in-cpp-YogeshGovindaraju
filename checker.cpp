#include "checker.h"
#include "checkerTest.h"

bool isBatteryOk(BatterySystem system)
{
    TemperatureManager temperatureManager(system.warningLevel, system.language);
    StateOfChargeManager stateOfChargeManager(system.warningLevel, system.language);
    ChargeRateManager chargeRateManager(system.warningLevel, system.language);
    bool temperatureStatus = getBatteryStatus(&temperatureManager, system.temperature, system.displayAlert);
    bool stateOfChargeStatus = getBatteryStatus(&stateOfChargeManager, system.stateOfCharge, system.displayAlert);
    bool chargeRateStatus = getBatteryStatus(&chargeRateManager, system.chargeRate, system.displayAlert);
    return (temperatureStatus && stateOfChargeStatus && chargeRateStatus);
}

bool getBatteryStatus(BatteryManagementSystem *batteryStatus, float value, void (*displayAlert)(Range, std::vector<std::string>))
{
    return batteryStatus->isWithinLimit(value, displayAlert);
}

void displayAlert(Range classifiedRange, std::vector<std::string> messages)
{
    if((classifiedRange == LOW_BREACH) || (classifiedRange == HIGH_BREACH))
    {
        std::cout << messages.at(OUT_OF_RANGE) << std::endl;
    }
    else
    {
        displayWarning(classifiedRange, messages);
    }
}

void displayWarning(Range classifiedRange, std::vector<std::string> messages)
{
    if(classifiedRange == LOW_WARNING)
    {
        std::cout << messages.at(LOW_WARNING_RANGE) << std::endl;
    }
    else if(classifiedRange == HIGH_WARNING)
    {
        std::cout << messages.at(HIGH_WARNING_RANGE) << std::endl;
    }
}

int main()
{
    testBatteryStatus();
    testBatteryTemperature();
    testBatteryStateOfCharge();
    testBatteryChargeRate();
    return 0;
}