/**
 * @file VESCBus.cpp
 * @author simonwilhelmstaetter
 * @date 10.11.2021
 */

#include <lib/vesc/uart/VESCUart.hpp>
#include "VESCBus.hpp"
#include "config/CarConstants.hpp"

namespace VESCLib {
    VESCBus::VESCBus(uint8_t idFrontLeft, uint8_t idFrontRight, uint8_t idRearLeft, uint8_t idRearRight) noexcept :
                     master(VESCLib::vescUartInit()),
                     motorFrontLeft(&master, idFrontLeft),
                     motorFrontRight(&master, idFrontRight),
                     motorRearLeft(&master, idRearLeft),
                     motorRearRight(&master, idRearRight) {
    }

    void VESCBus::setRpm(WheelRpmSetpoint setpoint) {
        motorFrontLeft.setRPM(static_cast<int32_t>(setpoint.frontLeft * MOTOR_POLE_PAIRS * MOTOR_TRANSMISSION));
        motorFrontRight.setRPM(static_cast<int32_t>(setpoint.frontRight * MOTOR_POLE_PAIRS * MOTOR_TRANSMISSION));
        motorRearLeft.setRPM(static_cast<int32_t>(setpoint.rearLeft * MOTOR_POLE_PAIRS * MOTOR_TRANSMISSION));
        motorRearRight.setRPM(static_cast<int32_t>(setpoint.rearRight * MOTOR_POLE_PAIRS * MOTOR_TRANSMISSION));
    }

    void VESCBus::stop() {
        setRpm({.frontLeft = 0, .frontRight = 0, .rearLeft = 0, .rearRight = 0});
    }
}
