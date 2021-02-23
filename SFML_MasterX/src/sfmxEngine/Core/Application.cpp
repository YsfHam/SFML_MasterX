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
        WindowProps props;
        initWindowProps(props);
        m_window = std::make_shared<WindowHolder>(props);

        MASTER_CORE_ASSERT(m_window, "The window is not initialised");

        Renderer::init(m_window);
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
                m_window->get().close();

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
}