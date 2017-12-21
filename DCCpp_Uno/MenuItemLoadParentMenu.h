#ifndef MENU_ITEM_LOAD_PARENT_MENU_H
#define MENU_ITEM_LOAD_PARENT_MENU_H
#include "Menu.h"
#include "MenuItem.h"
class MenuItemLoadParentMenu: public MenuItem {
  public:
    MenuItemLoadParentMenu::MenuItemLoadParentMenu(Menu*, char*);
    Menu* MenuItemLoadParentMenu::handler(int);
};
#endif
