#pragma once

#include"Coordinator.h"

namespace Waternion {
    namespace ECS {
        class Entity {
            public:
                Entity(const std::string& name = "Entity");
                Entity(EntityID entID, Shared<Coordinator> coordinator); 

                WATERNION_INLINE operator EntityID() const { return mID; }
                WATERNION_INLINE EntityID GetID() const { return mID; }
                WATERNION_INLINE bool GetIsActive() const { return mCoordinator->GetActivate(mID); }
                void SetActivate(bool value);

                WATERNION_INLINE bool operator==(const Entity& other) {
                    return this->mID == other.GetID();
                }

                template<typename T>
                WATERNION_INLINE Shared<T> GetComponent() {
                    return mCoordinator->GetComponent<T>(mID);
                }
                
                template<typename T, typename... Args>
                WATERNION_INLINE Shared<T> AddComponent(Args&&... args) {
                    return mCoordinator->AddComponent<T>(mID, std::forward<Args>(args)...);
                }

                template<typename T>
                WATERNION_INLINE bool RemoveComponent() {
                    return mCoordinator->RemoveComponent<T>(mID);
                }

                template<typename T>
                WATERNION_INLINE bool HasComponent() {
                    return mCoordinator->HasComponent<T>(mID);
                }

                WATERNION_INLINE bool Destroy() {
                    return mCoordinator->DeleteEntity(mID);
                }

                WATERNION_INLINE bool IsAlive() {
                    return mCoordinator->EntityIsAlive(mID);
                }
            private:
                EntityID mID;
                Shared<Coordinator> mCoordinator;
        };
    }
}