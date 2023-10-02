#ifndef MENU_MAINMENU_H_
#define MENU_MAINMENU_H_

#include "Menu.h"

class MainMenu : public Menu {
public:
  explicit MainMenu(MenuDependency& dependency);
  ~MainMenu() override = default;
};

#endif /* MENU_MAINMENU_H_ */
