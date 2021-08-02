
/*! \file  IO.c
    \brief Module de gestion des entrees/sorties standards
*/
#include "IO.h"
//-------------------------------------------------
/*! \fn     void IO_Init(void)
 *  \brief  Initialisation des entrees/sorties*/
void IO_Init(void)
{
    ANSELA = 0x0000;    //Entrees analogiques desactivees sur PORTA
    ANSELB = 0x0000;    //Entrees analogiques desactivees sur PORTB

    //affectation des entrees/sorties des PORTs du dsPIC (1 = entree / 0 = sortie)
    _TRISA0  = 0;   //1.8V EN
    _TRISA1  = 0;   //2.95V EN
    _TRISA2  = 0;   //3.7V EN
    _TRISA3  = 0;   //Sounder à la place LVC1
    _TRISA4  = 1;   //VC2

    _TRISB0  = 1;   //Vbatt
    _TRISB1  = 1;   //LVC1 à la place sounder
    _TRISB2  = 1;   //PGC
    _TRISB3  = 1;   //PGD
    _TRISB4  = 1;   //PUSH button
    _TRISB5  = 0;   //SDA2
    _TRISB6  = 0;   //SCL2
    _TRISB7  = 0;   //SCK
    _TRISB8  = 0;   //SDO
    _TRISB9  = 1;   //SDI
    _TRISB10 = 0;   //LED Digital
    _TRISB11 = 0;   //LED LOAD
    _TRISB12 = 0;   //LED CLK
    _TRISB13 = 0;   //MUX1
    _TRISB14 = 0;   //MUX2
    _TRISB15 = 1;   //EXT IN


//    RPINR0bits.INT1R   = 0x14;     //relier INT1 à RPI20 (RA4) (cf datasheet p176) pour utiliser l'entree RA4 en interruption
    
}

//-------------------------------------------------
//end of IO.c