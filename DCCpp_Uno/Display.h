#include <phi_interfaces.h>
#include <phi_prompt.h>
#include <LiquidCrystal.h>

#define phi_prompt_sense_select_list_escape -1
#define phi_prompt_sense_select_list_enter 1
#define phi_prompt_sense_select_list_left -2
#define phi_prompt_sense_select_list_right -3

#define lcd_rows 4
#define lcd_columns 20
#define total_buttons 6
#define my_btn_u 32
#define my_btn_d 33
#define my_btn_l 34
#define my_btn_r 35
#define my_btn_b 36
#define my_btn_a 37


//PROGMEM  const char msg_00[]="Control for DCC++\nby Gary Richards\nDCC++ BaseStation is developed by Gregg E. Berman\nPress select to continue";
//Developed by:\nDr.Liu 05/23/11\nhttp://liudr.wordpress.com\nThis is just a mock-up of an actual data acquisition system with a 2-level menu.\nIt serves as a template for your actual project. It also shows off various features of the phi_prompt library.\nGo in \"Set Menu Style\" to find out some menu features you could be using in your project.\nPress Confirm to continue";

//void (*current_menu_function)();
//phi_prompt_struct* current_menu;
//byte render=1;
//int last_button_press=NO_KEY;

void initDisplayAndControls(LiquidCrystal*, phi_button_groups*, phi_prompt_struct*);
void handleDisplay();
void initialiseSharedList();
void updateMenuTitleList(char*, char* [], int, void (*handler)());
void exitMenu();

void topMenuHandler();
void controlsMenuHandler();
void initControlsMenu();
void updateControlsMenu();
void controlsEditMenuHandler();
void initControlsEditMenu();
void updateControlsEditMenu();

