#ifndef _MENUITEM_H
#define _MENUITEM_H

#include <string_view>

#include "MenuDependency.h"

/**
 * A menu item, selectable by the user.
 * The item could perform a specific action or be another Menu in itself (see Menu).
 */
class MenuItem {
public:
  MenuItem(std::string_view text, MenuDependency& dependency) : text(std::move(text)), dependency(dependency){};
  virtual ~MenuItem(){};

  /**
   * Print the item to screen.
   */
  virtual void showText();

  /**
   * Navigate to this item and perform its action.
   */
  virtual void go() = 0;

  /**
   * @return A line from standard input.
   */
  [[nodiscard]] static std::string getInput();

  /**
   * Parse a signed integer from a string.
   * @param str the input string
   * @param num the output number
   * @return true when converted correctly, false otherwise
   */
  [[nodiscard]] static bool getIntFromString(const std::string& str, int32_t& num);

  /**
   * Parse an unsigned integer from a string.
   * @param str the input string
   * @param num the output number
   * @return true when converted correctly, false otherwise
   */
  [[nodiscard]] static bool getUintFromString(const std::string& str, uint32_t& num);

  [[nodiscard]] static bool getUintFromHexString(const std::string& str, uint32_t& num);

  /**
   * Parse a double from a string.
   * @param str the input string
   * @param num the output number
   * @return true when converted correctly, false otherwise
   */
  [[nodiscard]] static bool getDoubleFromString(const std::string& str, double& num);

  /**
   * A descriptive text for this menu item.
   */
  const std::string_view text;

  /**
   * Information needed by the item in order to perform its action.
   */
  MenuDependency& dependency;
};

#endif  // HAL_MENUITEM_H
