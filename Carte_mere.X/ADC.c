/*! \file  ADC.c
    \brief Module de gestion de l'Analog/Digital Converter du dsPIC
*/
#include "ADC.h"
//---------------------------------------------------------------------------------------------
/*! \fn     void ADC_Init(void)
 *  \brief  Initialisation de l'ADC*/
void ADC_Init(void)
{
    ANSELA = ANSELB = 0x0000;
    ANSELBbits.ANSB0 = 1; // Ensure AN0/RB0 is analog
    ANSELBbits.ANSB1 = 1; // Ensure AN1/RB1 is analog
    ANSELBbits.ANSB2 = 1; // Ensure AN2/RB2 is analog
    ANSELBbits.ANSB3 = 1; // Ensure AN5/RB3 is analog
    /* Initialize and enable ADC module */
    AD1CON1 = 0x000C; // Enable simultaneous sampling and auto-sample
    AD1CON2 = 0x0300; // Sample 4 channels
    AD1CON3 = 0x000F;
    AD1CON4 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0000;
    AD1CHS0bits.CH0SA = 5; // Select AN5 for CH0 +ve input
    AD1CHS0bits.CH0NA = 0; // Select Vref- for CH0 -ve input
    AD1CHS123bits.CH123SA1 = 0; // Select AN0 for CH1 +ve input
    AD1CHS123bits.CH123SA2 = 0;
    // Select AN1 for CH2 +ve input// Select AN2 for CH3 +ve input
    AD1CHS123bits.CH123NA = 0; // Select Vref- for CH1/CH2/CH3 -ve inputs
    AD1CON1bits.ADON = 1;
    __delay_us(20)
}

void ADC_Stop(void)
{
    AD1CON1bits.ADON = 0;       //Activation de l'ADC 

    ANSELAbits.ANSA4 = 0;       //RA4 configuree en IO VC2
    ANSELBbits.ANSB1 = 0;       //RB1 configuree en IO VC1
    ANSELBbits.ANSB0 = 0;       //RB0 configuree en entree analogique AN2 (VBATT) 
}
//---------------------------------------------------------------------------------------------
/*! \fn     WORD ADC_Convert(BYTE vChan)
 *  \brief  Lancement de la conversion
 *  \param  BYTE vChan : on indique ici le canal anologique a mesurer
    \return dwRes : on retourne la valeur de tension mesuree*/
void ADC_Convert()
{
    __delay_us(100); // Sample for 100 us
    AD1CON1bits.SAMP = 0; // Start the conversions
    while (!_AD1IF); // Wait for all 4 conversions to complete
    _AD1IF = 0; // Clear conversion done status bit
    ADCValues[0] = ADC1BUF0; // Read the AN5 conversion result
    ADCValues[1] = ADC1BUF1; // Read the AN0 conversion result
    ADCValues[2] = ADC1BUF2; // Read the AN1 conversion result
    ADCValues[3] = ADC1BUF3; // Read the AN2 conversion result
}
//---------------------------------------------------------------------------------------------
//end of ADC.c
