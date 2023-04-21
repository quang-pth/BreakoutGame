#pragma once

#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion
{
    namespace ECS {
        struct Particle {
            Math::Vector2 Position, Velocity;
            Math::Vector3 Color;
            float Alpha;
            float LifeTime;
            WATERNION_INLINE Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Alpha(1.0f), LifeTime(0.0f) {}
        };

        class Particle2DComponent : public SpriteComponent {
            public:
                Particle2DComponent();
                WATERNION_INLINE void SetLifeTime(float lifeTime) {
                }
                virtual void OnStart() override;
                virtual void Init(const char* filepath, bool alpha, const char* name) override;
                virtual void Draw(float deltaTime = 0.0f);
                virtual void OnUpdate(float deltaTime);
            private:
                void UpdateParticles(float deltaTime);
                void RespawnParticles(const Math::Vector2& offset);
                void SpawnParticles(Particle& particle, const Math::Vector2& offset);
                uint32_t GetUnusedParticleIdx();
                uint32_t mParticlesPerFrame;
                uint32_t mMaxParticles;
                uint32_t mLastUsedIdx;
                std::vector<Particle> mParticles;
                Shared<SpriteComponent> mOwnerSprite;
                Shared<TransformComponent> mOwnerTransform;
                std::vector<Math::Matrix4> mModels;
                std::vector<Math::Vector3> mColors;
                std::vector<float> mAlphas;
        };
    }
} // namespace Waternion