#include <can2040.h>
#include <hardware/regs/intctrl.h>
#include <stdio.h>
#include <pico/stdlib.h>

static struct can2040 cbus;

static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    // Put your code here....
}

static void PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

void canbus_setup(void)
{
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000, bitrate = 500000;
    uint32_t gpio_rx = 4, gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0, PIOx_IRQHandler);
    irq_set_priority(PIO0_IRQ_0, PICO_DEFAULT_IRQ_PRIORITY - 1);
    irq_set_enabled(PIO0_IRQ_0, 1);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

void main()
{
    stdio_init_all();
    canbus_setup();

    struct can2040_msg msg;

    msg.id = 0x001;
    msg.dlc = 8;
    uint8_t buf[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    for (int i = 0; i < 8; i++)
    {
        msg.data[i] = buf[i];
    }

    while (1)
    {
        can2040_transmit(&cbus, &msg);
        printf("CAN message sent\n");
        sleep_ms(5000);
    }
}
