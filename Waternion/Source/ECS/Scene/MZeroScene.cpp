#include"MZeroScene.h"

#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/Leviathan.h"

#include"ECS/System/Renderer.h"

namespace Waternion
{
    namespace ECS {
        MZeroScene::MZeroScene() : Scene() {
            RegisterSystem<AnimationSystem>();
        }

        bool MZeroScene::Load() {
            Shared<Entity> leviathan = MakeShared<Entity>("Leviathan");
            leviathan->AddComponent<ScriptComponent>()->Bind<Leviathan>();

            return InitSystems();;
        }
    }
} // namespace Waternion