/*! \file  ADC.h
    \brief Fichier d'entete ADC*/
#ifndef ADC_H
#define	ADC_H

#include "GLOBAL.h"

/*! \brief Canal analogique AN3 */
#define VC1_CHAN     3

/*! \brief Canal analogique AN24 */
#define VC2_CHAN          24


/*! \brief Canal analogique AN2 mesurant la température*/
#define VBATT_CHAN          2

void ADC_Init(void);
void ADC_Stop(void);
void ADC_Convert();

#endif	//ADC_H

