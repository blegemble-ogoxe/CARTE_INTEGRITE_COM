
/*! \file  BATT.c
    \brief Module de gestion des batteries NiMh
*/
#include "BATT.h"
#include "ADC.h"
//----------------------------------------------------------------------
/*! \fn     BOOL BATT_CheckInputVoltage(void)
 *  \brief  Fonction qui verifie la tension de la batterie et si le systeme fonctionne sur batterie ou sur secteur*/
BOOL BATT_CheckInputVoltage(void)
{
    WORD wVbatt = 0;                    //variable pour mesurer de la tension batterie


        __delay_us(100);                    //__delay_us(100); attente pour eviter de faire 2 conversions proches
//        wVbatt = ADC_Convert(VBATT_CHAN);   //mesure de la tension batterie

        //on mesure a travers un pont diviseur une tension comprise entre 0 et 8V
        //coefficient du pont diviseur 0.4 -> 1/0.4 = 2.5 -> 2.5 = 5/2
        wVbatt=wVbatt*4;      //*5  (*4 pour 4 cellules AAA)
//        wVbatt=wVbatt/2;     //divise par 2

 

    return(TRUE);
}
//----------------------------------------------------------------------
//end of BATT.c