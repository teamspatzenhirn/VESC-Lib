/**
 * @file VESC_UART_Zephyr.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 22.11.21
 * Description here TODO
 */

#include "VESC_UART_Zephyr.hpp"

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

    bool VESC_UART_Zephyr::writeData(const uint8_t *data, std::size_t size, uint32_t timeout) {

    }

    bool VESC_UART_Zephyr::readData(uint8_t *data, std::size_t size, uint32_t timeout) {

    }
}
