#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "WindowHolder.hpp"

namespace masterX
{
    WindowHolder::WindowHolder(const WindowProps& props) : m_window(nullptr)
    {
        m_window = new sf::RenderWindow(sf::VideoMode(props.width, props.height), 
                    props.title, props.style, props.settings);

        m_window->setFramerateLimit(props.frameRate);
    }
    WindowHolder::WindowHolder(sf::WindowHandle handle, const sf::ContextSettings& settings)
    : m_window(nullptr)
    {
        m_window = new sf::RenderWindow(handle, settings);
    }

    sf::RenderWindow& WindowHolder::get()
    {
        return *m_window;
    }
}