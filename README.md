# RIOT os STM32F103C8 (bluepill) DS18 temperature measure app

Wiring:

![----](docs/console.png)

![---](docs/ds18b20-waterproof-sensor.jpg)

![---](docs/DS18B20-STM32F103C-wiring.jpg)

Instructions

```
git clone https://github.com/RIOT-OS/RIOT.git
cd RIOT/examples

git clone https://github.com/knoppixmeister/RIOT-os-STM32F103C8-DS18-temp-app.git ds18-temp-app
cd ds18-temp-app

make -j4 BOARD=bluepill-stm32f103c8
make BOARD=bluepill-stm32f103c8 flash

```

Enjoy!

Based on code from: https://github.com/RIOT-OS/RIOT/blob/master/tests/drivers/ds18/main.c

Images:

https://circuitdigest.com/microcontroller-projects/getting-started-with-stm32-blue-pill-development-board-stm32f103c8-using-arduino-ide

Usefull links:

https://www.youtube.com/watch?v=TCArLiTjwNE

https://how2electronics.com/interfacing-ds18b20-temperature-sensor-with-stm32/

