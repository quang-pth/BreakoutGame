#pragma once

#include"Native.h"

namespace Waternion
{
    class Leviathan : public NativeScript {
        public:
            WATERNION_INLINE Leviathan() : NativeScript() {}
            WATERNION_INLINE Leviathan(ECS::EntityID id) : NativeScript(id) {}
            virtual void OnAwake() override;
            virtual void OnStart() override;
            virtual void OnWindowResized(const class WindowResizedEvent&) override;
    };
} // namespace Waternion