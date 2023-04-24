#include"Application.h"

namespace Waternion {
    Shared<Application> Application::GetInstance() {
        static Shared<Application> application;
        if (application == nullptr) {
            application.reset(new Application());
        }
        return application;
    }

    Application::Application() : mTimeScale(1.0f) {
        
    }

    bool Application::Init(int width, int height, const std::string& title, const std::string& version) {
        mCoordinator.reset(new ECS::Coordinator());
        mScene.reset(new ECS::Scene());
        mWindow.reset(new Window());

        if (!mWindow->Init(width, height, title)) {
            WATERNION_LOG_ERROR("Init Window succesfully");
        }

        if (!this->LoadScene()) {
            return false;
        }

        return true;
    }

    bool Application::LoadScene() {
        if (mScene->Load()) {
            mScene->Awake();
            mScene->Start();
            return true;
        }
        return false;
    }

    void Application::Run() {
        float lastTime = 0.0f;
        while (!mWindow->WindowShouldClose()) {
            float currentTime = GetDeltaTime();
            // Constrainst in 60FPS
            if ((currentTime - lastTime) * 1000 < MAX_DELTA_DIFF_MS) {
                continue;
            }
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;
            if (deltaTime >= MAX_DELTA_TIME) {
                deltaTime = MAX_DELTA_TIME;
            }
            
            this->ProcessInput();
            this->Update(deltaTime * mTimeScale);
            this->Render(deltaTime * mTimeScale);
        }
    }

    void Application::Shutdown() {
        mWindow->Shutdown();
        mScene->Shutdown();
    }

    void Application::ProcessInput() {
        mWindow->PollInputEvents();
    }

    void Application::Update(float deltaTime) {
        mScene->Update(deltaTime);
    }

    void Application::Render(float deltaTime) {
        mScene->BeginScene(deltaTime);
        mScene->Render(deltaTime);
        mScene->EndScene(deltaTime);
        mWindow->SwapBuffers();
    }
}