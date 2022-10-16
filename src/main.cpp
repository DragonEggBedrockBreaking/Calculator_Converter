#include <array>
#include <iostream>
#include <map>
#include <fmt/core.h>
#include "imgui.h"
#include <GL/glxew.h>
#include <GLFW/glfw3.h>
#include "lib/imgui_impl_glfw.h"
#include "lib/imgui_impl_opengl3.h"
#include "lib/imgui_stdlib.h"
#include "maths_functions.h"

int main()
{
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

    // Define the window open bools
    static bool main_dropdown = true;
    static bool maths_main = false;
    static bool graphs = false;
    static bool conversion_main = false;
    static const char* items[] {"None", "Mathematical Calculations", "Unit Conversions"};

    // Define some vars
    double xcoef1_e1 = 0.0, ycoef1_e1 = 0.0, zcoef1_e1 = 0.0, acoef1_e1 = 0.0, num1_e1 = 0.0,
           xcoef2_e1 = 0.0, ycoef2_e1 = 0.0, zcoef2_e1 = 0.0, acoef2_e1 = 0.0, num2_e1 = 0.0,
           xcoef1_e2 = 0.0, ycoef1_e2 = 0.0, zcoef1_e2 = 0.0, acoef1_e2 = 0.0, num1_e2 = 0.0,
           xcoef2_e2 = 0.0, ycoef2_e2 = 0.0, zcoef2_e2 = 0.0, acoef2_e2 = 0.0, num2_e2 = 0.0,
           xcoef1_e3 = 0.0, ycoef1_e3 = 0.0, zcoef1_e3 = 0.0, acoef1_e3 = 0.0, num1_e3 = 0.0,
           xcoef2_e3 = 0.0, ycoef2_e3 = 0.0, zcoef2_e3 = 0.0, acoef2_e3 = 0.0, num2_e3 = 0.0,
           xcoef1_e4 = 0.0, ycoef1_e4 = 0.0, zcoef1_e4 = 0.0, acoef1_e4 = 0.0, num1_e4 = 0.0,
           xcoef2_e4 = 0.0, ycoef2_e4 = 0.0, zcoef2_e4 = 0.0, acoef2_e4 = 0.0, num2_e4 = 0.0,
           x4coef1 = 0.0, x4coef2 = 0.0, x3coef1 = 0.0, x3coef2 = 0.0, x2coef1 = 0.0, x2coef2 = 0.0,
           xcoef1 = 0.0, xcoef2 = 0.0, num1 = 0.0, num2 = 0.0, error = 0.0;
    std::string ans1 = "", ans2 = "", ans3 = "", ans4 = "";

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Inputs
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main dropdown
        if (main_dropdown) {
            ImGui::Begin("Main Dropdown", &main_dropdown);
            static int selected_item = 0;
            ImGui::Combo("Options", &selected_item, items, IM_ARRAYSIZE(items));

            switch (selected_item) {
            case 0:
                maths_main = false;
                conversion_main = false;
                break;

            case 1:
                maths_main = true;
                conversion_main = false;
                break;

            case 2:
                maths_main = false;
                conversion_main = true;
                break;
            }

            ImGui::End();
        }

        // Maths dropdown
        if (maths_main) {
            ImGui::Begin("Maths dropdown", &maths_main);
            ImGui::Checkbox("Graphs", &graphs);
            static int selected_maths_opt;
            static const char* maths_options[] {"Basic Operations", "Linear Equations", "Non Linear Equations", "Calculus", "Probability"};
            ImGui::Combo("Mathematical Operations", &selected_maths_opt, maths_options, IM_ARRAYSIZE(maths_options));

            switch (selected_maths_opt) {
            case 0:
                static std::string expression;
                ImGui::InputText("Mathematical Expression", &expression);
                ImGui::Text("%s", fmt::format("Answer: {}", std::to_string(basic(expression))).c_str());
                break;

            case 1:
                static int unknowns = 1;
                ImGui::SliderInt("Number of unknowns", &unknowns, 1, 4);

                if (unknowns == 1) {
                    ImGui::PushItemWidth(74);
                    ImGui::InputDouble("x +##foo1", &xcoef1_e1, 0.0, 0.0, "%.8f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(74);
                    ImGui::InputDouble("=##foo2", &num1_e1, 0.0, 0.0, "%.8f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(74);
                    ImGui::InputDouble("x +##foo3", &xcoef2_e1, 0.0, 0.0, "%.8f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(74);
                    ImGui::InputDouble("##foo4", &num2_e1, 0.0, 0.0, "%.8f");

                    if (ImGui::Button("Solve")) {
                        ans1 = std::to_string(linear(xcoef1_e1, num1_e1, xcoef2_e1, num2_e1));
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answer: x = {}", ans1).c_str());
                }

                if (unknowns == 2) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo1", &xcoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo2", &ycoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo3", &num1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo4", &xcoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo5", &ycoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo6", &num2_e1, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo7", &xcoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo8", &ycoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo9", &num1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo10", &xcoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo11", &ycoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo12", &num2_e2, 0.0, 0.0, "%.5f");

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2] = linear(xcoef1_e1, ycoef1_e1, num1_e1, xcoef2_e1, ycoef2_e1, num2_e1,
                                                         xcoef1_e2, ycoef1_e2, num1_e2, xcoef2_e2, ycoef2_e2, num2_e2);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answer: x = {}, y = {}", ans1, ans2).c_str());
                }

                if (unknowns == 3) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo1", &xcoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo2", &ycoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo3", &zcoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo4", &num1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo5", &xcoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo6", &ycoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo7", &zcoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo8", &num2_e1, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo9", &xcoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo10", &ycoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo11", &zcoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo12", &num1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo13", &xcoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo14", &ycoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo15", &zcoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo16", &num2_e2, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo17", &xcoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo18", &ycoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo19", &zcoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo20", &num1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo21", &xcoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo22", &ycoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo23", &zcoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo24", &num2_e3, 0.0, 0.0, "%.5f");

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2, answer3] = linear(xcoef1_e1, ycoef1_e1, zcoef1_e1, num1_e1,
                                                           xcoef2_e1, ycoef2_e1, zcoef2_e1, num2_e1,
                                                           xcoef1_e2, ycoef1_e2, zcoef1_e2, num1_e2,
                                                           xcoef2_e2, ycoef2_e2, zcoef2_e2, num2_e2,
                                                           xcoef1_e3, ycoef1_e3, zcoef1_e3, num1_e3,
                                                           xcoef2_e3, ycoef2_e3, zcoef2_e3, num2_e3);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answer: x = {}, y = {}, z = {}", ans1, ans2, ans3).c_str());
                }

                if (unknowns == 4) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo1", &xcoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo2", &ycoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo3", &zcoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo4", &acoef1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo5", &num1_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo6", &xcoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo7", &ycoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo8", &zcoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo9", &acoef2_e1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo10", &num2_e1, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo11", &xcoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo12", &ycoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo13", &zcoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo14", &acoef1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo15", &num1_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo16", &xcoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo17", &ycoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo18", &zcoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo19", &acoef2_e2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo20", &num2_e2, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo21", &xcoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo22", &ycoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo23", &zcoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo24", &acoef1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo25", &num1_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo26", &xcoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo27", &ycoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo28", &zcoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo29", &acoef2_e3, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo30", &num2_e3, 0.0, 0.0, "%.5f");

                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo31", &xcoef1_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo32", &ycoef1_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo33", &zcoef1_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo34", &acoef1_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo35", &num1_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo36", &xcoef2_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("y +##foo37", &ycoef2_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("z +##foo38", &zcoef2_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("a +##foo39", &acoef2_e4, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo40", &num2_e4, 0.0, 0.0, "%.5f");

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2, answer3, answer4] = linear(xcoef1_e1, ycoef1_e1, zcoef1_e1, acoef1_e1, num1_e1,
                                xcoef2_e1, ycoef2_e1, zcoef2_e1, acoef2_e1, num2_e1,
                                xcoef1_e2, ycoef1_e2, zcoef1_e2, acoef1_e2, num1_e2,
                                xcoef2_e2, ycoef2_e2, zcoef2_e2, acoef2_e2, num2_e2,
                                xcoef1_e3, ycoef1_e3, zcoef1_e3, acoef1_e3, num1_e3,
                                xcoef2_e3, ycoef2_e3, zcoef2_e3, acoef2_e3, num2_e3,
                                xcoef1_e4, ycoef1_e4, zcoef1_e4, acoef1_e4, num1_e4,
                                xcoef2_e4, ycoef2_e4, zcoef2_e4, acoef2_e4, num2_e4);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3), ans4 = std::to_string(answer4);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answer: x = {}, y = {}, z = {}, a = {}", ans1, ans2, ans3, ans4).c_str());
                }

                break;

            case 2:
                static int exponent = 2;
                ImGui::SliderInt("Number of unknowns", &exponent, 2, 4);

                if (exponent == 2) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2 +##foo1", &x2coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo2", &xcoef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo3", &num1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2 +##foo4", &x2coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo5", &xcoef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo6", &num2, 0.0, 0.0, "%.5f");

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2] = quad(x2coef1, xcoef1, num1, x2coef2, xcoef2, num2);
                        auto [answer3, answer4] = quad_tp(x2coef1, xcoef1, num1, x2coef2, xcoef2, num2);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3), ans4 = std::to_string(answer4);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answers: x = {}, x = {}", ans1, ans2).c_str());
                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Turning point: ({}, {})", ans3, ans4).c_str());
                }

                if (exponent == 3) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^3 +##foo1", &x3coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2 +##foo2", &x2coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo3", &xcoef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo4", &num1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^3 +##foo5", &x3coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2##foo6", &x2coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo7", &xcoef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo8", &num2, 0.0, 0.0, "%.5f");

                    ImGui::Text("This solution uses the Newton-Raphson iterative method. Please enter the error leniency.");
                    ImGui::InputDouble("##foo9", &error);

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2, answer3] = cubic(error, x3coef1, x2coef1, xcoef1, num1, x3coef2, x2coef2, xcoef2, num2);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answers: x = {}, x = {}, x = {}", ans1, ans2, ans3).c_str());
                }

                if (exponent == 4) {
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^4 +##foo1", &x4coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^3 +##foo2", &x3coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2 +##foo3", &x2coef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo4", &xcoef1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("=##foo5", &num1, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^4 +##foo6", &x4coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^3 +##foo7", &x3coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x^2##foo8", &x2coef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("x +##foo9", &xcoef2, 0.0, 0.0, "%.5f");

                    ImGui::SameLine();
                    ImGui::PushItemWidth(55);
                    ImGui::InputDouble("##foo10", &num2, 0.0, 0.0, "%.5f");

                    ImGui::Text("This solution uses the Newton-Raphson iterative method. Please enter the error leniency.");
                    ImGui::InputDouble("##foo11", &error);

                    if (ImGui::Button("Solve")) {
                        auto [answer1, answer2, answer3, answer4] = quartic(error, x4coef1, x3coef1, x2coef1, xcoef1, num1, x4coef2, x3coef2, x2coef2, xcoef2, num2);
                        ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3), ans4 = std::to_string(answer4);
                    }

                    ImGui::SameLine();
                    ImGui::Text("%s", fmt::format("Answers: x = {}, x = {}, x = {}, x = {}", ans1, ans2, ans3, ans4).c_str());
                }
            }

            ImGui::End();
        }

        // Graphs
        if (maths_main && graphs) {
            ImGui::Begin("Graphs", &graphs);
            ImGui::End();
        }

        // Conversion dropdown
        if (conversion_main) {
            ImGui::Begin("Conversion dropdown", &conversion_main);
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
