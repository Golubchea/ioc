#pragma once
#include "Player.hpp"
#include <ECSEngineLib/World.hpp>

#include <ECSEngineLib/Components/FuelComponent.hpp>
#include <ECSEngineLib/Components/PositionComponent.hpp>
#include <ECSEngineLib/Components/VelocityComponent.hpp>

#include <InversionOfControl/InversionOfControl.h>

class PlayerFactory {
public:
    virtual ~PlayerFactory() = default;
    virtual std::shared_ptr<Player> CreatePlayer() = 0;
};

class DefaultPlayerFactory : public PlayerFactory {
public:
    explicit DefaultPlayerFactory(World& world) : world_(world) {}

    std::shared_ptr<Player> CreatePlayer() override {
      auto entity = world_.CreateEntity();

      // Добавляем начальные компоненты
      world_.AddComponent<PositionComponent>(entity,
                                             std::array<double, 2>{0.0, 0.0});
      world_.AddComponent<VelocityComponent>(entity,
                                             std::array<double, 2>{0.0, 0.0});
      world_.AddComponent<FuelComponent>(entity, 100.0);

      return std::make_shared<Player>(entity, world_);
    }

private:
    World& world_;
};
