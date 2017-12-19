#ifndef CONTROL_STATION_H
#define CONTROL_STATION_H
#include <phi_prompt.h>
#include <phi_interfaces.h>
#include "Control.h"
#include "PacketRegister.h"

#define LCD_RS 31
#define LCD_EN 30
#define LCD_D4 29
#define LCD_D5 28
#define LCD_D6 27
#define LCD_D7 26
#define lcd_rows 4
#define lcd_columns 20

class ControlStation {
  public:
    static void initialise(volatile RegisterList* mainRegs);
    static void update();
  private:
    static void initialiseLCD();
};
#endif
