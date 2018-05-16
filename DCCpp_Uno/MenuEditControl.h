#ifndef MENU_EDIT_CONTROL_H
#define MENU_EDIT_CONTROL_H
#include "MenuEditObject.h"
#include "EdittableControl.h"
#include "Control.h"
class MenuEditControl: public MenuEditObject {
  private:
    EdittableControl* edittable_control;
    Control* temporary_control;
  public:
    MenuEditControl::MenuEditControl(EdittableControl*, int);
    void MenuEditControl::updateTemporaryControl(int);
    void MenuEditControl::prepare(phi_prompt_struct*);
};
#endif
