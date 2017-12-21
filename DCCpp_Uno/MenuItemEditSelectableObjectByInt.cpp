#include "MenuItemEditSelectableObjectByInt.h"
MenuItemEditSelectableObjectByInt::MenuItemEditSelectableObjectByInt(
  Menu* menu,
  char* fmt,
  int title_size
) : MenuItem::MenuItem(
  menu,
  fmt
) {
//  this->next=next_menu;
  this->title_size = title_size;
  this->edittable_int = 0;
  this->actual_title = nullptr;
}

char* MenuItemEditSelectableObjectByInt::getTitle() {
  delete actual_title;
  actual_title = new char[title_size];
  sprintf(actual_title, title, edittable_int);
  return actual_title;
}

Menu* MenuItemEditSelectableObjectByInt::handler(int button_press) {
  switch(button_press) {
    case phi_prompt_sense_select_list_left:
Serial.println("left pressed");
    decrease(&edittable_int);
    menu->updateMenuItems();
    break;

    case phi_prompt_sense_select_list_right:
Serial.println("right pressed");
Serial.println(edittable_int);
    increase(&edittable_int);
Serial.println(edittable_int);
    menu->updateMenuItems();
    break;

    case phi_prompt_sense_select_list_enter:
    Serial.println("returning new menu");
    return this->next;
    break;
  }
  return 0; 
}

void MenuItemEditSelectableObjectByInt::decrease (int* num) {
  (*num)--;
}

void MenuItemEditSelectableObjectByInt::increase (int* num) {
  (*num)++;
}
