//Turns on all initiated GPIO ports if input on port 7 is high
//Turns off all ports if input on port 7 is LOW

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

uint32_t *SIO = (uint32_t *)0xd0000000;

uint32_t check_input(unsigned int port) 
{
    unsigned long input = *(SIO + 0x004 / 4);
    unsigned long mask = 1ul<<port;
    input&=mask;
    input>>=port;
    return input;
}

void gpio_on(unsigned int port) 
{
    *(SIO + 0x014 / 4) = 1ul<<port;
}

void gpio_off(unsigned int port) 
{
    *(SIO + 0x018 / 4) = 1ul<<port;
}

int main()
{  
    gpio_init(6);
    gpio_set_dir(6, GPIO_IN);
    gpio_init(7);
    gpio_set_dir(7, GPIO_IN);
    gpio_init(8);
    gpio_set_dir(8, GPIO_OUT);
    gpio_init(9);
    gpio_set_dir(9, GPIO_OUT);
    gpio_init(10);
    gpio_set_dir(10, GPIO_OUT);
    
    
    stdio_init_all();

    while (true)
    {
        uint32_t port_mask=(uint32_t)0b111<<8;

        if(check_input(7)!=0) {
             *(SIO + 0x014 / 4) = port_mask;           
        }
        if(check_input(6)!=0) {
            *(SIO + 0x018 / 4) = port_mask;
        }
        sleep_ms(20);
      
    }
}