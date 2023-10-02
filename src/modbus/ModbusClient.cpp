#include "device-manager/modbus/ModbusClient.hpp"

#include "ModbusConnectionHandle.hpp"

#include "spdlog/spdlog.h"

namespace RH {
struct ModbusClient::Impl {
  ModbusConnectionHandle connectionHandle;
};

ModbusClient::ModbusClient(std::string_view newHost, uint16_t newPort) : host(newHost), port(newPort),
    pImpl(std::make_shared<Impl>()){}

bool ModbusClient::connect() noexcept {
  if(!pImpl->connectionHandle.modbusHandle) {
    pImpl->connectionHandle.modbusHandle = std::make_unique<modbus>(host, port);
  }
  try {
    SPDLOG_INFO("Connecting...");
  } catch (...){

  }
  return pImpl->connectionHandle.modbusHandle->modbus_connect();
}
void ModbusClient::closeConnection() const noexcept {
  if(!pImpl->connectionHandle.modbusHandle) {
    return;
  }
  pImpl->connectionHandle.modbusHandle->modbus_close();
}
bool ModbusClient::isConnected() const noexcept {
  if(!pImpl->connectionHandle.modbusHandle) {
    return false;
  }
  return pImpl->connectionHandle.modbusHandle->is_connected();
}

std::shared_ptr<ModbusDevice> ModbusClient::addDevice(uint32_t newId) noexcept {
  if(!isConnected()){
    try {
      SPDLOG_ERROR("Cannot add device {} before creating a new connection", newId);
    } catch(...) {
      return {};
    }
    return {};
  }
  auto device = devices.find(newId);
  if(device != devices.end()) {
    try {
      SPDLOG_INFO("Device {} has already been added", newId);
    } catch(...) {
      return device->second;
    }
    return device->second;
  }
  devices[newId] = std::shared_ptr<ModbusDevice>(new (std::nothrow) ModbusDevice(newId, &(pImpl->connectionHandle)));
  return devices[newId];
}
}
