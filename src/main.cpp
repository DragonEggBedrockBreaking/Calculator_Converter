#include <iostream>

#include <GL/glxew.h>
#include <GLFW/glfw3.h>
#include "lib/imgui_impl_glfw.h"
#include "lib/imgui_impl_opengl3.h"
#include "lib/imgui_stdlib.h"

#include "guis.h"

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
    ImPlot::CreateContext();

    // Define the window open bools
    static const char* items[] {"None", "Mathematical Calculations", "Graphs", "Unit Conversions", "Scripting"};

    // Define some vars
    static const char* unit_types[] {
        "length",
        "mass",
        "time",
        "temperature",
        "velocity",
        "acceleration",
        "pressure",
        "energy",
        "area",
        "volume",
        "density",
        "currency"
    };
    double xcoef1_e1 = 0.0, ycoef1_e1 = 0.0, zcoef1_e1 = 0.0, acoef1_e1 = 0.0, num1_e1 = 0.0,
           xcoef2_e1 = 0.0, ycoef2_e1 = 0.0, zcoef2_e1 = 0.0, acoef2_e1 = 0.0, num2_e1 = 0.0,
           xcoef1_e2 = 0.0, ycoef1_e2 = 0.0, zcoef1_e2 = 0.0, acoef1_e2 = 0.0, num1_e2 = 0.0,
           xcoef2_e2 = 0.0, ycoef2_e2 = 0.0, zcoef2_e2 = 0.0, acoef2_e2 = 0.0, num2_e2 = 0.0,
           xcoef1_e3 = 0.0, ycoef1_e3 = 0.0, zcoef1_e3 = 0.0, acoef1_e3 = 0.0, num1_e3 = 0.0,
           xcoef2_e3 = 0.0, ycoef2_e3 = 0.0, zcoef2_e3 = 0.0, acoef2_e3 = 0.0, num2_e3 = 0.0,
           xcoef1_e4 = 0.0, ycoef1_e4 = 0.0, zcoef1_e4 = 0.0, acoef1_e4 = 0.0, num1_e4 = 0.0,
           xcoef2_e4 = 0.0, ycoef2_e4 = 0.0, zcoef2_e4 = 0.0, acoef2_e4 = 0.0, num2_e4 = 0.0,
           x4coef1 = 0.0, x4coef2 = 0.0, x3coef1 = 0.0, x3coef2 = 0.0, x2coef1 = 0.0, x2coef2 = 0.0,
           xcoef1 = 0.0, xcoef2 = 0.0, num1 = 0.0, num2 = 0.0, error = 0.0, value = 0.0,
           first = 0.0, second = 0.0, third = 0.0;

    std::string expression1 = "", expression2 = "", expression3 = "", expression4 = "", text = "",
                ans1 = "", ans2 = "", ans3 = "", ans4 = "", inpath = "", outpath = "", message = "";

    bool main_dropdown = true, maths_main = false, graphs = false, conversion_main = false, scripting = false,
         plot1 = false, plot2 = false, plot3 = false, plot4 = false, processing = false, currency_handled = false;

    ImVec4 colour1 = ImVec4(1, 0.75f, 0, 1), colour2 = ImVec4(0, 1, 0, 1),
           colour3 = ImVec4(1, 0, 1, 0), colour4 = ImVec4(0, 1, 1, 0);

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
                graphs = false;
                conversion_main = false;
                scripting = false;
                break;

            case 1:
                maths_main = true;
                graphs = false;
                conversion_main = false;
                scripting = false;
                break;

            case 2:
                maths_main = false;
                graphs = true;
                conversion_main = false;
                scripting = false;
                break;

            case 3:
                maths_main = false;
                graphs = false;
                conversion_main = true;
                scripting = false;
                break;

            case 4:
                maths_main = false;
                graphs = false;
                conversion_main = false;
                scripting = true;
                break;
            }

            if (ImGui::Button("Reset All")) {
                xcoef1_e1 = 0.0, ycoef1_e1 = 0.0, zcoef1_e1 = 0.0, acoef1_e1 = 0.0, num1_e1 = 0.0,
                xcoef2_e1 = 0.0, ycoef2_e1 = 0.0, zcoef2_e1 = 0.0, acoef2_e1 = 0.0, num2_e1 = 0.0,
                xcoef1_e2 = 0.0, ycoef1_e2 = 0.0, zcoef1_e2 = 0.0, acoef1_e2 = 0.0, num1_e2 = 0.0,
                xcoef2_e2 = 0.0, ycoef2_e2 = 0.0, zcoef2_e2 = 0.0, acoef2_e2 = 0.0, num2_e2 = 0.0,
                xcoef1_e3 = 0.0, ycoef1_e3 = 0.0, zcoef1_e3 = 0.0, acoef1_e3 = 0.0, num1_e3 = 0.0,
                xcoef2_e3 = 0.0, ycoef2_e3 = 0.0, zcoef2_e3 = 0.0, acoef2_e3 = 0.0, num2_e3 = 0.0,
                xcoef1_e4 = 0.0, ycoef1_e4 = 0.0, zcoef1_e4 = 0.0, acoef1_e4 = 0.0, num1_e4 = 0.0,
                xcoef2_e4 = 0.0, ycoef2_e4 = 0.0, zcoef2_e4 = 0.0, acoef2_e4 = 0.0, num2_e4 = 0.0,
                x4coef1 = 0.0, x4coef2 = 0.0, x3coef1 = 0.0, x3coef2 = 0.0, x2coef1 = 0.0, x2coef2 = 0.0,
                xcoef1 = 0.0, xcoef2 = 0.0, num1 = 0.0, num2 = 0.0, error = 0.0, value = 0.0,
                first = 0.0, second = 0.0, third = 0.0;

                expression1 = "", expression2 = "", expression3 = "", expression4 = "", text = "",
                ans1 = "", ans2 = "", ans3 = "", ans4 = "", inpath = "", outpath = "", message = "";

                main_dropdown = true, maths_main = false, graphs = false, conversion_main = false, scripting = false,
                plot1 = false, plot2 = false, plot3 = false, plot4 = false, processing = false;

                colour1 = ImVec4(1, 0.75f, 0, 1), colour2 = ImVec4(0, 1, 0, 1),
                colour3 = ImVec4(1, 0, 1, 0), colour4 = ImVec4(0, 1, 1, 0);
            }

            ImGui::End();
        }

        // Maths dropdown
        if (maths_main) {
            ImGui::Begin("Maths dropdown", &maths_main);
            static int selected_maths_opt;
            static const char* maths_options[] {"Basic Operations", "Linear Equations", "Non Linear Equations", "Calculus", "Probability"};
            ImGui::Combo("Mathematical Operations", &selected_maths_opt, maths_options, IM_ARRAYSIZE(maths_options));

            run_maths_gui(selected_maths_opt, xcoef1_e1, ycoef1_e1, zcoef1_e1, acoef1_e1, num1_e1,
                          xcoef2_e1, ycoef2_e1, zcoef2_e1, acoef2_e1, num2_e1,
                          xcoef1_e2, ycoef1_e2, zcoef1_e2, acoef1_e2, num1_e2,
                          xcoef2_e2, ycoef2_e2, zcoef2_e2, acoef2_e2, num2_e2,
                          xcoef1_e3, ycoef1_e3, zcoef1_e3, acoef1_e3, num1_e3,
                          xcoef2_e3, ycoef2_e3, zcoef2_e3, acoef2_e3, num2_e3,
                          xcoef1_e4, ycoef1_e4, zcoef1_e4, acoef1_e4, num1_e4,
                          xcoef2_e4, ycoef2_e4, zcoef2_e4, acoef2_e4, num2_e4,
                          x4coef1, x4coef2, x3coef1, x3coef2, x2coef1, x2coef2,
                          xcoef1, xcoef2, num1, num2, error, value,
                          first, second, third, ans1, ans2, ans3, ans4);

            ImGui::End();
        }

        // Graphs
        if (graphs) {
            ImGui::Begin("Graphs", &graphs);

            Graph graph;
            graph.run_graph_gui(expression1, plot1, expression2, plot2,
                                expression3, plot3, expression4, plot4,
                                colour1, colour2, colour3, colour4);

            ImGui::End();
        }

        // Conversion dropdown
        if (conversion_main) {
            ImGui::Begin("Conversion dropdown", &conversion_main);
            static int selected_conversion_opt;
            ImGui::Combo("Mathematical Operations", &selected_conversion_opt, unit_types, IM_ARRAYSIZE(unit_types));

            run_conversion_gui(selected_conversion_opt, value, text, currency_handled);

            ImGui::End();
        }

        // Scripting
        if (scripting) {
            ImGui::Begin("Scripting", &scripting);

            run_scripting_gui(inpath, outpath, message, processing);

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
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
