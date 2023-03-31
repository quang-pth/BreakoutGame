#include"Application.h"

namespace Waternion {
    static WindowConfig Config;

    Application::Application() : mIsRunning(true) {

    }

    bool Application::InitWindow(int width, int height, const std::string& title, const std::string& version) {
        mConfig.Height = width;
        mConfig.Width = height;
        mConfig.Title = title;
        mConfig.Version = version;
    
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW window object
        GLFWwindow* window = glfwCreateWindow(mConfig.Width, mConfig.Height, mConfig.Title.c_str(), NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        // Create the window context
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        
        // Init OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to init GLAD" << std::endl;
            return false;
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
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

        return true;
    }

    void Application::Run() {
        this->ProcessInput();
        this->Update(0.0f);
        this->Render(0.0f);
    }

    void Application::Shutdown() {

    }

    void Application::ProcessInput() {

    }

    void Application::Update(float deltaTime) {

    }

    void Application::Render(float deltaTime) {
        
    }
}