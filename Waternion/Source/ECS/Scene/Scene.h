#pragma once

#include"pch.h"

#include"ECS/Coordinator.h"
#include"ECS/System.h"

namespace Waternion
{
    class PostProcessor;
    struct InputState;

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
                void ProcessInput(const InputState&);
                void Update(float);
                void BeginScene(float);
                void Render(float);
                void EndScene(float);

                WATERNION_INLINE Shared<PostProcessor> GetPostProcessor() const {
                    return mPostProcessor;
                }

                template<typename T, typename... Args>
                WATERNION_INLINE void RegisterSystem(Args&&... args) {
                    UUID systemType = GetTypeID<T>();
                    WATERNION_STATIC_ASSERT(std::is_base_of<System, T>::value);
                    mSystemsMap[systemType] = MakeShared<T>(std::forward<Args>(args)...);
                }

                template<typename T>
                WATERNION_INLINE Shared<T> GetSystem() {
                    UUID systemType = GetTypeID<T>();
                    WATERNION_STATIC_ASSERT(std::is_base_of<System, T>::value);
                    return DyanmicPtrCast<T>(mSystemsMap.at(systemType));
                }

                Shared<Entity> FindEntity(const std::string& name) const;
                
                WATERNION_INLINE const std::vector<EntityID>& GetEntities() const {
                    return mEntities;
                }

                void AddEntity(EntityID id);
                const Shared<PostProcessor>& GetPostProcessor() {
                    return mPostProcessor;
                }
            private:
                bool InitSystems();
                std::unordered_map<UUID, Shared<System>> mSystemsMap;
                std::vector<EntityID> mEntities;
                Shared<Coordinator> mCoordinator;
                Shared<PostProcessor> mPostProcessor;
                float mShakeTime;
        };
    } // namespace ECS
} // namespace Waternion