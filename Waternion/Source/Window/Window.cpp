#include"Window.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/TextRenderer.h"

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

namespace Waternion {
    static InputState state;
    static Shared<Application> application;

    static void PrepareInputStates() {
        memcpy(state.Keyboard.PreviousState, state.Keyboard.CurrentState, NUM_KEYS);
        memset(state.Keyboard.CurrentState, false, NUM_KEYS);
    }

    static void ResizeCallback(GLFWwindow* window, int width, int height) {
        application->SetWindowWidth(width);
        application->SetWindowHeight(height);
        glViewport(0, 0, width, height);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (key >= 0 && key <= 1024) {
                state.Keyboard.CurrentState[key] = true;
            }
        }
    }

    static ImGuiIO io;
    bool Window::Init(uint32_t width, uint32_t height, const std::string& name) {
        mWidth = width;
        mHeight = height;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        mInstance = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (mInstance == nullptr) {
            WATERNION_LOG_ERROR("Failed to Init GLFW Window!");
            glfwTerminate();
            return false;
        }

        // Make window context
        glfwMakeContextCurrent(mInstance);
        glfwSetInputMode(mInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Register window callbacks
        glfwSetFramebufferSizeCallback(mInstance, ResizeCallback);
        glfwSetKeyCallback(mInstance, KeyCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            WATERNION_LOG_ERROR("Failed to Init GLAD!");
            return false;
        }

        // Setup IMGUI context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(mInstance, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        application = Application::GetInstance();
        WATERNION_LOG_INFO("Init Window Successfully!");
        return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    void Window::PollInputEvents() {
        PrepareInputStates();
        glfwPollEvents();
        application->GetScene()->GetSystem<ECS::InputSystem>()->ProcessInput(state);
    }

    static bool show_demo_window = true;
    static bool show_another_window = false;
    void Window::SwapBuffers() {
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
                   {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mInstance);
    }
}