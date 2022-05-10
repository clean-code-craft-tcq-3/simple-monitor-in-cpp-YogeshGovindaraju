#ifndef CHECKER
#define CHECKER

#include <iostream>
#include <assert.h>

#define MINIMUMTEMPERATURE 0
#define MAXIMUMTEMPERATURE 45
#define MINIMUMSTATEOFCHARGE 20
#define MAXIMUMSTATEOFCHARGE 80
#define MAXIMUMCHARGERATE 0.8f

enum Range {LOW, NORMAL, HIGH };

#include "BatteryManagementSystem.h"
#include "TemperatureManager.h"
#include "StateOfChargeManager.h"
#include "ChargeRateManager.h"

bool isBatteryOk(float temperature, float stateOfCharge, float chargeRate);

#endif