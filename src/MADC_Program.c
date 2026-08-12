#include "Std_type.h"

#include "MADC_Private.h"
#include "MADC_Interface.h"
#include "MADC_Config.h"



void MADC_voidInit(void)
{

    /*
       Enable ADC
    */

    ADC1->CR2 |= (1 << ADC_CR2_ADON);



    /*
       12 bit resolution
       default = 12 bit
    */


}



u16 MADC_u16GetChannelReading(u8 Copy_u8Channel)
{


    /*
      Select Channel
      ADC channel is stored in SQR3
      for first conversion
    */


    ADC1->SQR3 &= ~(0x1F);

    ADC1->SQR3 |= Copy_u8Channel;



    /*
       Set Sample Time

       SMPR2 controls channels 0-9
    */


    ADC1->SMPR2 &=
    ~(0x7 << (Copy_u8Channel*3));


    ADC1->SMPR2 |=
    (ADC_SAMPLE_TIME << (Copy_u8Channel*3));



    /*
       Start Conversion
    */


    ADC1->CR2 |=
    (1 << ADC_CR2_SWSTART);



    /*
       Wait End Of Conversion
    */

    while(!(ADC1->SR & (1<<ADC_SR_EOC)));



    /*
       Read Data Register
    */

    return (u16)ADC1->DR;


}
