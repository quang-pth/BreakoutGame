#pragma once

#include"pch.h"

#include"ECS/Coordinator.h"
#include"ECS/System.h"

namespace Waternion
{
    namespace ECS
    {
        class Scene {
            public:
                Scene();
                WATERNION_INLINE Scene(const Scene&) = default;

                bool Load();
                void Shutdown();
                void Awake();
                void Start();
                void Update(float);
                void BeginScene(float);
                void Render(float);
                void EndScene(float);

                template<typename T, typename... Args>
                WATERNION_INLINE void RegisterSystem(Args&&... args) {
                    UUID systemType = GetTypeID<T>();
                    WATERNION_STATIC_ASSERT(std::is_base_of<System, T>::value);
                    mSystemsMap[systemType].emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
                }

                template<typename T>
                WATERNION_INLINE std::vector<Shared<System>> GetSystems() {
                    UUID systemType = GetTypeID<T>();
                    WATERNION_STATIC_ASSERT(std::is_base_of<System, T>::value);
                    return mSystemsMap[systemType];
                }

                Shared<Entity> GetEntity(const std::string& name) const;

                void AddEntity(EntityID id);
            private:
                bool InitSystems();
                std::unordered_map<UUID, std::vector<Shared<System>>> mSystemsMap;
                std::vector<EntityID> mEntities;
                Shared<Coordinator> mCoordinator;
        };
    } // namespace ECS
} // namespace Waternion