#pragma once

#include"ECS/System.h"
#include"ECS/System/ControlState/Keyboard.h"

namespace Waternion
{
    namespace ECS {
        class InputSystem : public System {
            public:
                InputSystem();
                WATERNION_INLINE InputSystem(const InputSystem&) = default;
                virtual bool Init() override;
                virtual void Shutdown() override;
                virtual void Start() override;
                void ProcessInput(const InputState& inputState);
        };
    } // namespace ECS
} // namespace Waternion