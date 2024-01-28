#include "graphics.h"
#include "config.h"
#include "app.h"
void update(float ms)
{
    App* _app = reinterpret_cast<App *>(graphics::getUserData());
    _app->update();
}

void draw()
{
    App* _app = reinterpret_cast<App*>(graphics::getUserData());
    _app->draw();
}

int main()
{
    App app;
    graphics::createWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "App");

    graphics::setUserData(&app);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    app.init();
    graphics::startMessageLoop();
    graphics::destroyWindow();
    return 0;
}