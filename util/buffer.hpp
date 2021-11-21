/**
 * @file buffer.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 *
 * Modified version of VESC buffer handler from:
 * https://raw.githubusercontent.com/vedderb/bldc/master/buffer.h
 */

#ifndef CAROLO_APP_VESC_BUFFER_HPP
#define CAROLO_APP_VESC_BUFFER_HPP

#include <cstdint>

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    void buffer_append_int16(uint8_t *buffer, int16_t number, int32_t *index);

    void buffer_append_uint16(uint8_t *buffer, uint16_t number, int32_t *index);

    void buffer_append_int32(uint8_t *buffer, int32_t number, int32_t *index);

    void buffer_append_uint32(uint8_t *buffer, uint32_t number, int32_t *index);

    void buffer_append_float16(uint8_t *buffer, float number, float scale, int32_t *index);

    void buffer_append_float32(uint8_t *buffer, float number, float scale, int32_t *index);

    void buffer_append_float32_auto(uint8_t *buffer, float number, int32_t *index);

    int16_t buffer_get_int16(const uint8_t *buffer, int32_t *index);

    uint16_t buffer_get_uint16(const uint8_t *buffer, int32_t *index);

    int32_t buffer_get_int32(const uint8_t *buffer, int32_t *index);

    uint32_t buffer_get_uint32(const uint8_t *buffer, int32_t *index);

    float buffer_get_float16(const uint8_t *buffer, float scale, int32_t *index);

    float buffer_get_float32(const uint8_t *buffer, float scale, int32_t *index);

    float buffer_get_float32_auto(const uint8_t *buffer, int32_t *index);

}

#endif //CAROLO_APP_VESC_BUFFER_HPP
