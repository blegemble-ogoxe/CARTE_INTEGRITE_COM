/*! \file  GLOBAL.h
    \brief Description des variables globales
*/
#ifndef GLOBAL_H
#define	GLOBAL_H

/*! \brief Frequence CYcle a 4MHz pour l'utilisation des delais*/
#define FCY 3685000UL

#include "libpic30.h"

#include "Compiler.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"

extern BOOL         g_bEnoughVoltage;
extern uint16_t ADCValues[4];
extern BOOL        ALERT_VC1;
extern BOOL        ALERT_VC2;
extern BOOL        BTN;
extern BOOL       cycleNOT;
extern WORD         ADCresult;
extern LONG         pulsecount;
extern INT          temp;
extern uint8_t          compteurLV1;
extern uint8_t          compteurLV2;
extern INT          l;
extern INT          k1;
extern INT          k2;
extern uint16_t          batt;

extern BYTE        taux;
extern BYTE        timeractivity;
extern BYTE        I2Cbyte;
extern BYTE        test;

#endif	//GLOBAL_H

