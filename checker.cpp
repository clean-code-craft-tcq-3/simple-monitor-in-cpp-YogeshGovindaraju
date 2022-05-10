#include "checker.h"
#include "checkerTest.h"

bool isBatteryOk(float temperature, float stateOfCharge, float chargeRate)
{
    BatteryManagementSystem *batteryTemperatureStatus, *batteryStateOfChargeStatus, *batteryChargeRateStatus;
    TemperatureManager temperatureManager;
    StateOfChargeManager stateOfChargeManager;
    ChargeRateManager chargeRateManager;
    batteryTemperatureStatus = &temperatureManager;
    bool temperatureStatus = batteryTemperatureStatus->checkOptimumLimit(temperature);
    batteryStateOfChargeStatus = &stateOfChargeManager;
    bool stateOfChargeStatus = batteryStateOfChargeStatus->checkOptimumLimit(stateOfCharge);
    batteryChargeRateStatus = &chargeRateManager;
    bool chargeRateStatus = batteryChargeRateStatus->checkOptimumLimit(chargeRate);
    return (temperatureStatus && stateOfChargeStatus && chargeRateStatus);
}

int main()
{
    testBatteryStatus();
    testBatteryTemperature();
    testBatteryStateOfCharge();
    testBatteryChargeRate();
    return 0;
}
