#include "device-manager/modbus/ModbusDevice.hpp"
#include "ModbusConnectionHandle.hpp"

#include <array>
namespace RH {

struct ModbusDevice::Impl {
  Impl(ModbusConnectionHandle* newConnectionHandle) : connectionHandle(newConnectionHandle) {}
  ModbusConnectionHandle* connectionHandle;
};

ModbusDevice::ModbusDevice(uint32_t newId, ModbusConnectionHandle* newConnectionHandle) :
    id(newId), pImpl(std::make_shared<Impl>(newConnectionHandle)) {}

std::string ModbusDevice::getVendorName() const {
  (void)pImpl->connectionHandle->modbusHandle; //Just so compiler doesn't complain that it can be static
  return "Not Implemented";
}
std::string ModbusDevice::getProductCode() const {
  (void)pImpl->connectionHandle->modbusHandle; //Just so compiler doesn't complain that it can be static
  return "Not Implemented";
}
std::string ModbusDevice::getMajorMinorRevision() const {
  (void)pImpl->connectionHandle->modbusHandle; //Just so compiler doesn't complain that it can be static
  return "Not Implemented";
}
int ModbusDevice::readCoils(uint16_t address, uint16_t amount, bool *buffer) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);
  return pImpl->connectionHandle->modbusHandle->modbus_read_coils(address, amount, buffer);
}
int ModbusDevice::readDiscreteInputs(uint16_t address, uint16_t amount, bool *buffer) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);
  return pImpl->connectionHandle->modbusHandle->modbus_read_input_bits(address, amount, buffer);
}
int ModbusDevice::readHoldingRegisters(uint16_t address, uint16_t amount, uint16_t *buffer) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);
  return pImpl->connectionHandle->modbusHandle->modbus_read_holding_registers(address, amount, buffer);
}
int ModbusDevice::readInputRegisters(uint16_t address, uint16_t amount, uint16_t *buffer) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);
  return  pImpl->connectionHandle->modbusHandle->modbus_read_input_registers(address, amount, buffer);
}
int ModbusDevice::writeCoil(uint16_t address, std::vector<bool> &valueToWrite) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);

  constexpr uint16_t MAX_WRITE_BUFFER_SIZE = 256; // This is here now just because of a hack..
  const uint16_t numberOfValuesToWrite = static_cast<uint16_t>(valueToWrite.size());
  if(numberOfValuesToWrite > MAX_WRITE_BUFFER_SIZE) {
    return -1;
  }

  if(numberOfValuesToWrite <= 1) {
    return pImpl->connectionHandle->modbusHandle->modbus_write_coil(address, valueToWrite.front());
  }

  // Have to do this little "hack" because a vector<bool> can be optimized and the library we are using
  // needs a pointer to a buffer... so we need to build the buffer. Need to remove the library in the near future.
  std::array<bool, MAX_WRITE_BUFFER_SIZE> bufferToWrite{};
  for (size_t i = 0; i < valueToWrite.size(); i++) {
    try {
      bufferToWrite.at(i) = valueToWrite[i];
    } catch (...) {

    }
  }
  return pImpl->connectionHandle->modbusHandle->modbus_write_coils(address, numberOfValuesToWrite, bufferToWrite.data());
}
int ModbusDevice::writeRegister(uint16_t address, std::vector<uint16_t> &valueToWrite) noexcept {
  pImpl->connectionHandle->modbusHandle->modbus_set_slave_id(id);
  const uint16_t numberOfValuesToWrite =  static_cast<uint16_t>(valueToWrite.size());
  if(numberOfValuesToWrite <= 1) {
    return pImpl->connectionHandle->modbusHandle->modbus_write_register(address, valueToWrite.front());
  }
  return pImpl->connectionHandle->modbusHandle->modbus_write_registers(address, numberOfValuesToWrite, valueToWrite.data());
}
}
