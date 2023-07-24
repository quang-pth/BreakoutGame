#include"Scene.h"
#include"Core/Application.h"
#include"Render/Shader.h"
#include"Core/Manager/ResourceManager.h"
#include"Render/PostProcessor.h"
#include"Utils/Settings.h"

// Systems
#include"ECS/System/Renderer.h"
#include"ECS/System/ParticleSystem.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/ScriptingSystem.h"
#include"ECS/System/PhysicWorld.h"
#include"ECS/System/AudioSystem.h"
#include"ECS/System/TextRenderer.h"
#include"ECS/System/BatchRenderer.h"

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/PlayerController.h"
#include"Scripts/Background.h"
#include"Scripts/Ball.h"
#include"Scripts/GameLevel.h"
#include"Scripts/Powers/PowerManager.h"
#include"Scripts/GameManager.h"

namespace Waternion {
    using namespace ECS;

    Scene::Scene() {
        mCoordinator = Application::GetInstance()->GetCoordinator();
        WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");
    }

    Shared<Entity> Scene::FindEntity(const std::string& name) const {
        for (EntityID id : mEntities) {
            Shared<Entity> entity = MakeShared<Entity>(id, mCoordinator);
            Shared<InfoComponent> info = entity->GetComponent<InfoComponent>();
            if (!info->GetName().compare(name)) {
                return entity;
            }
        }
        WATERNION_ASSERT(false && "Get non-existing entity");
        return MakeShared<Entity>();
    }

    void Scene::AddEntity(EntityID id) {
        WATERNION_ASSERT(id != INVALID_ID && "Add invalid entity");
        auto iter = std::find(mEntities.begin(), mEntities.end(), id);
        if (iter == mEntities.end()) {
            mEntities.emplace_back(id);
            return;
        }
        WATERNION_LOG_WARNING("Adding the same entity more than once");
    }
} // namespace Waternion