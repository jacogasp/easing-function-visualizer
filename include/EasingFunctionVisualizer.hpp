//
// Created by Jacopo Gasparetto on 23/09/22.
//

#ifndef EASINGFUNCTIONSVISUALIZER_EASINGFUNCTIONVISUALIZER_HPP
#define EASINGFUNCTIONSVISUALIZER_EASINGFUNCTIONVISUALIZER_HPP

#include "CoreMath.h"
#include "ImGuiApp.hpp"
#include <algorithm>
#include <array>
#include <functional>
#include <imgui_internal.h>

template<size_t Size>
struct PlotData {
    std::array<float, Size> x;
    std::array<float, Size> y;
    size_t size = Size;
};

template<size_t Size, float func(float)>
constexpr PlotData<Size> makePlotData() {
    PlotData<Size> data{};
    for (size_t i = 0; i < Size; ++i) {
        data.x.at(i) = (float) i / Size;
        data.y.at(i) = func((float) i / Size);
    }
    return data;
}

class EasingFunctionVisualizer {
    static constexpr size_t size = 100;

    // Smooth start
    constexpr static PlotData<size> m_smoothStart2{makePlotData<size, CoreGame::smoothStart2<float>>()};
    constexpr static PlotData<size> m_smoothStart3{makePlotData<size, CoreGame::smoothStart3<float>>()};
    constexpr static PlotData<size> m_smoothStart4{makePlotData<size, CoreGame::smoothStart4<float>>()};
    constexpr static PlotData<size> m_smoothStart5{makePlotData<size, CoreGame::smoothStart5<float>>()};
    constexpr static PlotData<size> m_smoothStart6{makePlotData<size, CoreGame::smoothStart6<float>>()};

    // Smooth stop
    constexpr static PlotData<size> m_smoothStop2{makePlotData<size, CoreGame::smoothStop2<float>>()};
    constexpr static PlotData<size> m_smoothStop3{makePlotData<size, CoreGame::smoothStop3<float>>()};
    constexpr static PlotData<size> m_smoothStop4{makePlotData<size, CoreGame::smoothStop4<float>>()};
    constexpr static PlotData<size> m_smoothStop5{makePlotData<size, CoreGame::smoothStop5<float>>()};
    constexpr static PlotData<size> m_smoothStop6{makePlotData<size, CoreGame::smoothStop6<float>>()};

    // Smooth step
    constexpr static PlotData<size> m_smoothStep2{makePlotData<size, CoreGame::smoothStep2<float>>()};
    constexpr static PlotData<size> m_smoothStep3{makePlotData<size, CoreGame::smoothStep3<float>>()};
    constexpr static PlotData<size> m_smoothStep4{makePlotData<size, CoreGame::smoothStep4<float>>()};
    constexpr static PlotData<size> m_smoothStep5{makePlotData<size, CoreGame::smoothStep5<float>>()};
    constexpr static PlotData<size> m_smoothStep6{makePlotData<size, CoreGame::smoothStep6<float>>()};

    // Archs
    constexpr static PlotData<size> arch2{makePlotData<size, CoreGame::arch2<float>>()};
    constexpr static PlotData<size> smoothStartArch3{makePlotData<size, CoreGame::smoothStartArch3<float>>()};

    static void drawEasingPrimitives();

public:
    static void Update();
};


#endif//EASINGFUNCTIONSVISUALIZER_EASINGFUNCTIONVISUALIZER_HPP
