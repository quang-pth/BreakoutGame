#include"ParticleSystem.h"

#include"ECS/Component/Graphics/Particle2DComponent.h"

namespace Waternion::ECS
{
    ParticleSystem::ParticleSystem() : System() {

    }

    void ParticleSystem::Start() {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<Particle2DComponent>()) {
            entity->GetComponent<Particle2DComponent>()->OnStart();
        }
    }

    void ParticleSystem::Update(float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<Particle2DComponent>()) {
            entity->GetComponent<Particle2DComponent>()->OnUpdate(deltaTime);
        }
    }
} // namespace Waternion::ECS