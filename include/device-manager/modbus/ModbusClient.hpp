#ifndef MODBUS_TCP_MODBUSCLIENT_HPP
#define MODBUS_TCP_MODBUSCLIENT_HPP

#include "ModbusDevice.hpp"
#include <memory>
#include <string>
#include <map>

namespace RH {

class ModbusClient {
public:
  ModbusClient(std::string_view host, uint16_t port);
  virtual ~ModbusClient() = default;

  bool connect() noexcept;
  void closeConnection() const noexcept;

  [[nodiscard]] bool isConnected() const noexcept;

  std::shared_ptr<ModbusDevice> addDevice(uint32_t newId) noexcept;

private:
  const std::string host;
  const uint16_t port;
  std::map<uint32_t, std::shared_ptr<ModbusDevice>> devices;

  // Pointer to implementation pattern to not expose connection handle that should not be exposed in public header.
  struct Impl;
  std::shared_ptr<Impl> pImpl;
};
}
#endif  // MODBUS_TCP_MODBUSCLIENT_HPP
