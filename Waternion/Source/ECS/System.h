#pragma once

#include"pch.h"
#include"Entity.h"
#include"Coordinator.h"

namespace Waternion {
    namespace ECS {
        class System {
            public:
                System();
                WATERNION_INLINE System(const System&) = default;
                virtual ~System() = default;
                
                template<typename T>
                WATERNION_INLINE std::vector<Shared<Entity>> GetEntitiesHaveComponent() {
                    std::vector<Shared<Entity>> entities;
                    for (EntityID id : mCoordinator->GetEntityIDsHaveComponent<T>()) {
                        entities.emplace_back(MakeShared<Entity>(id, mCoordinator));
                    }
                    return entities;
                }
                
                template<typename T>
                WATERNION_INLINE const std::vector<Shared<T>>& GetComponentArray() {
                    return mCoordinator->GetComponentArray<T>()->GetComponents();
                }

                WATERNION_INLINE virtual bool Init() { return true; }
                WATERNION_INLINE virtual void Shutdown() {}
                WATERNION_INLINE virtual void Awake() {}
                WATERNION_INLINE virtual void Start() {}
                virtual void PreUpdate(float deltaTime);
                virtual void Update(float deltaTime);
                virtual void PostUpdate(float deltaTime);
                WATERNION_INLINE const std::string& GetName() { return mName; }
            protected:
                Shared<Coordinator> mCoordinator;
                std::string mName;
        };
    }
}