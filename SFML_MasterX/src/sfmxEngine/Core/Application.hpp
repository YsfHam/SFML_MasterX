#pragma once
#include <PCH/sfmxpch.hpp>

#include "WindowHolder.hpp"
#include "Base.hpp"
#include "LayerStack.hpp"

namespace masterX
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
        void pushLayer(Layer *layer);
        void onEvent();
        void onUpdate();
        static Application* get() { return s_instance; }
    protected:
        virtual void initWindowProps(WindowProps& props) = 0;
    private:
        Ref<WindowHolder> m_window;
        LayerStack m_layerStack;
        static Application *s_instance;
    };

    Application* createApplication();
}