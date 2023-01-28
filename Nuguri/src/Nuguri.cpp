#include <Nuguri.h>

namespace Nuguri {
    static void SetupMainMenu() {
        // set up main menu
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("(demo menu)", NULL, false, false);
                if (ImGui::MenuItem("New", "Ctrl+N")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::BeginMenu("Open Recent")) {
                    ImGui::MenuItem("fish_hat.c");
                    ImGui::MenuItem("fish_hat.inl");
                    ImGui::MenuItem("fish_hat.h");
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Save As..")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Quit", "Alt+F4")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Show(bool* p_open) {
        // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
        // Most functions would normally just crash if the context is missing.
        IM_ASSERT(ImGui::GetCurrentContext() != NULL &&
                  "Missing dear imgui context. Refer to examples app!");

        SetupMainMenu();

        // Demonstrate the various window flags. Typically you would just use the default!
        static bool no_titlebar = false;
        static bool no_scrollbar = false;
        static bool no_menu = false;
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = false;
        static bool no_close = false;
        static bool no_nav = false;
        static bool no_background = false;
        static bool no_bring_to_front = false;
        static bool unsaved_document = false;

        ImGuiWindowFlags window_flags = 0;
        if (no_titlebar)
            window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)
            window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)
            window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)
            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)
            window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)
            window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)
            window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)
            window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (unsaved_document)
            window_flags |= ImGuiWindowFlags_UnsavedDocument;
        if (no_close)
            p_open = NULL;    // Don't pass our bool* to Begin

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650,
                                       main_viewport->WorkPos.y + 20),
                                ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin("Nuguri Editor", p_open, window_flags)) {
            // Early out if window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        ImGui::Text("dear imgui says hello! (%s) (%d)", IMGUI_VERSION,
                    IMGUI_VERSION_NUM);
        ImGui::Spacing();

        ImGui::End();
    }
}    // namespace Nuguri