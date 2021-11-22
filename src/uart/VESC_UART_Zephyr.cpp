/**
 * @file VESC_UART_Zephyr.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 22.11.21
 * Description here TODO
 */

#include "VESC_UART_Zephyr.hpp"

#include <devicetree.h>
#include <logging/log.h>
#include <sys/ring_buffer.h>

LOG_MODULE_REGISTER(vesc_lib_uart, LOG_LEVEL_INF);

RING_BUF_DECLARE(uart_tx_buf, 256);
RING_BUF_DECLARE(uart_rx_buf, 256);

namespace VESC_LIB {

    namespace UART {

        void init(device *dev) {

            LOG_INF("Initializing VESC UART");

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

            uart_irq_callback_user_data_set(dev, isr, nullptr);

            LOG_INF("VESC UART initialization done!");
        }

        void isr(const device *dev, void * /* user_data */) {

            art_irq_update(dev);
            LOG_DBG("UART ISR called");
            if (uart_irq_tx_ready(dev)) {

                uint8_t *sendData;
                // Try to get as much data as ringbuffer can possibly hold
                auto size = ring_buf_capacity_get(&uart_tx_buf);
                auto claimed = ring_buf_get_claim(&uart_tx_buf, &sendData, size);
                // Try sending all continuous data the ringbuffer has
                auto sent = uart_fifo_fill(dev, sendData, claimed);
                LOG_DBG("Sent %d bytes of %ld claimed bytes out of %ld-byte tx ringbuffer.", sent, claimed, size);
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

            // ToDo: check...
            if (uart_irq_rx_ready(dev)) {

                uint8_t *readData;
                // Try to get as much data as ringbuffer can possibly hold
                auto size = ring_buf_capacity_get(&uart_rx_buf);
                auto claimed = ring_buf_get_claim(&uart_rx_buf, &sendData, size);
                // Try sending all continuous data the ringbuffer has
                auto read = uart_fifo_read(dev, readData, claimed);
                LOG_DBG("Read %d bytes of %ld claimed bytes out of %ld-byte rx ringbuffer.", sent, claimed, size);
                // Free all data that could actually be sent
                ring_buf_get_finish(&uart_rx_buf, read);
                if (ring_buf_is_empty(&uart_rx_buf)) {

                    // Sent everything!
                    LOG_DBG("Ring buffer is empty now, disabling rx irq!");
                    uart_irq_rx_disable(dev);
                }

            } else {
                LOG_DBG("RX not ready");
            }
        }

        bool writeData(cosnt device *dev, const uint8_t *data, std::size_t size) {

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

        bool readData(uint8_t *data) {

            LOG_DBG("Reading %d bytes", size);

            //uart_irq_rx_enable(dev);
            //ring_buf_get(&uart_rx_buf, data, size);
        }

        const struct uart_dt_spec *_uartDevSpec;

    }
}
