#pragma once

#include"Power.h"

namespace Waternion
{
    namespace ECS {
        class TransformComponent;
    };

    class WATERNION_API PowerManager : public NativeScript {
        public:
            PowerManager();
            PowerManager(ECS::EntityID id);
            virtual void OnAwake() override;
            virtual void OnStart() override;
            void SpawnRandomPower(Shared<ECS::TransformComponent> transform);
            WATERNION_INLINE void SetPowerActivating(bool activate) {
                mPowerActivating = activate;
            }
            bool ActivatePower(Shared<class Power> power);
            void DeactivatePower(Shared<class Power> power);
            void Reset();
        private:
            Shared<PowerUp> PickRandomPower();
            std::vector<Shared<PowerUp>> mPowerUps;
            bool mPowerActivating;
    };
} // namespace Waternion