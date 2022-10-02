//
// Created by Jacopo Gasparetto on 23/09/22.
//
#include "EasingFunctionVisualizer.hpp"

PlotData<100> plot_data;


void EasingFunctionVisualizer::drawEasingPrimitives() {
    ImGui::Begin("Hello");
    ImPlot::BeginPlot("SmoothStart");
    ImPlot::PlotLine("SmoothStart2", m_smoothStart2.x.data(), m_smoothStart2.y.data(), m_smoothStart2.size);
    ImPlot::PlotLine("SmoothStart3", m_smoothStart3.x.data(), m_smoothStart3.y.data(), m_smoothStart3.size);
    ImPlot::PlotLine("SmoothStart4", m_smoothStart4.x.data(), m_smoothStart4.y.data(), m_smoothStart4.size);
    ImPlot::PlotLine("SmoothStop2", m_smoothStop2.x.data(), m_smoothStop2.y.data(), m_smoothStop2.size);
    ImPlot::PlotLine("SmoothStop3", m_smoothStop3.x.data(), m_smoothStop3.y.data(), m_smoothStop3.size);
    ImPlot::PlotLine("SmoothStop4", m_smoothStop4.x.data(), m_smoothStop4.y.data(), m_smoothStop4.size);
    ImPlot::EndPlot();
    ImGui::End();
}


void EasingFunctionVisualizer::Update() {
    drawEasingPrimitives();

    ImGui::Begin("Culo");
    ImPlot::BeginPlot("Test");
    for (size_t i = 0; i < m_smoothStep.size; ++i) {
        m_smoothStep.x.at(i) = (float)i / (float)m_smoothStep.size;
        m_smoothStep.y.at(i) = CoreGame::smoothStep2(m_smoothStep.x.at(i));
    }
    ImPlot::PlotLine("SmoothStep2", m_smoothStep.x.data(), m_smoothStep.y.data(), m_smoothStep.size);
    ImPlot::EndPlot();
    ImGui::End();
}
