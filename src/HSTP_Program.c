#include "Std_type.h"

#include "MGPIO_Interface.h"

#include "HSTP_Interface.h"
#include "HSTP_Config.h"


/************************************************************
                Static Functions Prototypes
************************************************************/

static void HSTP_voidPulseClock(void);
static void HSTP_voidPulseLatch(void);



/************************************************************
                    Initialize STP
************************************************************/

void HSTP_voidInit(void)
{

    /* Configure pins as Output */

    MGPIO_voidSetMode(STP_CLK_PORT,
                      STP_CLK_PIN,
                      OUTPUT);


    MGPIO_voidSetMode(STP_DATA_PORT,
                      STP_DATA_PIN,
                      OUTPUT);


    MGPIO_voidSetMode(STP_LATCH_PORT,
                      STP_LATCH_PIN,
                      OUTPUT);



    /* Output configuration */

    MGPIO_voidSetOutputConfig(STP_CLK_PORT,
                              STP_CLK_PIN,
                              PUSH_PULL,
                              LOW_SPEED);


    MGPIO_voidSetOutputConfig(STP_DATA_PORT,
                              STP_DATA_PIN,
                              PUSH_PULL,
                              LOW_SPEED);


    MGPIO_voidSetOutputConfig(STP_LATCH_PORT,
                              STP_LATCH_PIN,
                              PUSH_PULL,
                              LOW_SPEED);



    /* Initial state */

    MGPIO_voidSetPinValue(STP_CLK_PORT,
                          STP_CLK_PIN,
                          LOW);


    MGPIO_voidSetPinValue(STP_DATA_PORT,
                          STP_DATA_PIN,
                          LOW);


    MGPIO_voidSetPinValue(STP_LATCH_PORT,
                          STP_LATCH_PIN,
                          LOW);

}



/************************************************************
                    Send One Byte
************************************************************/

void HSTP_voidSendByte(u8 Copy_u8Data)
{

    s32 Local_s32Bit;


    for(Local_s32Bit = 7;
        Local_s32Bit >= 0;
        Local_s32Bit--)
    {


        /* Put bit on DATA */

        MGPIO_voidSetPinValue
        (
            STP_DATA_PORT,
            STP_DATA_PIN,
            (Copy_u8Data >> Local_s32Bit) & 0x01
        );


        /* Clock pulse */

        HSTP_voidPulseClock();

    }


    /* Update output */

    HSTP_voidPulseLatch();

}



/************************************************************
              Send Multiple Bytes
************************************************************/

void HSTP_voidSendArray(u8 *Copy_pu8Data,
                        u8 Copy_u8Size)
{

    s32 Local_s32Byte;
    s32 Local_s32Bit;



    /*
       Send last byte first
       because QH' connected to DS
    */


    for(Local_s32Byte = Copy_u8Size-1;
        Local_s32Byte >= 0;
        Local_s32Byte--)
    {



        for(Local_s32Bit = 7;
            Local_s32Bit >= 0;
            Local_s32Bit--)
        {


            MGPIO_voidSetPinValue
            (
                STP_DATA_PORT,
                STP_DATA_PIN,
                (Copy_pu8Data[Local_s32Byte] >> Local_s32Bit) & 1
            );


            HSTP_voidPulseClock();

        }

    }



    /* Update outputs */

    HSTP_voidPulseLatch();

}



/************************************************************
                    Clear Shift Register
************************************************************/

void HSTP_voidClear(void)
{

    HSTP_voidSendByte(0x00);

}



/************************************************************
                    Clock Pulse
************************************************************/

static void HSTP_voidPulseClock(void)
{

    MGPIO_voidSetPinValue
    (
        STP_CLK_PORT,
        STP_CLK_PIN,
        HIGH
    );


    for(volatile u32 i = 0; i < 200; i++);


    MGPIO_voidSetPinValue
    (
        STP_CLK_PORT,
        STP_CLK_PIN,
        LOW
    );

}



/************************************************************
                    Latch Pulse
************************************************************/

static void HSTP_voidPulseLatch(void)
{

    MGPIO_voidSetPinValue
    (
        STP_LATCH_PORT,
        STP_LATCH_PIN,
        HIGH
    );


    for(volatile u32 i = 0; i < 200; i++);


    MGPIO_voidSetPinValue
    (
        STP_LATCH_PORT,
        STP_LATCH_PIN,
        LOW
    );

}
