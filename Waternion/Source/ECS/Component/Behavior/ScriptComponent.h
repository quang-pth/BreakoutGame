#pragma once

#include"ECS/Component/Defaults.h"
#include"Scripts/Native.h"

namespace Waternion::ECS
{
    using ScriptInstantiator = std::function<Shared<NativeScript> (EntityID id)>;

    class ScriptComponent : public Component {
        public:
            ScriptComponent();
            ScriptComponent(const ScriptComponent&) = default;
            template<typename T>
            WATERNION_INLINE void Bind() {
                mInstantiator = [](EntityID id) {
                    return DyanmicPtrCast<NativeScript>(MakeShared<T>(id));
                };
            }
            void OnStart();
            void OnProcessInput(const struct InputState&);
            void OnPreUpdate(float deltaTime);
            void OnUpdate(float deltaTime);
            void OnPostUpdate(float deltaTime);
            void OnCollision(Shared<ECS::Entity> collidedEntity);
            void OnDestroy();
            void Instantiate(EntityID id) {
                mInstance = mInstantiator(id);
            }
        private:
            Shared<NativeScript> mInstance;
            ScriptInstantiator mInstantiator;
    };
} // namespace Waternion::ECS