#ifndef MENU_EDIT_OBJECT_H
#define MENU_EDIT_OBJECT_H
#include "Menu.h"
#include "EdittableObject.h"

class MenuEditObject: public Menu {
  public:
    MenuEditObject::MenuEditObject(EdittableObject*, int);
    virtual void MenuEditObject::initialiseEdittableObject(int);
};
#endif
