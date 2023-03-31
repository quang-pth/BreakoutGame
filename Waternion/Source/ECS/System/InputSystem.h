#pragma once

#include"ECS/System.h"

namespace Waternion
{
    namespace ECS {
        class InputSystem : public System {
            public:
                WATERNION_INLINE InputSystem() : System() {}
                WATERNION_INLINE InputSystem(const InputSystem&) = default;
                WATERNION_INLINE virtual void Start() override {

                }
                void ProcessInput() {

                }
        };
    } // namespace ECS
} // namespace Waternion