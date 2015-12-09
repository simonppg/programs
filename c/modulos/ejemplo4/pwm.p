//pwm.p

//Copyright (C) 2013 ADLab - http://www.analogdigitallab.org/ 

// BBB Schematic  BBB port Assign Bit
// -------------  -------- ------ ------------
// LCD_DATA0      P8.45    PWM0     PRU1_R30_0
// LCD_DATA1      P8.46    PWM1     PRU1_R30_1
// LCD_DATA2      P8.43    PWM2     PRU1_R30_2
// LCD_DATA3      P8.44    PWM3     PRU1_R30_3
// LCD_DATA4      P8.41    PWM4     PRU1_R30_4

// 5 pwm and 5 enable bits beta
// BBB Schematic  BBB port Assign       Bit
// -------------  -------- ------ ------------
// LCD_DATA0      P8.45    Enable0      PRU1_R30_0
// LCD_DATA1      P8.46    PWM0         PRU1_R30_1
// LCD_DATA2      P8.43    Enable1      PRU1_R30_2
// LCD_DATA3      P8.44    PWM1         PRU1_R30_3
// LCD_DATA4      P8.41    Enable2      PRU1_R30_4
// LCD_DATA5      P8.42    PWM2         PRU1_R30_5
// LCD_DATA6      P8.39    Eenable3     PRU1_R30_6
// LCD_DATA7      P8.40    PWM3         PRU1_R30_7
// LCD_PCLK       P8.28    Enable4      PRU1_R30_10
// LCD_HSYNC      P8.29    PWM4         PRU1_R30_9



.origin 0
.entrypoint START

#include "pwm.hp"

#define GPIO1 0x4804c000
#define GPIO_CLEARDATAOUT 0x190
#define GPIO_SETDATAOUT 0x194
#define MEM_START 0x00000100

START:

// Preamble to set up OCP and shared RAM
// Enable OCP master port
LBCO    r0, CONST_PRUCFG, 4, 4
CLR     r0, r0, 4         		// Clear SYSCFG[STANDBY_INIT] to enable OCP master port
SBCO    r0, CONST_PRUCFG, 4, 4

// Configure the programmable pointer register for PRU1 by setting c28_pointer[15:0]
// field to 0x0100.  This will make C28 point to 0x00010000 (PRU shared RAM). 
MOV     r0, 0x00000100
MOV       r1, CTPPR_0
ST32      r0, r1

MOV r0, 0x00100000 
MOV r1, CTPPR_1 
ST32 r0, r1
// End of preamble

//**************
// PWM CODE 
//**************
    mov     r6, 1    // Banderas 1 estado alto, 0 estado bajo
    mov     r7, 1
    mov     r8, 1
    mov     r9, 1
    mov     r10, 1
    SET     r30.t1                          // Turn on all output channels for start of cycle
    SET     r30.t3
    SET     r30.t5
    SET     r30.t7
    SET     r30.t9
    mov     r11, 1109;

    //desde r0 a r4 son leidos desde la memoria compartida, hay que leer otros 5 bits
	//LBCO r0,CONST_PRUDRAM,0,20  //Load in registers from shared memory (20 bytes, 4 bytes por registro r0 -> r4 )
    LBCO r0,CONST_PRUDRAM,0,24    //cargar 4 bytes mas para controlar los enables bit de cada pwm (24 bytes, 4 bytes por registro r0 -> r5)
    //dejar de utilizar r5 -> r9 y utilizar r6 -> r10
    //r5[4:0] es para enable biit de cada pwm


LOOP1:                                      // Inner loop to handle channels
        SUB     r0, r0, 1                   // Subtract one from each register
        SUB     r1, r1, 1                   // Decrementando contadores apartir del las rpm
        SUB     r2, r2, 1
        SUB     r3, r3, 1
        SUB     r4, r4, 1

        QBNE    salto1, r0, 0
        QBNE    salto1, r6, 1
        CLR     r30.t1
        mov     r6, 0
        LBCO    r0, CONST_PRUDRAM, 0, 4
salto1:
        QBNE    salto2, r0, 0
        QBNE    salto2, r6, 0
 		SET     r30.t1
 		mov     r6, 1
 		LBCO    r0, CONST_PRUDRAM, 0, 4
salto2: 
        QBNE    salto3, r1, 0
        QBNE    salto3, r7, 1
        CLR     r30.t3
        mov     r7, 0
        LBCO    r1, CONST_PRUDRAM, 4, 4
salto3:
        QBNE    salto4, r1, 0
        QBNE    salto4, r7, 0
 		SET     r30.t3
 		mov     r7, 1
 		LBCO    r1, CONST_PRUDRAM, 4, 4		
salto4: 
        QBNE    salto5, r2, 0
        QBNE    salto5, r8, 1
 		CLR     r30.t5
 		mov     r8, 0
 		LBCO    r2, CONST_PRUDRAM, 8, 4 
salto5:
        QBNE    salto6, r2, 0
        QBNE    salto6, r8, 0
 		SET     r30.t5
 		mov     r8, 1
 		LBCO    r2, CONST_PRUDRAM, 8, 4 
salto6:
        QBNE    salto7, r3, 0
        QBNE    salto7, r9, 1
        CLR     r30.t7
        mov     r9, 0
        LBCO    r3, CONST_PRUDRAM, 12, 4
salto7:
        QBNE    salto8, r3, 0
        QBNE    salto8, r9, 0
 		SET     r30.t7
 		mov     r9, 1
 		LBCO    r3, CONST_PRUDRAM, 12, 4
salto8:
        QBNE    salto9, r4, 0
        QBNE    salto9, r10, 1
        CLR     r30.t9
        mov     r10, 0
        LBCO    r4, CONST_PRUDRAM, 16, 4
salto9: 
        QBNE    salto10, r4, 0
        QBNE    salto10, r10, 0
 		SET     r30.t9
 		mov     r10, 1
 		LBCO    r4, CONST_PRUDRAM, 16, 4	
salto10:
       AND     r5, r5, r11
       NOT     r11, r11
       AND     r30, r30, r11
       OR      r30, r30, r5
       mov     r11, 1109;
       LBCO    r5,CONST_PRUDRAM, 20, 4
//Metodo por bits        
//        QBBC    enable0_0, r5.t0
//        SET     r30.t0
//        LBCO    r5,CONST_PRUDRAM, 20, 4
//enable0_0:
//         QBBS    enable0_1, r5.t0
//         CLR     r30.t0
//         LBCO    r5,CONST_PRUDRAM, 20, 4
//enable0_1:

        JMP LOOP1
    HALT            
 
