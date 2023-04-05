#pragma once

#include"pch.h"
#include"Entity.h"
#include"Coordinator.h"

#include"Component/Defaults.h"
#include"Component/SpriteComponent.h"

namespace Waternion {
    namespace ECS {
        class System {
            public:
                System();
                WATERNION_INLINE System(const System&) = default;
                virtual ~System() = default;
                
                template<typename T>
                WATERNION_INLINE std::vector<Shared<Entity>> GetEntitiesHasComponentType() {
                    std::vector<Shared<Entity>> entities;
                    for (EntityID entID : mCoordinator->GetEntitesHasComponentType<T>()) {
                        entities.emplace_back(std::make_shared<Entity>(entID, mCoordinator));
                    }
                    return entities;
                }
                
                template<typename T>
                WATERNION_INLINE const std::vector<Shared<T>>& GetComponentArray() {
                    return mCoordinator->GetComponentArray<T>()->GetComponents();
                }

                WATERNION_INLINE virtual bool Init() { return true; }
                WATERNION_INLINE virtual void Shutdown() {}
                WATERNION_INLINE virtual void Start() {}
                WATERNION_INLINE virtual void Update(float deltaTime) {
                    for(Shared<Entity> entity : GetEntitiesHasComponentType<TransformComponent>()) {
                        entity->GetComponent<TransformComponent>()->UpdateWorldTransform();
                    }
                }
                WATERNION_INLINE const std::string& GetName() { return mName; }
            protected:
                Shared<Coordinator> mCoordinator;
                std::string mName;
        };
    }
}