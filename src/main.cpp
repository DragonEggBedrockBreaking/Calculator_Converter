#include <iostream>
#include "imgui.h"
#include <GL/glxew.h>
#include <GLFW/glfw3.h>
#include "lib/imgui_impl_glfw.h"
#include "lib/imgui_impl_opengl3.h"
#include "lib/imgui_stdlib.h"

int main()
{
    if (!glfwInit()) {
        return 1;
    }


    // GLFW window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui", NULL, NULL);

    if (window == NULL) {
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise OpenGL loader!\n";
        return 1;
    }

    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    // OpenGL version
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Base stuff
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    bool should_stay_open = true;

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Inputs
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render gui
        if (should_stay_open) {
            ImGui::Begin("Demo window");

            if (ImGui::Button("Hello!")) {
                std::clog << "Hello pressed!\n";
            }

            static int i = 0;
            ImGui::Text("string = %d", i);
            std::string s {""};
            ImGui::InputText("Text", &s);

            if (s != "") {
                std::clog << s << "\n";
            }

            static float f = 0.0f;
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

            if (f != 0.0f) {
                std::clog << f << "\n";
            }

            ImGui::Checkbox("Window Open", &should_stay_open);

            ImGui::End();
        }

        // Render imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
