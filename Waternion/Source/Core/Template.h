#pragma once

#include"pch.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Audio/SoundComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Graphics/Particle2DComponent.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/UI/TextComponent.h"

namespace Waternion
{
    template<typename T> using RefObject = Shared<T>; 

    template<typename T, typename... Args>
    RefObject<T> CreateObject(Args&&... args) {
        return MakeShared<T>(std::forward<Args>(args)...);
    }

    template<typename... Args> RefObject<ECS::Entity> CreateObject(Args&&... args);
    
    template RefObject<ECS::ScriptComponent> ECS::Entity::AddComponent();
    template RefObject<ECS::MoveComponent> ECS::Entity::AddComponent();
    template RefObject<ECS::TransformComponent> ECS::Entity::AddComponent();

    template RefObject<ECS::ScriptComponent> ECS::Entity::GetComponent();
} // namespace Waternion