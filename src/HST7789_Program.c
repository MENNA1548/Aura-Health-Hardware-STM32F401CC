//#include "Std_type.h"
//
//#include "MGPIO_Interface.h"
//#include "MSPI_Interface.h"
//#include "MSTK_Interface.h"
//
//#include "HST7789_Interface.h"
//#include "HST7789_Config.h"
//#include "HST7789_Private.h"
//
///* Private Functions */
//static void HST7789_voidReset(void);
//static void HST7789_voidWriteCommand(u8 Copy_u8Command);
//static void HST7789_voidWriteData(u8 Copy_u8Data);
//static void HST7789_voidWriteColor(u16 Copy_u16Color);
//static void HST7789_voidSetAddress(u16 X1,u16 Y1,u16 X2,u16 Y2);
//
///***********************************************************
//                        TFT Initialization
//***********************************************************/
//void HST7789_voidInit(void)
//{
//
//    HST7789_voidReset();
//
//
//    HST7789_voidWriteCommand(0x01); // Software reset
//    MSTK_voidSetBusyWait(5000000);
//
//
//
//    HST7789_voidWriteCommand(0x11); // Sleep out
//    MSTK_voidSetBusyWait(5000000);
//
//
//
//    HST7789_voidWriteCommand(0x3A); // Color mode
//    HST7789_voidWriteData(0x55);
//
//
//
//    HST7789_voidWriteCommand(0x36); // Rotation
//    HST7789_voidWriteData(0x00);
//
//
//
//    HST7789_voidWriteCommand(0x29); // Display ON
//    MSTK_voidSetBusyWait(5000000);
//
//}
//
///***********************************************************
//                        Reset TFT
//***********************************************************/
//static void HST7789_voidReset(void)
//{
//
//    MGPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,HIGH);
//
//    MSTK_voidSetBusyWait(100000);
//
//
//    MGPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,LOW);
//
//    MSTK_voidSetBusyWait(2000000);
//
//
//    MGPIO_voidSetPinValue(TFT_RST_PORT,TFT_RST_PIN,HIGH);
//
//    MSTK_voidSetBusyWait(5000000);
//
//}
///***********************************************************
//                    Send Command
//***********************************************************/
//static void HST7789_voidWriteCommand(u8 Copy_u8Command)
//{
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
//
//    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,LOW);
//
//
//    MSPI_u8Transcieve(Copy_u8Command);
//
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
//}
///***********************************************************
//                    Send Data
//***********************************************************/
//static void HST7789_voidWriteData(u8 Copy_u8Data)
//{
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
//
//    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
//
//
//    MSPI_u8Transcieve(Copy_u8Data);
//
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
//
//}
//
///***********************************************************
//                    Send RGB565 Color
//***********************************************************/
////static void HST7789_voidWriteColor(u16 Copy_u16Color)
////{
////    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
////    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
////
////    MSPI_u8Transcieve(Copy_u16Color >> 8);
////    MSPI_u8Transcieve(Copy_u16Color & 0xFF);
////
////    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
////}
//static void HST7789_voidWriteColor(u16 Color)
//{
//    MSPI_u8Transcieve(Color >> 8);
//    MSPI_u8Transcieve(Color & 0xFF);
//}
///***********************************************************
//                    Set Drawing Area
//***********************************************************/
//static void HST7789_voidSetAddress(
//        u16 X1,
//        u16 Y1,
//        u16 X2,
//        u16 Y2)
//{
//    HST7789_voidWriteCommand(ST7789_CASET);
//
//    HST7789_voidWriteData(X1 >> 8);
//    HST7789_voidWriteData(X1);
//
//    HST7789_voidWriteData(X2 >> 8);
//    HST7789_voidWriteData(X2);
//
//    HST7789_voidWriteCommand(ST7789_RASET);
//
//    HST7789_voidWriteData(Y1 >> 8);
//    HST7789_voidWriteData(Y1);
//
//    HST7789_voidWriteData(Y2 >> 8);
//    HST7789_voidWriteData(Y2);
//
//    HST7789_voidWriteCommand(ST7789_RAMWR);
//}
//
///***********************************************************
//                    Draw One Pixel
//***********************************************************/
////void HST7789_voidDrawPixel(
////        u16 X,
////        u16 Y,
////        u16 Color)
////{
////    if((X >= TFT_WIDTH) || (Y >= TFT_HEIGHT))
////        return;
////
////    HST7789_voidSetAddress(X,Y,X,Y);
////
////    HST7789_voidWriteColor(Color);
////}
//void HST7789_voidDrawPixel(u16 X,u16 Y,u16 Color)
//{
//    if(X>=TFT_WIDTH || Y>=TFT_HEIGHT)
//        return;
//
//    HST7789_voidSetAddress(X,Y,X,Y);
//
//    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
//
//    HST7789_voidWriteColor(Color);
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
//}
///***********************************************************
//                    Fill Entire Screen
//***********************************************************/
////void HST7789_voidFillScreen(u16 Color)
////{
////    u32 Counter;
////
////
////    HST7789_voidSetAddress(
////            0,
////            0,
////            TFT_WIDTH-1,
////            TFT_HEIGHT-1
////    );
////
////
////    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
////
////    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
////
////
////    for(Counter=0; Counter<(TFT_WIDTH*TFT_HEIGHT); Counter++)
////    {
////        HST7789_voidWriteColor(Color);
////    }
////
////
////    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
////
////}
//void HST7789_voidFillScreen(u16 Color)
//{
//    u32 i;
//
//    HST7789_voidSetAddress(0,0,TFT_WIDTH-1,TFT_HEIGHT-1);
//
//    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
//
//    for(i=0;i<(TFT_WIDTH*TFT_HEIGHT);i++)
//    {
//        HST7789_voidWriteColor(Color);
//    }
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
//}
////void HST7789_voidFillRectangle(u16 X, u16 Y, u16 Width, u16 Height, u16 Color)
////{
////    u32 i;
////    u32 Size = (u32)Width * Height;
////
////    HST7789_voidSetAddress(
////        X,
////        Y,
////        X + Width - 1,
////        Y + Height - 1
////    );
////
////    for(i = 0; i < Size; i++)
////    {
////        HST7789_voidWriteData(Color >> 8);
////        HST7789_voidWriteData(Color & 0xFF);
////    }
////}
//void HST7789_voidFillRectangle(u16 X,u16 Y,u16 Width,u16 Height,u16 Color)
//{
//    u32 i;
//    u32 Size=(u32)Width*Height;
//
//    HST7789_voidSetAddress(X,Y,X+Width-1,Y+Height-1);
//
//    MGPIO_voidSetPinValue(TFT_DC_PORT,TFT_DC_PIN,HIGH);
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,LOW);
//
//    for(i=0;i<Size;i++)
//    {
//        HST7789_voidWriteColor(Color);
//    }
//
//    MGPIO_voidSetPinValue(TFT_CS_PORT,TFT_CS_PIN,HIGH);
//}
//const u8 Font5x7[][5]=
//{
//{0x00,0x00,0x00,0x00,0x00}, // Space
//{0x00,0x00,0x5F,0x00,0x00}, // !
//{0x3E,0x51,0x49,0x45,0x3E}, // 0
//{0x00,0x42,0x7F,0x40,0x00}, // 1
//{0x42,0x61,0x51,0x49,0x46}, // 2
//{0x21,0x41,0x45,0x4B,0x31}, // 3
//{0x18,0x14,0x12,0x7F,0x10}, // 4
//{0x27,0x45,0x45,0x45,0x39}, // 5
//{0x3C,0x4A,0x49,0x49,0x30}, // 6
//{0x01,0x71,0x09,0x05,0x03}, // 7
//{0x36,0x49,0x49,0x49,0x36}, // 8
//{0x06,0x49,0x49,0x29,0x1E}, // 9
//
//{0x7E,0x11,0x11,0x11,0x7E}, // A
//{0x7F,0x49,0x49,0x49,0x36}, // B
//{0x3E,0x41,0x41,0x41,0x22}, // C
//{0x7F,0x41,0x41,0x22,0x1C}, // D
//{0x7F,0x49,0x49,0x49,0x41}, // E
//{0x7F,0x09,0x09,0x09,0x01}, // F
//{0x3E,0x41,0x49,0x49,0x7A}, // G
//{0x7F,0x08,0x08,0x08,0x7F}, // H
//{0x00,0x41,0x7F,0x41,0x00}, // I
//{0x20,0x40,0x41,0x3F,0x01}, // J
//{0x7F,0x08,0x14,0x22,0x41}, // K
//{0x7F,0x40,0x40,0x40,0x40}, // L
//{0x7F,0x02,0x04,0x02,0x7F}, // M
//{0x7F,0x04,0x08,0x10,0x7F}, // N
//{0x3E,0x41,0x41,0x41,0x3E}, // O
//{0x7F,0x09,0x09,0x09,0x06}, // P
//{0x3E,0x41,0x51,0x21,0x5E}, // Q
//{0x7F,0x09,0x19,0x29,0x46}, // R
//{0x46,0x49,0x49,0x49,0x31}, // S
//{0x01,0x01,0x7F,0x01,0x01}, // T
//{0x3F,0x40,0x40,0x40,0x3F}, // U
//{0x1F,0x20,0x40,0x20,0x1F}, // V
//{0x7F,0x20,0x18,0x20,0x7F}, // W
//{0x63,0x14,0x08,0x14,0x63}, // X
//{0x07,0x08,0x70,0x08,0x07}, // Y
//{0x61,0x51,0x49,0x45,0x43}  // Z
//};
//void HST7789_voidDrawChar(u16 X,u16 Y,char C,u16 Color,u16 BgColor)
//{
//    u8 Row,Col;
//    u8 Index;
//
//    if(C==' ')
//        Index=0;
//    else if(C=='!')
//        Index=1;
//    else if(C>='0' && C<='9')
//        Index=(C-'0')+2;
//    else if(C>='A' && C<='Z')
//        Index=(C-'A')+12;
//    else
//        return;
//
//    for(Col=0;Col<5;Col++)
//    {
//        u8 Line=Font5x7[Index][Col];
//
//        for(Row=0;Row<8;Row++)
//        {
//            if(Line&(1<<Row))
//            {
//                HST7789_voidDrawPixel(X+Col,Y+Row,Color);
//            }
//            else
//            {
//                HST7789_voidDrawPixel(X+Col,Y+Row,BgColor);
//            }
//        }
//    }
//}
//void HST7789_voidDrawString(u16 X,u16 Y,char *Str,u16 Color,u16 BgColor)
//{
//    while(*Str)
//    {
//        HST7789_voidDrawChar(X,Y,*Str,Color,BgColor);
//
//        X += 6;
//
//        if(X > 234)
//        {
//            X = 0;
//            Y += 8;
//        }
//
//        Str++;
//    }
//}
//void HST7789_voidDrawNumber(u16 X,u16 Y,s32 Number,u16 Color,u16 BgColor)
//{
//    char Buffer[12];
//    s8 i=0,j;
//    s32 Temp;
//
//    if(Number==0)
//    {
//        HST7789_voidDrawChar(X,Y,'0',Color,BgColor);
//        return;
//    }
//
//    if(Number<0)
//    {
//        HST7789_voidDrawChar(X,Y,'-',Color,BgColor);
//        X+=6;
//        Number=-Number;
//    }
//
//    Temp=Number;
//
//    while(Temp>0)
//    {
//        Buffer[i++]=(Temp%10)+'0';
//        Temp/=10;
//    }
//
//    for(j=i-1;j>=0;j--)
//    {
//        HST7789_voidDrawChar(X,Y,Buffer[j],Color,BgColor);
//        X+=6;
//    }
//}
#include "Std_type.h"

#include "MGPIO_Interface.h"
#include "MSPI_Interface.h"
#include "MSTK_Interface.h"

#include "HST7789_Interface.h"
#include "HST7789_Config.h"
#include "HST7789_Private.h"

/*========================================================
 * Private Functions
 *========================================================*/
static void HST7789_voidReset(void);
static void HST7789_voidWriteCommand(u8 Copy_u8Command);
static void HST7789_voidWriteData(u8 Copy_u8Data);
static void HST7789_voidWriteColor(u16 Copy_u16Color);
static void HST7789_voidSetAddress(
        u16 X1,
        u16 Y1,
        u16 X2,
        u16 Y2);


/*========================================================
 * FONT TABLE
 *
 * Index:
 * 0  = SPACE
 * 1  = !
 * 2  = -
 * 3-12  = 0-9
 * 13-38 = A-Z
 *========================================================*/
const u8 Font5x7[][5] =
{
    /* SPACE */
    {0x00,0x00,0x00,0x00,0x00},

    /* ! */
    {0x00,0x00,0x5F,0x00,0x00},

    /* - */
    {0x08,0x08,0x08,0x08,0x08},

    /* 0 */
    {0x3E,0x51,0x49,0x45,0x3E},

    /* 1 */
    {0x00,0x42,0x7F,0x40,0x00},

    /* 2 */
    {0x42,0x61,0x51,0x49,0x46},

    /* 3 */
    {0x21,0x41,0x45,0x4B,0x31},

    /* 4 */
    {0x18,0x14,0x12,0x7F,0x10},

    /* 5 */
    {0x27,0x45,0x45,0x45,0x39},

    /* 6 */
    {0x3C,0x4A,0x49,0x49,0x30},

    /* 7 */
    {0x01,0x71,0x09,0x05,0x03},

    /* 8 */
    {0x36,0x49,0x49,0x49,0x36},

    /* 9 */
    {0x06,0x49,0x49,0x29,0x1E},

    /* A */
    {0x7E,0x11,0x11,0x11,0x7E},

    /* B */
    {0x7F,0x49,0x49,0x49,0x36},

    /* C */
    {0x3E,0x41,0x41,0x41,0x22},

    /* D */
    {0x7F,0x41,0x41,0x22,0x1C},

    /* E */
    {0x7F,0x49,0x49,0x49,0x41},

    /* F */
    {0x7F,0x09,0x09,0x09,0x01},

    /* G */
    {0x3E,0x41,0x49,0x49,0x7A},

    /* H */
    {0x7F,0x08,0x08,0x08,0x7F},

    /* I */
    {0x00,0x41,0x7F,0x41,0x00},

    /* J */
    {0x20,0x40,0x41,0x3F,0x01},

    /* K */
    {0x7F,0x08,0x14,0x22,0x41},

    /* L */
    {0x7F,0x40,0x40,0x40,0x40},

    /* M */
    {0x7F,0x02,0x04,0x02,0x7F},

    /* N */
    {0x7F,0x04,0x08,0x10,0x7F},

    /* O */
    {0x3E,0x41,0x41,0x41,0x3E},

    /* P */
    {0x7F,0x09,0x09,0x09,0x06},

    /* Q */
    {0x3E,0x41,0x51,0x21,0x5E},

    /* R */
    {0x7F,0x09,0x19,0x29,0x46},

    /* S */
    {0x46,0x49,0x49,0x49,0x31},

    /* T */
    {0x01,0x01,0x7F,0x01,0x01},

    /* U */
    {0x3F,0x40,0x40,0x40,0x3F},

    /* V */
    {0x1F,0x20,0x40,0x20,0x1F},

    /* W */
    {0x7F,0x20,0x18,0x20,0x7F},

    /* X */
    {0x63,0x14,0x08,0x14,0x63},

    /* Y */
    {0x07,0x08,0x70,0x08,0x07},

    /* Z */
    {0x61,0x51,0x49,0x45,0x43}
};


/*========================================================
 * TFT INITIALIZATION
 *========================================================*/
void HST7789_voidInit(void)
{
    HST7789_voidReset();

    /* Software reset */
    HST7789_voidWriteCommand(0x01);
    MSTK_voidSetBusyWait(500000);

    /* Sleep out */
    HST7789_voidWriteCommand(0x11);
    MSTK_voidSetBusyWait(500000);

    /* 16-bit RGB565 */
    HST7789_voidWriteCommand(0x3A);
    HST7789_voidWriteData(0x55);

    /* Memory access control */
    HST7789_voidWriteCommand(0x36);
    HST7789_voidWriteData(0x00);

    /* Display ON */
    HST7789_voidWriteCommand(0x29);
    MSTK_voidSetBusyWait(500000);
}


/*========================================================
 * RESET
 *========================================================*/
static void HST7789_voidReset(void)
{
    MGPIO_voidSetPinValue(
            TFT_RST_PORT,
            TFT_RST_PIN,
            HIGH);

    MSTK_voidSetBusyWait(100000);

    MGPIO_voidSetPinValue(
            TFT_RST_PORT,
            TFT_RST_PIN,
            LOW);

    MSTK_voidSetBusyWait(200000);

    MGPIO_voidSetPinValue(
            TFT_RST_PORT,
            TFT_RST_PIN,
            HIGH);

    MSTK_voidSetBusyWait(500000);
}


/*========================================================
 * WRITE COMMAND
 *========================================================*/
static void HST7789_voidWriteCommand(u8 Copy_u8Command)
{
    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            LOW);

    MGPIO_voidSetPinValue(
            TFT_DC_PORT,
            TFT_DC_PIN,
            LOW);

    MSPI_u8Transcieve(Copy_u8Command);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            HIGH);
}


/*========================================================
 * WRITE DATA
 *========================================================*/
static void HST7789_voidWriteData(u8 Copy_u8Data)
{
    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            LOW);

    MGPIO_voidSetPinValue(
            TFT_DC_PORT,
            TFT_DC_PIN,
            HIGH);

    MSPI_u8Transcieve(Copy_u8Data);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            HIGH);
}


/*========================================================
 * WRITE RGB565 COLOR
 *========================================================*/
static void HST7789_voidWriteColor(u16 Copy_u16Color)
{
    MSPI_u8Transcieve(
            (u8)(Copy_u16Color >> 8));

    MSPI_u8Transcieve(
            (u8)(Copy_u16Color & 0xFF));
}


/*========================================================
 * SET ADDRESS WINDOW
 *========================================================*/
static void HST7789_voidSetAddress(
        u16 X1,
        u16 Y1,
        u16 X2,
        u16 Y2)
{
    /* Column address */
    HST7789_voidWriteCommand(ST7789_CASET);

    HST7789_voidWriteData((u8)(X1 >> 8));
    HST7789_voidWriteData((u8)X1);

    HST7789_voidWriteData((u8)(X2 >> 8));
    HST7789_voidWriteData((u8)X2);

    /* Row address */
    HST7789_voidWriteCommand(ST7789_RASET);

    HST7789_voidWriteData((u8)(Y1 >> 8));
    HST7789_voidWriteData((u8)Y1);

    HST7789_voidWriteData((u8)(Y2 >> 8));
    HST7789_voidWriteData((u8)Y2);

    /* Write RAM */
    HST7789_voidWriteCommand(ST7789_RAMWR);
}


/*========================================================
 * DRAW PIXEL
 *========================================================*/
void HST7789_voidDrawPixel(
        u16 X,
        u16 Y,
        u16 Color)
{
    if(X >= TFT_WIDTH || Y >= TFT_HEIGHT)
    {
        return;
    }

    HST7789_voidSetAddress(
            X,
            Y,
            X,
            Y);

    MGPIO_voidSetPinValue(
            TFT_DC_PORT,
            TFT_DC_PIN,
            HIGH);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            LOW);

    HST7789_voidWriteColor(Color);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            HIGH);
}


/*========================================================
 * FILL SCREEN
 *========================================================*/
void HST7789_voidFillScreen(u16 Color)
{
    u32 i;

    HST7789_voidSetAddress(
            0,
            0,
            TFT_WIDTH - 1,
            TFT_HEIGHT - 1);

    MGPIO_voidSetPinValue(
            TFT_DC_PORT,
            TFT_DC_PIN,
            HIGH);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            LOW);

    for(i = 0;
        i < ((u32)TFT_WIDTH * TFT_HEIGHT);
        i++)
    {
        HST7789_voidWriteColor(Color);
    }

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            HIGH);
}


/*========================================================
 * FILL RECTANGLE
 *========================================================*/
void HST7789_voidFillRectangle(
        u16 X,
        u16 Y,
        u16 Width,
        u16 Height,
        u16 Color)
{
    u32 i;
    u32 Size;

    /* Check boundaries */
    if(X >= TFT_WIDTH || Y >= TFT_HEIGHT)
    {
        return;
    }

    if((X + Width) > TFT_WIDTH)
    {
        Width = TFT_WIDTH - X;
    }

    if((Y + Height) > TFT_HEIGHT)
    {
        Height = TFT_HEIGHT - Y;
    }

    Size = (u32)Width * Height;

    HST7789_voidSetAddress(
            X,
            Y,
            X + Width - 1,
            Y + Height - 1);

    MGPIO_voidSetPinValue(
            TFT_DC_PORT,
            TFT_DC_PIN,
            HIGH);

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            LOW);

    for(i = 0; i < Size; i++)
    {
        HST7789_voidWriteColor(Color);
    }

    MGPIO_voidSetPinValue(
            TFT_CS_PORT,
            TFT_CS_PIN,
            HIGH);
}


/*========================================================
 * DRAW CHARACTER
 *========================================================*/
void HST7789_voidDrawChar(
        u16 X,
        u16 Y,
        char C,
        u16 Color,
        u16 BgColor)
{
    u8 Row;
    u8 Col;
    u8 Index;
    u8 Line;

    if(C == ' ')
    {
        Index = 0;
    }
    else if(C == '!')
    {
        Index = 1;
    }
    else if(C == '-')
    {
        Index = 2;
    }
    else if(C >= '0' && C <= '9')
    {
        Index = (C - '0') + 3;
    }
    else if(C >= 'A' && C <= 'Z')
    {
        Index = (C - 'A') + 13;
    }
    else
    {
        return;
    }

    for(Col = 0; Col < 5; Col++)
    {
        Line = Font5x7[Index][Col];

        for(Row = 0; Row < 8; Row++)
        {
            if(Line & (1 << Row))
            {
                HST7789_voidDrawPixel(
                        X + Col,
                        Y + Row,
                        Color);
            }
            else
            {
                HST7789_voidDrawPixel(
                        X + Col,
                        Y + Row,
                        BgColor);
            }
        }
    }
}


/*========================================================
 * DRAW STRING
 *========================================================*/
void HST7789_voidDrawString(
        u16 X,
        u16 Y,
        char *Str,
        u16 Color,
        u16 BgColor)
{
    if(Str == 0)
    {
        return;
    }

    while(*Str)
    {
        HST7789_voidDrawChar(
                X,
                Y,
                *Str,
                Color,
                BgColor);

        X += 6;

        if(X > 234)
        {
            X = 0;
            Y += 8;
        }

        if(Y >= TFT_HEIGHT)
        {
            break;
        }

        Str++;
    }
}


/*========================================================
 * DRAW NUMBER
 *
 * Correctly displays:
 *
 * 0
 * 123
 * 1250
 * 29107
 * -50
 *========================================================*/
void HST7789_voidDrawNumber(
        u16 X,
        u16 Y,
        s32 Number,
        u16 Color,
        u16 BgColor)
{
    char Buffer[12];
    u8 Index = 0;
    u8 j;
    u32 Value;

    /* ZERO */
    if(Number == 0)
    {
        HST7789_voidDrawChar(
                X,
                Y,
                '0',
                Color,
                BgColor);

        return;
    }

    /* NEGATIVE NUMBER */
    if(Number < 0)
    {
        HST7789_voidDrawChar(
                X,
                Y,
                '-',
                Color,
                BgColor);

        X += 6;

        Value = (u32)(-Number);
    }
    else
    {
        Value = (u32)Number;
    }

    /* Convert digits */
    while(Value > 0 && Index < 11)
    {
        Buffer[Index] =
                (char)((Value % 10) + '0');

        Value /= 10;

        Index++;
    }

    /* Display in reverse */
    while(Index > 0)
    {
        Index--;

        HST7789_voidDrawChar(
                X,
                Y,
                Buffer[Index],
                Color,
                BgColor);

        X += 6;
    }
}
