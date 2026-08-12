#include "Std_type.h"

#include "MADC_Interface.h"
#include "MSTK_Interface.h"

#include "HHEARTBEAT_Interface.h"
#include "HHEARTBEAT_Config.h"
#include "HHEARTBEAT_Private.h"



static u32 CurrentTime = 0;

static u32 LastBeatTime = 0;


static u8 BeatDetected = 0;

static u8 BPM = 0;



void HHEARTBEAT_voidInit(void)
{

    MADC_voidInit();


    CurrentTime = 0;

    LastBeatTime = 0;

    BeatDetected = 0;

    BPM = 0;

}




u16 HHEARTBEAT_u16ReadSensor(void)
{

    return MADC_u16GetChannelReading(
            HEARTBEAT_ADC_CHANNEL);

}




u8 HHEARTBEAT_u8GetBPM(void)
{

    u16 SensorValue;

    u32 BeatPeriod;



    /* Read ADC */

    SensorValue = HHEARTBEAT_u16ReadSensor();



    /*
       Increase time
       HEARTBEAT_SAMPLE_TIME = 10 ms
    */

    CurrentTime += HEARTBEAT_SAMPLE_TIME;




    /*
       Detect rising edge
    */

    if(SensorValue > HEARTBEAT_THRESHOLD)
    {


        if(BeatDetected == 0)
        {


            /*
              Ignore first detection
            */

            if(LastBeatTime != 0)
            {


                BeatPeriod =
                CurrentTime - LastBeatTime;



                if((BeatPeriod >= HEARTBEAT_MIN_PERIOD) &&
                   (BeatPeriod <= HEARTBEAT_MAX_PERIOD))
                {

                    BPM = (u8)(60000 / BeatPeriod);

                }

            }



            LastBeatTime = CurrentTime;


            BeatDetected = 1;


        }


    }

    else
    {

        BeatDetected = 0;

    }



    return BPM;

}
