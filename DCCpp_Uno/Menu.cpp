#include "Menu.h"
Menu::Menu(char* title, int num_items) {
  this->title = title;
  this->parent = NULL;
//  this->list = char* [num_items];
}

Menu* Menu::getParent() {
  return parent;
}

Menu* Menu::handler(phi_prompt_struct* current_phi_prompt_struct) {
  int button_press=sense_select_list(current_phi_prompt_struct);
  switch(button_press) {
    case phi_prompt_content_needs_update:
    Serial.println("content needs update  in menu");
    render_list(current_phi_prompt_struct);
    break;

    case phi_prompt_sense_select_list_escape:
    Serial.println("escape pressed in menu");
    return parent;
    break;
  }

  return this;
}

void Menu::prepare(phi_prompt_struct* current_phi_prompt_struct) {
  center_text(this->title);
  current_phi_prompt_struct->ptr.list=list;
  current_phi_prompt_struct->low.i=0; // Default item highlighted on the list
  current_phi_prompt_struct->high.i=0; //listSize()-1; // Last item of the list is size of the list - 1.
  render_list(current_phi_prompt_struct); 
}

void Menu::setParent(Menu* parent) {
  this->parent = parent;
}

int Menu::listSize() {
  return sizeof(list)/sizeof(list[0]);
}
