/*! \file  main.c
    \brief Boucle d'execution principale
*/
#include "Compiler.h"

#include "HardwareProfile.h"
#include "ADC.h"
#include "I2C.h"
#include "IT.h"
#include "IO.h"
#include "BATT.h"


//----------------------------------------------------------------------

// DSPIC33EV256GM002 Configuration Bit Settings

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect Bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSS2 = OFF               // Boot Segment Control Bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect Bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect Bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = DISABLE        // Alternate Interrupt Vector Table Disable Bit  (Disable Alternate Vector Table)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Code Flash Page Address Limit Bits (Enter Hexadecimal value)

// FOSCSEL
#pragma config FNOSC = FRC              // Initial oscillator Source Selection Bits (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two Speed Oscillator Start-Up Bit (Start up device with user selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select Bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin I/O Function Enable Bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration Bit (Allow Only One reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode Bits (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Enable Bit (Clock switch to PLL source will wait until the PLL lock signal is valid)

// FWDT
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128) --> 4ms
#pragma config WDTPOST = PS1024          // Watchdog Timer Postscaler bits (1:512) 512*4ms = 2048ms
#pragma config FWDTEN = OFF             // Watchdog Timer Enable Bits (WDT and SWDTEN Disabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable Bit (Watchdog timer in Non-Window Mode)
#pragma config WDTWIN = WIN25           // Watchdog Window Select Bits (WDT Window is 25% of WDT period)

// FPOR
#pragma config BOREN0 = OFF             // Brown Out Reset Detection Bit (BOR is Disabled)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select Bits (Communicate on PGEC1 and PGED1)

// FDMTINTVL
#pragma config DMTIVTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Window Interval (Enter Hexadecimal value)

// FDMTINTVH
#pragma config DMTIVTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Window Interval (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Enter Hexadecimal value)

// FDMT
#pragma config DMTEN = ENABLE           // Dead Man Timer Enable Bit (Dead Man Timer is Enabled and cannot be disabled by software)

// FDEVOPT
#pragma config PWMLOCK = ON             // PWM Lock Enable Bit (Certain PWM registers may only be written after key sequence)
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pins Selection Bit (I2C1 mapped to SDA1/SCL1 pins)

// FALTREG
#pragma config CTXT1 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 1 (Not Assigned)
#pragma config CTXT2 = NONE             // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 2 (Not Assigned)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <math.h>

unsigned char i=0;
unsigned short  j=0;
unsigned short  k=0;
uint8_t unites;
uint8_t dizaines;
uint8_t centaines;
uint8_t milliers;
uint16_t ndivis=0;
uint16_t rpm=0;
uint16_t ndecomp=0;

uint8_t ogoxe[7]={0x40,'O','G','O','X','E',0};
uint8_t set_dram5[2]={0x00,0x85};
uint8_t set_dramL2[2]={0x00,0xC0};
uint8_t dat1[2]={0x00,0b00111000};
uint8_t dat2[8]={0x00,0b00111001,0b00010100,0b01111001,0b01010000,0b01101100,0b00001100,0b00000001};
uint8_t alerte1[17]={0x40,'A','L','E','R','T','E',' ','I','N','P','U','T',' ','1',' ','!'};
uint8_t alerte2[17]={0x40,'A','L','E','R','T','E',' ','I','N','P','U','T',' ','2',' ','!'};
uint8_t alerte12[17]={0x40,'A','L','E','R','T','E',' ','I','N','P','U','T','1','&','2','!'};
uint16_t address = 0b0111110;
uint8_t clear[2]={0x00,0x01};  
uint8_t off[2]={0x00,0x08};
uint8_t on[2]={0x00,0x0C};
uint8_t Display_ADC_resutlt1[14]={0x40,'I','N','P','U','T','1','=',' ',' ',' ',' ','m','V'};
uint8_t Display_ADC_resutlt2[14]={0x40,'I','N','P','U','T','2','=',' ',' ',' ',' ','m','V'};
uint8_t display_LV1[15]={0x40,'C','o','m','p','t','e','u','r','1',':',' ',' ',' ',' '}; 
uint8_t display_LV2[15]={0x40,'C','o','m','p','t','e','u','r','2',':',' ','0',' ',' '}; 
uint8_t out1_off[17]={0x40,'T','u','r','n','i','n','g',' ','O','F','F',' ','O','U','T','1'};
uint8_t out2_off[17]={0x40,'T','u','r','n','i','n','g',' ','O','F','F',' ','O','U','T','2'};
uint8_t stop[15]={0x40,'S','T','O','P',':','H','o','l','d',' ','B','T','N','1'};
uint8_t display_batt[12]={0x40,'B','A','T','T',':',' ',' ','.',' ',' ','V'};
uint8_t batt_good[5]={0x40,'G','O','O','D'};
uint8_t batt_low[5]={0x40,'L','O','W',' '};
I2C1_MESSAGE_STATUS statusI2C1 = I2C1_MESSAGE_PENDING;

// 				PROTOTYPES			     //

void    mesurebatt();
void ST7032i_Init(){
    
    __delay_ms(30);
    I2C1_MasterWrite(dat1,2,address,&statusI2C1);
    //while(statusI2C1!=0x0002){};
    __delay_ms(30);
    I2C1_MasterWrite(dat2,8,address,&statusI2C1);
    //PORTBbits.RB4 = 0; // 5V Enable
}
void	decomposition(uint16_t rpm)
{
	unites=0;
	dizaines=0;
	centaines=0;
    milliers=0;
	ndivis=0;

	ndecomp=rpm;
	if (ndecomp>=1)
	{
        ndivis=ndecomp/10;
        unites=rpm-(floor(ndivis)*10);
	}

	ndecomp=(floor(ndivis));
	if (ndecomp>=1)
	{
        ndivis=ndecomp/10;
        dizaines=ndecomp-(floor(ndivis)*10);
	}

	ndecomp=(floor(ndivis));
	if (ndecomp>=1)
	{
        ndivis=ndecomp/10;
        centaines=ndecomp-(floor(ndivis)*10);
	}	
    
    ndecomp=(floor(ndivis));
	if (ndecomp>=1)
	{
        ndivis=ndecomp/10;
        milliers=ndecomp-(floor(ndivis)*10);
	}	
    
    unites+=0x30;
	dizaines+=0x30;
	centaines+=0x30;
    milliers+=0x30;
}
#pragma code


void   mesurebatt()
{
	ADC_Convert();
	batt=ADCValues[3];
}


//----------------------------------------------------------------------
/*! \fn     int main(void)
 *  \brief  Fonction principale*/
int main()
{


    IO_Init();                          //Initialisation entrees/sorties (a appeler avant ADC Init !)
    IT_Init();                          //Initialisation interruptions
     
    I2C1_Initialize();
    __delay_ms(40);
    ST7032i_Init();
    __delay_ms(500);    
    PORTBbits.RB12 = 1; // BACKLIGHT LCD ON
    I2C1_MasterWrite(on,2,address,&statusI2C1);
    __delay_ms(200); 
    I2C1_MasterWrite(set_dram5,2,address, &statusI2C1);
    __delay_ms(200); 
    I2C1_MasterWrite(ogoxe,7,address, &statusI2C1);             
    __delay_ms(2000);     
    I2C1_MasterWrite(clear,2,address, &statusI2C1); 
    __delay_ms(200);     
    I2C1_MasterWrite(off,2,address, &statusI2C1); 
    PORTBbits.RB12 = 0; // BACKLIGHT LCD ON
    EN_18=1;
    __delay_ms(100);    
    EN_29=1;
    EN_37=0;
    
    
    //Boucle principale
    while(i==0)
    {    
        if (ALERT_VC1==TRUE) //*********************PRE ALERTE
        {       
            PORTBbits.RB13=0; //Sélection carte SD slot J2 
            EN_37=1; // Activation du module LTE et envoi première salve messages            
            __delay_ms(1000);
            k1++;
        }
        
        
        if (ALERT_VC2==TRUE) //*********************ALERTE
        {
            if(ALERT_VC1==1){
                EN_37=0;
                ALERT_VC1=0;
                __delay_ms(3000);                
            }
            PORTAbits.RA3=1;    //Mise en route sirène           
            PORTBbits.RB13=1; //Sélection carte SD slot J3 
            k2++;
            EN_37=1;
            __delay_ms(1000);             
        }        
        
        if(BTN){
            switch(ALERT_VC2){
                case TRUE : 
                    PORTAbits.RA3=0;    //stop sirène
                    ALERT_VC2 = 0;
                    ALERT_VC1 = 0;
                    BTN = 0;
                    break;
                case FALSE : 
                    decomposition(compteurLV1);
                    display_LV1[11]=milliers;
                    display_LV1[12]=centaines;
                    display_LV1[13]=dizaines;
                    display_LV1[14]=unites;
                    
                    decomposition(compteurLV2);
                    display_LV2[11]=milliers;
                    display_LV2[12]=centaines;
                    display_LV2[13]=dizaines;
                    display_LV2[14]=unites;
                    
                    PORTBbits.RB12 = 1; // BACKLIGHT LCD ON
                    I2C1_MasterWrite(on,2,address,&statusI2C1);
                    __delay_ms(200); 
                    I2C1_MasterWrite(display_LV1,15,address, &statusI2C1);
                    __delay_ms(200); 
                    I2C1_MasterWrite(set_dramL2,2,address, &statusI2C1);
                    __delay_ms(200); 
                    I2C1_MasterWrite(display_LV2,15,address, &statusI2C1);       
                    __delay_ms(2000);   
                     
                    
                    CNENBbits.CNIEB1 = 0; // Enable RB1 pin for interrupt detection
                    CNENAbits.CNIEA4 = 0; // Enable RA4 pin for interrupt detection
                    CNENBbits.CNIEB4 = 0; // Enable RB4 pin for interrupt detection
                    ADC_Init();
                    mesurebatt();
                    batt*=3.032;
                    ADC_Stop();
                    decomposition(batt);
                    display_batt[10] = unites;
                    display_batt[9] = dizaines;
                    display_batt[7] = centaines;
                    display_batt[6] = milliers;
                    I2C1_MasterWrite(clear,2,address, &statusI2C1);
                    __delay_ms(200); 
                    I2C1_MasterWrite(display_batt,12,address, &statusI2C1);  
                    __delay_ms(20);
                    I2C1_MasterWrite(set_dramL2,2,address, &statusI2C1);
                    __delay_ms(20);
                    if(batt>=1200) I2C1_MasterWrite(batt_good,5,address, &statusI2C1); 
                    else I2C1_MasterWrite(batt_low,5,address, &statusI2C1);
                    __delay_ms(2000);   
                    I2C1_MasterWrite(clear,2,address, &statusI2C1);
                    __delay_ms(200); 
                    I2C1_MasterWrite(off,2,address, &statusI2C1);                    
                    PORTBbits.RB12 = 0; // BACKLIGHT LCD ON
                    BTN = 0;
                    CNENBbits.CNIEB1 = 1; // Enable RB1 pin for interrupt detection
                    CNENAbits.CNIEA4 = 1; // Enable RA4 pin for interrupt detection
                    CNENBbits.CNIEB4 = 1; // Enable RB4 pin for interrupt detection
                    break;
                default : 
                    BTN = 0;
                    break;
            }
        }
        if(k1>60){//1 minute depuis EN_37=1
            EN_37 = 0;
            k1=0;
            ALERT_VC1 = 0;
        }
        if(k2>60){//1 minute depuis EN_37=1
            EN_37 = 0;
            k2=0;
            PORTAbits.RA3=0;
            ALERT_VC2 = 0;
        }
        
        if(ALERT_VC1==FALSE && ALERT_VC2==FALSE){            
            EN_37=0;
            PORTAbits.RA3=0;
            Sleep();
            
        }
    }
    return 0;
}
//----------------------------------------------------------------------
//end of main.c
