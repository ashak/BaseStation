#include "MenuItemLoadPreviousMenu.h"
MenuItemLoadPreviousMenu::MenuItemLoadPreviousMenu(
  Menu* menu,
  char* title
) : MenuItem::MenuItem(
  menu,
  title
) {

}

Menu* MenuItemLoadNewMenu::handler(int button_press) {
  switch(button_press) {
    case phi_prompt_sense_select_list_enter:
    Serial.println("returning new menu");
    return this->next;
    break;
  }
  return NULL; 
}
