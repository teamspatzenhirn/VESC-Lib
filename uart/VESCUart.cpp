/**
 * @file VESCUart.cpp
 * @author ottojo & Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#include "VESCUart.hpp"

#include <devicetree.h>
#include <logging/log.h>
#include <sys/ring_buffer.h>

LOG_MODULE_REGISTER(vesc_lib_uart, LOG_LEVEL_INF);

// Find devicetree alias "vesc-serial": Should point to STM32 us?art
#define VESC_UART_NODE DT_ALIAS(vesc_serial)
#if !DT_NODE_EXISTS(VESC_UART_NODE)
#error "VESC uart node does not exist"
#endif
#if !DT_NODE_HAS_STATUS(VESC_UART_NODE, okay)
#error "Unsupported board: VESC uart not available"
#endif

RING_BUF_DECLARE(uart_tx_buf, 256);

namespace VESCLib {

    /**
     * VESC UART Interrupt Service Routine: Responsible for sending data from uart_tx_buf ring buffer.
     * With uart_irq_tx_enable, an interrupt is generated whenever the uart peripheral is ready to accept new data.
     */
    void vescUartISR(const device *dev, void * /* user_data */) {

        uart_irq_update(dev);
        LOG_DBG("UART ISR called");
        if (uart_irq_tx_ready(dev)) {

            uint8_t *sendData;
            // Try to get as much data as ringbuffer can possibly hold
            auto size = ring_buf_capacity_get(&uart_tx_buf);
            auto claimed = ring_buf_get_claim(&uart_tx_buf, &sendData, size);
            // Try sending all continuous data the ringbuffer has
            auto sent = uart_fifo_fill(dev, sendData, claimed);
            LOG_DBG("Sent %d bytes of %ld claimed bytes out of %ld-byte ringbuffer.", sent, claimed, size);
            // Free all data that could actually be sent
            ring_buf_get_finish(&uart_tx_buf, sent);
            if (ring_buf_is_empty(&uart_tx_buf)) {

                // Sent everything!
                LOG_DBG("Ring buffer is empty now, disabling tx irq!");
                uart_irq_tx_disable(dev);

            }

        } else {
            LOG_DBG("TX not ready");
        }

    }

    void sendUart(const device *dev, const uint8_t *data, std::size_t size) {
        LOG_DBG("Sending %d bytes", size);

        // TODO (long-term): Use the ASYNC API, which seems to not be available on F7 right now.
        //  Initial implementation here: https://github.com/zephyrproject-rtos/zephyr/pull/30917
        //  Ongoing work here: https://github.com/zephyrproject-rtos/zephyr/pull/32833, there seem to be issues regarding
        //  DMA+Caching.

        // Zephyr doc: Use cases involving multiple writers to the ring buffer must prevent
        // concurrent write operations, either by preventing all writers from being preempted
        // or by using a mutex to govern writes to the ring buffer.
        ring_buf_put(&uart_tx_buf, data, size);

        uart_irq_tx_enable(dev);
    }

    ConstDevicePtr vescUartInit() {

        LOG_INF("Initializing VESC UART");

        const device *dev;

        dev = device_get_binding(DT_LABEL(VESC_UART_NODE));
        if (dev == nullptr) {
            LOG_ERR("VESC UART device binding not available!");
            return nullptr;
        }

        if (!device_is_ready(dev)) {
            LOG_ERR("VESC UART not ready!");
            return nullptr;
        }

        const struct uart_config uart_cfg = {
                .baudrate = 115200,
                .parity = UART_CFG_PARITY_NONE,
                .stop_bits = UART_CFG_STOP_BITS_1,
                .data_bits = UART_CFG_DATA_BITS_8,
                .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
        };

        if (uart_configure(dev, &uart_cfg) != 0) {
            LOG_ERR("VESC UART configuration not successful");
            return nullptr;
        }

        uart_irq_callback_user_data_set(dev, vescUartISR, nullptr);

        LOG_INF("VESC UART initialization done!");

        return dev;
    }
}
