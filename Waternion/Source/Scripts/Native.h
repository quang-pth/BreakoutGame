#pragma once

#include"pch.h"
#include"ECS/Entity.h"
#include"ECS/System/PhysicWorld.h"

namespace Waternion {
    class NativeScript {
        public:
            NativeScript();
            NativeScript(ECS::EntityID id);
            NativeScript(const NativeScript&) = default;
            virtual void OnAwake();
            virtual void OnStart();
            virtual void OnProcessInput(const struct InputState&);
            virtual void OnPreUpdate(float deltaTime);
            virtual void OnUpdate(float deltaTime);
            virtual void OnPostUpdate(float deltaTime);
            virtual void OnCollision(const ECS::CollisionDetails& details);
            virtual void OnDestroy();
            virtual void OnActivate();
            virtual void OnDeactivate();
            WATERNION_INLINE Shared<ECS::Entity> GetOwner() {
                return MakeShared<ECS::Entity>(mEntityID, mCoordinator);               
            }
        protected:
            template<typename T, typename... Args>
            WATERNION_INLINE Shared<T> AddComponent(Args&&... args) {
                return mCoordinator->AddComponent<T>(mEntityID, std::forward<Args>(args)...);
            }
            
            template<typename T>
            WATERNION_INLINE bool RemoveComponent() {
                return mCoordinator->RemoveComponent<T>(mEntityID);
            }

            template<typename T>
            WATERNION_INLINE bool HasComponent() {
                return mCoordinator->HasComponent<T>(mEntityID);
            }

            template<typename T>
            WATERNION_INLINE Shared<T> GetComponent() {
                return mCoordinator->GetComponent<T>(mEntityID);
            }

            WATERNION_INLINE Shared<ECS::Entity> AddEntity() {
                Shared<ECS::Entity> entity;
                entity.reset(new ECS::Entity());
                return entity;
            }
        private:
            Shared<ECS::Coordinator> mCoordinator;
            ECS::EntityID mEntityID;
    };
}