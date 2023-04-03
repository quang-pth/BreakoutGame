#pragma once

#include"Math/Vec.h"

namespace Waternion
{
    namespace ECS
    {
        class InfoComponent {
            public:
                WATERNION_INLINE InfoComponent() = default;
                WATERNION_INLINE InfoComponent(const InfoComponent&) = default;
                WATERNION_INLINE void SetName(const std::string& name) { mName = name; }
                WATERNION_INLINE void SetTag(const std::string& tag) { mTag = tag; }
                WATERNION_INLINE const std::string& GetName() { return mName; }
                WATERNION_INLINE const std::string& GetTag() { return mTag; }
            private:
                std::string mName = "Entity";
                std::string mTag = "None";
        };

        class TransformComponent {
            public:
                WATERNION_INLINE TransformComponent() = default;
                WATERNION_INLINE TransformComponent(const TransformComponent&) = default;
                WATERNION_INLINE void SetPosition(const Math::Vector2& position) { mPosition = position; }
                WATERNION_INLINE void SetPosition(float x, float y) { mPosition.x = x; mPosition.y = y; }
                WATERNION_INLINE void SetScale(const Math::Vector2& scale) { mScale = scale; }
                WATERNION_INLINE void SetScale(float x, float y) { mScale.x = x; mScale.y = y; }
                WATERNION_INLINE void SetScale(float value) { mScale.x = value; mScale.y = value; }
                WATERNION_INLINE void SetRotation(float rotation) { mRotation = rotation; }
                WATERNION_INLINE const Math::Vector2& GetPosition() { return mPosition; }
                WATERNION_INLINE const Math::Vector2& GetScale() { return mScale; }
                WATERNION_INLINE float GetRotation() { return mRotation; }
            private:
                Math::Vector2 mPosition = Math::Vector2::Zero;
                Math::Vector2 mScale = Math::Vector2(1, 1);
                float mRotation = 0.0f;
        };
    } // namespace ECS
} // namespace Waternion