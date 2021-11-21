/**
 * @file VESCMaster.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#include "VESCMaster.hpp"

#include <logging/log.h>

#include "util/crc.hpp"
#include "uart/VESCUart.hpp"

K_HEAP_DEFINE(vescMasterHeap, 512);

LOG_MODULE_REGISTER(vesc_master, LOG_LEVEL_INF);

namespace VESCLib {

    VESCMaster::VESCMaster(const device *uart) : uart(uart) {}

    void VESCMaster::sendCommand(const Message &msg) const {

        uint32_t msgSize = msg.getTotalSize();
        uint32_t index = 0;
        uint8_t *dataToSend;
        uint32_t dataToSendSize = 0;

        // set msg size
        if (msgSize <= 0xff) {
            dataToSendSize = msgSize + 6;
        } else {
            dataToSendSize = msgSize + 7;
        }

        // allocate memory
        dataToSend = (uint8_t *) k_heap_alloc(&vescMasterHeap, dataToSendSize, K_NO_WAIT);
        if (dataToSend == nullptr) {
            LOG_ERR("heap allocation failed!");
            return;
        }

        // append msg size
        appendMessageSize(dataToSend, index, msgSize);

        // copy the msg
        msg.writeMsgToBuffer(dataToSend, dataToSendSize, index);

        // calc crc & add crc
        uint16_t crc = crc16(&dataToSend[index], msgSize);
        index += msgSize;
        dataToSend[index++] = (uint8_t) (crc >> 8);
        dataToSend[index++] = (uint8_t) (crc & 0xff);
        dataToSend[index++] = 3;
        dataToSend[index] = '\0';

        // send data via uart
        sendUart(uart, dataToSend, dataToSendSize);

        // delete
        k_heap_free(&vescMasterHeap, dataToSend);
    }

    void VESCMaster::appendMessageSize(uint8_t *dataToSend, uint32_t &index, uint32_t msgSize) {
        if (msgSize > 0xff) {
            dataToSend[index++] = 3;
            dataToSend[index++] = (uint8_t) (msgSize >> 8);
            dataToSend[index++] = (uint8_t) (msgSize & 0xff);

        } else {
            dataToSend[index++] = 2;
            dataToSend[index++] = msgSize;
        }
    }

}
