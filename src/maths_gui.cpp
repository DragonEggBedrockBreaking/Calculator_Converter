#include <fmt/core.h>
#include "imgui.h"
#include "lib/imgui_stdlib.h"
#include "maths_functions.h"
#include "guis.h"
#include "utils.h"

void linear(double& xcoef1_e1, double& ycoef1_e1, double& zcoef1_e1, double& acoef1_e1, double& num1_e1,
            double& xcoef2_e1, double& ycoef2_e1, double& zcoef2_e1, double& acoef2_e1, double& num2_e1,
            double& xcoef1_e2, double& ycoef1_e2, double& zcoef1_e2, double& acoef1_e2, double& num1_e2,
            double& xcoef2_e2, double& ycoef2_e2, double& zcoef2_e2, double& acoef2_e2, double& num2_e2,
            double& xcoef1_e3, double& ycoef1_e3, double& zcoef1_e3, double& acoef1_e3, double& num1_e3,
            double& xcoef2_e3, double& ycoef2_e3, double& zcoef2_e3, double& acoef2_e3, double& num2_e3,
            double& xcoef1_e4, double& ycoef1_e4, double& zcoef1_e4, double& acoef1_e4, double& num1_e4,
            double& xcoef2_e4, double& ycoef2_e4, double& zcoef2_e4, double& acoef2_e4, double& num2_e4,
            std::string& ans1, std::string& ans2, std::string& ans3, std::string& ans4
           )
{
    static int unknowns = 1;
    ImGui::SliderInt("Number of unknowns", &unknowns, 1, 4);

    if (unknowns == 1) {
        ImGui::PushItemWidth(74);
        input_double("x +##foo1", &xcoef1_e1, "%.8f", false);
        input_double("=##foo2", &num1_e1, "%.8f", true);
        input_double("x +##foo3", &xcoef2_e1, "%.8f", true);
        input_double("##foo4", &num2_e1, "%.8f", true);

        if (ImGui::Button("Solve")) {
            ans1 = std::to_string(linear(xcoef1_e1, num1_e1, xcoef2_e1, num2_e1));
        }

        ImGui::SameLine();
        ImGui::Text("%s", fmt::format("Answer: x = {}", ans1).c_str());
    }

    if (unknowns == 2) {
        ImGui::PushItemWidth(55);
        input_double("x +##foo1", &xcoef1_e1, "%.5f", false);
        input_double("y +##foo2", &ycoef1_e1, "%.5f", true);
        input_double("=##foo3", &num1_e1, "%.5f", true);
        input_double("x +##foo4", &xcoef2_e1, "%.5f", true);
        input_double("y +##foo5", &ycoef2_e1, "%.5f", true);
        input_double("##foo6", &num2_e1, "%.5f", true);

        input_double("x +##foo7", &xcoef1_e2, "%.5f", false);
        input_double("y +##foo8", &ycoef1_e2, "%.5f", true);
        input_double("=##foo9", &num1_e2, "%.5f", true);
        input_double("x +##foo10", &xcoef2_e2, "%.5f", true);
        input_double("y +##foo11", &ycoef2_e2, "%.5f", true);
        input_double("##foo12", &num2_e2, "%.5f", true);

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
        input_double("x +##foo1", &xcoef1_e1, "%.5f", false);
        input_double("y +##foo2", &ycoef1_e1, "%.5f", true);
        input_double("z +##foo3", &zcoef1_e1, "%.5f", true);
        input_double("=##foo4", &num1_e1, "%.5f", true);
        input_double("x +##foo5", &xcoef2_e1, "%.5f", true);
        input_double("y +##foo6", &ycoef2_e1, "%.5f", true);
        input_double("z +##foo7", &zcoef2_e1, "%.5f", true);
        input_double("##foo8", &num2_e1, "%.5f", true);

        input_double("x +##foo9", &xcoef1_e2, "%.5f", false);
        input_double("y +##foo10", &ycoef1_e2, "%.5f", true);
        input_double("z +##foo11", &zcoef1_e2, "%.5f", true);
        input_double("=##foo12", &num1_e2, "%.5f", true);
        input_double("x +##foo13", &xcoef2_e2, "%.5f", true);
        input_double("y +##foo14", &ycoef2_e2, "%.5f", true);
        input_double("z +##foo15", &zcoef2_e2, "%.5f", true);
        input_double("##foo16", &num2_e2, "%.5f", true);

        input_double("x +##foo17", &xcoef1_e3, "%.5f", false);
        input_double("y +##foo18", &ycoef1_e3, "%.5f", true);
        input_double("z +##foo19", &zcoef1_e3, "%.5f", true);
        input_double("=##foo20", &num1_e3, "%.5f", true);
        input_double("x +##foo21", &xcoef2_e3, "%.5f", true);
        input_double("y +##foo22", &ycoef2_e3, "%.5f", true);
        input_double("z +##foo23", &zcoef2_e3, "%.5f", true);
        input_double("##foo24", &num2_e3, "%.5f", true);

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
        input_double("x +##foo1", &xcoef1_e1, "%.5f", false);
        input_double("y +##foo2", &ycoef1_e1, "%.5f", true);
        input_double("z +##foo3", &zcoef1_e1, "%.5f", true);
        input_double("a +##foo4", &acoef1_e1, "%.5f", true);
        input_double("=##foo5", &num1_e1, "%.5f", true);
        input_double("x +##foo6", &xcoef2_e1, "%.5f", true);
        input_double("y +##foo7", &ycoef2_e1, "%.5f", true);
        input_double("z +##foo8", &zcoef2_e1, "%.5f", true);
        input_double("a +##foo9", &acoef2_e1, "%.5f", true);
        input_double("##foo10", &num2_e1, "%.5f", true);

        input_double("x +##foo11", &xcoef1_e2, "%.5f", false);
        input_double("y +##foo12", &ycoef1_e2, "%.5f", true);
        input_double("z +##foo13", &zcoef1_e2, "%.5f", true);
        input_double("a +##foo14", &acoef1_e2, "%.5f", true);
        input_double("=##foo15", &num1_e2, "%.5f", true);
        input_double("x +##foo16", &xcoef2_e2, "%.5f", true);
        input_double("y +##foo17", &ycoef2_e2, "%.5f", true);
        input_double("z +##foo18", &zcoef2_e2, "%.5f", true);
        input_double("a +##foo19", &acoef2_e2, "%.5f", true);
        input_double("##foo20", &num2_e2, "%.5f", true);

        input_double("x +##foo21", &xcoef1_e3, "%.5f", false);
        input_double("y +##foo22", &ycoef1_e3, "%.5f", true);
        input_double("z +##foo23", &zcoef1_e3, "%.5f", true);
        input_double("a +##foo24", &acoef1_e3, "%.5f", true);
        input_double("=##foo25", &num1_e3, "%.5f", true);
        input_double("x +##foo26", &xcoef2_e3, "%.5f", true);
        input_double("y +##foo27", &ycoef2_e3, "%.5f", true);
        input_double("z +##foo28", &zcoef2_e3, "%.5f", true);
        input_double("a +##foo29", &acoef2_e3, "%.5f", true);
        input_double("##foo30", &num2_e3, "%.5f", true);

        input_double("x +##foo31", &xcoef1_e4, "%.5f", false);
        input_double("y +##foo32", &ycoef1_e4, "%.5f", true);
        input_double("z +##foo33", &zcoef1_e4, "%.5f", true);
        input_double("a +##foo34", &acoef1_e4, "%.5f", true);
        input_double("=##foo35", &num1_e4, "%.5f", true);
        input_double("x +##foo36", &xcoef2_e4, "%.5f", true);
        input_double("y +##foo37", &ycoef2_e4, "%.5f", true);
        input_double("z +##foo38", &zcoef2_e4, "%.5f", true);
        input_double("a +##foo39", &acoef2_e4, "%.5f", true);
        input_double("##foo40", &num2_e4, "%.5f", true);

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
}

void non_linear(double& x4coef1, double& x4coef2, double& x3coef1, double& x3coef2, double& x2coef1, double& x2coef2,
                double& xcoef1, double& xcoef2, double& num1, double& num2, double& error,
                std::string& ans1, std::string& ans2, std::string& ans3, std::string& ans4)
{
    static int exponent = 2;
    ImGui::SliderInt("Number of unknowns", &exponent, 2, 4);

    if (exponent == 2) {
        ImGui::PushItemWidth(55);
        input_double("x^2 +##foo1", &x2coef1, "%.5f", false);
        input_double("x +##foo2", &xcoef1, "%.5f", true);
        input_double("=##foo3", &num1, "%.5f", true);
        input_double("x^2 +##foo4", &x2coef2, "%.5f", true);
        input_double("x +##foo5", &xcoef2, "%.5f", true);
        input_double("##foo6", &num2, "%.5f", true);

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
        input_double("x^3 +##foo1", &x3coef1, "%.5f", false);
        input_double("x^2 +##foo2", &x2coef1, "%.5f", true);
        input_double("x +##foo3", &xcoef1, "%.5f", true);
        input_double("=##foo4", &num1, "%.5f", true);
        input_double("x^3 +##foo5", &x3coef2, "%.5f", true);
        input_double("x^2##foo6", &x2coef2, "%.5f", true);
        input_double("x +##foo7", &xcoef2, "%.5f", true);
        input_double("##foo8", &num2, "%.5f", true);

        ImGui::Text("This solution uses the Newton-Raphson iterative method. Please enter the error leniency.");
        ImGui::PushItemWidth(610);
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
        input_double("x^4 +##foo1", &x4coef1, "%.5f", false);
        input_double("x^3 +##foo2", &x3coef1, "%.5f", true);
        input_double("x^2 +##foo3", &x2coef1, "%.5f", true);
        input_double("x +##foo4", &xcoef1, "%.5f", true);
        input_double("=##foo5", &num1, "%.5f", true);
        input_double("x^4 +##foo6", &x4coef2, "%.5f", true);
        input_double("x^3 +##foo7", &x3coef2, "%.5f", true);
        input_double("x^2##foo8", &x2coef2, "%.5f", true);
        input_double("x +##foo9", &xcoef2, "%.5f", true);
        input_double("##foo10", &num2, "%.5f", true);

        ImGui::Text("This solution uses the Newton-Raphson iterative method. Please enter the error leniency.");
        ImGui::PushItemWidth(610);
        ImGui::InputDouble("##foo11", &error);

        if (ImGui::Button("Solve")) {
            auto [answer1, answer2, answer3, answer4] = quartic(error, x4coef1, x3coef1, x2coef1, xcoef1, num1, x4coef2, x3coef2, x2coef2, xcoef2, num2);
            ans1 = std::to_string(answer1), ans2 = std::to_string(answer2), ans3 = std::to_string(answer3), ans4 = std::to_string(answer4);
        }

        ImGui::SameLine();
        ImGui::Text("%s", fmt::format("Answers: x = {}, x = {}, x = {}, x = {}", ans1, ans2, ans3, ans4).c_str());
    }
}

void run_maths_gui(const int& selected_maths_opt,
                   double& xcoef1_e1, double& ycoef1_e1, double& zcoef1_e1, double& acoef1_e1, double& num1_e1,
                   double& xcoef2_e1, double& ycoef2_e1, double& zcoef2_e1, double& acoef2_e1, double& num2_e1,
                   double& xcoef1_e2, double& ycoef1_e2, double& zcoef1_e2, double& acoef1_e2, double& num1_e2,
                   double& xcoef2_e2, double& ycoef2_e2, double& zcoef2_e2, double& acoef2_e2, double& num2_e2,
                   double& xcoef1_e3, double& ycoef1_e3, double& zcoef1_e3, double& acoef1_e3, double& num1_e3,
                   double& xcoef2_e3, double& ycoef2_e3, double& zcoef2_e3, double& acoef2_e3, double& num2_e3,
                   double& xcoef1_e4, double& ycoef1_e4, double& zcoef1_e4, double& acoef1_e4, double& num1_e4,
                   double& xcoef2_e4, double& ycoef2_e4, double& zcoef2_e4, double& acoef2_e4, double& num2_e4,
                   double& x4coef1, double& x4coef2, double& x3coef1, double& x3coef2, double& x2coef1, double& x2coef2,
                   double& xcoef1, double& xcoef2, double& num1, double& num2, double& error, double& value,
                   double& first, double& second, double& third,
                   std::string& ans1, std::string& ans2, std::string& ans3, std::string& ans4)
{
    switch (selected_maths_opt) {
    case 0:
        static std::string expression;
        ImGui::InputText("Mathematical Expression", &expression);
        ImGui::Text("%s", fmt::format("Answer: {}", std::to_string(basic(expression))).c_str());
        break;

    case 1:
        linear(xcoef1_e1, ycoef1_e1, zcoef1_e1, acoef1_e1, num1_e1,
               xcoef2_e1, ycoef2_e1, zcoef2_e1, acoef2_e1, num2_e1,
               xcoef1_e2, ycoef1_e2, zcoef1_e2, acoef1_e2, num1_e2,
               xcoef2_e2, ycoef2_e2, zcoef2_e2, acoef2_e2, num2_e2,
               xcoef1_e3, ycoef1_e3, zcoef1_e3, acoef1_e3, num1_e3,
               xcoef2_e3, ycoef2_e3, zcoef2_e3, acoef2_e3, num2_e3,
               xcoef1_e4, ycoef1_e4, zcoef1_e4, acoef1_e4, num1_e4,
               xcoef2_e4, ycoef2_e4, zcoef2_e4, acoef2_e4, num2_e4,
               ans1, ans2, ans3, ans4);
        break;

    case 2:
        non_linear(x4coef1, x4coef2, x3coef1, x3coef2, x2coef1, x2coef2,
                   xcoef1, xcoef2, num1, num2, error, ans1, ans2, ans3, ans4);
        break;

    case 3:
        static std::string equation;
        ImGui::InputText("Mathematical Equation", &equation);

        try {
            ImGui::Text("%s", fmt::format("Differentiated: {}", diff(equation)).c_str());
        }
        catch (std::invalid_argument) {
            ImGui::Text("Differentiated:");
        }

        try {
            ImGui::Text("%s", fmt::format("Integrated: {}", integr(equation)).c_str());
        }
        catch (std::invalid_argument) {
            ImGui::Text("Integrated:");
        }

        break;

    case 4:
        ImGui::PushItemWidth(55);

        input_double("P##foo1", &first, "%.5f", false);
        input_double("=##foo2", &second, "%.5f", true);
        ImGui::SameLine();
        ImGui::Text("%s", fmt::format("{}", npr(first, second)).c_str());

        input_double("C##foo3", &first, "%.5f", false);
        input_double("=##foo4", &second, "%.5f", true);
        ImGui::SameLine();
        ImGui::Text("%s", fmt::format("{}", ncr(first, second)).c_str());

        ImGui::Text("X ~ B(");
        input_double(", ##foo5", &first, "%.5f", true);
        input_double(")##foo6", &second, "%.5f", true);
        ImGui::SameLine();
        ImGui::Text("P(X =");
        input_double(") =##foo7", &third, "%.5f", true);
        ImGui::SameLine();
        ImGui::Text("%s", fmt::format("{}", bin_dist(third, first, second)).c_str());

        break;
    }
}
