#include "Display.h"
#include <LiquidCrystal.h>
#include <phi_prompt.h>
#include <phi_interfaces.h>
#include "Config.h"
#include "Control.h"

//char up_keys[]={"U"};
//char down_keys[]={"D"};
//char left_keys[]={"L"};
//char right_keys[]={"R"};
//char ent_keys[]={"B"};
//char esc_keys[]={"A"};
//char * function_keys[]={up_keys,down_keys,left_keys,right_keys,ent_keys,esc_keys};

LiquidCrystal* lcd;

//byte pins[]={my_btn_u,my_btn_d,my_btn_l,my_btn_r,my_btn_b,my_btn_a};
//char mapping[]={'U','D','L','R','B','A'};
//phi_button_groups* my_btns= new phi_button_groups(mapping, pins, total_buttons);
//multiple_button_input * keypads[]={my_btns, 0};
phi_button_groups* my_btns;

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
int global_style=357;

// Settings menu. The first one we see when the menu is turned on.
char top_menu_item00[]="Controls";
char top_menu_item01[]="Upload to PC";
char top_menu_item02[]="Set Menu Style";
char top_menu_item03[]="File management";
char top_menu_item04[]="Show credit See who spent so much time making it happen!";
char top_menu_item05[]="Exit";
char * top_menu_items[] = {top_menu_item00, top_menu_item01, top_menu_item02, top_menu_item03, top_menu_item04, top_menu_item05};
int top_menu_size=6;

char controls_menu_item01[]="Edit control <XX>";
char controls_menu_item02[]="Back";
char * controls_menu_items[] = {controls_menu_item01, controls_menu_item02};
int controls_menu_size=2;
int controls_menu_edit_i=0;

char controls_edit_menu_item01[]="Enabled: <False>";
char controls_edit_menu_item02[]="LocoAddr:<XXXXX>";
char controls_edit_menu_item03[]="Dir pin:    <XX>";
char controls_edit_menu_item04[]="Speed pin: A<XX>";
char * controls_edit_menu_items[] = {controls_edit_menu_item01, controls_edit_menu_item02, controls_edit_menu_item03, controls_edit_menu_item04};
int controls_edit_menu_size=4;
bool controls_edit_menu_enabled=false;
int controls_edit_menu_loco_address=0;
int controls_edit_menu_dir_pin=0;
int controls_edit_menu_speed_pin=0;

phi_prompt_struct stuff_to_render;
bool menu_displayed=false;

void (*currentDisplayHandler)();

void initDisplayAndControls(LiquidCrystal* _lcd, phi_button_groups* btns, phi_prompt_struct* pps) {
  lcd = _lcd;
  my_btns = btns;
  stuff_to_render = *pps;
//  Serial.println("Nums:");
//  Serial.println(sizeof(top_menu_items)/sizeof(top_menu_items[0]));
//  Serial.println(sizeof(controls_menu_items)/sizeof(controls_menu_items[0]));
}

void topMenuHandler() {
  int temp1=sense_select_list(&stuff_to_render);

  switch (temp1) {
    case phi_prompt_content_needs_update:
    Serial.println("content needs update  in menu");
    Serial.println(stuff_to_render.low.i);
    render_list(&stuff_to_render);
    break;

    case phi_prompt_sense_select_list_escape:
    Serial.println("escape pressed in menu");
    Serial.println(stuff_to_render.low.i);
    exitMenu();
    break;

    case phi_prompt_sense_select_list_enter: {
    Serial.println("enter pressed in menu");
    Serial.println(stuff_to_render.low.i);
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    Serial.println("bob");
    Serial.println(menu_pointer_1);
    Serial.println("/bob");
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      Serial.println("case 0");
      initControlsMenu();
      updateMenuTitleList("Controls", controls_menu_items, sizeof(controls_menu_items)/sizeof(controls_menu_items[0]), &controlsMenuHandler);
      break;
//      case 1:
//      top_menu_function_2();
//      break;
//      
//      case 2:
//      top_menu_function_3(&myMenu); // This is the setting function that changes how menu is rendered
//      break;
//      
//      case 3:
//      sub_menu_1(); // This is actually the sub menu.
//      break;
//  
//      case 4:
//      top_menu_function_5(); // If this were a sub level menu, this last one should return to previous level by using "return".
//      break;
//
      case 5:
      Serial.println("case 5");
      exitMenu();
      break;

      default:
      Serial.println("default switch");
      break;
    }
    }
    break;

    default:
//    Serial.println("blah");
//    Serial.println(temp1);
//    Serial.println("/blah");
    break;
  }
}

void initControlsMenu() {
  controls_menu_edit_i=0;
  updateControlsMenu();
}
void updateControlsMenu() {
  sprintf(controls_menu_item01, "Edit control <%02d>", controls_menu_edit_i+1);
}

void controlsMenuHandler() {
  int temp1=sense_select_list(&stuff_to_render);

  switch (temp1) {
    case phi_prompt_content_needs_update:
    render_list(&stuff_to_render);
    break;

    case phi_prompt_sense_select_list_left: {
      Serial.println("pressed left");
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      if(controls_menu_edit_i > 0)
        controls_menu_edit_i--;
        updateControlsMenu();
        render_list(&stuff_to_render);
      break;
    }
    break;
    }

    case phi_prompt_sense_select_list_right: {
      Serial.println("pressed right");
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      if(controls_menu_edit_i < (MAX_MAIN_REGISTERS-2)) // -2, one for register 0, 1 because the display starts at 1, not 0.
        controls_menu_edit_i++;
        updateControlsMenu();
        render_list(&stuff_to_render);
      break;
    }
    break;
    }
    
    case phi_prompt_sense_select_list_escape:
      updateMenuTitleList("Settings", top_menu_items, sizeof(top_menu_items)/sizeof(top_menu_items[0]), &topMenuHandler);
    break;

    case phi_prompt_sense_select_list_enter:
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      char temp[13];
      sprintf(temp, "Edit Ctrl %02d", controls_menu_edit_i+1);
      initControlsEditMenu();
      updateMenuTitleList(temp, controls_edit_menu_items, sizeof(controls_edit_menu_items)/sizeof(controls_edit_menu_items[0]), &controlsEditMenuHandler);
      break;

      case 1:
      updateMenuTitleList("Settings", top_menu_items, sizeof(top_menu_items)/sizeof(top_menu_items[0]), &topMenuHandler);
      break;

      default:
      break;
    }
    break;
  }
}

void initControlsEditMenu() {
  Control *control = getControls()[controls_menu_edit_i];
  if (control->enabled)
    controls_edit_menu_enabled=true;
  if (control->loco_address)
    controls_edit_menu_loco_address=control->loco_address;
  if (control->dir_pin)
    controls_edit_menu_dir_pin=control->dir_pin;
  if (control->speed_pin)
    controls_edit_menu_speed_pin=control->speed_pin;
  updateControlsEditMenu();
}
void updateControlsEditMenu() {
  sprintf(controls_edit_menu_item01, "Enabled: %s", controls_edit_menu_enabled ? " <True>" : "<False>");
  sprintf(controls_edit_menu_item02, "LocoAddr:<%05d>", controls_edit_menu_loco_address);
  sprintf(controls_edit_menu_item03, "Dir pin:    <%02d>", controls_edit_menu_dir_pin);
  sprintf(controls_edit_menu_item04, "Speed pin: A<%02d>", controls_edit_menu_speed_pin - NUM_DIGITAL_PINS + NUM_ANALOG_INPUTS);
}

void controlsEditMenuHandler() {
  int temp1=sense_select_list(&stuff_to_render);

  switch (temp1) {
    case phi_prompt_content_needs_update:
    render_list(&stuff_to_render);
    break;

    case phi_prompt_sense_select_list_left: {
      Serial.println("pressed left");
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      controls_edit_menu_enabled = !controls_edit_menu_enabled;
      updateControlsEditMenu();
      break;

      case 1:
      if(controls_edit_menu_loco_address > 0)
        controls_edit_menu_loco_address--;
        updateControlsEditMenu();
      break;

      case 2:
      if(controls_edit_menu_dir_pin > 0)
        controls_edit_menu_dir_pin--;
        updateControlsEditMenu();
      break;

      case 3:
      if(controls_edit_menu_speed_pin > 0)
        controls_edit_menu_speed_pin--;
        updateControlsEditMenu();
      break;
    }
    render_list(&stuff_to_render);
    break;
    }

    case phi_prompt_sense_select_list_right: {
      Serial.println("pressed right");
    int menu_pointer_1=stuff_to_render.low.i; // Get the selected item number and store it in the menu pointer.
    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
    {
      case 0:
      controls_edit_menu_enabled = !controls_edit_menu_enabled;
      updateControlsEditMenu();
      break;

      case 1:
      if(controls_edit_menu_loco_address < 10294)
        controls_edit_menu_loco_address++;
        updateControlsEditMenu();
      break;

      case 2:
      if(controls_edit_menu_dir_pin < (NUM_DIGITAL_PINS - NUM_ANALOG_INPUTS - 1))
        controls_edit_menu_dir_pin++;
        updateControlsEditMenu();
      break;

      case 3:
      if(controls_edit_menu_speed_pin < (NUM_ANALOG_INPUTS - 1))
        controls_edit_menu_speed_pin++;
        updateControlsEditMenu();
      break;
    }
    render_list(&stuff_to_render);
    break;
    }
    
    case phi_prompt_sense_select_list_escape:
      updateMenuTitleList("Controls", controls_menu_items, sizeof(controls_menu_items)/sizeof(controls_menu_items[0]), &controlsMenuHandler);
    break;

    case phi_prompt_sense_select_list_enter:
    Control *control = getControls()[controls_menu_edit_i];
    control->enabled=controls_edit_menu_enabled;
    control->loco_address=controls_edit_menu_loco_address;
    control->dir_pin=controls_edit_menu_dir_pin;
    control->speed_pin=controls_edit_menu_speed_pin ;
    controls_edit_menu_enabled=false;
    controls_edit_menu_loco_address=0;
    controls_edit_menu_dir_pin=0;
    controls_edit_menu_speed_pin=0;
    updateMenuTitleList("Controls", controls_menu_items, sizeof(controls_menu_items)/sizeof(controls_menu_items[0]), &controlsMenuHandler);
    break;
  }
}

void handleDisplay() {
  if (menu_displayed) {
    currentDisplayHandler();
  } else {
    char button_press=my_btns->getKey();
    if (button_press!=NO_KEY) {
      updateMenuTitleList("Settings", top_menu_items, sizeof(top_menu_items)/sizeof(top_menu_items[0]), &topMenuHandler);
      menu_displayed=true;
    }
  }
}

void updateMenuTitleList(char* title, char** list, int list_size, void (*handler)()) {
  lcd->display();
  lcd->clear();
  lcd->noBlink();
  center_text(title);
  stuff_to_render.ptr.list=list;
  stuff_to_render.low.i=0; // Default item highlighted on the list
  stuff_to_render.high.i=list_size-1; // Last item of the list is size of the list - 1.
  currentDisplayHandler=handler;
  render_list(&stuff_to_render);
}

void exitMenu() {
  currentDisplayHandler=0;
  lcd->clear();
  lcd->noDisplay();
  menu_displayed=false;
}
//
//void show_credit()
//{
//  // Display credits
//  phi_prompt_struct myLongMsg;
//
//  lcd.clear();
//  lcd.noBlink();
//  center_text("Credits"); // Prompt user for input. Use center_text to display center-aligned.
//  myLongMsg.ptr.msg_P=msg_00; // Assign the address of the text string to the pointer.
//  myLongMsg.low.i=0; // Default text starting position. 0 is highly recommended.
//  myLongMsg.high.i=strlen_P(msg_00); // Position of the last character in the text string, which is size of the string - 1.
//  myLongMsg.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
//  myLongMsg.step.c_arr[1]=lcd_columns-1; // one col list
//  myLongMsg.col=0; // Display the text area starting at column 0
//  myLongMsg.row=1; // Display the text area starting at row 0
//  myLongMsg.option=1; // Option 0, display classic message, option 1, display message with scroll bar on right.
//
//  text_area_P(&myLongMsg);
//}
//// Menu texts
//PROGMEM const char top_menu_item00[]="Collect data";
//PROGMEM const char top_menu_item01[]="Upload to PC";
//PROGMEM const char top_menu_item02[]="Set Menu Style";
//PROGMEM const char top_menu_item03[]="File management";
//PROGMEM const char top_menu_item04[]="Show credit See who spent so much time making it happen!";
//PROGMEM const char top_menu_item05[]="Exit";
//PROGMEM const char * const top_menu_items[] = {top_menu_item00, top_menu_item01, top_menu_item02, top_menu_item03, top_menu_item04, top_menu_item05};
//
//PROGMEM const char sub_menu_1_item00[]="Load file";
//PROGMEM const char sub_menu_1_item01[]="Save file";
//PROGMEM const char sub_menu_1_item02[]="Delete file";
//PROGMEM const char sub_menu_1_item03[]="Back to main menu";
//PROGMEM const char * const sub_menu_1_items[] = {sub_menu_1_item00, sub_menu_1_item01, sub_menu_1_item02, sub_menu_1_item03};
//
//PROGMEM const char menu_style00[]="Arrow/dot indicator on";
//PROGMEM const char menu_style01[]="Index1 on-excludes index2";
//PROGMEM const char menu_style02[]="Index2 on-excludes index1";
//PROGMEM const char menu_style03[]="Autoscroll long items on";
//PROGMEM const char menu_style04[]="Flashing cursor on";
//PROGMEM const char menu_style05[]="Center on item on";
//PROGMEM const char menu_style06[]="Scroll bar to the right on";
//PROGMEM const char * const menu_styles[] = {menu_style00, menu_style01, menu_style02, menu_style03, menu_style04, menu_style05, menu_style06};
//
////This program is the main menu. It handles inputs from the keys, updates the menu or executes a certain menu function accordingly.
//int global_style=109; // This is the style of the menu
//
//phi_prompt_struct * init_top_menu() {
//  phi_prompt_struct myMenu; // This structure stores the main menu.
//
//// Initialize the top menu
//  myMenu.ptr.list=(char**)&top_menu_items; // Assign the list to the pointer
//  myMenu.low.i=0; // Default item highlighted on the list
//  myMenu.high.i=5; // Last item of the list is size of the list - 1.
//  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
//  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
//  myMenu.step.c_arr[1]=1; // one col list
//  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
//  myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // x for additional feature such as an index
//  myMenu.col=0; // Display menu at column 0
//  myMenu.row=1; // Display menu at row 1
//  myMenu.option=global_style; // Option 0, display classic list, option 1, display 2X2 list, option 2, display list with index, option 3, display list with index2.
//
//  return &myMenu;
//}
//
//void display_menu(char* title, phi_prompt_struct* myMenu) {
//}
//void top_menu()
//{
//  if (!current_menu)
//    current_menu=init_top_menu();
//  int menu_pointer_1=0; // This stores the menu choice the user made.
//
////  bool stay_in_menu=true;
////  while(stay_in_menu) // This loops every time a menu item is selected.
//  {
//
////    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
////    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. Auto fit the size of the list to the screen. Length in characters of the longest list item.
////    myMenu.step.c_arr[3]=lcd_columns-4-((global_style&phi_prompt_index_list)!=0); // This makes sure the change of menu style is updated if there is a menu style option in this level of menu. x for additional feature such as an index
//
//    while(render)
//      center_text("Top Menu");
//      render=render_list(&myMenu);
//
//    int temp1=sense_select_list(current_menu);
//    if (temp1==phi_prompt_content_needs_update) {
//      render=1;
//    } else {
//      switch (temp1) {
//        case phi_prompt_escape:
//        current_menu_function=0;
//        lcd.clear();
//        lcd.noDisplay();
//        break;
//
//        case phi_prompt_enter:
//        render=1;
//        Serial.println("Pressed Enter!");
////    menu_pointer_1=myMenu.low.i; // Get the selected item number and store it in the menu pointer.
////    switch (menu_pointer_1) // See which menu item is selected and execute that correspond function
////    {
////      case 0:
////      top_menu_function_1();
////      break;
////      case 1:
////      top_menu_function_2();
////      break;
////      
////      case 2:
////      top_menu_function_3(&myMenu); // This is the setting function that changes how menu is rendered
////      break;
////      
////      case 3:
////      sub_menu_1(); // This is actually the sub menu.
////      break;
////  
////      case 4:
////      top_menu_function_5(); // If this were a sub level menu, this last one should return to previous level by using "return".
////      break;
////
////      case 5:
////      lcd.clear();
////      lcd.noDisplay();
////      stay_in_menu=false;
////      break;
////  
////      default:
////      break;
////    }
//        break;
//
//        default:
//        break;
//      }
//    }
////        if ((temp1==phi_prompt_content_needs_update)||(render)) render=render_list(&myMenu);// Render the list if update is needed either because the user scrolled or the renderer says so (scrolling long item).
////        if ((temp1==1)||(temp1==-1)) return(temp1);
//    //    int button_pushed = select_list(&myMenu); // Use the select_list to ask the user to select an item of the list, that is a menu item from your menu.
//
//
//  }
//}
//
//// Menu functions go here. The functions are called when their menu items are selected. They are called only once so if you want to do something repeatedly, make sure you have a while loop.
//void top_menu_function_1() //Replace this with the actual function of menu item #1
//{
//  lcd.clear();
//  lcd.print("Collecting data.");
//  lcd.setCursor(0,1);
//  lcd.print("-Your code here-");
//  wait_on_escape(4000);
//}
//
//void top_menu_function_2() //Replace this with the actual function of menu item #2
//{
//  lcd.clear();
//  lcd.print("Sending data....");
//  lcd.setCursor(0,1);
//  lcd.print("-Your code here-");
//  wait_on_escape(4000);
//}
//
//void top_menu_function_3(phi_prompt_struct * para) //Settings
//{
//  char buffer[32];
//  byte opt=global_style, yn;
//  
//  lcd.clear();
//  sprintf(buffer, "%s%d","Current style:", global_style);
//  lcd.print(buffer);
//  wait_on_escape(2000);
//  for (byte i=0;i<7;i++)
//  {
//    lcd.clear();
//    strcpy_P(buffer,(char*)pgm_read_word(menu_styles+i));
//    yn=yn_dialog(buffer);
//    bitWrite(opt,i,yn);
//  }
//
//  lcd.clear();
//  sprintf(buffer, "%s%d","New style:", global_style=opt);
//  lcd.print(buffer);
//  wait_on_escape(2000);
//  lcd.clear();
//}
//
//void sub_menu_1() // This is the sub_menu_1
//{
//  int menu_pointer_1=0;
//  phi_prompt_struct myMenu; // This structure stores the sub menu.
//
//// Initialize the top menu
//  myMenu.ptr.list=(char**)&sub_menu_1_items; // Assign the list to the pointer
//  myMenu.low.i=0; // Default item highlighted on the list
//  myMenu.high.i=3; // Last item of the list is size of the list - 1.
//  myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
//  myMenu.step.c_arr[0]=lcd_rows-1; // rows to auto fit entire screen
//  myMenu.step.c_arr[1]=1; // one col list
//  myMenu.step.c_arr[2]=0; // y for additional feature such as an index
//  myMenu.step.c_arr[3]=lcd_columns-4; // x for additional feature such as an index
//  myMenu.col=0; // Display prompt at column 0
//  myMenu.row=1; // Display prompt at row 1
//  myMenu.option=global_style;
//
//  while(1)
//  {
//    lcd.clear();  // Refresh menu if a button has been pushed
//    center_text("File Menu");
//
//    myMenu.option=global_style; // This makes sure the change of menu style is updated if there is a menu style option in this level of menu.
//    myMenu.width=lcd_columns-((global_style&phi_prompt_arrow_dot)!=0)-((global_style&phi_prompt_scroll_bar)!=0); // Auto fit the size of the list to the screen. Length in characters of the longest list item.
//
//
//    select_list(&myMenu);
//    menu_pointer_1=myMenu.low.i;
//    switch (menu_pointer_1)
//    {
//      case 0:
//      sub_menu_1_function_1();
//      break;
//      case 1:
//      sub_menu_1_function_2();
//      break;
//      
//      case 2:
//      sub_menu_1_function_3();
//      break;
//      
//      case 3: // This option returns to previous level.
//      return; // This returns to previous menu level. Only sub menus should have this unless the top level menu also returns.
//      break;
//  
//      default:
//      break;
//    }
//  }
//}
//
//void top_menu_function_5() //Replace this with the actual function of menu item #2
//{
//  show_credit();
//}
//
//void sub_menu_1_function_1()
//{
//  lcd.clear();
//  lcd.print("Loading file...");
//  lcd.setCursor(0,1);
//  lcd.print("-Your code here-");
//  wait_on_escape(4000);
//}
//
//void sub_menu_1_function_2()
//{
//  lcd.clear();
//  lcd.print("Saving file....");
//  lcd.setCursor(0,1);
//  lcd.print("-Your code here-");
//  wait_on_escape(4000);
//}
//
//void sub_menu_1_function_3()
//{
//  lcd.clear();
//  lcd.print("Deleting file..");
//  lcd.setCursor(0,1);
//  lcd.print("-Your code here-");
//  wait_on_escape(4000);
//}
