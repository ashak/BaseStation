#ifndef MENU_ITEM_LOAD_NEW_MENU_H
#define MENU_ITEM_LOAD_NEW_MENU_H
#include "Menu.h"
#include "MenuItem.h"
class MenuItemLoadNewMenu: public MenuItem {
  private:
    Menu* next;

  public:
    MenuItemLoadNewMenu::MenuItemLoadNewMenu(Menu*, Menu*);
    Menu* MenuItemLoadNewMenu::handler(int);
};
#endif
