#pragma once

#include"ECS/Component/Defaults.h"
#include"Scripts/Native.h"

namespace Waternion::ECS
{
    class ScriptComponent : public Component {
        public:
            ScriptComponent();
            ScriptComponent(const ScriptComponent&) = default;
            template<typename T>
            WATERNION_INLINE void Bind() {
                mInstance = DyanmicPtrCast<NativeScript>(MakeShared<T>(GetOwner()->GetID()));
            }
            void OnStart();
            void OnProcessInput(const struct InputState&);
            void OnPreUpdate(float deltaTime);
            void OnUpdate(float deltaTime);
            void OnPostUpdate(float deltaTime);
            void OnCollision(Shared<ECS::Entity> collidedEntity);
            void OnDestroy();
            template<typename T>
            WATERNION_INLINE Shared<T> GetInstance() const {
                return DyanmicPtrCast<T>(mInstance);
            }
        private:
            Shared<NativeScript> mInstance;
    };
} // namespace Waternion::ECS