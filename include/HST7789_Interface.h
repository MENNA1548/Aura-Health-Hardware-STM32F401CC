/*
 * HST7789_Interface.h
 *
 * Updated Interface
 */

#ifndef HST7789_INTERFACE_H_
#define HST7789_INTERFACE_H_

#include "Std_type.h"

/*=============================
   Colors
=============================*/
#define TFT_BLACK      0x0000
#define TFT_WHITE      0xFFFF
#define TFT_RED        0xF800
#define TFT_GREEN      0x07E0
#define TFT_BLUE       0x001F
#define TFT_YELLOW     0xFFE0
#define TFT_CYAN       0x07FF
#define TFT_MAGENTA    0xF81F

/*=============================
   Initialization
=============================*/
void HST7789_voidInit(void);

/*=============================
   Basic Drawing
=============================*/
void HST7789_voidDrawPixel(
        u16 X,
        u16 Y,
        u16 Color
);

void HST7789_voidFillScreen(
        u16 Color
);

/*=============================
   Character Drawing
=============================*/
void HST7789_voidDrawChar(
        u16 X,
        u16 Y,
        char Character,
        u16 Color,
        u16 BackgroundColor
);

/*=============================
   String Drawing
=============================*/
void HST7789_voidDrawString(u16 X,
                            u16 Y,
                            char *Str,
                            u16 Color,
                            u16 BgColor);
/*=============================
   Number Drawing
=============================*/
void HST7789_voidDrawNumber(
        u16 X,
        u16 Y,
        s32 Number,
        u16 Color,
        u16 BackgroundColor
);

/*=============================
   Rectangle
=============================*/
void HST7789_voidFillRectangle(
        u16 X,
        u16 Y,
        u16 Width,
        u16 Height,
        u16 Color
);

#endif /* HST7789_INTERFACE_H_ */
