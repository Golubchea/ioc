#include "CommandLib/Commands/BurnFuelCommand.hpp"
#include <CommandLib/Commands/MoveCommand.hpp>
#include <CommandLib/Commands/RotateCommand.hpp>
#include <ECSEngineLib/World.hpp>
#include <InversionOfControl/InversionOfControl.h>
#include <ServerLogic/CommandExecutor.hpp>
#include <ServerLogic/CommandService.hpp>
#include <ServerLogic/Player.hpp>
#include <ServerLogic/PlayerFactory.hpp>
#include <iostream>
#include <network/INetworkServer.hpp>
#include <network/NetworkFactory.hpp>
#include <string>
#include <utils/conversionUtils.hpp>

std::vector<uint8_t> SendMoveCommand(double x, double y) {
  std::array<double, 2> delta{x, y};
  auto moveCmd = std::make_shared<MoveCommand>(delta);
  return moveCmd->Serialize();
}

std::vector<uint8_t> SendRotateCommand(float angle) {
  auto rotCmd = std::make_shared<RotateCommand>(angle);
  return rotCmd->Serialize();
}

std::vector<uint8_t> SendBurnFuelCommand(float fuel) {
  auto rotCmd = std::make_shared<BurnFuelCommand>(fuel);
  return rotCmd->Serialize();
}

int main(int, const char **) {

  World ecsWorld;

  // Создаем контейнер

  // IoCContainer::GetInstance();

  // Регистрируем зависимости
  // container->registerService<PlayerFactory>(
  //     "PlayerFactory", [&ecsWorld]() -> std::shared_ptr<PlayerFactory> {
  //       return std::make_shared<DefaultPlayerFactory>(ecsWorld);
  //     });

  // container->registerService<CommandService>(
  //     "CommandService", []() -> std::shared_ptr<CommandService> {
  //       return std::make_shared<CommandExecutor>([]() {
  //         std::cout << "Game state updated\n" << std::flush;
  //       });
  //     });

  std::string address = "127.0.0.1";
  std::string port = "8080";

  auto client = network::NetworkFactory::createClient();
  client->setOnConnect([&]() {
    std::cout << "Connected to server\n " << std::flush;

    for (auto i = 0u; i < 3; ++i) {
      client->send((SendMoveCommand(1, 0)));
    }
    client->send((SendBurnFuelCommand(15)));
  });

  client->setOnMessage([](const std::vector<uint8_t> &data) {
    std::string msg(data.begin(), data.end());
    std::cout << "Client received: " << msg << "\n" << std::flush;
 
  });
  client->connect(address, port);
  client->start();
}
