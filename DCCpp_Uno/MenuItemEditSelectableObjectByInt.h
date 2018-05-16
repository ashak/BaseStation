#ifndef MENU_ITEM_EDIT_SELECTABLE_OBJECT_BY_INT_H
#define MENU_ITEM_EDIT_SELECTABLE_OBJECT_BY_INT_H
#include "Menu.h"
#include "MenuEditObject.h"
#include "MenuItem.h"
class MenuItemEditSelectableObjectByInt: public MenuItem {
  private:
    Menu* next;
    char* actual_title;
    int title_size;
    int edittable_int;
    void decrease(int*);
    void increase(int*);

  public:
    MenuItemEditSelectableObjectByInt::MenuItemEditSelectableObjectByInt(Menu*, MenuEditObject*, char*, int);
    Menu* MenuItemEditSelectableObjectByInt::handler(int);
    char* MenuItemEditSelectableObjectByInt::getTitle();
};
#endif
