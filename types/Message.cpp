/**
 * @file Message.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#include "Message.hpp"

#include <cstring>

#include "datatypes.hpp"
#include "config/CarConstants.hpp"

namespace VESCLib {

    Message::Message(uint8_t commandID, uint8_t canID, uint8_t *payload, uint16_t payloadSize)
            : commandID(commandID), canID(canID), payload(payload), payloadSize(payloadSize) {
    }

    uint32_t Message::getTotalSize() const {

        // Add command id to total size
        uint32_t totalSize = 1;

        // Add payload size to total size
        totalSize += payloadSize;

        // Add CAN information to size if necessary
        if (isCANMsg()) {
            totalSize += 2;
        }

        return totalSize;

    }

    uint32_t Message::writeMsgToBuffer(uint8_t *msgBuffer, uint32_t bufferSize, uint32_t startIndex) const {

        if (bufferSize - startIndex < this->getTotalSize()) {
            return 0;
        }

        uint32_t index = startIndex;

        // write CAN information if necessary
        if (isCANMsg()) {
            msgBuffer[index++] = COMM_FORWARD_CAN;
            msgBuffer[index++] = canID;
        }

        // write the command and payload
        msgBuffer[index++] = commandID;

        // copy payload
        std::memcpy(&msgBuffer[index], payload, payloadSize);

        return index + payloadSize;
    }

    bool Message::isCANMsg() const {
        if (canID == VESC_MASTER_CAN_ID) {
            return false;
        } else {
            return true;
        }
    }
}
