/**
 * @file crc.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 *
 * Modified version of VESC crc handler from (without hardware crc):
 * https://raw.githubusercontent.com/vedderb/bldc/master/crc.h
 */

#ifndef CAROLO_APP_VESC_CRC_HPP
#define CAROLO_APP_VESC_CRC_HPP

#include <cstdint>

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * Calculates a 16 bit crc of some date in software.
     * @param buf A Pointer to the buffer containing the data.
     * @param len The size of the data.
     * @return A 16 bit crc value.
     */
    uint16_t crc16(uint8_t *buf, uint32_t len);

}


#endif //CAROLO_APP_VESC_CRC_HPP
