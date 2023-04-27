#include"BallState.h"
#include"Scripts/Ball.h"

namespace Waternion
{
    std::unordered_map<const char*, Shared<BallState>> BallState::States;
    std::stack<Shared<BallState>> BallState::StateStack;

    BallState::BallState(Ball* owner) : mOwner(owner) {
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

    void BallState::OnContinue() {
        
    }

    void BallState::OnExit() {
    }

    void BallState::SetOwner(Ball* owner) {
        mOwner = owner;
    }

    Shared<BallState> BallState::RestoreState() {
        Shared<BallState> state = StateStack.top();
        StateStack.pop();
        return state;
    }

    void BallState::BackupState(Shared<BallState> state) {
        if (state) {
            StateStack.push(state);
        }
    }
} // namespace Waternion