/**
 * @file VESCUart.hpp
 * @author ottojo & Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#ifndef SRC_VESCUART_HPP
#define SRC_VESCUART_HPP

#include <cstdint>
#include <cstddef>
#include <drivers/uart.h>

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * @brief Transmit buffer to VESC via UART
     *
     * Writes to ring-buffer, add mutex if concurrent access is required. Uses basic FIFO uart-method, which works byte-wise
     * on STM32, but whatever...
     */
    void sendUart(const device *dev, const uint8_t *data, std::size_t size);

    using ConstDevicePtr = const device *;

    /**
     * Initialize the vesc uart interface.
     * @return On success a new uart device fort the vesc, else nullptr.
     */
    ConstDevicePtr vescUartInit();

}

#endif //SRC_VESCUART_HPP
