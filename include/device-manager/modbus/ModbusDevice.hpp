#ifndef MODBUS_TCP_MODBUSDEVICE_HPP
#define MODBUS_TCP_MODBUSDEVICE_HPP

#include <string>
#include <vector>
#include <memory>
namespace RH {
class ModbusConnectionHandle;

class ModbusDevice {
  friend class ModbusClient;
public:
  ModbusDevice() = delete;
  virtual ~ModbusDevice() = default;


  // FOR ALL FUNCTIONS TODO: NEED TO RETURN AN OPTIONAL OR HOW TO REPORT ERROR. MAYBE USE RESULT CLASS.
  /**
   * Function to get the Vendor name.
   *
   * It is synchronous.
   *
   * Modbus Function 43.
   * @return The vendor name.
   */
  std::string getVendorName() const;

  /**
   * Function to get the Product code.
   *
   * Synchronous function.
   *
   * @return The product code.
   */
  std::string getProductCode() const;

  /**
   * Function to get the major and minor revision of the product
   *
   * Synchronous function.
   *
   * @return The major and minor revision
   */
  std::string getMajorMinorRevision() const;

  /**
   * Method to read the coils from a device.
   *
   * One can set the start address and the number of coils to be written.
   * Coils are addressed starting at zero
   *
   * Modbus Function 01
   *
   * @param address start address of the coil
   * @param amount Number of coils to read
   * @param buffer Pointer to buffer of where the result will be stored
   * @return If the operation was successful.
   */
  int readCoils(uint16_t address, uint16_t amount, bool *buffer) noexcept;

  /**
   * This function is used to read the status of discrete inputs in a remote device.
   * You can specify the starting address, i.e. the address of the first input specified, and the number of inputs.
   *
   * The inputs are addressed starting at zero, therefore discrete inputs numbered 1-16 are addressed as 0-15.
   *
   * Status is indicated as True= ON; False= OFF.
   *
   * This method is synchronous.
   *
   * Modbus Function 02
   *
   * @param address Start address of the discrete input
   * @param amount Number of inputs to be read
   * @param buffer Buffer where the results will be stored
   * @return If the operation was successful.
   */
  int readDiscreteInputs(uint16_t address, uint16_t amount, bool *buffer) noexcept;
  /**
   * This function is used to read blocks of holding registers in a remote device.
   * You can specify the starting register address and the number of registers.
   *
   * The registers are addressed starting at zero, therefore registers numbered 1-16 are addressed as 0-15.
   *
   * This method is synchronous.
   *
   * Modbus Function 03
   *
   * @param address Starting address of the register to read
   * @param amount Number of registers to read
   * @param buffer Buffer where the results will be stored
   * @return If the operation was successful
   */
  int readHoldingRegisters(uint16_t address, uint16_t amount, uint16_t *buffer) noexcept;
  /**
   * This function is used to read input registers in a remote device.
   * You can specify the starting register address and the number of registers.
   *
   * The registers are addressed starting at zero, therefore input registers numbered 1-16 are addressed as 0-15.
   *
   * Modbus Function 04
   *
   * @param address Start address of the register to read
   * @param amount Number of registers to read
   * @param buffer Buffer where the results will be stored
   * @return If the operation was successful
   */
  int readInputRegisters(uint16_t address, uint16_t amount, uint16_t *buffer) noexcept;

  /**
   * This function is used to force one or multiple coils in a sequence of coils to either ON (true) or OFF (false)
   * state in a remote device. You can specify the coil references to be forced.
   *
   * Coils are addressed starting at zero, therefore coil numbered 1 is addressed as 0.
   *
   * A maximum of 1968 coils can be written at once, due to size limitations of the Modbus protocol data unit.
   *
   *    - Modbus Function 05: Only one value in the vector
   *    - Modbus Function 15: More than one value in the vector
   *
   * @param address Starting address of the coil to be written
   * @param valueToWrite Value(s) to be written
   * @return If the value was successfully written.
   */
  int writeCoil(uint16_t address, std::vector<bool>& valueToWrite) noexcept;
  /**
   * This function is used to write in one or multiple blocks of contiguous registers (1 to 123 registers)
   * in a remote device.
   *
   * A maximum of 123 registers can be written at once, due to size limitations of the Modbus protocol data unit.
   *
   *    - Modbus Function 06: Only one value in the vector
   *    - Modbus Function 16: More than one value in the vector
   * @param address Starting address of the register to be written
   * @param value Value(s) to be written
   * @return If the value was successfully written
   */
  int writeRegister(uint16_t address, std::vector<uint16_t>& value) noexcept;

protected:
  /**
   * Protected constructor that should only be invoked by the ModbusClient object.
   * @param newId ID of this device.
   * @param connectionHandle Pointer to connection handle
   */
  ModbusDevice(uint32_t newId, ModbusConnectionHandle* connectionHandle);

private:
  const uint32_t id;      ///< ID of this device

  // Pointer to implementation pattern to not expose connection handle that should not be exposed in public header.
  struct Impl;
  std::shared_ptr<Impl> pImpl;
};
}  // namespace RH

#endif  // MODBUS_TCP_MODBUSDEVICE_HPP
