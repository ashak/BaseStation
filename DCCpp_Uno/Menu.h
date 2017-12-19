#ifndef MENU_H
#define MENU_H
#include <phi_prompt.h>
#define phi_prompt_sense_select_list_escape -1
#define phi_prompt_sense_select_list_enter 1
#define phi_prompt_sense_select_list_left -2
#define phi_prompt_sense_select_list_right -3
class Menu {
  public:
    Menu::Menu(char*, int);
    Menu* Menu::getParent();
    Menu* Menu::handler(phi_prompt_struct*);
    void Menu::prepare(phi_prompt_struct*);
    void Menu::setParent(Menu*);
  private:
    int Menu::listSize();

    char* title;
    Menu* parent;
    char** list;
};
#endif
