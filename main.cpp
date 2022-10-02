#include "EasingFunctionVisualizer.hpp"

int main() {
    KCE::AppSettings appSettings{};
    appSettings.title = "Easing Functions Visualizer";
    KCE::App<EasingFunctionVisualizer> app{appSettings};
    app.Run();
    return 0;
}