#include "MenuItemLoadParentMenu.h"
MenuItemLoadParentMenu::MenuItemLoadParentMenu(
  Menu* menu,
  char* title
) : MenuItem::MenuItem(
  menu,
  title
) {

}

Menu* MenuItemLoadParentMenu::handler(int button_press) {
//Serial.println("LoadParentMenu Handler");
  switch(button_press) {
    case phi_prompt_sense_select_list_enter:
    Serial.println("returning parent menu");
    return menu->getParent();
    break;
  }
//Serial.println("LoadParentMenu Handler");
  return 0;
}

