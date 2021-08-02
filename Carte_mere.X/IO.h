/*! \file  IO.h
    \brief Fichier d'entete IO
*/
#ifndef IO_H
#define	IO_H

/*! \brief LED eteinte*/
#define OFF     0

/*! \brief LED rouge*/
#define RED     1

/*! \brief LED verte*/
#define BLUE   2

/*! \brief LED orange*/
#define ORANGE  3

#include "GLOBAL.h"
#include "HardwareProfile.h"

void IO_Init(void);
void IO_LED_SetColor(BYTE vColor);
void IO_LED_SetColorBlink(BYTE vColor,BYTE vNbBlink);
void IO_BUZ_Bip(WORD wTms,BYTE vNbBip);

#endif	/* IO_H */

