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

        void fullScreenMode(bool fullScreen = true);

        bool isFullScreenMode() const { return m_window->isFullScreen(); }
        
        static Application* get();

    protected:
        virtual void initProps(WindowProps& props) = 0;
        virtual void init() = 0;
        void pushLayer(Layer *layer);

    private:
        void onEvent();
        void onUpdate();

        void initAppSettings();

    private:
        Ref<WindowHolder> m_window;
        LayerStack m_layerStack;
        float m_deltaTime;
        static Application *s_instance;
    };

    // To be defined by the client
    Application* createApplication();
}