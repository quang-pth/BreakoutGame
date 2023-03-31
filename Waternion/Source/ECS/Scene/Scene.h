#pragma once

#include"pch.h"

#include"ECS/System/InputSystem.h"
#include"ECS/Coordinator.h"

namespace Waternion
{
    namespace ECS
    {
        class Scene {
            public:
                Scene();
                WATERNION_INLINE Scene(const Scene&) = default;

                bool Load();
                void Start();
                void ProcessInput();
                void Update(float);
                void Render(float);

                template<typename T, typename... Args>
                WATERNION_INLINE void RegisterSystem(Args&&... args) {
                    UUID systemType = GetTypeID<T>();
                    WATERNION_STATIC_ASSERT(std::is_base_of<System, T>::value);
                    mSystemsMap[systemType].emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
                }
            private:
                std::unordered_map<UUID, std::vector<Shared<System>>> mSystemsMap;
                std::vector<Shared<InputSystem>> mInputSystems;
                std::shared_ptr<Coordinator> mCoordinator;
        };
    } // namespace ECS
} // namespace Waternion