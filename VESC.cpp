/**
 * @file VESC.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#include <logging/log.h>
#include "VESC.hpp"

#include "types/datatypes.hpp"
#include "util/buffer.hpp"

LOG_MODULE_REGISTER(vesc_lib, LOG_LEVEL_INF);

namespace VESCLib {

    VESC::VESC(const VESCMaster *vescMaster, const uint8_t canID)
            : vescMaster(vescMaster), canID(canID) {
    }

    void VESC::setRPM(int32_t rpm) {

        int32_t index = 0;
        uint8_t payload[4];
        buffer_append_int32(payload, rpm, &index);

        Message msg(COMM_SET_RPM, canID, payload, 4);

        vescMaster->sendCommand(msg);

    }

}
