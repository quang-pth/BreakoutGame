#include"PhysicWorld.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"

#include"Collisions/Collision.h"

namespace Waternion::ECS 
{
    PhysicWorld::PhysicWorld() : System(), mCircles(), mBoxes() {

    }

    void PhysicWorld::Start() {
        for(Shared<Entity> entity : System::GetEntitiesHaveComponent<CircleComponent>()) {
            entity->GetComponent<CircleComponent>()->OnStart();           
        }
        for(Shared<Entity> entity : System::GetEntitiesHaveComponent<Box2DComponent>()) {
            entity->GetComponent<Box2DComponent>()->OnStart();           
        }
    }

    void PhysicWorld::PreUpdate(float deltaTime) {
        mCircles.clear();
        mBoxes.clear();
    }

    void PhysicWorld::Update(float deltaTime) {
        for(Shared<Entity> entity : System::GetEntitiesHaveComponent<CircleComponent>()) {
            Shared<CircleComponent> circle = entity->GetComponent<CircleComponent>();
            if (!circle->GetDisabled()) {
                mCircles.emplace_back(circle);
            }
        }
        for(Shared<Entity> entity : System::GetEntitiesHaveComponent<Box2DComponent>()) {
            Shared<Box2DComponent> box = entity->GetComponent<Box2DComponent>();
            if (!box->GetDisabled()) {
                mBoxes.emplace_back(box);
            }
        }
    }

    void PhysicWorld::PostUpdate(float deltaTime) {
        for (Shared<CircleComponent> circle : mCircles) 
        {
            Shared<Entity> circleOwner = circle->GetOwner();

            for (Shared<Box2DComponent> box : mBoxes) {
                Shared<Entity> boxOwner = box->GetOwner();

                if (circleOwner == boxOwner) continue;

                if (Collisions::IsIntersect(circle->GetCircle(), box->GetWorldBox())) {
                    circleOwner->GetComponent<ScriptComponent>()->OnCollision(boxOwner);
                }
            }           
        }
    }
}