#include "MenuItemLoadNewMenu.h"
MenuItemLoadNewMenu::MenuItemLoadNewMenu(
  Menu* menu,
  Menu* next_menu
) : MenuItem::MenuItem(
  menu,
  next_menu->getTitle()
) {
  this->next=next_menu;
}

Menu* MenuItemLoadNewMenu::handler(int button_press) {
  switch(button_press) {
    case phi_prompt_sense_select_list_enter:
    Serial.println("returning new menu");
    return this->next;
    break;
  }
  return 0; 
}
