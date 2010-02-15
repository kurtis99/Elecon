#ifndef  NLS_INC
#define  NLS_INC

#include    "struct_define.h"
#include	<MnemoColors.h>

const unsigned char NUM_OF_MNEMO = 4;

extern MNEMO_OUTPUT_STRUCT mnemo[NUM_OF_MNEMO];
extern uint8_t MSK_FIELD[];
extern outPort IoField[];

/* Всякие полезные лампочки */
#define mReady      mnemo[0].LED_FIELD[71]
#define mAvar       mnemo[0].LED_FIELD[63]
#define mNet        mnemo[0].LED_FIELD[55]
#define mPozNas     mnemo[1].LED_FIELD[71]
#define mODS        mnemo[1].LED_FIELD[47]
#define mZasuvka    mnemo[1].LED_FIELD[63]

// Fire from SPZ-1
#define mNetSpz     mnemo[1].LED_FIELD[45]

#define mD1M        mnemo[0].LED_FIELD[77] 
#define mD2M        mnemo[0].LED_FIELD[69]
#define mP1M        mnemo[0].LED_FIELD[61] 
#define mP2M        mnemo[0].LED_FIELD[53] 
#define mP3M        mnemo[0].LED_FIELD[45] 
#define mP4M        mnemo[1].LED_FIELD[77]
#define mP5M        mnemo[1].LED_FIELD[61]
#define mP6M        mnemo[1].LED_FIELD[53]

#define mYA26_1     mnemo[0].LED_FIELD[62]
#define mYA26_2     mnemo[0].LED_FIELD[54]
#define mYA26_3     mnemo[0].LED_FIELD[46]
#define mYA26_4     mnemo[1].LED_FIELD[78]
#define mYA26_5     mnemo[1].LED_FIELD[70]
#define mYA26_6     mnemo[1].LED_FIELD[62]

/*Клапана УА1*/
#define mY1_0       mnemo[2].LED_FIELD[36]
#define mY1_1       mnemo[2].LED_FIELD[37]
#define mY1_2       mnemo[2].LED_FIELD[38]
#define mY1_3       mnemo[2].LED_FIELD[39]
#define mY1_4       mnemo[2].LED_FIELD[72]
#define mY1_5       mnemo[2].LED_FIELD[73]
#define mY1_6       mnemo[2].LED_FIELD[74]
#define mY1_7       mnemo[2].LED_FIELD[75]
#define mY1_8       mnemo[2].LED_FIELD[76]
#define mY1_9       mnemo[2].LED_FIELD[77]

/*Клапана УА2*/
#define mY2_0       mnemo[2].LED_FIELD[28]
#define mY2_1       mnemo[2].LED_FIELD[29]
#define mY2_2       mnemo[2].LED_FIELD[30]
#define mY2_3       mnemo[2].LED_FIELD[31]
#define mY2_4       mnemo[2].LED_FIELD[64]
#define mY2_5       mnemo[2].LED_FIELD[65]
#define mY2_6       mnemo[2].LED_FIELD[66]
#define mY2_7       mnemo[2].LED_FIELD[67]
#define mY2_8       mnemo[2].LED_FIELD[68]
#define mY2_9       mnemo[2].LED_FIELD[69]

/*Состояние СПС*/
#define mSPS0       mnemo[3].LED_FIELD[28]
#define mSPS1       mnemo[3].LED_FIELD[29]
#define mSPS2       mnemo[3].LED_FIELD[30]
#define mSPS3       mnemo[3].LED_FIELD[31]
#define mSPS4       mnemo[3].LED_FIELD[64]
#define mSPS5       mnemo[3].LED_FIELD[65]
#define mSPS6       mnemo[3].LED_FIELD[66]
#define mSPS7       mnemo[3].LED_FIELD[67]
#define mSPS8       mnemo[3].LED_FIELD[68]
#define mSPS9       mnemo[3].LED_FIELD[69]

/* Лампочка БУПК */
#define mBUPK0      mnemo[3].LED_FIELD[12]
#define mBUPK1      mnemo[3].LED_FIELD[13]
#define mBUPK2      mnemo[3].LED_FIELD[14]
#define mBUPK3      mnemo[3].LED_FIELD[15]
#define mBUPK4      mnemo[3].LED_FIELD[48]
#define mBUPK5      mnemo[3].LED_FIELD[49]
#define mBUPK6      mnemo[3].LED_FIELD[50]
#define mBUPK7      mnemo[3].LED_FIELD[51]
#define mBUPK8      mnemo[3].LED_FIELD[52]
#define mBUPK9      mnemo[3].LED_FIELD[53]

/* Лампочка SB/SQ */
#define mSBSQ0      mnemo[3].LED_FIELD[20]
#define mSBSQ1      mnemo[3].LED_FIELD[21]
#define mSBSQ2      mnemo[3].LED_FIELD[22]
#define mSBSQ3      mnemo[3].LED_FIELD[23]
#define mSBSQ4      mnemo[3].LED_FIELD[56]
#define mSBSQ5      mnemo[3].LED_FIELD[57]
#define mSBSQ6      mnemo[3].LED_FIELD[58]
#define mSBSQ7      mnemo[3].LED_FIELD[59]
#define mSBSQ8      mnemo[3].LED_FIELD[60]
#define mSBSQ9      mnemo[3].LED_FIELD[61]

/* Лампочка БФПП */
#define mFIRE0 	    mnemo[3].LED_FIELD[ 5]
#define mFIRE1 	    mnemo[3].LED_FIELD[ 7]
#define mFIRE2 	    mnemo[3].LED_FIELD[41]
#define mFIRE3 	    mnemo[3].LED_FIELD[43]
#define mFIRE4 	    mnemo[3].LED_FIELD[44]

/*Злой и страшный дядя ВИТ*/
#define VIT_FIREFLOOR   data_for_vit.fire_floor
#define VIT_STATUS      data_for_vit.status
#define VIT_BUZZER      data_for_vit.fire_buzer
#define mNetVit         mnemo[3].LED_FIELD[ 0]

/*Описание функции порта 1*/

/* Прием МСК */
#define kFIRE1_0        MSK_FIELD[ 0]
#define kFIRE2_0        MSK_FIELD[ 1]
#define kFIRE1_1        MSK_FIELD[ 2]
#define kFIRE2_1        MSK_FIELD[ 3]
#define kFIRE1_2        MSK_FIELD[ 4]
#define kFIRE2_2        MSK_FIELD[ 5]
#define kFIRE1_3        MSK_FIELD[ 6]
#define kFIRE2_3        MSK_FIELD[ 7]

#define kFIRE1_4        MSK_FIELD[ 8]
#define kFIRE2_4        MSK_FIELD[ 9]
#define kFIRE1_5        MSK_FIELD[10]
#define kFIRE2_5        MSK_FIELD[11]
#define kFIRE1_6        MSK_FIELD[12]
#define kFIRE2_6        MSK_FIELD[13]
#define kFIRE1_7        MSK_FIELD[14]
#define kFIRE2_7        MSK_FIELD[15]

#define KFIRE23          MSK_FIELD[24]
#define KFIRE24          MSK_FIELD[25]
#define K_VVOD1          MSK_FIELD[26]
#define K_VVOD2          MSK_FIELD[27]
#define K_PK01           MSK_FIELD[28]
#define K_NASOS          MSK_FIELD[29]
#define K_TEST           MSK_FIELD[30]
#define K_STOP_PDZ       MSK_FIELD[31]

/* Выдача на МТ */
#define OP_ZVUK          IoField[ 0]
//#define OP_NULL          IoField[ 1]
#define OP_ODS_FIRE      IoField[ 2]
#define OP_ODS_ERR       IoField[ 3]
//#define OP_NULL          IoField[ 4]
//#define OP_NULL          IoField[ 5]
//#define OP_NULL          IoField[ 6]
//#define OP_NULL          IoField[ 7]
//#define OP_NULL          IoField[ 8]
//#define OP_NULL          IoField[ 9]
//#define OP_NULL          IoField[10]
//#define OP_NULL          IoField[11]
//#define OP_NULL          IoField[12]
//#define OP_NULL          IoField[13]
//#define OP_NULL          IoField[14]
//#define OP_NULL          IoField[15]

#define VIT_FIREFLOOR   data_for_vit.fire_floor
#define VIT_STATUS      data_for_vit.status
#define VIT_BUZZER      data_for_vit.fire_buzer

// Не трогать!
#define KEY_1   (Menu::KEY_wrk[0]&(1<<0))
#define KEY_2   (Menu::KEY_wrk[0]&(1<<1))
#define KEY_3   (Menu::KEY_wrk[0]&(1<<2))
#define KEY_OK  (Menu::KEY_wrk[0]&(1<<3))

#define KEY_4   (Menu::KEY_wrk[0]&(1<<4))
#define KEY_5   (Menu::KEY_wrk[0]&(1<<5))
#define KEY_6   (Menu::KEY_wrk[0]&(1<<6))
#define KEY_0   (Menu::KEY_wrk[0]&(1<<7))

#define KEY_7   (Menu::KEY_wrk[1]&(1<<0))
#define KEY_8   (Menu::KEY_wrk[1]&(1<<1))
#define KEY_9   (Menu::KEY_wrk[1]&(1<<2))
#define KEY_NO  (Menu::KEY_wrk[1]&(1<<3))

#define KEY_F1  (Menu::KEY_wrk[1]&(1<<4))
#define KEY_F2  (Menu::KEY_wrk[1]&(1<<5))
#define KEY_F3  (Menu::KEY_wrk[1]&(1<<6))
#define KEY_F4  (Menu::KEY_wrk[1]&(1<<7))

// Дубль-кнопки
#define KEY_IN  KEY_OK
#define KEY_OUT KEY_3
#define KEY_P   KEY_5
#define KEY_M   KEY_2

#define KEY_DIST    KEY_4
#define KEY_OPER    KEY_7
#define KEY_OPEN    KEY_8
#define KEY_CLSE    KEY_NO
#define KEY_ERR     KEY_1

#endif   // ----- #ifndef NLS_INC  -----
