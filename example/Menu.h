#ifndef MENU_H_
#define MENU_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "MenuItem.h"

/**
 * A menu that prints possible item choices to the user.
 */
class Menu : public MenuItem {
public:
  Menu() = delete;
  Menu(std::string_view text, MenuDependency& dependency);
  ~Menu() override = default;
  void go() override;

  /**
   * A function called prior to printing menu items, in case extra information should be printed out.
   */
  virtual void showBody();

  /**
   * Add menu items to this menu.
   * @param item to be added to this menu
   */
  void addItem(std::unique_ptr<MenuItem> item) {
    items.push_back(std::move(item));
  }

  /**
   * Remove all items from this menu.
   */
  void clearItems() {
    items.clear();
  }

private:
  /**
   * The collection of items in this menu.
   */
  std::vector<std::unique_ptr<MenuItem> > items;

  /**
   * If the menu should quit its execution loop (i.e. quit waiting for user inputs).
   */
  bool terminate = false;
};

#endif /* MENU_H_ */
