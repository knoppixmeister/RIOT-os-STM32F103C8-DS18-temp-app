#include "architecture.h"
#include "thread.h"
#include "xtimer.h"
#include "ztimer.h"

#include "uuid.h"

#include "clk.h"

#include <stdio.h>
#include <string.h>

#include "shell.h"

#include "cpu.h"
#include "periph_conf.h"

#include "ds18.h"
#include "ds18_params.h"

#define SAMPLING_PERIOD     1

int test(int argc, char **argv)
{
    ds18_t dev;
    int result;

    puts("DS18B20 test application\n");

    const ds18_params_t params = {
        .pin         =    GPIO_PIN(PORT_A, 8),
        .out_mode    =    DS18_PARAM_PULL
    };

    printf("+------------Initializing------------+\n");
    result = ds18_init(&dev, &params);

    /*
    #define LED0_PIN           GPIO_PIN(PORT_B,  0)
    #define LED0_MASK          (1 << 0)
    #define LED0_ON            (GPIOB->PCOR = LED0_MASK)
    #define LED0_OFF           (GPIOB->PSOR = LED0_MASK)
    #define LED0_TOGGLE        (GPIOB->PTOR = LED0_MASK)
    */

    // LED0_TOGGLE;

    printf("RES: %d", result);

    if (result == DS18_ERROR) {
        puts("[Error] The sensor pin could not be initialized");
        return 1;
    }

    printf("\n+--------Starting Measurements--------+\n");

    while (1) {
        int16_t temperature;

        if (ds18_get_temperature(&dev, &temperature) == DS18_OK) {
            temperature *= 0.8; // without this shows not correct temp.

            bool negative = (temperature < 0);
            if (negative) {
                temperature = -temperature;
            }

            printf(
                "Temperature [ºC]: %c%d.%02d"
                "\n+-------------------------------------+\n",
                negative ? '-': ' ',
                temperature / 100,
                temperature % 100
            );

            LED0_TOGGLE;
        }
        else {
            puts("[Error] Could not read temperature. Exit proc");
            break;
        }

        xtimer_sleep(SAMPLING_PERIOD);
    }

    return 0;
}

const shell_command_t commands[] = {
    { "t", "test", test },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("Welcome to RIOT!");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
