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
        }

        m_window->setFramerateLimit(props.frameRate);

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

        auto videoMode = sf::VideoMode::getDesktopMode();
        sf::ContextSettings settings = m_window->getSettings();
        m_window->create(videoMode, m_props.title, 
        sf::Style::Fullscreen | sf::Style::Close, settings);
        m_isFullScreen = true;
    }

    void WindowHolder::setWindowedMode()
    {
        m_window->create(sf::VideoMode(m_props.width, m_props.height), 
            m_props.title, m_props.style, m_props.settings);

        m_isFullScreen = false;
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
}