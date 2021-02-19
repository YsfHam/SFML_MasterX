#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif
#include "Core/Application.hpp"

#include "Base.hpp"


namespace masterX
{
    Application *Application::instance = nullptr;


    Application::Application()
        : m_window(nullptr)
    {
        MASTER_CORE_ASSERT(instance == nullptr, "The application is already lanched");
        instance = this;
        
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
            sf::Event event;
            while (m_window->get().pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->get().close();
            }

            m_window->get().clear(sf::Color(200, 50, 50));
            m_window->get().display();
        }
    }
}