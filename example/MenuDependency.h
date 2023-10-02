#ifndef MENUDEPENDENCY_H
#define MENUDEPENDENCY_H

#include <memory>
#include "device-manager/modbus/ModbusClient.hpp"
#include "device-manager/modbus/ModbusDevice.hpp"

constexpr uint16_t DEFAULT_PORT = 502;
/**
 * Information needed for menu items to perform their actions.
 * Rewrite as needed for your application.
 */
struct MenuDependency {
  std::unique_ptr<RH::ModbusClient> modbusClient;
  std::shared_ptr<RH::ModbusDevice> modbusDevice;
  std::string host{"127.0.0.1"};
  uint32_t port{DEFAULT_PORT};
};

#endif  // MENUDEPENDENCY_H
