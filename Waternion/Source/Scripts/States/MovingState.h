#pragma once

#include"BallState.h"

namespace Waternion
{
    class MovingState : public BallState {
        public:
            MovingState();
            MovingState(class Ball*);
            ~MovingState();
            virtual void OnEnter() override;
            virtual void OnExit() override;
            virtual void OnUpdate(float) override;
            virtual void OnCollision(const ECS::CollisionDetails&) override;
        private:
            float mDisabledDuration;
            float mSpeed;
    };
} // namespace Waternion