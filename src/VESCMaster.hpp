/**
 * @file VESCMaster.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#ifndef CAROLO_APP_VESC_VESCMASTER_HPP
#define CAROLO_APP_VESC_VESCMASTER_HPP

#include <cstdint>

#include "types/Message.hpp"
#include <drivers/uart.h>

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * @class VESCMaster
     *
     * This class provides functions to send (and receive) data to the vesc's over one master vesc.
     * The master vesc is connected via uart and all other vesc are connected to the master vesc via the can bus.
     */
    class VESCMaster {

    public:

        /**
         * Initializes a new VescMaster object.
         * @param uart A reference to a fully initialized and configured uart device.
         * The master vesc must be connected to this uart device.
         */
        explicit VESCMaster(const device *uart);

        /**
         * Sends a command to a vesc. The specific destination vesc is defined in the msg.
         * @param msg The message which shall be send.
         */
        void sendCommand(const Message &msg) const;


    private:

        /**
         * The internal reference to the uart device.
         */
        const device *uart;

        /**
         * Appends the message size to the data which is send to the vesc.
         * @param dataToSend The data buffer.
         * @param index The index ref.
         * @param msgSize The size of the complete msg.
         */
        static void appendMessageSize(uint8_t *dataToSend, uint32_t &index, uint32_t msgSize);

    };

}

#endif //CAROLO_APP_VESC_VESCMASTER_HPP
