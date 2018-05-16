#include "MenuEditControl.h"
MenuEditControl::MenuEditControl(
  EdittableControl* edittable_control,
  int num_items
) : MenuEditObject::MenuEditObject(
  (EdittableObject*)edittable_control,
  num_items
) {
  this->edittable_control = edittable_control;
  temporary_control = createControl();
}

void MenuEditControl::updateTemporaryControl(int control_index) {
  Control* control = getControls()[control_index];
  temporary_control->enabled = control->enabled;
  temporary_control->loco_address = control->loco_address;
  temporary_control->dir_pin = control->dir_pin;
  temporary_control->speed_pin = control->speed_pin;
}

void MenuEditControl::prepare(phi_prompt_struct* current_phi_prompt_struct) {
//  updateTemporaryContro(X);
  Menu::prepare(current_phi_prompt_struct);
}
