#include"BallState.h"
#include"Scripts/Ball.h"

namespace Waternion
{
    std::unordered_map<const char*, Shared<BallState>> BallState::States;

    BallState::BallState(Ball* owner) {
        mOwner = owner;
    }

    void BallState::OnAwake() {
        
    }

    void BallState::OnStart() {
    }

    void BallState::OnProcessInput(const InputState& inputState) {

    }
    
    void BallState::OnPreUpdate(float deltaTime) {

    }
    
    void BallState::OnUpdate(float deltaTime) {

    }

    void BallState::OnPostUpdate(float deltaTime) {
        mOwner->ConstraintsInBoundsX();
        mOwner->ConstraintsInBoundsY();
    }

    void BallState::OnCollision(const ECS::CollisionDetails& details) {

    }

    void BallState::OnEnter() {
        
    }

    void BallState::OnExit() {

    }

    void BallState::SetOwner(Ball* owner) {
        mOwner = owner;
    }
} // namespace Waternion