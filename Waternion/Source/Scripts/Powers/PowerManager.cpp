#include"PowerManager.h"

#include"ECS/Component/Behavior/ScriptComponent.h"

namespace Waternion {
    PowerManager::PowerManager() : mPowerUps() {
    }

    PowerManager::PowerManager(ECS::EntityID id) : NativeScript(id) {

    }

    void PowerManager::OnAwake() {
        for (uint16_t i = 0; i < 20; i++) {
            Shared<ECS::Entity> powerup = MakeShared<ECS::Entity>("Chaos");
            Shared<ECS::ScriptComponent> script = powerup->AddComponent<ECS::ScriptComponent>();
            script->Bind<PowerUp>();
            script->GetInstance<PowerUp>()->SetPower<Chaos>("assets/textures/powerup_chaos.png", Math::Vector3(0.9f, 0.25f, 0.25f));
            mPowerUps.emplace_back(script->GetInstance<PowerUp>());

            powerup = MakeShared<ECS::Entity>("Confuse");
            script = powerup->AddComponent<ECS::ScriptComponent>();
            script->Bind<PowerUp>();
            script->GetInstance<PowerUp>()->SetPower<Confuse>("assets/textures/powerup_confuse.png", Math::Vector3(1.0f, 0.3f, 0.3f));
            mPowerUps.emplace_back(script->GetInstance<PowerUp>());
        }

        // powerup = MakeShared<ECS::Entity>("Increase");
        // script = powerup->AddComponent<ECS::ScriptComponent>();
        // script->Bind<PowerUp>();
        // script->GetInstance<PowerUp>()->SetPower<Increase>("assets/textures/powerup_increase.png", Math::Vector3(1.0f, 0.6f, 0.4f));
        // mPowerUps.emplace_back(script->GetInstance<PowerUp>());
        
        // powerup = MakeShared<ECS::Entity>("Passthrough");
        // script = powerup->AddComponent<ECS::ScriptComponent>();
        // script->Bind<PowerUp>();
        // script->GetInstance<PowerUp>()->SetPower<Passthrough>("assets/textures/powerup_passthrough.png", Math::Vector3(0.5f, 1.0f, 0.5f));
        // mPowerUps.emplace_back(script->GetInstance<PowerUp>());
        
        // powerup = MakeShared<ECS::Entity>("Speedy");
        // script = powerup->AddComponent<ECS::ScriptComponent>();
        // script->Bind<PowerUp>();
        // script->GetInstance<PowerUp>()->SetPower<Speedy>("assets/textures/powerup_speedy.png", Math::Vector3(0.5f, 0.5f, 1.0f));
        // mPowerUps.emplace_back(script->GetInstance<PowerUp>());
        
        // powerup = MakeShared<ECS::Entity>("Sticky");
        // script = powerup->AddComponent<ECS::ScriptComponent>();
        // script->Bind<PowerUp>();
        // script->GetInstance<PowerUp>()->SetPower<Sticky>("assets/textures/powerup_sticky.png", Math::Vector3(1.0f, 0.5f, 1.0f));
        // mPowerUps.emplace_back(script->GetInstance<PowerUp>());
    }

    void PowerManager::OnStart() {
    }

    void PowerManager::SpawnRandomPower(Shared<ECS::TransformComponent> transform) {
        Shared<PowerUp> power = this->PickRandomPower();
        power->GetOwner()->SetActivate(true);
        power->GetOwner()->GetComponent<ECS::TransformComponent>()->SetPosition(transform->GetPosition());
    }

    Shared<PowerUp> PowerManager::PickRandomPower() {
        if (mPowerUps.empty()) {
            return nullptr;
        }
        
        uint32_t randomIdx;
        Shared<PowerUp> pickedPower;
        uint8_t maxAttempt = 3;
        uint8_t count = 0;
        do {
            randomIdx = rand() % mPowerUps.size();
            pickedPower = mPowerUps[randomIdx];
            count++;
            if (count > maxAttempt) {
                break;
            }
        } while (pickedPower->GetOwner()->GetIsActive());
        
        return pickedPower;   
    }
}