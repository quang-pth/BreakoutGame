#pragma once

#include"Power.h"

namespace Waternion
{
    namespace ECS {
        class TransformComponent;
    };

    class PowerManager : public NativeScript {
        public:
            PowerManager();
            PowerManager(ECS::EntityID id);
            virtual void OnAwake() override;
            virtual void OnStart() override;
            void SpawnRandomPower(Shared<ECS::TransformComponent> transform);
        private:
            Shared<PowerUp> PickRandomPower();
            std::vector<Shared<PowerUp>> mPowerUps;
    };
} // namespace Waternion