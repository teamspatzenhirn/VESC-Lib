/**
 * @file VESC_UART_Zephyr.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 22.11.21
 * Description here TODO
 */

#ifndef VESC_UART_Zephyr_hpp
#define VESC_UART_Zephyr_hpp

// std libraries
#include <inttypes.h>

// zephyr libraries
#include <logging/log.h>
#include <devicetree.h>
#include <drivers/uart.h>

/**
 *
 */
namespace VESC_ComBackend {

    /**
     *
     */
    class VESC_UART_Zephyr {

        public:

            /**
             *
             * @param uartDevSpec
             */
            void VESC_UART_Zephyr(const struct uart_dt_spec *uartDevSpec);

            /**
             *
             */
            void init();

            /**
             *
             * @param data
             * @param size
             * @param timeout
             * @return
             */
            bool writeData(const uint8_t *data, std::size_t size, uint32_t timeout);

            /**
             *
             * @param data
             * @param size
             * @param timeout
             * @return
             */
            bool readData(uint8_t *data, std::size_t size, uint32_t timeout);

        private:

            /**
             *
             */
            const struct uart_dt_spec *_uartDevSpec;
    }
}

#endif // VESC_UART_Zephyr_hpp
