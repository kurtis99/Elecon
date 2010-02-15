#include "AllStrings.h"

	const char no_arch_str[] = "нет архива";
	const char no_iic_str[] = "Ошибка I2C";

    const char sys_set_restart_str[] = "Заводск. уставки";

    const char message_str[][15] = {
        "Старт системы",
        "Пожар этаж",
        "Авария Д1М",
        "Авария П1М",
        "Авария П2М",
        "Блок. Лифт",
        "Пожар от ПК",
        "Пожар от СПС",
        "Стоп ПДЗ",
    };

    const char mnemo_str[7][5] = {
        "ПОЛЕ",
        "АВТО",
        "ЧЕРН",
        "КРАС",
        "ЖЕЛТ",
        "ЗЕЛН",
        "ОСТН"
    };

    const char msk_test_str[4][6] = {
        "МСК1:",
        "МСК2:",
        "МСК3:",
        "МСК4:"
    };

    const char sys_set_str[][14] = {
        "1.Перезапуск",
        "2.Время",
        "Сист. уставки",
    };

    const char pdz_stad_op_str[][16] = {
        "Откр клапан",
        "Пуск ПД",
        "Пуск ДУ",
        "-= Конец =-",
        "Пуск ППЗМ",
    };

    const char pdz_name_str[] = "ПДЗ";
    const char pdz_norma_str[] = "В норме";

	const char dev_error[]       = "Ош:";
	const char dev_error_press[] = "давл";
	const char dev_error_mp[]    = "МП";
	const char dev_error_ktr[]   = "КТР";
	const char dev_error_os[]    = "ОС";
	const char dev_error_noop[]  = "неотк";
	const char dev_error_nocl[]  = "незак";
	const char dev_error_noready[] = "негот";
	const char dev_error_position[] = "полож";

    const char kpd_error_str[][9] = {
        "Ош:",
        "неотк",
        "незак",
        "негот",
        "нап",
        "Rabbit"
    };

    /* Devs.cpp */
    /* Текущий режим работы
        OP - открыт (запущен)
        CL - закрыт (остановлен)
        ST - ??? */
    const char strTechStadInfo[3][3] =
    {
        "OP",
        "CL",
        "ST"
    };
    const char strTechMode[3][5] =
    {
        "АВТО",
        "ОПЕР",
        "ДИСТ"
    };
    const char dev_set_name_str[][17] =
    {
        "Т ожид давления",
    };
    const char strNoDevsDefined[] = "Нет устройств!";

    /* DevsXXX.cpp */
    const char strKogErrorMessages[5][5] =
    {
        "Ош:",
        "Давл",
        "МП",
        "КТР",
        "ОС"
    };
    const char strOutOfNetError[] = "Не в сети";

    /* Menu.cpp */
    //sg - String Global

    const char strMenuPdz[]  = ")ПДЗ";
    const char strMenuDevs[] = ")Устройства";
    const char strMenuBFPP[] = ")БФПП";
    const char strMenuEtaz[] = ")Этаж";
    const char strMenuSets[] = ")Уставки";
    const char strMenuTest[] = ")Тест";
    const char strMenuMessages[] = ")Архив";
    const char strMenuServ[] = ")Служебное";

    const char strSetPdz[]  = ".ПДЗ";
    const char strSetDevs[] = ".Устройства";
    const char strSetSystem[] = ".Система";
    //const char BlaBlaBla[] = "Блаблаблаю";

    const char strTestMt[]    = ".МТ";
    const char strTestMsk[]   = ".МСК";
    const char strTestMnemo[] = ".Мнемосхема";
    const char strTestLcd[]   = ".ЖКИ-тест";
    const char strTestZvuk[]  = ".Звук";
    const char strTestBfpp[]  = ".БФПП";
    const char strReset[]     = ".Сброс";

    const char strSpz2[] = " ЩПЗ-1";
    const char strSpz1[]   = " ЩПЗ-2";

    const char strShowVer[] = " Версия ПО";

    // Дата и Время компиляции прошивки ??\
    тут все как-то странно работает
    const char strCompilationDate[] = __DATE__;
    const char strCompilationTime[] = __TIME__;
    const char strEtazTest[] = "Вы в меню ЭТАЖ";

    const char pdz_stad_cl_str[][16] =
    {
        "Останов ПДЗ",
        "Дежурный"
    };

    const char hui[] = "ХУЙ";

    const char stop_pdz_str[] = "Нажат Стоп ПДЗ";
    const char MSK_error_str[] = "Перемычка на МСК";
    const char fireSTR[] = "Пожар";
    const char etaz_str[] = "Этаж";
    const char net_str[] = "сеть";
    const char menu_str[] = "меню";
    const char button_str[] = "СПС";
    const char prosto_tak_str[] = "просто так";
    const char fire_section1[] = "Секция 1";
    const char fire_section2[] = "Секция 2";
    const char fire_section3[] = "Секция 3";
    const char section_str[] = "общ.";

    /* Etaz.cpp */
    const char bfpp_test_str[2][7] = {
        "Пакет:",
        "Связь:"
    };

    const char pdz_set_name_str[][16] =
    {
        "Хуйня 1",
        "Хуйня 2",
        "Хуйня 3",
    };
   
    const char norma_str[]    = "Норма";
    const char nolink_str[]   = "Не в сети";
    const char noadr_str[]    = "Адр";
    const char fire_str[]     = "Пожар сеть";
    const char firePK_str[]   = "Пожар БФПП";
    const char fireSPS_str[]  = "Пожар СПС";
    const char fireMenu_str[] = "Пожар Меню";
    const char dist_str[]     = "Дист";
    const char osh24_str[]    = "24";
    const char osh220_str[]   = "220";
    const char luch_str[]     = "Луч";
    const char kz_str[]       = "КЗ";
    const char pk_str[]       = "ПК";

    const char bfpp_str[]      = "БФПП";
	const char strStopPdz[] = " Стоп ПДЗ";

    const char str_D1M[]  = "Д1-М";
    const char str_D2M[]  = "Д2-М";
    const char str_D3M[]  = "Д3-М";
    const char str_D4M[]  = "Д4-М";
    const char str_D5M[]  = "Д5-М";
    const char str_D6M[]  = "Д6-М";
    const char str_D7M[]  = "Д7-М";
    const char str_D8M[]  = "Д8-М";
    const char str_D9M[]  = "Д9-М";
    const char str_D10M[] = "Д10-М";

    const char str_P1M[]  = "П1-М";
    const char str_P2M[]  = "П2-М";
    const char str_P3M[]  = "П3-М";
    const char str_P4M[]  = "П4-М";
    const char str_P5M[]  = "П5-М";
    const char str_P6M[]  = "П6-М";
    const char str_P7M[]  = "П7-М";
    const char str_P8M[]  = "П8-М";
    const char str_P9M[]  = "П9-М";
    const char str_P10M[] = "П10-М";
    const char str_P11M[] = "П11-М";
    const char str_P12M[] = "П12-М";

    const char str_YA26_1[] = "26УА1";
    const char str_YA26_2[] = "26УА2";
    const char str_YA26_3[] = "26УА3";
    const char str_YA26_4[] = "26УА4";
    const char str_YA26_5[] = "26УА5";
    const char str_YA26_6[] = "26УА6";

