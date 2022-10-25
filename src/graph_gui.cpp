#include <regex>

#include <imgui.h>
#include "lib/imgui_stdlib.h"

#include "guis.h"
#include "muParser.h"

template <typename T>
inline T remap(T x, T x0, T x1, T y0, T y1)
{
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

double Graph::get_y(double& x, const std::string& str)
{
    try {
        const std::string expr = std::regex_replace(str, std::regex(" "), "");
        mu::Parser p;
        p.DefineVar("x", &x);
        p.SetExpr(str);
        return p.Eval();
    }
    catch (mu::Parser::exception_type &e) {
        return NAN;
    }
}

void Graph::line_setup(std::string& expression, std::string& str, bool& plot, ImVec4& colour, const std::string& num)
{
    ImGui::InputText(("f(x)##line" + num).c_str(), &expression);
    str = expression;

    if (ImGui::Button(("Toggle Line " + num).c_str())) {
        plot = !plot;
    }

    ImGui::SameLine();
    ImGui::ColorEdit4(("##colour" + num).c_str(), &colour.x, ImGuiColorEditFlags_NoInputs);
}

void Graph::draw_line(bool& plot, ImVec4& colour, const std::string& num)
{
    if (plot) {
        ImPlot::SetNextLineStyle(colour);
        ImPlot::PlotLineG(("##item" + num).c_str(),
        [](int idx, void* data) {
            auto& self = *(Graph*)data;
            double x = remap((double)idx, 0.0, 999.0, self.limits.X.Min, self.limits.X.Max);
            double y = self.get_y(x, self.str);
            return ImPlotPoint(x, y);
        },
        this,
        1000);
    }
}

void Graph::run_graph_gui(std::string& expression1, bool& plot1, std::string& expression2, bool& plot2,
                          std::string& expression3, bool& plot3, std::string& expression4, bool& plot4,
                          ImVec4& colour1, ImVec4& colour2, ImVec4& colour3, ImVec4& colour4)
{
    line_setup(expression1, str1, plot1, colour1, "1");
    line_setup(expression2, str2, plot2, colour2, "2");
    line_setup(expression3, str3, plot3, colour3, "3");
    line_setup(expression4, str4, plot4, colour4, "4");

    if (ImPlot::BeginPlot("Graph")) {
        limits = ImPlot::GetPlotLimits();

        this->str = this->str1;
        draw_line(plot1, colour1, "1");

        this->str = this->str2;
        draw_line(plot2, colour2, "2");

        this->str = this->str3;
        draw_line(plot3, colour3, "3");

        this->str = this->str4;
        draw_line(plot4, colour4, "4");

        ImPlot::EndPlot();
    }
}
