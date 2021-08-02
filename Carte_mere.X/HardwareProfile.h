/*! \file  HardwareProfile.h
    \brief Fichier de description des ports entrees/sorties du microcontroleur

*    AI_... = Analog  Input <br />
*    DI_... = Digital Input <br />
*    DO_... = Digital Output<br />
*    IO_... = Input/Output  
*/
//-------------------------------------------------------------
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//PORT A-------------------------------------------------------

#define PUSH1   _RB4
#define VC2     _RA4
#define EN_37   LATAbits.LATA2
#define EN_29   LATAbits.LATA1
#define EN_18   LATAbits.LATA0
#define VC1     _RB1

#endif  //HARDWARE_PROFILE_H
