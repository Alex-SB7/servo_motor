#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"     
#include "hardware/adc.h"      

#define led_sei_la_qual 22
#define joystick_io 26
uint level_pwm = 0;
uint ad_min = 10;
uint ad_max = 4095;
uint pwm_min = 500;
uint pwm_max = 2000;



int main()
{
    stdio_init_all();
    sleep_ms(200);

    //Configuração da leitura do canal AD
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    //Configuração do módulo PWM
    gpio_set_function(led_sei_la_qual, GPIO_FUNC_PWM); 
    uint slice = pwm_gpio_to_slice_num(led_sei_la_qual); 
    pwm_set_clkdiv(slice, 2.0); 
    pwm_set_wrap(slice, 2000); 
    pwm_set_enabled(slice, true); 



    while (true) {
        uint16_t ad_in = adc_read();
        
        if (ad_in < ad_min)
        {
            level_pwm = pwm_min;
        }
        else if(ad_in > ad_max)
        {
            level_pwm = pwm_max;
        }
        else
        {
            level_pwm = ((ad_in - ad_min)*(pwm_max - pwm_min))/(ad_max - ad_min) + pwm_min;   
        }

        pwm_set_gpio_level(led_sei_la_qual, level_pwm); //definir o ciclo de trabalho (duty cycle) do pwm
    }
}
