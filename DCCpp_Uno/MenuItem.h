#ifndef MENU_ITEM_H
#define MENU_ITEM_H
#include "Menu.h"
class Menu;

class MenuItem {
  protected:
    Menu* menu;
    char* title;
  public:
    MenuItem::MenuItem(Menu*, char*);
    virtual char* MenuItem::getTitle();
    virtual Menu * MenuItem::handler(int);
};
#endif
