#include "Sgwork.h"

uint16_t scafe_fl;

void all_ind()
{
}

void Work_init()
{
}

uint8_t stop_sound;

void Work_drv()
{
    if (error_kog_num > error_kog_num_cpy) {
        tech_fl |= SOUND;
    }
    error_kog_num_cpy = error_kog_num;

    if (error_vzk_num > error_vzk_num_cpy) {
        tech_fl |= SOUND;
    }
    error_vzk_num_cpy = error_vzk_num;

    if (error_buzz_num > error_buzz_num_cpy) {
        tech_fl |= SOUND;
    }
    error_buzz_num_cpy = error_buzz_num;

    if ((!K_TEST) || (KEY_ERR)) {
        SoundOFF();
        tech_fl &= ~SOUND;
        error_buzz_num = 0;
        error_vzk_num = 0;
        error_kog_num = 0;

        error_buzz_num_cpy = 0;
        error_vzk_num_cpy = 0;
        error_kog_num_cpy = 0;
    }
}

void SoundON()
{

}

void SoundOFF()
{

}
