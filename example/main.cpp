
#include "MainMenu.h"
#include "MenuDependency.h"

#include "spdlog/spdlog.h"


#include <memory>

#include <array>


int main() {
  spdlog::default_logger()->set_level(spdlog::level::level_enum::trace);

  MenuDependency menuDependency;
  MainMenu mainMenu(menuDependency);
  mainMenu.go();

//    try {
//    const std::string host{"127.0.0.1"};
//    const std::string port{"502"};
//
//    modbusClient = std::make_unique<RH::ModbusClient>(host, std::stoi(port));
//    const bool connectResult = modbusClient->connect();
//
//    if(!connectResult) {
//      SPDLOG_ERROR("Could not open connection");
//      return 0;
//    }
//
//    auto device = modbusClient->addDevice(1);
//    if(!device) {
//      SPDLOG_ERROR("Could not add device");
//      return 0;
//    }
//    constexpr uint16_t ADDR_START = 0x123;
//    constexpr uint16_t NUM_REGS = 2;
//    std::array<uint16_t, NUM_REGS> registers{};
//
//    device->readInputRegisters(ADDR_START, registers.size(), registers.data());
//
//    SPDLOG_INFO("Register {:X} with values: ", ADDR_START);
//    for(uint32_t i = 0 ; i < NUM_REGS ; i++) {
//        SPDLOG_INFO("    {:X}: {:X}", ADDR_START + i, registers.at(i));
//    }
//  } catch (...) {}


//
//  try {
//  auto screen = ScreenInteractive::FitComponent();
//
//  // -- Menu
//  // ----------------------------------------------------------------------
//  const std::vector<std::string> menuEntries = {
//    "Menu 1",
//    "Menu 2",
//    "Menu 3",
//    "Menu 4",
//  };
//  int menuSelected = 0;
//  auto menu = Menu(&menuEntries, &menuSelected);
//  menu = wrap("RH Device Manager", menu);
//
//  // -- host and port ------------------------------------------------------------------
//  std::string host;
//  auto hostField = Input(&host, "Host");
//  hostField = wrap("Host", hostField);
//
//  std::string port;
//  auto portInput = Input(&port, "502");
//  portInput = wrap("Port", portInput);
//
//
////  // -- Toggle------------------------------------------------------------------
////  int toggle_selected = 0;
////  std::vector<std::string> toggle_entries = {
////    "Toggle_1",
////    "Toggle_2",
////  };
////  auto toggle = Toggle(&toggle_entries, &toggle_selected);
////  toggle = wrap("Toggle", toggle);
//
//  // -- Checkbox ---------------------------------------------------------------
////  bool checkbox_1_selected = false;
////  bool checkbox_2_selected = false;
////  bool checkbox_3_selected = false;
////  bool checkbox_4_selected = false;
////
////  auto checkboxes = Container::Vertical({
////    Checkbox("checkbox1", &checkbox_1_selected),
////    Checkbox("checkbox2", &checkbox_2_selected),
////    Checkbox("checkbox3", &checkbox_3_selected),
////    Checkbox("checkbox4", &checkbox_4_selected),
////  });
////  checkboxes = wrap("Checkbox", checkboxes);
//
//  // -- Radiobox ---------------------------------------------------------------
////  int radiobox_selected = 0;
////  std::vector<std::string> radiobox_entries = {
////    "Radiobox 1",
////    "Radiobox 2",
////    "Radiobox 3",
////    "Radiobox 4",
////  };
////  auto radiobox = Radiobox(&radiobox_entries, &radiobox_selected);
////  radiobox = wrap("Radiobox", radiobox);
//
//  // -- Input ------------------------------------------------------------------
////  std::string input_label;
////  auto input = Input(&input_label, "placeholder");
////  input = wrap("Input", input);
//
//  // -- Button -----------------------------------------------------------------
//  const std::string buttonLabel = "Connect";
//  const std::function<void()> onConnectedClick = [&host, &port, &modbusClient] {
//    if(host.empty() || port.empty()) {
//      spdlog::default_logger()->error("Host and port must be specified");
//      return;
//    }
//    modbusClient = std::make_unique<RH::ModbusClient>(host, std::stoi(port));
//    modbusClient->connect();
//  };
//  auto button = Button(&buttonLabel, onConnectedClick);
//  button = wrap("Button", button);
//
//  // -- Slider -----------------------------------------------------------------
////  int slider_value_1 = 12;
////  int slider_value_2 = 56;
////  int slider_value_3 = 128;
////  auto sliders = Container::Vertical({
////    Slider("R:", &slider_value_1, 0, 256, 1),
////    Slider("G:", &slider_value_2, 0, 256, 1),
////    Slider("B:", &slider_value_3, 0, 256, 1),
////  });
////  sliders = wrap("Slider", sliders);
//
//  // -- Layout -----------------------------------------------------------------
//  auto layout = Container::Vertical({
//    menu,
////    toggle,
////    checkboxes,
////    radiobox,
////    input,
////    sliders,
//    button,
//  });
//
//  constexpr uint32_t BORDER_SIZE = 40;
//  auto component = Renderer(layout, [&] {
//    return vbox({
//             menu->Render(),
//             separator(),
////             toggle->Render(),
////             separator(),
////             checkboxes->Render(),
////             separator(),
////             radiobox->Render(),
////             separator(),
////             input->Render(),
////             separator(),
////             sliders->Render(),
//             separator(),
//             button->Render(),
//           }) |
//           xflex | size(WIDTH, GREATER_THAN, BORDER_SIZE) | border;
//  });
//
//
//    screen.Loop(component);
//  } catch(...) {
//
//  }
  return 0;
}
