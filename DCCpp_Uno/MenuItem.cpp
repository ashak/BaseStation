#include "MenuItem.h"
MenuItem::MenuItem(Menu* menu, char* title) {
  this->menu = menu;
  this->title = title;
  menu->addMenuItem(this);
}

char* MenuItem::getTitle() {
  return title;
}

Menu* MenuItem::handler(int) {
  return 0;
}
