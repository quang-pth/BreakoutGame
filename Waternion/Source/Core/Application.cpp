#include"Application.h"

#include"ECS/System/InputSystem.h"
#include"Core/Event/EventDispatcher.h"
#include"Layer/GUI/GUI.h"

namespace Waternion {
    Shared<Application> Application::GetInstance() {
        static Shared<Application> application;
        if (application == nullptr) {
            application.reset(new Application());
        }
        return application;
    }

    Application::Application() : mTimeScale(1.0f), mIsRunning(true) {
        
    }

    bool Application::Init(int width, int height, const std::string& title, const std::string& version) {
        mCoordinator.reset(new ECS::Coordinator());
        mScene.reset(new ECS::Scene());

        if (!Window::Init(width, height, title)) {
            WATERNION_LOG_ERROR("Init Window succesfully");
        }

        Window::sEventDispatcher->RegisterCallback<WindowResizedEvent>([](const WindowResizedEvent& event) {
            glViewport(0, 0, event.GetWidth(), event.GetHeight());            
            return true;
        });

        Window::sEventDispatcher->RegisterCallback<KeyPressedEvent>([&](const KeyPressedEvent& event) {
            if (event.GetKey() == GLFW_KEY_ESCAPE) {
                mIsRunning = false;
            }
            return false;
        });

        if (!this->LoadScene()) {
            return false;
        }

        GUI* gui = new GUI();
        if (!gui->Init()) {
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
        while (mIsRunning) {
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
        Window::Shutdown();
        mScene->Shutdown();
        for (auto iter = mLayers.crbegin(); iter != mLayers.crend(); iter++) {
            (*iter)->Shutdown();
        }
    }

    void Application::PushLayer(Layer* layer) {
        Shared<Layer> newLayer;
        newLayer.reset(layer);
        auto iter = std::find(mLayers.begin(), mLayers.end(), newLayer);
        if (iter == mLayers.end()) {
            mLayers.emplace_back(newLayer);
            return;
        }
        WATERNION_LOG_WARNING("Pushing already existed layer");
    }

    void Application::ProcessInput() {
        Window::PrepareInputStates();
        Window::PollInputEvents();
        mScene->ProcessInput(Window::sInputState);
    }

    void Application::Update(float deltaTime) {
        mScene->Update(deltaTime);
        for (auto iter = mLayers.crbegin(); iter != mLayers.crend(); iter++) {
            (*iter)->Update(deltaTime);
        }
    }

    void Application::Render(float deltaTime) {
        mScene->BeginScene(deltaTime);
        mScene->Render(deltaTime);
        mScene->EndScene(deltaTime);

        if (const Shared<GUI>& gui = this->GetLayer<GUI>()) {
            gui->Begin();
            for (auto iter = mLayers.crbegin(); iter != mLayers.crend(); iter++) {
                (*iter)->Render();
            }
            gui->End();   
        }

        Window::SwapBuffers();
    }
}