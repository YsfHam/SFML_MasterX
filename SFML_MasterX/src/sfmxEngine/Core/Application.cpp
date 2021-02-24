#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif
#include "Application.hpp"

#include "Base.hpp"


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
        return m_window->get().getSize().x;
    }

    uint32_t Application::windowHeight() const
    {
        return m_window->get().getSize().y;
    }

    void Application::run()
    {
        MASTER_CORE_ASSERT(!m_window, "The application is already initialised !");
        initProps(m_winProps);
        m_window = std::make_shared<WindowHolder>(m_winProps);

        MASTER_CORE_ASSERT(m_window, "The window is not initialised");
        Renderer::init(m_window);

        init();
        
        sf::Clock clock;
        while (m_window->get().isOpen())
        {
            onEvent();
            m_deltaTime = clock.restart().asSeconds();
            onUpdate();
            Renderer::display();
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

        while (m_window->get().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                onCloseEvent();

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

    void Application::onCloseEvent()
    {
        m_window->get().close();
    }
}