#pragma once

#include"ECS/Component/Defaults.h"
#include"Core/Native.h"
#include"ECS/System/PhysicWorld.h"

namespace Waternion::ECS
{
    class WATERNION_API ScriptComponent : public Component {
        public:
            ScriptComponent();
            ScriptComponent(const ScriptComponent&) = default;
            template<typename T>
            WATERNION_INLINE void Bind() {
                mInstance = DyanmicPtrCast<NativeScript>(MakeShared<T>(GetOwner()->GetID()));
            }
            void Bind(NativeScript* nativeScript);
            void OnAwake();
            virtual void OnStart() override;
            void OnProcessInput(const struct InputState&);
            virtual void OnPreUpdate(float deltaTime) override;
            virtual void OnUpdate(float deltaTime) override;
            virtual void OnPostUpdate(float deltaTime) override;
            void OnCollision(const CollisionDetails& details);
            void OnDestroy();
            virtual void OnActivate() override;
            virtual void OnDeactivate() override;
            template<typename T>
            WATERNION_INLINE Shared<T> GetInstance() const {
                return DyanmicPtrCast<T>(mInstance);
            }
        private:
            Shared<NativeScript> mInstance;
    };
} // namespace Waternion::ECS