#include	<Etaz1.h>

// Возвращаем количество обслуживаемых этажей
uint8_t EtazItem1::num_of_floors()
{
    return 1;
}

uint8_t EtazItem1::getErrorPacket()
{
    return cBfppClass.get_error_packet();
}

uint8_t EtazItem1::getSendAddress()
{
    return cBfppClass.get_send_adr();
}

#define BFPP_INFO ((NET_BFPP_INPUT_STRUCT *) cBfppClass.Get_Psend_arr())

void EtazItem1::CheckBfpp()
{
    status = 0;

    if (getErrorPacket() > 10) {
        status |= NETWORK_ERROR;
        return;
    }
    else {
        status &= ~NETWORK_ERROR;
    }

    if ((0xB0 + (BFPP_INFO->dip & 0x1f)) == BFPP_INFO->head.adr) {
        status &= ~ADDRESS_ERROR;
    }
    else {
        status |= ADDRESS_ERROR;
        return;
    }

    if ((BFPP_INFO->dip) & (1 << 7)) {
        status &= ~DIST_ERROR;
    }
    else {
        status |= DIST_ERROR;
        return;
    }

    if (BFPP_INFO->status & (1<<4)) {
        status |= ERROR_220V;
        return;
    }
    else {
        status &= ~ERROR_220V;
    }

    if (BFPP_INFO->msk1 & ((1 << 4)|(1 << 5))) {
        status |= KZ_ERROR;
        return;
    }
    else {
        status &= ~KZ_ERROR;
    }
}

uint8_t EtazItem1::EtazDrv()
{
    show_mnem();

    if (kFireSPS1)
        floor1.set_fire(FromSPS);

    if (status) {
        // Если работоспособность БФПП под вопросом, то тогда убираем
        // отображение информации и выходим.
        floor1.screen_off();
        return 0xFF; // TODO: подумать. По идее мы должны вернуть
                    // значение, которое будет выведено на порты БФПП
                    // так что возвращать какую-то ерунду по идее не
                    // правильно, но ситуация у нас аварийная, значит
                    // БФПП не должен ничего делать (???)
                    //
                    // или сделать goto куда-то вниз (???)
    }

    /* "Пожар" от кнопок на этаже */
    if (BFPP_INFO->msk1 & BFPP_FIRE_FLOOR1)
        floor1.set_fire(FromPK);

    /* "Пожар" */
    YA_WorkDrv();                // Обработка состояние клапанов
    BUPK_WorkDrv();              // Светим БУПК
    SBSQ_WorkDrv();              // какая-то хрень о_О

    // Светодиод состояния связи, должен постоянно моргать (изменять
    // свое состояние)
    out ^= HL0;

    if (floor1.have_fire()) {
        drv_YA1();
    }

    return out;
}

void EtazItem1::show_mnem()
{
    uint8_t temp = GREEN_LAMP;

    switch (status) {
        case ERROR_220V:
            temp = B_YELLOW_LAMP;
            break;

        case NETWORK_ERROR:
            temp = YELLOW_LAMP;
            break;

        case ADDRESS_ERROR:
            temp = YELLOW_LAMP;
            break;

        case DIST_ERROR:
            temp = B_YELLOW_LAMP;
            break;

        case KZ_ERROR:
            temp = B_YELLOW_LAMP;
            break;

        default:
            temp = GREEN_LAMP;
            break;
    }				// -----  end switch  -----

    if (floor1.have_fire()) {
        temp = B_RED_LAMP;
    }

    FireMnemo = temp;
}

uint8_t EtazItem1::get_current_floor()
{
    return CurrentFloor;
}

// Выбираем следующий этаж
// Суть в вот в чем, на одном БФПП может быть несколько этажей, и каждый
// отдельный класс БФПП может делать перебор либо по всем своим этажам,
// либо если у него нету этажей (или все этажи уже перебрали) то
// работает со следующим БФПП
//void EtazItem1::increment()
//{
    //if (CurrentBfppFloor.floor_counter) {
        //CurrentBfppFloor.floor_counter = 0;
        //++CurrentBfppFloor.bfpp_counter;
        //++CurrentFloor;
        //if (CurrentBfppFloor.bfpp_counter >= number_of_created_devices) {
            //CurrentBfppFloor.bfpp_counter = 0;
            //CurrentFloor = 0;
        //}
    //} else {
        //CurrentBfppFloor.floor_counter = 1;
        //++CurrentFloor;
    //}
//}
/*
TODO:
    Создаются лишние копии объектов, нужно как-то переиначить
*/
uint8_t EtazItem1::return_CurrentFloor()
{
    return CurrentFloor;
}
BfppFloorCounter EtazItem1::return_CurrentBfppFloor()
{
    return CurrentBfppFloor;
}

void EtazItem1::set_next_fire_floor(BfppFloorCounter & bfpp_counter)
{
    // TODO: Продумать ситуацию, когда когда bfpp_counter.fire_floor
    // будет больше (меньше) максимально возможного значения этажности
    // для данного класса
    //
    // мне кажется, что должно быть как-то так
    //
    if (bfpp_counter.floor_counter >= num_of_floors())
        bfpp_counter.floor_counter = num_of_floors() - 1;

    if (KEY_5) {
        bfpp_counter.floor_counter = 0;
        bfpp_counter.bfpp_counter++;
        if (bfpp_counter.bfpp_counter >= number_of_created_devices)
            bfpp_counter.bfpp_counter = 0;
    }
    if (KEY_2) {
        bfpp_counter.floor_counter = 0xFF;
        if (!bfpp_counter.bfpp_counter)
            bfpp_counter.bfpp_counter = number_of_created_devices - 1;
        else
            bfpp_counter.bfpp_counter--;
    }
}//end

void EtazItem1::show_menu(uint8_t cur_floor)
{
    LCD.init();
    LCD << bfpp_str << (BfppCount.bfpp_counter + 1) << ':';
    if (status == 0)
        LCD << norma_str;
    if (status & NETWORK_ERROR)
        LCD << nolink_str;
    if (status & ERROR_220V)
        LCD << osh220_str;
    if (status & ADDRESS_ERROR)
        LCD << noadr_str;
    if (status & DIST_ERROR)
        LCD << dist_str;
    if (status & KZ_ERROR)
        LCD << kz_str;

    LCD.newLine();

    switch (BfppCount.floor_counter) {
        case 0:
            floor1.show_lcd(cur_floor+1);
            break;

        default:
            break;
    }				// -----  end switch  -----
}

/* Возвращаем номер этажа на котором ты делаем пожар */
uint8_t EtazItem1::set_fire(eFireSource state)
{
    switch (BfppCount.floor_counter) {
        case 0:
            floor1.set_fire(state);
            return 1;
            break;

        default:
        return 0;
            break;
    }
    return 0;
}

void EtazItem1::drv_YA1()
{
    /* Через 3 секунды нужно отключить напряжение на клапанах */
    if (!sec_tik)
        poweroff_counter++;

    switch (poweroff_counter) {
        /* сигнал на открытие первого клапана */
        case 0 ... 3:
            out &= ~(OUT_BFPP1|HL1);
            out |= OUT_BFPP2;
            break;

        /* сигнал на открытие второго клапана */
        case 4 ... 6:
            out &= ~(OUT_BFPP2|HL1);
            out |= OUT_BFPP1;
            break;

        /* снимаем все сигналы управления */
        default:
            out |= OUT_BFPP1|OUT_BFPP2;
            /* Нужно убедиться что переменная не переполниться */
            poweroff_counter = 10;
            break;
    }
}

void EtazItem1::YA_WorkDrv()
{
    BFPP_INFO->msk1 & (1 << 0) ? floor1.set_event(Closed ,YA1) : \
                                 floor1.set_event(Opened ,YA1);
    if (BFPP_INFO->status & (1 << 0)) floor1.set_event(Error, YA1);

    BFPP_INFO->msk1 & (1 << 1) ? floor1.set_event(Closed ,YA2) : \
                                 floor1.set_event(Opened ,YA2);
    if (BFPP_INFO->status & (1 << 1)) floor1.set_event(Error, YA2);

    //BFPP_INFO->msk1 & (1 << 2) ? floor2.set_event(Closed ,YA1) : \
        //floor2.set_event(Opened ,YA1);
    //if (BFPP_INFO->status & (1 << 2)) floor2.set_event(Error, YA1);

    //BFPP_INFO->msk1 & (1 << 3) ? floor2.set_event(Closed ,YA2) : \
        //floor2.set_event(Opened ,YA2);
    //if (BFPP_INFO->status & (1 << 3)) floor2.set_event(Error, YA2);
}

void EtazItem1::BUPK_WorkDrv()
{
    floor1.set_event(PkNormal);

    if (BFPP_INFO->msk2 & (1 << 0)) floor1.set_event(PkNoPower);
    /*TODO: Эта строка будет закомментированна из-за того что на
     * полигоне сломался переключатель на БФПП, и оно постоянно выдает
     * ошибку, лампочка моргает, я нервничаю. Убрал, в финальной версии
     * строчку нужно раскомментировать а этот комментарий удалить */
    //if (BFPP_INFO->msk2 & (1 << 1)) floor2.set_event(PkNoPower);

    if (!(BFPP_INFO->msk2 & (1 << 5))) {
        floor1.set_event(PkIsOpen);
    }
}

void EtazItem1::SBSQ_WorkDrv()
{
    floor1.set_event(SBSQNormal);

    if (BFPP_INFO->msk2 & (1 << 6)) floor1.set_event(OpenPKDoor);

    if (!(BFPP_INFO->msk2 & (1 << 4))) {
        floor1.set_event(StartNasosFromPK);
    }
}

/* Вызывается если была нажата кнопка "СТОП ПДЗ". Осбнуляет текущее
 * состояние БФПП и сбрасывает пожарные этажи для  */
void EtazItem1::doStopPdz()
{
    StartUp();

    floor1.doStopPdz();
}
