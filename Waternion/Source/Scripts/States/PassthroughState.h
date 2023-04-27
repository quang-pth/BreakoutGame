#pragma once

#include"MovingState.h"

namespace Waternion
{

    namespace ECS {
        class Particle2DComponent;
    }

    class PassthroughState : public MovingState {
        public:
            PassthroughState();
            PassthroughState(class Ball*);
            virtual void OnEnter() override;
            virtual void OnExit() override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnCollision(const ECS::CollisionDetails&) override;
        private:
            Shared<ECS::Particle2DComponent> mOwnerParticle;
    };
} // namespace Waternion