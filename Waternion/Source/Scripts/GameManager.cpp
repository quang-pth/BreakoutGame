#include"GameManager.h"

#include"Core/Application.h"
#include"ECS/System/InputSystem.h"

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/GameLevel.h"
#include"ECS/Component/UI/TextComponent.h"

namespace Waternion
{
    using namespace ECS;

    GameManager::GameManager(EntityID id) : NativeScript(id), mGameState(EGameState::Paused) {
        
    }

    void GameManager::OnAwake() {
        mText = AddComponent<TextComponent>(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight());
        mText->SetFont("assets/fonts/OCRAEXT.TTF", 30);
    }

    void GameManager::OnStart() {
        Shared<Entity> level = Application::GetInstance()->GetScene()->FindEntity("GameLevel");
        mGameLevel = level->GetComponent<ScriptComponent>()->GetInstance<GameLevel>();
    }

    void GameManager::OnProcessInput(const InputState& inputState) {
        switch(mGameState) {
            case EGameState::Paused:
            {
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_ENTER) == ButtonState::EPressed) {
                    mGameState = EGameState::Playing;
                }
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_1) == ButtonState::EPressed) {
                    mGameLevel->ChangeLevel(mGameLevel->GetCurrentLevel() + 1);
                }
                
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_2) == ButtonState::EReleased) {
                    mGameLevel->ChangeLevel(mGameLevel->GetCurrentLevel() - 1);
                }
                break;
            }
            case EGameState::Playing:
            {
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_ENTER) == ButtonState::EPressed) {
                    mGameState = EGameState::Paused;
                }
                break;
            }
            case EGameState::Won:
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_R) == ButtonState::EPressed) {
                    mGameLevel->Reset();
                }
                break;
        }
    }

    void GameManager::OnUpdate(float deltaTime) {
        if (mGameLevel->IsCompleted()) {
            mGameState = EGameState::Won;
        }

        switch(mGameState) {
            case EGameState::Paused:
                mText->SetText("Pressed ENTER to play");
                mText->SetScale(0.8f);
                mText->SetPosition(Math::Vector2(-150.0f, 0.0f));
                mText->SetColor(Math::Vector3(0.3f, 0.2f, .9f));
                Application::GetInstance()->SetTimeScale(0.0f);
                break;
            case EGameState::Playing:
                mText->SetText("");
                Application::GetInstance()->SetTimeScale(1.0f);
                break;
            case EGameState::Won:
                mText->SetText("You WON! Press R to restart");
                mText->SetColor(Math::Vector3(1.0f, 1.0f, 0.0f));
                Application::GetInstance()->SetTimeScale(1.0f);
                break;
        };
    }
} // namespace Waternion