#include "MainMenu.h"

#include "spdlog/spdlog.h"
#include <thread>


struct SetHost : public MenuItem {
  explicit SetHost(MenuDependency& dependency) : MenuItem("Set IP to connect with Client", dependency){};
  ~SetHost() override = default;
  void go() override {
    std::cout << "Server IP address: ";
    dependency.host = getInput();
  }
};

struct SetPort : public MenuItem {
  explicit SetPort(MenuDependency& dependency) : MenuItem("Set Port to connect with Client", dependency){};
  ~SetPort() override = default;
  void go() override {
    std::cout << "Server port: ";
    const bool converted = getUintFromString(getInput(), dependency.port);
    if(!converted) {
      SPDLOG_ERROR("Invalid port. Must be a number");
    }
  }
};

struct OpenConnection : public MenuItem {
  explicit OpenConnection(MenuDependency& dependency) : MenuItem("Open Connection with server", dependency){};
  ~OpenConnection() override = default;
  void go() override {
    dependency.modbusClient = std::make_unique<RH::ModbusClient>(dependency.host, dependency.port);
    const bool connectionSuccessful = dependency.modbusClient->connect();
    if(!connectionSuccessful) {
      SPDLOG_ERROR("Could not connect to {}:{}", dependency.host, dependency.port);
    }

  }
};

struct OpenConnectionToSlave : public MenuItem {
  explicit OpenConnectionToSlave(MenuDependency& dependency) : MenuItem("Open Connection with slave", dependency){};
  ~OpenConnectionToSlave() override = default;
  void go() override {
    if(!dependency.modbusClient) {
      SPDLOG_ERROR("Open the connection with the server first.");
      return;
    }
    std::cout << "Set the slave ID: ";
    uint32_t slaveId = 0;
    const bool converted = getUintFromString(getInput(), slaveId);
    if(!converted) {
      SPDLOG_ERROR("Invalid number");
    }
    dependency.modbusDevice = dependency.modbusClient->addDevice(slaveId);
  }
};

struct ReadInputRegister : public MenuItem {
  explicit ReadInputRegister(MenuDependency& dependency) : MenuItem("Read slave input register", dependency){};
  ~ReadInputRegister() override = default;
  void go() override {
    if(!dependency.modbusDevice) {
      SPDLOG_ERROR("Open the connection with the slave first.");
      return;
    }
    std::cout << "Register address in hex without '0x': ";
    uint32_t registerAddress = 0;
    const bool converted = getUintFromHexString(getInput(), registerAddress);
    if(!converted) {
      SPDLOG_ERROR("Invalid number");
    }
    uint16_t value;
    dependency.modbusDevice->readInputRegisters(registerAddress, 1, &value);
    SPDLOG_INFO("Register {:X} has value {:X}", registerAddress, value);
  }
};

struct WriteRegister : public MenuItem {
  explicit WriteRegister(MenuDependency& dependency) : MenuItem("Write to slave register", dependency){};
  ~WriteRegister() override = default;
  void go() override {
    if(!dependency.modbusDevice) {
      SPDLOG_ERROR("Open the connection with the slave first.");
      return;
    }
    std::cout << "Register address in hex without '0x': ";
    uint32_t registerAddress = 0;
    const bool converted = getUintFromHexString(getInput(), registerAddress);
    if(!converted) {
      SPDLOG_ERROR("Invalid number");
      return;
    }

    std::cout << "Value to write in hex without '0x': ";
    uint32_t value = 0;
    const bool convertedValue = getUintFromHexString(getInput(), value);
    if(!convertedValue) {
      SPDLOG_ERROR("Invalid number");
      return;
    }

    std::vector<uint16_t> values{static_cast<uint16_t>(value)};
    dependency.modbusDevice->writeRegister(registerAddress, values);
  }
};

MainMenu::MainMenu(MenuDependency& dependency) : Menu("Main Menu", dependency) {
  addItem(std::unique_ptr<MenuItem>(new SetHost(dependency)));
  addItem(std::unique_ptr<MenuItem>(new SetPort(dependency)));
  addItem(std::unique_ptr<MenuItem>(new OpenConnection(dependency)));
  addItem(std::unique_ptr<MenuItem>(new OpenConnectionToSlave(dependency)));
  addItem(std::unique_ptr<MenuItem>(new ReadInputRegister(dependency)));
  addItem(std::unique_ptr<MenuItem>(new WriteRegister(dependency)));

}
