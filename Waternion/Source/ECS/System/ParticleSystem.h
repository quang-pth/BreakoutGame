#pragma once

#include"ECS/System.h"

namespace Waternion::ECS
{
    class ParticleSystem : public System {
        public:
            ParticleSystem();
            virtual void Start() override;
            virtual void Update(float deltaTime) override;
    };
} // namespace Waternion::ECS