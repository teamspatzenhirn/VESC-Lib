/**
 * @file VESC_UART_Zephyr.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 22.11.21
 * Description here TODO
 */

#include "VESC_UART_Zephyr.hpp"+

// zephyr libraries
#include <errno.h>

LOG_MODULE_REGISTER(vesc_lib_uart, LOG_LEVEL_DBG);

namespace VESC_ComBackend {

    VESC_UART_Zephyr::VESC_UART_Zephyr(const struct uart_dt_spec *uartDevSpec) {
        _uartDevSpec = uartDevSpec;

        if (_uartDevSpec == nullptr) {
            LOG_ERR("UART spec null!");
            return;
        }
    }

    void VESC_UART_Zephyr::init() {
        LOG_INF("Initializing VESC UART");

        if (!spi_is_ready(_uartDevSpec)) {
            LOG_ERR("VESC UART not ready!");
            return;
        }

        LOG_INF("VESC UART is ready!");
    }

    int VESC_UART_Zephyr::writeData(const uint8_t *data, std::size_t size, uint32_t timeout) {

        int64_t timeoutTime = k_uptime_get() + K_MSEC(timeout);
        std::size_t writtenCounter = 0;
        const struct device *dev = nullptr; // @ToDo!

        while (true) {

            if (k_uptime_get() > timeoutTime) {
                return -ETIME;
            }

            if (writtenCounter >= size) {
                break;
            }

            uart_poll_in(dev, data[writtenCounter++])
        }

        return writtenCounter;
    }

    int VESC_UART_Zephyr::readData(uint8_t *data, std::size_t size, uint32_t timeout) {

        int64_t timeoutTime = k_uptime_get() + K_MSEC(timeout);
        std::size_t readCounter = 0;
        const struct device *dev = nullptr; // @ToDo!

        while (true) {

            if (k_uptime_get() > timeoutTime) {
                return -ETIME;
            }

            uint8_t readByte = 0;

            // uart_poll_in return value
            // 0        If data arrived.
            // -1       If no data was available to read (i.e., the UART input buffer was empty).
            // -ENOTSUP	If API is not enabled.
            // -ENOSYS	If the operation is not supported.
            // -EBUSY	If reception was enabled using uart_rx_enabled
            int v = uart_poll_in(dev, &readByte)
            if ( v == 0) {
                data[readCounter++] = readByte;
                if (readCounter >= size) {
                    break;
                }
            }
            else if (v == -1) {
                break;
            }
            else {
                return v;
            }
        }

        return readCounter;
    }
}
