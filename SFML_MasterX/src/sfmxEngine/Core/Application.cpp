#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif
#include "Application.hpp"

#include "Asserts.hpp"


namespace masterX
{
    Application *Application::s_instance = nullptr;


    Application::Application()
        : m_window(nullptr), m_deltaTime(0.0f)
    {
        MASTER_CORE_ASSERT(s_instance == nullptr, "The application is already lanched");
        s_instance = this;
    }
    Application::~Application()
    {
    }

    Application* Application::get() 
    {
        MASTER_CORE_ASSERT(s_instance != nullptr, "The application is not initialised yet");
        return s_instance; 
    }

    uint32_t Application::windowWidth() const
    {
        return m_window->getWidth();
    }

    uint32_t Application::windowHeight() const
    {
        return m_window->getHeight();
    }

    void Application::fullScreenMode(bool fullScreen)
    {
        if (fullScreen && !isFullScreenMode())
            m_window->setFullScreenMode();
        else if (m_window->isFullScreen() && !fullScreen)
            m_window->setWindowedMode();
    }

    void Application::run()
    {
        initAppSettings();

        sf::Clock clock;
        while (m_window->isOpen())
        {
            onEvent();
            m_deltaTime = clock.restart().asSeconds();
            onUpdate();
        }
    }

    void Application::pushLayer(Layer *layer)
    {
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::onEvent()
    {
        sf::Event event;

        while (m_window->pollWindowEvents(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                m_window->close();
            
            else if (event.type == sf::Event::Resized)
            {
                m_window->resizeEvent();

                event.size.width = windowWidth();
                event.size.height = windowHeight();
            }

            for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); it++)
            {
                if ((*it)->onEvent(event))
                    break;
            }
        }
    }

    void Application::onUpdate()
    {
        for (Layer *layer : m_layerStack)
            layer->onUpdate(m_deltaTime);
    }

    void Application::initAppSettings()
    {
        MASTER_CORE_ASSERT(!m_window, "The application is already initialised !");
        WindowProps props;
        initProps(props);
        m_window = createRef<WindowHolder>(props);

        MASTER_CORE_ASSERT(m_window, "The window is not initialised");
        Renderer::init(m_window->getRenderTarget());

        init();
    }

    void Application::shutdown()
    {
        m_window->onCloseEvent = [](){
            return true;
        };

        m_window->close();
    }
}