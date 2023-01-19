#include "reanimation_ui.h"

#include <corecrt_math.h>
#include <imgui.h>
#include <imgui_node_editor.h>

namespace ed = ax::NodeEditor;

void ReanimationUI::Init(bool* p_open) {
    ed::Config config;
    config.SettingsFile = "Simple.json";

    ed::EditorContext* m_Context = ed::CreateEditor(&config);
    auto& io = ImGui::GetIO();

    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate,
                io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ImGui::Separator();

    ed::SetCurrentEditor(m_Context);
    ed::Begin("My Editor", ImVec2(0.0, 0.0f));
    int uniqueId = 1;
    // Start drawing nodes.
    // clang-format off
    ed::BeginNode(uniqueId++);
        ImGui::Text("Node A");
            ed::BeginPin(uniqueId++, ed::PinKind::Input);
        ImGui::Text("-> In");
            ed::EndPin();
        ImGui::SameLine();
            ed::BeginPin(uniqueId++, ed::PinKind::Output);
        ImGui::Text("Out ->");
    ed::EndPin();
    ed::EndNode();
    ed::End();
    // clang-format on

    // IM_ASSERT(
    //     ImGui::GetCurrentContext() != NULL &&
    //     "Missing dear imgui context. Refer to examples app!");    // Exceptionally add an extra assert here for people confused with initial dear imgui setup

    // ImGui::Begin("My First Tools", p_open, ImGuiWindowFlags_MenuBar);
    // if (ImGui::BeginMenuBar()) {
    //     if (ImGui::BeginMenu("File")) {
    //         if (ImGui::MenuItem("Open Project..", "Ctrl+O")) { /* Do stuff */
    //         }
    //         if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
    //         }
    //         if (ImGui::MenuItem("Close", "Ctrl+W")) {
    //             p_open = false;
    //         }
    //         ImGui::EndMenu();
    //     }
    //     ImGui::EndMenuBar();
    // }

    // static float my_color[4] = {0.4f, 0.7f, 0.0f, 0.5f};

    // // Edit a color stored as 4 floats
    // ImGui::ColorEdit4("Color", my_color);

    // // Generate samples and plot them
    // float samples[100];
    // for (int n = 0; n < 100; n++)
    //     samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    // ImGui::PlotLines("Samples", samples, 100);

    // // Display contents in a scrolling region
    // ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    // ImGui::BeginChild("Scrolling");
    // for (int n = 0; n < 50; n++)
    //     ImGui::Text("%04d: Some text", n);
    // ImGui::EndChild();
    // ImGui::End();
}