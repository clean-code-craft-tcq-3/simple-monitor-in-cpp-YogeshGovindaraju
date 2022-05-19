#include "checker.h"
#include "checkerTest.h"

bool isBatteryStatusWithinLimit(BatteryManagementSystem *batteryStatus, float value, void (*displayAlert)(Range, std::vector<std::string>))
{
    return batteryStatus->isWithinLimit(value, displayAlert);
}

bool isBatteryOk(BatterySystem system)
{
    TemperatureManager temperatureManager(system.warningLevel, system.language);
    StateOfChargeManager stateOfChargeManager(system.warningLevel, system.language);
    ChargeRateManager chargeRateManager(system.warningLevel, system.language);
    bool temperatureStatus = isBatteryStatusWithinLimit(&temperatureManager, system.temperature, system.displayAlert);
    bool stateOfChargeStatus = isBatteryStatusWithinLimit(&stateOfChargeManager, system.stateOfCharge, system.displayAlert);
    bool chargeRateStatus = isBatteryStatusWithinLimit(&chargeRateManager, system.chargeRate, system.displayAlert);
    return (temperatureStatus && stateOfChargeStatus && chargeRateStatus);
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

int main()
{
    testBatteryStatus();
    testBatteryTemperature();
    testBatteryStateOfCharge();
    testBatteryChargeRate();
    return 0;
}