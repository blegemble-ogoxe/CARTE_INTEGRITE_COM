
/*! \file  GLOBAL.c
    \brief Affectation des variables globales
*/
#include "GLOBAL.h"


/*! \brief Variable globale indiquant s'il reste assez de tension dans les batteries pour nebuliser*/
BOOL        g_bEnoughVoltage = TRUE;

BOOL        ALERT_VC1 = FALSE;

BOOL        ALERT_VC2 = FALSE;

BOOL    BTN = FALSE;

uint16_t ADCValues[4]={0,0,0,0};


/*! \brief Variable globale pour mesure */
WORD        ADCresult=0;

/*! \brief Variable globale pour mesure flow*/
LONG        pulsecount=0;

/*! \brief Variable globale pour mesure temp*/
INT        temp=0;

/*! \brief Variable globale pour mesure batt*/
uint16_t        batt=0;

//Variables globales pour calcul taux

BYTE taux = 0;     // MAX par défaut 100%

//Variables globales pour activité

BYTE timeractivity = 0;     // MAX par défaut 100%

//Variables globales pour I2C

BYTE I2Cbyte = 0;

BYTE test = 0;  
uint8_t          compteurLV1=0;
uint8_t          compteurLV2=0;
INT          l=0;
INT          k1=0;
INT          k2=0;
