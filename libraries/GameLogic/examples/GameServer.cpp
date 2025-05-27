#include <ECSEngineLib/World.hpp>
#include <InversionOfControl/InversionOfControl.h>
#include <ServerLogic/Player.hpp>
#include <ServerLogic/PlayerFactory.hpp>
#include <iostream>
#include <network/INetworkServer.hpp>
#include <network/NetworkFactory.hpp>

#include <ServerLogic/CommandExecutor.hpp>
#include <ServerLogic/CommandService.hpp>

int main(int, const char **) {

  auto &container = IoCContainer::GetInstance();

  container.RegisterFactory<World>("World",
                                   []() { return std::make_shared<World>(); });

  // Регистрация PlayerFactory
  container.RegisterFactory<PlayerFactory>("PlayerFactory", [&container]() {
    auto world = container.Resolve<std::shared_ptr<World>>("World");
    return std::make_shared<DefaultPlayerFactory>(*world);
  });

  // Регистрация CommandService
  container.RegisterFactory<CommandExecutor>("CommandService", [&container]() {
    auto world = container.Resolve<std::shared_ptr<World>>("World");
    return std::make_shared<CommandExecutor>([world]() {
      std::cout << "Game state updated" << std::endl;
      std::cout << *world.get() << std::endl;
    });
  });

  // Сервер
  auto networkServer = network::NetworkFactory::createServer(8080);

  networkServer->setOnClientConnect([&container](ISession::Ptr session) {
    auto playerFactory =
        container.Resolve<std::shared_ptr<PlayerFactory>>("PlayerFactory");
    auto commandService =
        container.Resolve<std::shared_ptr<CommandExecutor>>("CommandService");
    auto worldService = container.Resolve<std::shared_ptr<World>>("World");
    auto player = playerFactory->CreatePlayer();

    std::cout << "Player connected with Entity ID: " << player->entity() << "\n"
              << std::flush;

    session->setOnMessage(
        [commandService, player](const std::vector<uint8_t> &data) {
          std::string msg(data.begin(), data.end());
          auto deserialized =
              ICommand::Deserialize(data.data(), data.size(), nullptr);
          std::cout << "Received from player " << player->entity() << ": "
                    << deserialized->Type() << "\n"
                    << std::flush;
          commandService->EnqueueCommand(deserialized, player);
          commandService->WorkerLoop();
        });

    session->setOnDisconnect([player, worldService]() {
      worldService->DestroyEntity(player->entity());
      std::cout << "Player disconnected: Entity ID " << player->entity() << "\n"
                << *worldService << std::flush;
    });
  });

  networkServer->start();
}
