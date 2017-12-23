#include "ControlStation.h"
#include <LiquidCrystal.h>
#include "MenuSystem.h"
#include "Menu.h"
#include "MenuItem.h"
#include "MenuItemLoadNewMenu.h"
#include "MenuItemLoadParentMenu.h"
#include "MenuItemEditSelectableObjectByInt.h"

static LiquidCrystal* lcd;
MenuSystem* menu_system;

static void ControlStation::initialise(volatile RegisterList* mainRegs) {
  initialiseLCD();
  menu_system = new MenuSystem(lcd);
  Menu* settings_menu = new Menu("Settings", 3);
  Menu* controls_menu = new Menu("Controls", 2);
  Menu* edit_control_menu = new Menu("Edit Ctrl <%02d", 4);
  new MenuItemLoadNewMenu(settings_menu, controls_menu);
  new MenuItem(settings_menu, "Programming");
  new MenuItemLoadParentMenu(settings_menu, "Exit");
  new MenuItemEditSelectableObjectByInt(controls_menu, "Edit Control <%02d>", sizeof("Edit Control <XX>"));
  new MenuItemLoadParentMenu(controls_menu, "Exit");
  menu_system->setStartMenu(settings_menu);

  initControls(mainRegs, 19);
  enableControl(1, 8, 15, A8);
  enableControl(2, 20, 16, A9);
  enableControl(3, 4, 17, A10);
  enableControl(4, 97, 18, A11);
Serial.println(controls_menu->getTitle());
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

