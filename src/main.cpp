#include "core/application.hpp"
#include "game/scripts/baseScene.hpp"

int main() {
    Application app;

    std::unique_ptr<Scene> baseScene = std::make_unique<BaseScene>(app.getWhiteTexture());

    app.loadScene(std::move(baseScene));

    app.run();

    return 0;
}