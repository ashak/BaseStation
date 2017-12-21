#include "Menu.h"

Menu::Menu(char* title, int num_items) {
  this->title = title;
  this->parent = NULL;
  this->num_menu_items = num_items;
  this->menu_items = calloc(num_items, sizeof(Menu*));
  this->prepared_menu_items = nullptr;
  this->added_network_items = 0;
  this->force_render = false;
}

void Menu::addMenuItem(MenuItem* menu_item) {
  if (added_network_items < num_menu_items) {
    menu_items[added_network_items] = menu_item;
  }
  added_network_items++;
}

void Menu::setForceRender() {
  force_render = true;
}

char* Menu::getTitle() {
  return title;
}
Menu* Menu::getParent() {
  return parent;
}

Menu* Menu::handler(phi_prompt_struct* current_phi_prompt_struct) {
//Serial.println("handler");
  int button_press=sense_select_list(current_phi_prompt_struct);
  switch(button_press) {
    case phi_prompt_content_needs_update:
    Serial.println("content needs update  in menu");
Serial.println((long) &current_phi_prompt_struct, HEX);
    render_list(current_phi_prompt_struct);
    Serial.println("content needs update  in menu done");
    break;

    case phi_prompt_sense_select_list_escape:
    Serial.println("escape pressed in menu");
    return parent;
    break;

    default:
    int menu_item_highlighted=current_phi_prompt_struct->low.i;
    Menu* new_menu = menu_items[menu_item_highlighted]->handler(button_press);
//Serial.println("blah");
    if (new_menu!=0) {
//Serial.println("blah1");
      return new_menu;
    }
    break;
  }
  if (force_render) {
    render_list(current_phi_prompt_struct);
    force_render = false;
  }
//Serial.println("/handler");
  return this;
}

void Menu::prepare(phi_prompt_struct* current_phi_prompt_struct) {
Serial.println("prepare");
  center_text(this->getTitle());
  updateMenuItems();
  current_phi_prompt_struct->ptr.list=prepared_menu_items;
  current_phi_prompt_struct->low.i=0; // Default item highlighted on the list
Serial.println(current_phi_prompt_struct->high.i=num_menu_items);
  current_phi_prompt_struct->high.i=num_menu_items-1; // Last item of the list is size of the list - 1.
  render_list(current_phi_prompt_struct); 
Serial.println("/prepare");
}

void Menu::setParent(Menu* parent) {
  this->parent = parent;
}

char** Menu::prepareMenuItems() {
Serial.println("blah1");
  char** new_menu_items = calloc(num_menu_items, sizeof(char*));
Serial.println("blah2");
  for (int i=0; i < num_menu_items; i++) {
Serial.println("blah3");
Serial.println(menu_items[i]->getTitle());
    new_menu_items[i] = menu_items[i]->getTitle();
Serial.println("blah4");
  }
Serial.println("blah5");
  return new_menu_items;
}

void Menu::updateMenuItems() {
  if (prepared_menu_items) {
    delete prepared_menu_items;
  }
  prepared_menu_items = prepareMenuItems();
  setForceRender();
}
