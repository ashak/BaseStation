#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H
#include "Display.h"
#include <LiquidCrystal.h>
#include "Menu.h"
static char up_keys[]={"U"};
static char down_keys[]={"D"};
static char left_keys[]={"L"};
static char right_keys[]={"R"};
static char ent_keys[]={"B"};
static char esc_keys[]={"A"};
static char * function_keys[]={up_keys,down_keys,left_keys,right_keys,ent_keys,esc_keys};

static byte pins[]={my_btn_u,my_btn_d,my_btn_l,my_btn_r,my_btn_b,my_btn_a};
static char mapping[]={'U','D','L','R','B','A'};
static phi_button_groups* my_btns= new phi_button_groups(mapping, pins, total_buttons);
static multiple_button_input * keypads[]={my_btns, 0};

// This is the style of the menu
// 101 == 01100101
//        ||||||| List display option for using arrow/dot before a list item.
//        |||||| List display option for using an index list such as 12*4 for 4 total items and 3 is highlighted.
//        ||||| List display option for using a current/total index such as 2/4.
//        |||| List display option for using auto scrolling items longer than the width of the list.
//        ||| List display option for using flash cursor as indicator of highlighted item.
//        || List display option for using centering highlighted item on screen so highlighted item is always in the middle when possible.
//        | List display option for using a scroll bar on the right.
//         List display option for using inverted text. Only some modified version of the library uses it.
//int global_style=101;
static int global_style=357;

class MenuSystem {
  public:
    MenuSystem(LiquidCrystal*);
    MenuSystem(LiquidCrystal*, phi_prompt_struct*);
    void handleDisplayAndDisplayControls();
    void setStartMenu(Menu*);
//    void addMenu(char*);
  private:
    void initialisePhiPrompt();
    void initialisePhiPromptStruct();
    void initialisePhiPromptStruct(phi_prompt_struct*);
    void prepareDisplay();
    void switchBackToMenu(Menu *);
    void switchToMenu(Menu *);
    void defaultMenuHandler();

    phi_prompt_struct* current_phi_prompt_struct;
    Menu* currently_displayed_menu;
    LiquidCrystal* lcd;
    Menu* start_menu;
};
#endif
