#ifndef MENU_H
#define MENU_H
#include <phi_prompt.h>
#include "MenuItem.h"
#define phi_prompt_sense_select_list_escape -1
#define phi_prompt_sense_select_list_enter 1
#define phi_prompt_sense_select_list_left -2
#define phi_prompt_sense_select_list_right -3
class MenuItem;

class Menu {
  public:
    Menu::Menu(char*, int);
    void Menu::addMenuItem(MenuItem*);
    void Menu::setForceRender();
    Menu* Menu::getParent();
    char* Menu::getTitle();
    Menu* Menu::handler(phi_prompt_struct*);
    virtual void Menu::prepare(phi_prompt_struct*);
    void Menu::setParent(Menu*);
    void Menu::updateMenuItems();
  private:
    char** Menu::prepareMenuItems();

    int added_menu_items;
    bool force_render;
    int num_menu_items;
    char* title;
    Menu* parent;
    MenuItem** menu_items;
    char** prepared_menu_items;
};
#endif
