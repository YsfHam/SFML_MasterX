#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif
#include "Application.hpp"

#include "Base.hpp"


namespace masterX
{
    Application *Application::s_instance = nullptr;


    Application::Application()
        : m_window(nullptr)
    {
        MASTER_CORE_ASSERT(s_instance == nullptr, "The application is already lanched");
        s_instance = this;
        
    }
    Application::~Application()
    {
    }

    void Application::run()
    {
        WindowProps props;
        initWindowProps(props);
        m_window = std::make_shared<WindowHolder>(props);

        MASTER_CORE_ASSERT(m_window, "The window is not initialised");

        while (m_window->get().isOpen())
        {
            onEvent();
            onUpdate();
            m_window->get().clear(sf::Color(200, 50, 50));
            m_window->get().display();
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
            layer->onUpdate();
    }
}