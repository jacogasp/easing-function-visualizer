//
// Created by Jacopo Gasparetto on 23/09/22.
//
#include "EasingFunctionVisualizer.hpp"

static PlotData<100> plot_data;

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

static void statusBar() {
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    float height = ImGui::GetFrameHeight();

    if (ImGui::BeginViewportSideBar("##MainStatusBar", viewport, ImGuiDir_Down, height, window_flags)) {
        if (ImGui::BeginMenuBar()) {
            ImGui::Text(
                    "Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }
}

void drawDockspace() {
    // If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
    // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
    // In this specific demo, we are not using DockSpaceOverViewport() because:
    // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
    // - we allow the host window to have padding (when opt_padding == true)
    // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
    // TL;DR; this demo is more complicated than what you would normally use.
    // If we removed all the options we are showcasing, this demo would become:
    //     void ShowExampleAppDockSpace()
    //     {
    //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //     }

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    } else {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    static bool p_open = true;
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Options")) {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", nullptr, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            if (ImGui::MenuItem("Close", nullptr, false, p_open))
                // &p_open = false;
                ImGui::EndMenu();
        }
        HelpMarker(
                "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!\n"
                "- Drag from window title bar or their tab to dock/undock.\n"
                "- Drag from window menu button (upper-left button) to undock an entire node (all windows).\n"
                "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)\n"
                "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)\n"
                "This demo app has nothing to do with enabling docking!\n\n"
                "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window.\n\n"
                "Read comments in ShowExampleAppDockSpace() for more details.");

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void EasingFunctionVisualizer::drawEasingPrimitives() {
    static float f = 0.0f;
    ImGui::Begin("Primitives");
    if (ImGui::BeginTabBar("##Tabs"), ImGuiTabBarFlags_DockNode) {
        if (ImGui::BeginTabItem("SmoothStart/Stop")) {
            if (ImPlot::BeginPlot("SmoothStart")) {
                ImPlot::PlotLine("SmoothStart2", m_smoothStart2.x.data(), m_smoothStart2.y.data(), m_smoothStart2.size);
                ImPlot::PlotLine("SmoothStart3", m_smoothStart3.x.data(), m_smoothStart3.y.data(), m_smoothStart3.size);
                ImPlot::PlotLine("SmoothStart4", m_smoothStart4.x.data(), m_smoothStart4.y.data(), m_smoothStart4.size);
                ImPlot::PlotLine("SmoothStart5", m_smoothStart5.x.data(), m_smoothStart5.y.data(), m_smoothStart5.size);
                ImPlot::PlotLine("SmoothStart6", m_smoothStart6.x.data(), m_smoothStart6.y.data(), m_smoothStart6.size);

                ImPlot::PlotLine("SmoothStop2", m_smoothStop2.x.data(), m_smoothStop2.y.data(), m_smoothStop2.size);
                ImPlot::PlotLine("SmoothStop3", m_smoothStop3.x.data(), m_smoothStop3.y.data(), m_smoothStop3.size);
                ImPlot::PlotLine("SmoothStop4", m_smoothStop4.x.data(), m_smoothStop4.y.data(), m_smoothStop4.size);
                ImPlot::PlotLine("SmoothStop5", m_smoothStop5.x.data(), m_smoothStop5.y.data(), m_smoothStop5.size);
                ImPlot::PlotLine("SmoothStop6", m_smoothStop6.x.data(), m_smoothStop6.y.data(), m_smoothStop6.size);
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("SmoothStep")) {
            ImGui::SliderFloat("Mix", &f, 0.0f, 1.0f);
            if (ImPlot::BeginPlot("Test")) {
                ImPlot::PlotLine("SmoothStep2", m_smoothStep2.x.data(), m_smoothStep2.y.data(), m_smoothStep2.size);
                ImPlot::PlotLine("SmoothStep3", m_smoothStep3.x.data(), m_smoothStep3.y.data(), m_smoothStep3.size);
                ImPlot::PlotLine("SmoothStep4", m_smoothStep4.x.data(), m_smoothStep4.y.data(), m_smoothStep4.size);
                ImPlot::PlotLine("SmoothStep5", m_smoothStep5.x.data(), m_smoothStep5.y.data(), m_smoothStep5.size);
                ImPlot::PlotLine("SmoothStep6", m_smoothStep6.x.data(), m_smoothStep6.y.data(), m_smoothStep6.size);

                for (size_t i = 0; i < size; ++i) {
                    plot_data.x.at(i) = (float) i / size;
                    plot_data.y.at(i) = CoreGame::crossfade(m_smoothStart2.y.at(i), m_smoothStop2.y.at(i), f);
                }
                ImPlot::PlotLine("SmoothStep", plot_data.x.data(), plot_data.y.data(), size);
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Arch")) {
            if (ImPlot::BeginPlot("Arch")) {
                ImPlot::PlotLine("Arch2", arch2.x.data(), arch2.y.data(), size);
                ImPlot::PlotLine("smoothStartArch3", smoothStartArch3.x.data(), smoothStartArch3.y.data(), size);
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}


void EasingFunctionVisualizer::Update() {
    drawDockspace();
    drawEasingPrimitives();
    statusBar();
}
