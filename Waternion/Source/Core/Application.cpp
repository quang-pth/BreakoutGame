#include"Application.h"

namespace Waternion {
    Application::Application() {
        mWindow.reset(new Window());
    }

    bool Application::InitWindow(int width, int height, const std::string& title, const std::string& version) {
        if (!mWindow->Init(width, height, title)) {
            WATERNION_LOG_ERROR("Init Window succesfully");
        }

        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cout << "Failed to init Freetype\n";
            return false; 
        }
        FT_Face face;
        if (FT_New_Face(ft, "assets/fonts/arial.ttf", 0, &face)) {
            std::cout << "Failed to Load font\n";
            return false; 
        }

        return true;
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
            this->Update(deltaTime);
            this->Render(deltaTime);
        }
    }

    void Application::Shutdown() {
        mWindow->Shutdown();
    }

    void Application::ProcessInput() {
        mWindow->ProcessInput();
    }

    void Application::Update(float deltaTime) {

    }

    void Application::Render(float deltaTime) {
        
    }
}