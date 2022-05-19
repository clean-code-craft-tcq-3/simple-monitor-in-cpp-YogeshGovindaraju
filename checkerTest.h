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

bool isBatteryStatusRangeAsExpected(BatteryStatus batteryStatus)
{
    return (batteryStatus.batteryManagementStatus->isWithinLimit(batteryStatus.value, batteryStatus.displayAlert) == batteryStatus.limit) &&
           (batteryStatus.batteryManagementStatus->classifyRange(batteryStatus.value) == batteryStatus.range);
}

void testBatteryTemperature()
{
    TemperatureManager temperatureWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    assert(isBatteryStatusRangeAsExpected({&temperatureWithoutWarning, -1, EXCEEDED_LIMIT, LOW_BREACH, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithoutWarning, 1, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithoutWarning, 30, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithoutWarning, 44, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithoutWarning, 46, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
    
    TemperatureManager temperatureWithWarning(WITHWARNINGLEVEL, GERMAN);
    assert(isBatteryStatusRangeAsExpected({&temperatureWithWarning, -1, EXCEEDED_LIMIT, LOW_BREACH, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithWarning, 1, WITHIN_LIMIT, LOW_WARNING, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithWarning, 30, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithWarning, 44, WITHIN_LIMIT, HIGH_WARNING, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&temperatureWithWarning, 46, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
}

void testBatteryStateOfCharge()
{
    StateOfChargeManager stateOfChargeWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithoutWarning, 19, EXCEEDED_LIMIT, LOW_BREACH, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithoutWarning, 21, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithoutWarning, 50, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithoutWarning, 79, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithoutWarning, 81, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
    
    StateOfChargeManager stateOfChargeWithWarning(WITHWARNINGLEVEL, GERMAN);
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithWarning, 19, EXCEEDED_LIMIT, LOW_BREACH, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithWarning, 21, WITHIN_LIMIT, LOW_WARNING, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithWarning, 50, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithWarning, 79, WITHIN_LIMIT, HIGH_WARNING, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&stateOfChargeWithWarning, 81, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
}

void testBatteryChargeRate()
{
    ChargeRateManager chargeRateWithoutWarning(WITHOUTWARNINGLEVEL, ENGLISH);
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithoutWarning, 0.01, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithoutWarning, 0.5, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithoutWarning, 0.79, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithoutWarning, 0.81, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
    
    ChargeRateManager chargeRateWithWarning(WITHWARNINGLEVEL, GERMAN);
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithWarning, 0.01, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithWarning, 0.5, WITHIN_LIMIT, NORMAL, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithWarning, 0.79, WITHIN_LIMIT, HIGH_WARNING, displayAlert}));
    assert(isBatteryStatusRangeAsExpected({&chargeRateWithWarning, 0.81, EXCEEDED_LIMIT, HIGH_BREACH, displayAlert}));
}

#endif