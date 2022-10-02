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
    constexpr static PlotData<size> m_smoothStart2{makePlotData<size, CoreGame::smoothStart2<float>>()};
    constexpr static PlotData<size> m_smoothStart3{makePlotData<size, CoreGame::smoothStart3<float>>()};
    constexpr static PlotData<size> m_smoothStart4{makePlotData<size, CoreGame::smoothStart4<float>>()};
    constexpr static PlotData<size> m_smoothStop2{makePlotData<size, CoreGame::smoothStop2<float>>()};
    constexpr static PlotData<size> m_smoothStop3{makePlotData<size, CoreGame::smoothStop3<float>>()};
    constexpr static PlotData<size> m_smoothStop4{makePlotData<size, CoreGame::smoothStop4<float>>()};
    PlotData<size> m_smoothStep{};

    void drawEasingPrimitives();

public:
    void Update();
};


#endif//EASINGFUNCTIONSVISUALIZER_EASINGFUNCTIONVISUALIZER_HPP
