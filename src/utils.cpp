#include <iostream>

#include <imgui.h>

#include "utils.h"

void input_double(const char* id, double* var, const char* decimals, const bool& same_line)
{
    if (same_line) {
        ImGui::SameLine();
    }

    ImGui::InputDouble(id, var, 0.0, 0.0, decimals);
}

void split(std::vector<std::string>& output, std::string string, const std::string& delimiter)
{
    size_t pos = 0;
    std::string token;

    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        output.push_back(token);
        string.erase(0, pos + delimiter.length());
    }

    output.push_back(string);
}

std::string replace(std::string string, const std::string& from, const std::string& to)
{
    size_t pos = 0;

    while((pos = string.find(from, pos)) != std::string::npos) {
        string.replace(pos, from.length(), to);
        pos += to.length();
    }

    return string;
}

std::string double_to_string(const double& input)
{
    std::string str = std::to_string(input);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);

    if (str == "-0") {
        str = "0";
    }

    return str;
}
