#pragma once

#include"pch.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/PhysicWorld.h"

namespace Waternion
{
    class BallState {
        public:
            WATERNION_API static std::unordered_map<const char*, Shared<BallState>> States;
            WATERNION_API static std::stack<Shared<BallState>> StateStack;
            BallState() = default;
            BallState(class Ball*);
            virtual ~BallState() = default;
            virtual void OnAwake();
            virtual void OnStart();
            virtual void OnProcessInput(const InputState&);
            virtual void OnPreUpdate(float);
            virtual void OnUpdate(float);
            virtual void OnPostUpdate(float);
            virtual void OnCollision(const ECS::CollisionDetails&);
            template<typename T, typename... Args>
            WATERNION_API static void RegisterState(Args&&... args) {
                WATERNION_STATIC_ASSERT(std::is_base_of<BallState, T>::value);
                const char* type = typeid(T).name();
                BallState::States.insert({type, MakeShared<T>(std::forward<Args>(args)...)});
            }
            template<typename T>
            WATERNION_API static Shared<BallState> ChangeState() {
                WATERNION_STATIC_ASSERT(std::is_base_of<BallState, T>::value);
                const char* type = typeid(T).name();
                if (BallState::States.count(type)) {
                    return BallState::States.at(type);
                }
                return nullptr;
            }
            WATERNION_API static Shared<BallState> RestoreState();
            WATERNION_API static void BackupState(Shared<BallState> state);
            virtual void OnEnter();
            virtual void OnContinue();
            virtual void OnExit();
            void SetOwner(class Ball*);
        protected:
            class Ball* mOwner;
    };
} // namespace Waternion