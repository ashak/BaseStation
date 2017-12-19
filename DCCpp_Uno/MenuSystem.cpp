#include "MenuSystem.h"

MenuSystem::MenuSystem(LiquidCrystal* lcd) {
  this->lcd = lcd;
  this->currently_displayed_menu=NULL;
  initialisePhiPrompt();
  initialisePhiPromptStruct();
  initDisplayAndControls(lcd, my_btns, current_phi_prompt_struct);
}

MenuSystem::MenuSystem(LiquidCrystal* lcd, phi_prompt_struct* phi_prompt_struct_p) {
  this->lcd = lcd;
  this->currently_displayed_menu=NULL;
  initialisePhiPrompt();
  initialisePhiPromptStruct(phi_prompt_struct_p);
  initDisplayAndControls(lcd, my_btns, current_phi_prompt_struct);
}

void MenuSystem::handleDisplayAndDisplayControls() {
  if (currently_displayed_menu) {
    Menu* ret_menu = currently_displayed_menu->handler(current_phi_prompt_struct);
    if(ret_menu!=currently_displayed_menu) {
      if(ret_menu==currently_displayed_menu->getParent()) {
        switchBackToMenu(currently_displayed_menu->getParent());
      } else {
        switchToMenu(ret_menu);
      }
    }
//    currentDisplayHandler();
  } else {
    char button_press=my_btns->getKey();
    if (button_press!=NO_KEY) {
      Serial.println(button_press);
      prepareDisplay();
      switchToMenu(start_menu);
    }
  }
}

void MenuSystem::setStartMenu(Menu* start_menu) {
  this->start_menu=start_menu;
}

//Menu* MenuSystem::addMenu(char* title, int num_items) {
//  return new Menu(title, num_items);
//}

void MenuSystem::initialisePhiPrompt() {
  init_phi_prompt(lcd, keypads, function_keys, lcd_columns, lcd_rows, '~');
}

void MenuSystem::initialisePhiPromptStruct() {
  phi_prompt_struct* phi_prompt_struct_p = (phi_prompt_struct*) calloc(1,sizeof(phi_prompt_struct));
  phi_prompt_struct_p->low.i=0; // Default item highlighted on the list
  phi_prompt_struct_p->width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
  phi_prompt_struct_p->step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
  phi_prompt_struct_p->step.c_arr[1]=1; // one col list
  phi_prompt_struct_p->step.c_arr[2]=0; // y for additional feature such as an index
  phi_prompt_struct_p->step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // x for additional feature such as an index
  phi_prompt_struct_p->col=0; // Display menu at column 0
  phi_prompt_struct_p->row=1; // Display menu at row 1
  phi_prompt_struct_p->option=global_style; // Option 0, display classic list, option 1, display 2X2 list, option 2, display list with index, option 3, display list with index2.
  initialisePhiPromptStruct(phi_prompt_struct_p);
}

void MenuSystem::initialisePhiPromptStruct(phi_prompt_struct* phi_prompt_struct_p) {
  this->current_phi_prompt_struct = phi_prompt_struct_p;
}

void MenuSystem::prepareDisplay() {
  lcd->display();
  lcd->clear();  
  lcd->noBlink();
  Serial.println("Prepared display");
}

void MenuSystem::switchBackToMenu(Menu* menu) {
  if(currently_displayed_menu->getParent()) {
    currently_displayed_menu->setParent(NULL);
    currently_displayed_menu = menu;
    currently_displayed_menu->prepare(current_phi_prompt_struct);
  } else {
    currently_displayed_menu = NULL;
    lcd->clear();
    lcd->noDisplay();
  }
}

void MenuSystem::switchToMenu(Menu* menu) {
  if(currently_displayed_menu) {
    menu->setParent(currently_displayed_menu);
  }
  currently_displayed_menu = menu;
  currently_displayed_menu->prepare(current_phi_prompt_struct);
  Serial.println("Switched to menu");
}

