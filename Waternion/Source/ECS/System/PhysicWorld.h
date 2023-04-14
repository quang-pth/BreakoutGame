#pragma once

#include"ECS/System.h"
#include"Math/Vec.h"

namespace Waternion::ECS
{
    struct CollisionDetails {
        Shared<Entity> Collider;
        float Penetration;
        Math::Vector2 ContactedPoint;
        Math::Vector2 Different;
        Math::Vector2 ClosestDirection;
    };

    class PhysicWorld : public System {
        public:
            PhysicWorld();
            virtual void Start() override;
            virtual void PreUpdate(float deltaTime) override;
            virtual void Update(float deltaTime) override;
            virtual void PostUpdate(float deltaTime) override;
        private:
            Math::Vector2 CalcClosestDirection(Math::Vector2 vector);
            std::vector<Shared<class MoveComponent>> mMoves;
            std::vector<Shared<class CircleComponent>> mCircles;
            std::vector<Shared<class Box2DComponent>> mBoxes;
    };
} // namespace ECS