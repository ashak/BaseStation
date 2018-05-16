#include "ControlStation.h"
#if CONTROLSTATION_MENU_ENABLE == 1
#include <LiquidCrystal.h>
#include "MenuSystem.h"
#include "Menu.h"
#include "MenuEditControl.h"
#include "MenuItem.h"
#include "MenuItemLoadNewMenu.h"
#include "MenuItemLoadParentMenu.h"
#include "MenuItemEditSelectableObjectByInt.h"
#include "MenuItemEditObjectParameter.h"

static LiquidCrystal* lcd;
MenuSystem* menu_system;
#endif

static void ControlStation::initialise(volatile RegisterList* mainRegs) {
#if CONTROLSTATION_MENU_ENABLE == 1
  initialiseLCD();
  menu_system = new MenuSystem(lcd);
  Menu* settings_menu = new Menu("Settings", 3);
  Menu* controls_menu = new Menu("Controls", 2);
  Menu* edit_control_menu = new MenuEditControl(new EdittableControl(), 5);
// "Edit Ctrl %02d", 2, );

  new MenuItemLoadNewMenu(settings_menu, controls_menu);
  new MenuItem(settings_menu, "Programming");
  new MenuItemLoadParentMenu(settings_menu, "Exit");

  new MenuItemEditSelectableObjectByInt(controls_menu, edit_control_menu, "Edit Control <%02d>", sizeof("Edit Control <XX>"));
  new MenuItemLoadParentMenu(controls_menu, "Exit");

  new MenuItemEditObjectParameter(edit_control_menu, "enabled");
  new MenuItemEditObjectParameter(edit_control_menu, "locoaddr");
  new MenuItemEditObjectParameter(edit_control_menu, "dir_pin");
  new MenuItemEditObjectParameter(edit_control_menu, "speed_pin");
  new MenuItemLoadParentMenu(edit_control_menu, "Exit");

//"Enabled: %s", sizeof("Enabled: <XXXXX>"));
//  new MenuItemEditObjectParameterInt(edit_control_menu, "LocoAddr:<%05d>", sizeof("LocoAddr:<XXXXX>");
//  new MenuItemEditObjectParameterInt(edit_control_menu, "Dir pin:    <%02d>", sizeof("Dir pin:    <XX>");
//  new MenuItemEditObjectParameterInt(edit_control_menu, "Speed pin: A<%02d>", sizeof("Speed pin: A<XX>"));

  menu_system->setStartMenu(settings_menu);
#endif

  initControls(mainRegs, 19);
  enableControl(1, 8, 15, A8);
  enableControl(2, 20, 16, A9);
  enableControl(3, 4, 17, A10);
  enableControl(4, 97, 18, A11);
//Serial.println(controls_menu->getTitle());
}

static void ControlStation::update() {
  handleControlChanges();
#if CONTROLSTATION_MENU_ENABLE == 1
  menu_system->handleDisplayAndDisplayControls();
#endif
//  handleDisplay();
}

static void ControlStation::initialiseLCD() {
#if CONTROLSTATION_MENU_ENABLE == 1
  lcd = new LiquidCrystal(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
  lcd->begin(lcd_columns, lcd_rows);
  lcd->noDisplay();
#endif
}

