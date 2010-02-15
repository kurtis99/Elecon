#ifndef ALLSTRINGS_H
    #define ALLSTRINGS_H

    #include <Main.h>
    // I2C
    extern const char no_arch_str[] PROGMEM;
    extern const char no_iic_str[] PROGMEM;
    extern const char pdz_set_name_str[][16] PROGMEM;

	extern const char dev_error[] PROGMEM;
	extern const char dev_error_press[] PROGMEM;
	extern const char dev_error_mp[] PROGMEM;
	extern const char dev_error_ktr[] PROGMEM;
	extern const char dev_error_os[] PROGMEM;
	extern const char dev_error_noop[] PROGMEM;
	extern const char dev_error_nocl[] PROGMEM;
	extern const char dev_error_noready[] PROGMEM;
	extern const char dev_error_position[] PROGMEM;

    extern const char sys_set_restart_str[] PROGMEM;
    /* Test.cpp */
    extern const char sys_set_str[][14] PROGMEM;
    extern const char message_str[][15] PROGMEM;
    extern const char mnemo_str[][5] PROGMEM;
    extern const char msk_test_str[][6] PROGMEM;
    extern const char mt_test_str[][14] PROGMEM;
    extern const char MSK_pressed[] PROGMEM;
    extern const char test_str[3][6] PROGMEM;
    extern const char sys_set_str[][14] PROGMEM;

    extern const char pdz_stad_op_str[][16] PROGMEM;

    /* Pdz.cpp */
    extern const char pdz_name_str[6] PROGMEM;
    extern const char pdz_norma_str[] PROGMEM;
    /* Dev_kpd.cpp*/
    extern const char kpd_error_str[][9] PROGMEM;

    /* Devs.cpp */
    extern const char strTechStadInfo[][3] PROGMEM;
    extern const char strTechMode[][5] PROGMEM;
    extern const char strDevName[][5] PROGMEM;
    extern const char dev_set_name_str[][17] PROGMEM;
    extern const char strNoDevsDefined[] PROGMEM;
    /* DevsXXX.cpp */
    extern const char strKogErrorMessages[][5] PROGMEM;
    extern const char strOutOfNetError[] PROGMEM;
    /* Menu.cpp */
    extern const char strMenuPdz[] PROGMEM;
    extern const char strMenuEtaz[] PROGMEM;
    extern const char strMenuBFPP[] PROGMEM;
    extern const char strMenuDevs[] PROGMEM;
    extern const char strMenuSets[] PROGMEM;
    extern const char strMenuTest[] PROGMEM;
    extern const char strMenuMessages[] PROGMEM;
    extern const char strMenuServ[] PROGMEM;

    extern const char strSetPdz[] PROGMEM;
    extern const char strSetDevs[] PROGMEM;
    extern const char strSetSystem[] PROGMEM;


    extern const char strTestMt[] PROGMEM;
    extern const char strTestMsk[] PROGMEM;
    extern const char strTestMnemo[] PROGMEM;
    extern const char strTestLcd[] PROGMEM;
    extern const char strTestZvuk[] PROGMEM;
    extern const char strTestBfpp[] PROGMEM;

    extern const char strSpz2[] PROGMEM;
    extern const char strSpz1[] PROGMEM;

    extern const char strShowVer[] PROGMEM;

    extern const char strCompilationDate[] PROGMEM;
    extern const char strCompilationTime[] PROGMEM;
    extern const char strEtazTest[] PROGMEM;

    // Pdz.cpp
    extern const char pdz_set_name_str[][16] PROGMEM;
    extern const char pdz_stad_cl_str[][16] PROGMEM;

    extern const char MSK_error_str[] PROGMEM;
    extern const char fireSTR[] PROGMEM;
    extern const char etaz_str[] PROGMEM;
    extern const char net_str[]  PROGMEM;
    extern const char menu_str[] PROGMEM;
    extern const char button_str[] PROGMEM;
    extern const char prosto_tak_str[] PROGMEM;

    extern const char fire_section1[] PROGMEM;
    extern const char fire_section2[] PROGMEM;
    extern const char fire_section3[] PROGMEM;
    extern const char section_str[] PROGMEM;

    extern const char hui[] PROGMEM;

    /* Etaz.cpp */
    extern const char etaz_str[] PROGMEM;
    extern const char bfpp_test_str[][7] PROGMEM;
	extern const char kz_str[]      PROGMEM;
    extern const char pk_str[]      PROGMEM;

    extern const char norma_str[]    PROGMEM;
    extern const char nolink_str[]   PROGMEM;
    extern const char noadr_str[]    PROGMEM;
    extern const char fire_str[]     PROGMEM;
    extern const char firePK_str[]   PROGMEM;
    extern const char fireSPS_str[]  PROGMEM;
    extern const char fireMenu_str[] PROGMEM;
    extern const char dist_str[]     PROGMEM;
    extern const char osh24_str[]    PROGMEM;
    extern const char osh220_str[]   PROGMEM;
    extern const char luch_str[]     PROGMEM;
    extern const char kz_str[]       PROGMEM;
    extern const char pk_str[]       PROGMEM;

    extern const char bfpp_str[]   PROGMEM; 
	extern const char strStopPdz[] PROGMEM;
    extern const char strReset[]  PROGMEM;

    extern const char str_D1M[]  PROGMEM;
    extern const char str_D2M[]  PROGMEM;
    extern const char str_D3M[]  PROGMEM;
    extern const char str_D4M[]  PROGMEM;
    extern const char str_D5M[]  PROGMEM;
    extern const char str_D6M[]  PROGMEM;
    extern const char str_D7M[]  PROGMEM;
    extern const char str_D8M[]  PROGMEM;
    extern const char str_D9M[]  PROGMEM;
    extern const char str_D10M[] PROGMEM;

    extern const char str_P1M[]  PROGMEM;
    extern const char str_P2M[]  PROGMEM;
    extern const char str_P3M[]  PROGMEM;
    extern const char str_P4M[]  PROGMEM;
    extern const char str_P5M[]  PROGMEM;
    extern const char str_P6M[]  PROGMEM;
    extern const char str_P7M[]  PROGMEM;
    extern const char str_P8M[]  PROGMEM;
    extern const char str_P9M[]  PROGMEM;
    extern const char str_P10M[] PROGMEM;
    extern const char str_P11M[] PROGMEM;
    extern const char str_P12M[] PROGMEM;

    extern const char str_YA26_1[] PROGMEM;
    extern const char str_YA26_2[] PROGMEM;
    extern const char str_YA26_3[] PROGMEM;
    extern const char str_YA26_4[] PROGMEM;
    extern const char str_YA26_5[] PROGMEM;
    extern const char str_YA26_6[] PROGMEM;

#endif /* ALLSTRINGS_H */
