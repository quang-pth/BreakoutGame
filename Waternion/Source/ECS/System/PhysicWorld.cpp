#include"PhysicWorld.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"

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
        mMoves.clear();
        // Get moves entities
        for(Shared<Entity> entity : System::GetEntitiesHaveComponent<MoveComponent>()) {
            Shared<MoveComponent> move = entity->GetComponent<MoveComponent>();
            if (!move->GetDisabled()) {
                mMoves.emplace_back(move);
            }
        }
    }

    void PhysicWorld::Update(float deltaTime) {
        for(Shared<MoveComponent> move : mMoves) {
            move->Update(deltaTime);
        }
        // Get collider components
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

                if (circleOwner->GetID() == boxOwner->GetID()) {
                    continue;
                }
                
                const ColliderInfo& collider = Collisions::IsIntersect(circle->GetCircle(), box->GetBox()); 
                if (collider.Intersected) {
                    CollisionDetails details;
                    details.Collider = boxOwner;
                    details.Penetration = collider.Penetration;
                    details.ContactedPoint = collider.ContactedPoint;
                    details.Different = circle->GetCenter() - collider.ContactedPoint;
                    details.ClosestDirection = this->CalcClosestDirection(details.Different);
                    
                    circleOwner->GetComponent<ScriptComponent>()->OnCollision(details);
                    details.Collider = circleOwner;
                    boxOwner->GetComponent<ScriptComponent>()->OnCollision(details);
                }
            }  
        }
    }

    Math::Vector2 PhysicWorld::CalcClosestDirection(Math::Vector2 vector) {
        vector.SafeNormalized();
        
        Math::Vector2 basis[] = {
            Math::Vector2::UnitX,                
            -Math::Vector2::UnitX,                
            Math::Vector2::UnitY,                
            -Math::Vector2::UnitY,                
        };

        uint16_t idx = -1;
        float maxDiff = Math::MIN_NUMERICS;
        for (uint16_t i = 0; i < sizeof(basis) / sizeof(Math::Vector2); i++) {
            float dot = Math::Vector2::Dot(vector, basis[i]);
            if (dot > maxDiff) {
                maxDiff = dot;
                idx = i;
            }
        }

        return basis[idx];
    }
    
}