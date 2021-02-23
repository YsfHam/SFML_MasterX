#pragma once
#include <PCH/sfmxpch.hpp>

#include "WindowHolder.hpp"
#include "Base.hpp"
#include "LayerStack.hpp"
#include "sfmxEngine/Renderer/Renderer.hpp"

namespace masterX
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        uint32_t windowWidth() const;
        uint32_t windowHeight() const;
        
        static Application* get() { return s_instance; }

    protected:
        virtual void initWindowProps(WindowProps& props) = 0;
        void pushLayer(Layer *layer);

    private:
        void onEvent();
        void onUpdate();

    private:
        Ref<WindowHolder> m_window;
        LayerStack m_layerStack;
        float m_deltaTime;
        static Application *s_instance;
    };

    Application* createApplication();
}