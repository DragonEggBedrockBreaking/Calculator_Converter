#include <imgui.h>

#include "utils.h"

void input_double(const char* id, double* var, const char* decimals, const bool& same_line)
{
    if (same_line) {
        ImGui::SameLine();
    }

    ImGui::InputDouble(id, var, 0.0, 0.0, decimals);
}
