#ifndef CHECKERTEST
#define CHECKERTEST

void testBatteryStatus()
{
    assert(isBatteryOk(25, 70, 0.7) == true);
    assert(isBatteryOk(-10, 85, 0) == false);
    assert(isBatteryOk(50, 90, 0) == false);
    assert(isBatteryOk(20, 10, 0) == false);
    assert(isBatteryOk(30, 85, 0) == false);
    assert(isBatteryOk(45, 80, 0.8) == true);
    assert(isBatteryOk(0, 20, 1) == false);
}

void testBatteryTemperature()
{
    TemperatureManager temperatureManager;
    BatteryManagementSystem *batteryTemperatureStatus = &temperatureManager;
    assert(batteryTemperatureStatus->checkOptimumLimit(-1) == false);
    assert(batteryTemperatureStatus->getRange(-1) == LOW);
    assert(batteryTemperatureStatus->checkOptimumLimit(30) == true);
    assert(batteryTemperatureStatus->getRange(30) == NORMAL);
    assert(batteryTemperatureStatus->checkOptimumLimit(46) == false);
    assert(batteryTemperatureStatus->getRange(46) == HIGH);
}

void testBatteryStateOfCharge()
{
    StateOfChargeManager stateOfChargeManager;
    BatteryManagementSystem *batteryStateOfChargeStatus = &stateOfChargeManager;
    assert(batteryStateOfChargeStatus->checkOptimumLimit(19) == false);
    assert(batteryStateOfChargeStatus->getRange(19) == LOW);
    assert(batteryStateOfChargeStatus->checkOptimumLimit(50) == true);
    assert(batteryStateOfChargeStatus->getRange(50) == NORMAL);
    assert(batteryStateOfChargeStatus->checkOptimumLimit(81) == false);
    assert(batteryStateOfChargeStatus->getRange(81) == HIGH);
}

void testBatteryChargeRate()
{
    ChargeRateManager chargeRateManager;
    BatteryManagementSystem *batteryChargeRateStatus = &chargeRateManager;
    assert(batteryChargeRateStatus->checkOptimumLimit(0.5) == true);
    assert(batteryChargeRateStatus->getRange(0.5) == NORMAL);
    assert(batteryChargeRateStatus->checkOptimumLimit(0.81) == false);
    assert(batteryChargeRateStatus->getRange(0.81) == HIGH);
}

#endif