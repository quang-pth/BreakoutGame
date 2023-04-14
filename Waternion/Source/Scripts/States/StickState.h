#pragma once

#include"BallState.h"

namespace Waternion
{
    class StickState : public BallState {
        public:
            StickState();
            StickState(class Ball*);
            ~StickState();
            virtual void OnEnter() override;
            virtual void OnExit() override;
            virtual void OnProcessInput(const InputState&);
            virtual void OnUpdate(float);
        private:
    }; 
} // namespace Waternion
