#pragma once
#include <PCH/sfmxpch.hpp>

#include "WindowHolder.hpp"
#include "Base.hpp"

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
        virtual void initWindowProps(WindowProps& props) = 0;
    private:
        Ref<WindowHolder> m_window;
        static Application *instance;
    };

    Application* createApplication();
}