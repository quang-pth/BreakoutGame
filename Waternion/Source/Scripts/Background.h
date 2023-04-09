#pragma once

#include"Native.h"

namespace Waternion
{
    class Background : public NativeScript {
        public:
            WATERNION_INLINE Background() : NativeScript() {}
            WATERNION_INLINE Background(ECS::EntityID id) : NativeScript(id) {}
            virtual void OnStart() override;
    };
} // namespace Waternion