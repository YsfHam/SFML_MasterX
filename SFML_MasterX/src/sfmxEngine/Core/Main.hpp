#pragma once
#include "sfmxEngine/Core/Application.hpp"
#include "sfmxEngine/Core/Asserts.hpp"

extern masterX::Application* masterX::createApplication();

int main()
{
    masterX::Log::init();
    MASTER_CORE_INFO("App starting ...");
    masterX::Application *app = masterX::createApplication();
    MASTER_CORE_ASSERT(app, "The application does not start correctly (app == null)!!");
    MASTER_CORE_INFO("App started correctly");
    MASTER_CORE_INFO("App running...");
    app->run();
    delete app;
    MASTER_CORE_INFO("App terminated correctly");
    return 0;
}