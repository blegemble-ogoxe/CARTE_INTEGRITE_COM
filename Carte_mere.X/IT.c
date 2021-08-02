/*! \file  IT.c
    \brief Module de gestion des interruptions
 * 6 mai 2014 : dans l'interruption _INT1Interrupt(void) on a commente la fonction reset()
 * pour permettre un fonctionnement sans coupure entre alim par batterie et alim par secteur
*/
#include "IT.h"
#include "BATT.h"
#include "GLOBAL.h"
#include "GenericTypeDefs.h"

//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _AddressError(void)
 *  \brief  Interruption sur erreur du pointeur d'adresse*/
void __attribute__((__interrupt__,no_auto_psv)) _AddressError(void)
{
    Reset();
}
//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _StackError(void)
 *  \brief  Interruption sur overflow de la pile (division par 0)*/
void __attribute__((__interrupt__,no_auto_psv)) _StackError(void)
{
    Reset();
}
//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
 *  \brief  Interruption du Timer 1 gerant le hachage*/
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
if(T1CONbits.TON==1)        // Test sur activation T1 VR
    {
        __delay_ms(1); 
    }
    TMR1 = 0;
    _T1IF = 0;
}
//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _T4Interrupt(void)
 *  \brief  Interruption du Timer 4 gerant le clignotement de la LED en charge batterie*/
void __attribute__((__interrupt__,no_auto_psv)) _T4Interrupt(void)
{

        timeractivity++; 

//**********************************************************************************
    TMR4 = 0;
    _T4IF = 0;
}
//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
 *  \brief  Interruption sur INT0 : appui detecte*/
void __attribute__((__interrupt__,no_auto_psv)) _INT0Interrupt(void)
{
 

   _INT0IF = 0;             //on desactive le flag d'interruption
}
//----------------------------------------------------------------------
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
 *  \brief  Interruption sur INT1, cable secteur branche/debranche*/
void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)    //si on branche ou debranche le secteur, on reset le dsPIC par securite
{
    _INT1IF = 0;             //on desactive le flag d'interruption
}

void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
{
__delay_ms(1); 
_INT2IF = 0; 
}


void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void)
{
    __delay_ms(100);
    unsigned int tdetect=100;     //  100*10ms=1s

    if((VC1==0)&&(ALERT_VC1==FALSE))       // Test sur activation T1 VR
    {
        l=0;
        while((VC1==0)&&(l<tdetect))
            {
                __delay_ms(10);
                l++;            
            }
        if(l>(tdetect-2))
        {
            ALERT_VC1=TRUE;
            if(compteurLV1<9999){
                compteurLV1++;
            }
        }
    }
    if((VC2==0)&&(ALERT_VC2==FALSE))         // Test sur activation T1 VR
    {
        l=0;
        while((VC2==0)&&(l<tdetect))
            {
                __delay_ms(10);
                l++;            
            }
        if(l>(tdetect-2))
        {        
            ALERT_VC2=TRUE;
            if(compteurLV2<9999){
                compteurLV2++;
            }
        }
    }
    if(VC1==1)
    {
        ALERT_VC1=FALSE;
        __delay_ms(10);

    }
    if(VC2==1)
    {
        ALERT_VC2=FALSE;
        __delay_ms(10);        
    }
    if(PUSH1==0)        // Test sur activation T1 VR
    {
        l=0;
        while((PUSH1==0)&&(l<20))
            {
                __delay_ms(100);
                l++;            
            }
            if(l>18)
            {
                BTN = 1;  
            }          
    }        
        
   
 
IFS1bits.CNIF = 0;
}

//----------------------------------------------------------------------
/*! \fn     void IT_Init(void)
 *  \brief  Initialisation des interruptions*/
void IT_Init(void)
{
    //interruption bouton (RB7, INT0)
    _INT0EP = 1;    //front descendant
    _INT0IP = 1;    //niveau 1 de priorite
    _INT0IF = 0;    //mise a 0 du flag d'interruption
    _INT0IE = 0;    //activation de l'interruption

    //interruption Flow (RA4, INT1)
    _INT1EP = 0;  //Positive edge
    _INT1IP = 1;
    _INT1IF = 0;
    _INT1IE = 0;

    //interruption Timer 1 hachage du signal
    _T1IP = 1;
    _T1IF = 0;
    _T1IE = 0;

    //interruption Timer 4 10ms activity
    _T4IP = 1;
    _T4IF = 0;
    _T4IE = 0;

    //interruption mesure Fréquence extérieure (RB9, INT2)
    _INT2EP = 1;
    _INT2IP = 1;
    _INT2IF = 0;
    _INT2IE = 0;
    
    // Interrupt on change
    
    /* Enable CN interrupts */
    CNENBbits.CNIEB1 = 1; // Enable RB1 pin for interrupt detection
    CNENAbits.CNIEA4 = 1; // Enable RA4 pin for interrupt detection
    CNENBbits.CNIEB4 = 1; // Enable RB4 pin for interrupt detection
    IEC1bits.CNIE = 1; // Enable CN interrupts
    IFS1bits.CNIF = 0; // Reset CN interrupt

}
/*! \fn     void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
 *  \brief  Interruption sur INT2, mesure fréquence extérieure*/


