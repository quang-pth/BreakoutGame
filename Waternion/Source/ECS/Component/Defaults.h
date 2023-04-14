#pragma once

#include"Math/Matrix.h"
#include"ECS/Type.h"
#include"ECS/Entity.h"

namespace Waternion
{
    namespace ECS
    {
        class Component {
            public:
                Component();
                virtual ~Component() = default;
                WATERNION_INLINE Shared<Entity> GetOwner() const { 
                    return MakeShared<Entity>(mOwnerID, mCoordinator); 
                }
                WATERNION_INLINE void SetOwner(EntityID id) { 
                    mOwnerID = id;
                }
                WATERNION_INLINE UUID GetID() const { return mID; }
                WATERNION_INLINE void SetID(UUID id) { mID = id; }
                virtual void OnStart() {}
                virtual void OnPreUpdate(float deltaTime) {}
                virtual void OnUpdate(float deltaTime) {}
                virtual void OnPostUpdate(float deltaTime) {}
                virtual void OnUpdateWorldTransform() {}
                WATERNION_INLINE void SetDisabled(bool disabled) {
                    mDisabled = disabled;
                }
                WATERNION_INLINE bool GetDisabled() const {
                    return mDisabled;
                }
            protected:
                UUID mID = INVALID_ID;
                EntityID mOwnerID;
                bool mDisabled;
            private:
                Shared<class Coordinator> mCoordinator;
        };

        class InfoComponent : public Component {
            public:
                WATERNION_INLINE InfoComponent() : Component() {}
                WATERNION_INLINE InfoComponent(const InfoComponent&) = default;
                WATERNION_INLINE void SetName(const std::string& name) { mName = name; }
                WATERNION_INLINE void SetTag(const std::string& tag) { mTag = tag; }
                WATERNION_INLINE const std::string& GetName() { return mName; }
                WATERNION_INLINE const std::string& GetTag() { return mTag; }
            private:
                std::string mName = "Entity";
                std::string mTag = "None";
        };

        class TransformComponent : public Component {
            public:
                TransformComponent();
                WATERNION_INLINE TransformComponent(const TransformComponent&) = default;
                WATERNION_INLINE void SetPosition(const Math::Vector3& position) { mPosition = position; mRecomputeTransform = true; }
                WATERNION_INLINE void SetPosition(float x, float y, float z) { mPosition.x = x; mPosition.y = y; mPosition.z = z; mRecomputeTransform = true; }
                WATERNION_INLINE void SetPositionX(float x) { mPosition.x = x; mRecomputeTransform = true; }
                WATERNION_INLINE void SetPositionY(float y) { mPosition.y = y; mRecomputeTransform = true; }
                WATERNION_INLINE void SetPositionZ(float z) { mPosition.z = z; mRecomputeTransform = true; }
                WATERNION_INLINE void SetScale(const Math::Vector3& scale) { mScale = scale; mRecomputeTransform = true ;}
                WATERNION_INLINE void SetScale(float x, float y, float z) { mScale.x = x; mScale.y = y; mScale.z = z; mRecomputeTransform = true; }
                WATERNION_INLINE void SetScale(float value) { mScale.x = value; mScale.y = value; mScale.z = value; mRecomputeTransform = true; }
                WATERNION_INLINE void SetRotation(float rotation) { mRotation = rotation;  mRecomputeTransform = true; }
                WATERNION_INLINE const Math::Vector3& GetPosition() const { return mPosition; }
                WATERNION_INLINE const Math::Vector3& GetScale() const { return mScale; }
                WATERNION_INLINE float GetRotation() const { return mRotation; }
                WATERNION_INLINE const Math::Matrix4& GetWorldTransform() const { return mWorldTransform; }
                void UpdateWorldTransform();
            private:
                Math::Matrix4 mWorldTransform;
                Math::Vector3 mPosition;
                Math::Vector3 mScale;
                float mRotation;
                bool mRecomputeTransform;
        };
    } // namespace ECS
} // namespace Waternion