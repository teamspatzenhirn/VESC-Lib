/**
 * @file VESC_UART_Zephyr.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 22.11.21
 * Description here TODO
 */

#ifndef VESC_UART_Zephyr_hpp
#define VESC_UART_Zephyr_hpp

#include <inttypes.h>

namespace VESC_LIB {

    namespace UART {

        void init();

        void isr(const device *dev, void * /* user_data */);

        bool writeData(cosnt device *dev, const uint8_t *data, std::size_t size)

        bool readData(uint8_t * data);

        extern const struct uart_dt_spec *_uartDevSpec;
    }
}

#endif // VESC_UART_Zephyr_hpp
