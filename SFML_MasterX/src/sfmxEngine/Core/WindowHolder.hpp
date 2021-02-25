#pragma once

#include <PCH/sfmxpch.hpp>
#include "Base.hpp"

namespace masterX
{

    struct WindowProps
    {
        uint32_t width;
        uint32_t height;
        std::string title;
        uint32_t style = sf::Style::Default;
        sf::ContextSettings settings;
        uint32_t frameRate = 60;
    };

    class WindowHolder
    {
    public:
        WindowHolder(const WindowProps& props);
        WindowHolder(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());

        Ref<sf::RenderTarget> getRenderTarget();
        bool pollWindowEvents(sf::Event& event);
        void close();
        bool isOpen();

        uint32_t getWidth() { return m_window->getSize().x; }
        uint32_t getHeight() { return m_window->getSize().y; }

    public:
        std::function<bool()> onCloseEvent;

    private:
        Ref<sf::RenderWindow> m_window;
    };
}