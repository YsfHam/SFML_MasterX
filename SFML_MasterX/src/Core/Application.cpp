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
        delete m_window;
    }

    void Application::run()
    {
        MASTER_CORE_ASSERT(m_window, "The window is not initialised");
        
        while (m_window->isOpen())
        {
            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }

            m_window->clear();
            m_window->display();
        }
    }
}