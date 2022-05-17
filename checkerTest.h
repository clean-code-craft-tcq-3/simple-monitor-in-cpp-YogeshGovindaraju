#ifndef CHECKERTEST
#define CHECKERTEST

void testBatteryStatus()
{
    assert(isBatteryOk({25, 70, 0.7, WITHOUTWARNINGLEVEL, ENGLISH, displayAlert}) == true);
    assert(isBatteryOk({-10, 85, 0, WITHWARNINGLEVEL, GERMAN, displayAlert}) == false);
    assert(isBatteryOk({50, 21, 0.5, WITHOUTWARNINGLEVEL, ENGLISH, displayAlert}) == false);
    assert(isBatteryOk({1, 78, 0.79, WITHWARNINGLEVEL, GERMAN, displayAlert}) == true);
    assert(isBatteryOk({44, 30, 1, WITHOUTWARNINGLEVEL, ENGLISH, displayAlert}) == false);
    assert(isBatteryOk({45, 80, 0.01, WITHWARNINGLEVEL, GERMAN, displayAlert}) == true);
    assert(isBatteryOk({0, 20, 0, WITHOUTWARNINGLEVEL, ENGLISH, displayAlert}) == false);
    assert(isBatteryOk({45, 80, 0.8, WITHWARNINGLEVEL, GERMAN, displayAlert}) == true);
}

void testBatteryTemperature()
{
    TemperatureManager temperatureWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    BatteryManagementSystem *batteryTemperatureStatus = &temperatureWithoutWarning;
    assert(batteryTemperatureStatus->isWithinLimit(-1, displayAlert) == false);
    assert(batteryTemperatureStatus->classifyRange(-1) == LOW_BREACH);
    assert(batteryTemperatureStatus->isWithinLimit(1, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(1) == NORMAL);
    assert(batteryTemperatureStatus->isWithinLimit(30, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(30) == NORMAL);
    assert(batteryTemperatureStatus->isWithinLimit(44, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(44) == NORMAL);
    assert(batteryTemperatureStatus->isWithinLimit(46, displayAlert) == false);
    assert(batteryTemperatureStatus->classifyRange(46) == HIGH_BREACH);
    
    TemperatureManager temperatureWithWarning(WITHWARNINGLEVEL, GERMAN);
    batteryTemperatureStatus = &temperatureWithWarning;
    assert(batteryTemperatureStatus->isWithinLimit(-1, displayAlert) == false);
    assert(batteryTemperatureStatus->classifyRange(-1) == LOW_BREACH);
    assert(batteryTemperatureStatus->isWithinLimit(1, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(1) == LOW_WARNING);
    assert(batteryTemperatureStatus->isWithinLimit(30, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(30) == NORMAL);
    assert(batteryTemperatureStatus->isWithinLimit(44, displayAlert) == true);
    assert(batteryTemperatureStatus->classifyRange(44) == HIGH_WARNING);
    assert(batteryTemperatureStatus->isWithinLimit(46, displayAlert) == false);
    assert(batteryTemperatureStatus->classifyRange(46) == HIGH_BREACH);
}

void testBatteryStateOfCharge()
{
    StateOfChargeManager stateOfChargeWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    BatteryManagementSystem *batteryStateOfChargeStatus = &stateOfChargeWithoutWarning;
    assert(batteryStateOfChargeStatus->isWithinLimit(19, displayAlert) == false);
    assert(batteryStateOfChargeStatus->classifyRange(19) == LOW_BREACH);
    assert(batteryStateOfChargeStatus->isWithinLimit(21, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(21) == NORMAL);
    assert(batteryStateOfChargeStatus->isWithinLimit(50, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(50) == NORMAL);
    assert(batteryStateOfChargeStatus->isWithinLimit(79, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(79) == NORMAL);
    assert(batteryStateOfChargeStatus->isWithinLimit(81, displayAlert) == false);
    assert(batteryStateOfChargeStatus->classifyRange(81) == HIGH_BREACH);
    
    StateOfChargeManager stateOfChargeWithWarning(WITHWARNINGLEVEL, GERMAN);
    batteryStateOfChargeStatus = &stateOfChargeWithWarning;
    assert(batteryStateOfChargeStatus->isWithinLimit(19, displayAlert) == false);
    assert(batteryStateOfChargeStatus->classifyRange(19) == LOW_BREACH);
    assert(batteryStateOfChargeStatus->isWithinLimit(21, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(21) == LOW_WARNING);
    assert(batteryStateOfChargeStatus->isWithinLimit(50, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(50) == NORMAL);
    assert(batteryStateOfChargeStatus->isWithinLimit(79, displayAlert) == true);
    assert(batteryStateOfChargeStatus->classifyRange(79) == HIGH_WARNING);
    assert(batteryStateOfChargeStatus->isWithinLimit(81, displayAlert) == false);
    assert(batteryStateOfChargeStatus->classifyRange(81) == HIGH_BREACH);
}

void testBatteryChargeRate()
{
    ChargeRateManager chargeRateWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    BatteryManagementSystem *batteryChargeRateStatus = &chargeRateWithoutWarning;
    assert(batteryChargeRateStatus->isWithinLimit(0.01, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.01) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.5, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.5) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.79, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.79) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.81, displayAlert) == false);
    assert(batteryChargeRateStatus->classifyRange(0.81) == HIGH_BREACH);
    
    ChargeRateManager chargeRateWithWarning(WITHWARNINGLEVEL, GERMAN);
    batteryChargeRateStatus = &chargeRateWithWarning;
    assert(batteryChargeRateStatus->isWithinLimit(0.01, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.01) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.5, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.5) == NORMAL);
    assert(batteryChargeRateStatus->isWithinLimit(0.79, displayAlert) == true);
    assert(batteryChargeRateStatus->classifyRange(0.79) == HIGH_WARNING);
    assert(batteryChargeRateStatus->isWithinLimit(0.81, displayAlert) == false);
    assert(batteryChargeRateStatus->classifyRange(0.81) == HIGH_BREACH);
}

#endif