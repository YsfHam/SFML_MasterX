#pragma once
#include <PCH/sfmxpch.hpp>

namespace masterX
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        static Application* get() { return instance; }
    protected:
        sf::RenderWindow *m_window;
    private:
        static Application *instance;
    };

    Application* createApplication();
}