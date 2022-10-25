#include <imgui.h>
#include <portable-file-dialogs.h>

#include "guis.h"
#include "scripting.h"

void run_scripting_gui(std::string& inpath, std::string& outpath, std::string& message, bool& processing)
{
    if (processing) {
        if (scripting(inpath, outpath)) {
            message = "Script ran successfully!";
        }
        else {
            message = "Error processing script; check logs for errors.";
        }

        processing = false;
    }
    else {
        if (ImGui::Button("Input File:")) {
            auto selection = pfd::open_file("Select a file", ".", { "Toml Files", "*.toml", "All Files", "*" });

            while (!selection.ready());

            inpath = selection.result().at(0);
        }

        ImGui::SameLine();
        ImGui::Text("%s", inpath.c_str());

        if (ImGui::Button("Output file:")) {
            auto selection = pfd::open_file("Select a file", ".", { "Markdown Files", "*.md", "All Files", "*" });

            while (!selection.ready());

            outpath = selection.result().at(0);
        }

        ImGui::SameLine();
        ImGui::Text("%s", outpath.c_str());

        if (ImGui::Button("Process") && inpath != "" && outpath != "") {
            processing = true;
        }

        ImGui::SameLine();
        ImGui::Text("%s", message.c_str());
    }
}
