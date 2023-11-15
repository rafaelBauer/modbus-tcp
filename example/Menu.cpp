#include "Menu.h"

#include <algorithm>
#include <sstream>

Menu::Menu(std::string_view text, MenuDependency& dependency) : MenuItem(text, dependency) {}

void Menu::go() {
  terminate = false;
  while (!terminate){
    int32_t itemnum(1);
    std::cout << "+----------------------------------------------------------+\n";
    std::cout << "| " << text << "\n";
    std::cout << "+==========================================================+\n";
    std::cout << "| ";
    showBody();
    std::cout << "\n| Choose: ";
    std::for_each(items.begin(), items.end(), [&](std::unique_ptr<MenuItem> const& item) {
      std::cout << "\n| " << itemnum << "\t" << item->text;
      itemnum++;
    });
    std::cout << "\n|\n| 0\tExit\n+----------------------------------------------------------+\n";
    //    std::cout << "\n\n\tYour choice: ";
    uint32_t choice = 0;
    if (getUintFromString(getInput(), choice)) {
      if ((choice > 0) && (static_cast<uint32_t>(items.size()) >= choice)) {
        items.at(choice - 1)->go();
      }
    }
    if (choice == 0) {
      terminate = true;
    }
  }
}

std::string MenuItem::getInput() {
  std::string input;
  getline(std::cin, input);
  return (input);
}

bool MenuItem::getIntFromString(const std::string& str, int32_t& num) {
  // This code converts from string to number safely.
  std::stringstream stream(str);
  if (!(stream >> num)) {
    std::cout << "Invalid number!" << '\n';
    return false;
  }
  return true;
}

bool MenuItem::getUintFromString(const std::string& str, uint32_t& num) {
  // This code converts from string to number safely.
  std::stringstream stream(str);
  if (!(stream >> num)) {
    std::cout << "Invalid number!" << '\n';
    return false;
  }
  return true;
}

bool MenuItem::getUintFromHexString(const std::string& str, uint32_t& num) {
  // This code converts from string to number safely.
  std::stringstream stream;
  stream << std::hex << str;
  if (!(stream >> num)) {
    std::cout << "Invalid number!" << '\n';
    return false;
  }
  return true;
}

bool MenuItem::getDoubleFromString(const std::string& str, double& num) {
  // This code converts from string to number safely.
  std::stringstream stream(str);
  if (!(stream >> num)) {
    std::cout << "Invalid number!" << '\n';
    return false;
  }
  return true;
}

void MenuItem::showText() {
  std::cout << text << '\n';
}

void Menu::showBody() {}
