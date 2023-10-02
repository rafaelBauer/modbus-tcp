#ifndef MODBUS_TCP_MODBUSCONNECTIONHANDLE_HPP
#define MODBUS_TCP_MODBUSCONNECTIONHANDLE_HPP

#include "modbus.h"

namespace RH {

class ModbusConnectionHandle {
public:
  std::unique_ptr<modbus> modbusHandle;
};

}  // namespace RH

#endif  // MODBUS_TCP_MODBUSCONNECTIONHANDLE_HPP
