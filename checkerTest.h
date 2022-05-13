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
    assert(batteryTemperatureStatus->isWithinLimit(-1) == false);
    assert(batteryTemperatureStatus->classifyRange(-1) == LOW);
    assert(batteryTemperatureStatus->isWithinLimit(30) == true);
    assert(batteryTemperatureStatus->classifyRange(30) == NORMAL);
    assert(batteryTemperatureStatus->isWithinLimit(46) == false);
    assert(batteryTemperatureStatus->classifyRange(46) == HIGH);
}

void testBatteryStateOfCharge()
{
    StateOfChargeManager stateOfChargeManager;
    BatteryManagementSystem *batteryStateOfChargeStatus = &stateOfChargeManager;
    assert(batteryStateOfChargeStatus->isWithinLimit(19) == false);
    assert(batteryStateOfChargeStatus->classifyRange(19) == LOW);
    assert(batteryStateOfChargeStatus->isWithinLimit(50) == true);
    assert(batteryStateOfChargeStatus->classifyRange(50) == NORMAL);
    assert(batteryStateOfChargeStatus->isWithinLimit(81) == false);
    assert(batteryStateOfChargeStatus->classifyRange(81) == HIGH);
}

void testBatteryChargeRate()
{
    ChargeRateManager chargeRateManager;
    BatteryManagementSystem *batteryChargeRateStatus = &chargeRateManager;
    assert(batteryChargeRateStatus->isWithinLimit(0.5) == true);
    assert(batteryChargeRateStatus->classifyRange(0.5) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.81) == false);
    assert(batteryChargeRateStatus->classifyRange(0.81) == HIGH);
}

#endif