//Turns on all initiated GPIO ports if input on port 7 is high
//Turns off all ports if input on port 7 is LOW

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

uint32_t *SIO = (uint32_t *)0xd0000000;

uint32_t check_input(int port) 
{
    unsigned long input = *(SIO + 0x004 / 4);
    unsigned long mask = 1ul<<port;
    input&=mask;
    input>>=port;
    return input;
}

int main()
{  
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_init(8);
    gpio_set_dir(8, GPIO_OUT);
    gpio_init(9);
    gpio_set_dir(9, GPIO_OUT);
    gpio_init(10);
    gpio_set_dir(10, GPIO_OUT);
    gpio_init(7);
    gpio_set_dir(7, GPIO_IN);
    
    stdio_init_all();

    while (true)
    {
        printf("input value %d",check_input(7));
        
        if(check_input(7)!=0)
            *(SIO + 0x014 / 4) = 0xffff;
        else
            *(SIO + 0x018 / 4) = 0xffff;
        sleep_ms(1000);
      
    }
}