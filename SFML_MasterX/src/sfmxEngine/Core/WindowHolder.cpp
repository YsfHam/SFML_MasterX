#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "WindowHolder.hpp"

namespace masterX
{
    WindowHolder::WindowHolder(const WindowProps& props) : m_window(nullptr)
    {
        m_window = createRef<sf::RenderWindow>(sf::VideoMode(props.width, props.height),
            props.title, props.style, props.settings);

        m_window->setFramerateLimit(props.frameRate);

        onCloseEvent = [](){
            return true;
        };
    }
    WindowHolder::WindowHolder(sf::WindowHandle handle, const sf::ContextSettings& settings)
    : m_window(nullptr)
    {
        m_window = createRef<sf::RenderWindow>(handle, settings);

        onCloseEvent = [](){
            return true;
        };
    }

    Ref<sf::RenderTarget> WindowHolder::getRenderTarget()
    {
        return m_window;
    }

    bool WindowHolder::pollWindowEvents(sf::Event& event)
    {
        return m_window->pollEvent(event);
    }

    void WindowHolder::close()
    {
        if (onCloseEvent())
            m_window->close();
    }

    bool WindowHolder::isOpen()
    {
        return m_window->isOpen();
    }
}