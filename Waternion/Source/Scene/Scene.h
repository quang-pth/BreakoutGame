#pragma once

#include"pch.h"

#include"ECS/Coordinator.h"
#include"ECS/System.h"

namespace Waternion
{
    class PostProcessor;
    struct InputState;

    class Scene {
        public:
            Scene();
            virtual ~Scene() = default;
            virtual bool Init() { return true; }
            virtual void Shutdown() {}
            virtual void Load() {}
            virtual void Awake() {}
            virtual void Start() {}
            virtual void ProcessInput(const InputState&) {}
            virtual void Update(float) {}
            virtual void BeginScene(float) {}
            virtual void Render(float) {}
            virtual void EndScene(float) {}
            virtual void AddScene(Scene* scene) {}
            virtual void RemoveScene(Scene* scene) {}

            template<typename T, typename... Args>
            WATERNION_INLINE void RegisterSystem(Args&&... args) {
                UUID systemType = GetTypeID<T>();
                WATERNION_STATIC_ASSERT(std::is_base_of<ECS::System, T>::value);
                mSystemsMap[systemType] = MakeShared<T>(std::forward<Args>(args)...);
            }

            template<typename T>
            WATERNION_INLINE Shared<T> GetSystem() {
                UUID systemType = GetTypeID<T>();
                WATERNION_STATIC_ASSERT(std::is_base_of<ECS::System, T>::value);
                return DyanmicPtrCast<T>(mSystemsMap.at(systemType));
            }

            void AddEntity(ECS::EntityID id);
            Shared<ECS::Entity> FindEntity(const std::string& name) const;
            
            WATERNION_INLINE const std::vector<ECS::EntityID>& GetEntities() const {
                return mEntities;
            }
        protected:
            std::unordered_map<UUID, Shared<ECS::System>> mSystemsMap;
            std::vector<ECS::EntityID> mEntities;
            Shared<ECS::Coordinator> mCoordinator;
    };
} // namespace Waternion