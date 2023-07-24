#include"GameManager.h"

#include"Core/Application.h"
#include"ECS/System/InputSystem.h"
#include"Scene/GameScene.h"

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
        mText->SetColor(Math::Vector3(1.0f, 1.0f, 1.0f));

        mGameScene = Application::GetInstance()->FindScene<GameScene>();
    }

    void GameManager::OnStart() {
        Shared<Entity> level = mGameScene->FindEntity("GameLevel");
        mGameLevel = level->GetComponent<ScriptComponent>()->GetInstance<GameLevel>();
    }

    void GameManager::OnProcessInput(const InputState& inputState) {
        switch(mGameState) {
            case EGameState::Paused:
            {
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_ENTER) == ButtonState::EPressed) {
                    mGameState = EGameState::Playing;
                }
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_UP) == ButtonState::EPressed) {
                    mGameLevel->Reset(mGameLevel->GetCurrentLevel() + 1);
                }
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_DOWN) == ButtonState::EReleased) {
                    mGameLevel->Reset(mGameLevel->GetCurrentLevel() - 1);
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
                    mGameLevel->Reset(mGameLevel->GetCurrentLevel() + 1);
                    mGameState = EGameState::Playing;
                }
                break;
            case EGameState::Lose:
                if (inputState.Keyboard.GetKeyState(GLFW_KEY_R) == ButtonState::EPressed) {
                    mGameLevel->Reset(mGameLevel->GetCurrentLevel());
                    mGameState = EGameState::Playing;
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
                Application::GetInstance()->SetTimeScale(0.0f);
                break;
            case EGameState::Playing:
                mText->SetText("");
                Application::GetInstance()->SetTimeScale(1.0f);
                break;
            case EGameState::Won:
                mText->SetText("You WON! Press R to restart");
                Application::GetInstance()->SetTimeScale(0.0f);
                break;
            case EGameState::Lose:
                mText->SetText("You LOSE! Press R to restart");
                Application::GetInstance()->SetTimeScale(0.0f);
                break;
        };
    }
} // namespace Waternion