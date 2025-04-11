#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "TMC4671.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19


void tmc4671_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength){
    gpio_put(PIN_CS, 0);

	uint8_t read_buffer[5] = { 0 };
    printf("data HEX SENT: ");
    for (size_t i = 0; i < dataLength; i++) {
        printf("%02x", data[i]);  // Print each byte in hexadecimal
    }
    printf("  |  ");

	int value = spi_write_read_blocking(SPI_PORT, data, &read_buffer[0], dataLength);
    printf("Bytes written/read: %d\n", value);

    printf("data RECIEVED: ");
    for (size_t i = 0; i < dataLength; i++) {
        printf("%02x", read_buffer[i]);  // Print each byte in hexadecimal
    }
    printf("\n");

    data = read_buffer;

    gpio_put(PIN_CS, 1);
}

void pico_init_() {
    stdio_init_all();
    
    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

}

void tmc_init_() {
    tmc4671_writeRegister(0, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0x003041); // Set motor type and number of pole pairs
}

int main()
{
    pico_init_();
    tmc_init_();

    

    while (true) {
        tmc4671_readRegister(0, TMC4671_MOTOR_TYPE_N_POLE_PAIRS);
        tmc4671_writeRegister(0, TMC4671_OPENLOOP_MODE, 0x00000001);
        tmc4671_writeRegister(0, TMC4671_OPENLOOP_ACCELERATION, 0x00000100);
        tmc4671_writeRegister(0, TMC4671_OPENLOOP_VELOCITY_TARGET, 0x00000100);
        tmc4671_readRegister(0, TMC4671_OPENLOOP_VELOCITY_TARGET);
        printf("Is working\n");
        sleep_ms(4000);
    }
}
