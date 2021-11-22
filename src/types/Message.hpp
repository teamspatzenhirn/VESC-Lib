/**
 * @file Message.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#ifndef CAROLO_APP_VESC_MESSAGE_HPP
#define CAROLO_APP_VESC_MESSAGE_HPP

#include <cstdint>

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * @class Message
     *
     * This class represents a message object which contains a command and payload which get's send to a vesc.
     */
    class Message {

        public:

            /**
             * @brief Initializes an new CAN Message object.
             * 
             * @param commandID A vesc command id.
             * @param canID The can id of the destination vesc.
             * @param payload The payload of the message.
             * @param payloadSize The size of the message payload.
             * @param vescMasterCanId The CAN ID of the vesc vesc.
             */
            Message(uint8_t commandID, uint8_t canID, uint8_t *payload, uint16_t payloadSize, uint8_t vescMasterCanId = 0);

            /**
             * @brief Variable for the command id.
             */
            uint8_t commandID;

            /**
             * @brief Variable for the CAN id.
             */
            uint8_t canID;

            /**
             * @brief Pointer to the payload of the msg.
             */
            uint8_t *payload;

            /**
             * @brief Variable for the size of the msg payload.
             */
            uint16_t payloadSize;

            /**
             * @brief The CAN ID of the vesc master.
             */
            uint8_t svescMasterCanId;

            /**
             * @brief Checks if the msg is a msg which gets forwarded over the can bus.
             * 
             * @return True if msg is a can msg, false if msg isn't forwarded over the can bus
             */
            [[nodiscard]] bool isCANMsg() const;

            /**
             * @brief Get the total size of the msg.
             * 
             * @return The total size of the msg.
             */
            [[nodiscard]] uint32_t getTotalSize() const;

            /**
             * @brief Writes the complete msg to a buffer.
             * 
             * @param[out] msgBuffer The buffer were the msg is written to.
             * @param bufferSize The maximum size of the buffer (must be at least the size of 'Message.getTotalSize()').
             * @param startIndex The index were this function should start writing data.
             * @return the amount of bytes written to the buffer.
             */
            uint32_t writeMsgToBuffer(uint8_t *msgBuffer, uint32_t bufferSize, uint32_t startIndex = 0) const;

    };

}

#endif //CAROLO_APP_VESC_MESSAGE_HPP
