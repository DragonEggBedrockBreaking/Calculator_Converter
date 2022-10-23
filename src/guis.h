#pragma once

#include <string>
#include "lib/implot.h"

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
                   std::string& ans1, std::string& ans2, std::string& ans3, std::string& ans4);

struct Graph {
    ImPlotRect limits;
    std::string str1, str2, str3, str4, str;

    double get_y(double& x, const std::string& str);
    void line_setup(std::string& expression, std::string& str, bool& plot, ImVec4& colour, const std::string& num);
    void draw_line(bool& plot, ImVec4& colour, const std::string& num);
    void run_graph_gui(std::string& expression1, bool& plot1, std::string& expression2, bool& plot2,
                       std::string& expression3, bool& plot3, std::string& expression4, bool& plot4,
                       ImVec4& colour1, ImVec4& colour2, ImVec4& colour3, ImVec4& colour4);
};

void run_conversion_gui(const int& selected_conversion_int, double& value, std::string& text);
