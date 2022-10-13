#include <iostream>
#include "imgui.h"
#include <GL/glxew.h>
#include <GLFW/glfw3.h>
#include "lib/imgui_impl_glfw.h"
#include "lib/imgui_impl_opengl3.h"
#include "lib/imgui_stdlib.h"
#include "maths_functions.h"

void test()
{
    double l1 = linear(1, 2, 2, -1);
    std::cout << l1 << std::endl;
    std::cout << 3 << std::endl << std::endl;

    auto [l21, l22] = linear(1.0, 1.0, 0.0, -2.0, 0.0, 13.0, 1.0, -1.0, -4.0, -4.0, 1.0, 3.0);
    std::cout << l21 << ", " << l22 << std::endl;
    std::cout << "3.0, 4.0" << std::endl << std::endl;

    auto [l31, l32, l33] = linear(1.0, 2.0, -1.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 12.0, 1.0, -1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 5.0);
    std::cout << l31 << ", " << l32 << ", " << l33 << std::endl;
    std::cout << "1.0, 2.0, 3.0" << std::endl << std::endl;

    auto [l41, l42, l43, l44] = linear(1.0, 2.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0, 1.5, 1.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 8.0, 4.0, 4.0, 3.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 22.0, 0.4, 0.0, 0.2, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0);
    std::cout << l41 << ", " << l42 << ", " << l43 << ", " << l44 << std::endl;
    std::cout << "16.0, -6.0, -2.0, -3.0" << std::endl << std::endl;

    auto [q1, q2] = quad(1.0, 0.0, -9.0, 0.0, 0.0, 0.0);
    std::cout << q1 << ", " << q2 << std::endl;
    std::cout << "3.0, -3.0" << std::endl << std::endl;

    auto [tp1, tp2] = quad_tp(1.0, 0.0, -9.0, 0.0, 0.0, 0.0);
    std::cout << tp1 << ", " << tp2 << std::endl;
    std::cout << "0.0, -9.0" << std::endl << std::endl;
}
int main()
{
    test();
    return 0;

    // ImGui stuff
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

    // Base stuff
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    // bool should_stay_open = true;

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
        /*if (should_stay_open) {
            ImGui::Begin("Demo window");

            if (ImGui::Button("Hello!")) {
                std::clog << "Hello pressed!\n";
            }

            static int i = 0;
            ImGui::Text("string = %d", i);
            std::string s {""};
            ImGui::InputText("Text", &s);
            static float f = 0.0f;
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::Checkbox("Window Open", &should_stay_open);

            ImGui::End();
        }*/

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
