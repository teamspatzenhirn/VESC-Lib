/**
 * @file VESCBus.hpp
 * @author simonwilhelmstaetter
 * @date 10.11.2021
 */

#ifndef CAROLO_APP_VESCBUS_HPP
#define CAROLO_APP_VESCBUS_HPP

#include <lib/steering/WheelRpmSetpoint.hpp>
#include "lib/vesc/VESC.hpp"
#include "lib/vesc/VESCMaster.hpp"


/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * @class VESCBus
     *
     * This class provides an object which represents the whole VESC bus.
     */
    class VESCBus {

    public:
        /**
         * Initialize a new VESCBus object
         * @param idFrontLeft     front left motor
         * @param idFrontRight    front right motor
         * @param idRearLeft      rear left motor
         * @param idRearRight     rear right motor
         */
        VESCBus(uint8_t idFrontLeft, uint8_t idFrontRight, uint8_t idRearLeft, uint8_t idRearRight) noexcept;

        void setRpm(WheelRpmSetpoint setpoint);

        void stop();

    private:
        // instance for the master
        VESCLib::VESCMaster master;

        // VESC instances for each motor
        VESCLib::VESC motorFrontLeft;
        VESCLib::VESC motorFrontRight;
        VESCLib::VESC motorRearLeft;
        VESCLib::VESC motorRearRight;

    };
}


#endif //CAROLO_APP_VESCBUS_HPP
