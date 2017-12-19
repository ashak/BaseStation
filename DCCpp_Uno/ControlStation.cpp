#include "ControlStation.h"
#include <LiquidCrystal.h>
#include "MenuSystem.h"
#include "Menu.h"

static LiquidCrystal* lcd;
MenuSystem* menu_system;

static void ControlStation::initialise(volatile RegisterList* mainRegs) {
  initialiseLCD();
  menu_system = new MenuSystem(lcd);
  Menu* settings_menu = new Menu("Settings", 3);
  menu_system->setStartMenu(settings_menu);
  initControls(mainRegs, 21);
  enableControl(1, 8, 22, A15);
}

static void ControlStation::update() {
  handleControlChanges();
  menu_system->handleDisplayAndDisplayControls();
//  handleDisplay();
}

static void ControlStation::initialiseLCD() {
  lcd = new LiquidCrystal(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
  lcd->begin(lcd_columns, lcd_rows);
  lcd->noDisplay();
}

