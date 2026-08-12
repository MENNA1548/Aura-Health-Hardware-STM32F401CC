#include "Std_type.h"

#include "MGPIO_Interface.h"


#include "HROW_Interface.h"
#include "HROW_Config.h"



static void HROW_voidPulseClock(void);

static void HROW_voidPulseLatch(void);



void HROW_voidInit(void)
{


    /* Configure pins */


    MGPIO_voidSetMode(
            ROW_CLK_PORT,
            ROW_CLK_PIN,
            OUTPUT);



    MGPIO_voidSetMode(
            ROW_DATA_PORT,
            ROW_DATA_PIN,
            OUTPUT);



    MGPIO_voidSetMode(
            ROW_LATCH_PORT,
            ROW_LATCH_PIN,
            OUTPUT);




    /* Output configuration */


    MGPIO_voidSetOutputConfig(
            ROW_CLK_PORT,
            ROW_CLK_PIN,
            PUSH_PULL,
            LOW_SPEED);



    MGPIO_voidSetOutputConfig(
            ROW_DATA_PORT,
            ROW_DATA_PIN,
            PUSH_PULL,
            LOW_SPEED);



    MGPIO_voidSetOutputConfig(
            ROW_LATCH_PORT,
            ROW_LATCH_PIN,
            PUSH_PULL,
            LOW_SPEED);




    /* Initial state */


    MGPIO_voidSetPinValue(
            ROW_CLK_PORT,
            ROW_CLK_PIN,
            LOW);



    MGPIO_voidSetPinValue(
            ROW_DATA_PORT,
            ROW_DATA_PIN,
            LOW);



    MGPIO_voidSetPinValue(
            ROW_LATCH_PORT,
            ROW_LATCH_PIN,
            LOW);


}






void HROW_voidSendByte(u8 Copy_u8Data)
{


    s8 Local_s8Bit;



    for(Local_s8Bit = 7 ; Local_s8Bit >=0 ; Local_s8Bit--)
    {


        MGPIO_voidSetPinValue
        (
            ROW_DATA_PORT,
            ROW_DATA_PIN,
            (Copy_u8Data >> Local_s8Bit) & 1
        );



        HROW_voidPulseClock();

    }



    HROW_voidPulseLatch();



}







void HROW_voidClear(void)
{


    HROW_voidSendByte(0x00);


}









static void HROW_voidPulseClock(void)
{

    MGPIO_voidSetPinValue(
            ROW_CLK_PORT,
            ROW_CLK_PIN,
            HIGH);



    for(volatile u32 i=0;i<50;i++);



    MGPIO_voidSetPinValue(
            ROW_CLK_PORT,
            ROW_CLK_PIN,
            LOW);

}





static void HROW_voidPulseLatch(void)
{


    MGPIO_voidSetPinValue(
            ROW_LATCH_PORT,
            ROW_LATCH_PIN,
            HIGH);



    for(volatile u32 i=0;i<50;i++);



    MGPIO_voidSetPinValue(
            ROW_LATCH_PORT,
            ROW_LATCH_PIN,
            LOW);


}
