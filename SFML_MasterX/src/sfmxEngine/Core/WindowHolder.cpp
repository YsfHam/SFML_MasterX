#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "WindowHolder.hpp"

namespace masterX
{
    WindowHolder::WindowHolder(const WindowProps& props) 
        : 
        m_window(nullptr), m_isFullScreen(false), m_props(props)
    {
        if (props.fullScreen)
        {
            m_window = createRef<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), props.title,
                                sf::Style::Fullscreen | sf::Style::Close, props.settings);
            
            m_isFullScreen = true;
        }
        else
        {
            m_window = createRef<sf::RenderWindow>(sf::VideoMode(props.width, props.height), 
            props.title, props.style, props.settings);

             auto winPos = m_window->getPosition();
            if (props.position.x)
            winPos.x = props.position.x;

            if (props.position.y)
            winPos.y = props.position.y;

            m_window->setPosition(winPos);
        }

        setSettings();

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

    void WindowHolder::setSize(uint32_t width, uint32_t height)
    {
        auto currentSize = m_window->getSize();

        if (width)
            currentSize.x = width;
        if (height)
            currentSize.y = height;

        m_window->setSize(currentSize);
    }

    void WindowHolder::setFullScreenMode()
    {
        if (m_isFullScreen)
            return;

        // track current size and position
        m_props.position = m_window->getPosition();
        m_props.width = m_window->getSize().x;
        m_props.height = m_window->getSize().y;

        m_window->create(sf::VideoMode::getDesktopMode(), m_props.title, 
        sf::Style::Fullscreen | sf::Style::Close);
        m_isFullScreen = true;

        setSettings();
    }

    void WindowHolder::setWindowedMode()
    {
        if (!m_isFullScreen)
            return;
        m_window->create(sf::VideoMode(m_props.width, m_props.height), 
            m_props.title, m_props.style, m_props.settings);
        setSettings();

        m_isFullScreen = false;

        m_window->setPosition(m_props.position);
        m_window->setSize({ m_props.width, m_props.height });
    }

    void WindowHolder::resizeEvent()
    {
        uint32_t width = getWidth();
        uint32_t height = getHeight();
        if (width < m_props.minWidth)
            width = m_props.minWidth;
        else if (width > m_props.maxWidth)
            width = m_props.maxWidth;

        if (height < m_props.minHeight)
            height = m_props.minHeight;
        else if (height > m_props.maxHeight)
            height = m_props.maxHeight;

        setSize(width, height);
    }
    void WindowHolder::setSettings()
    {
        m_window->setFramerateLimit(m_props.frameRate);
        m_window->setVerticalSyncEnabled(m_props.vsync);
    }
}