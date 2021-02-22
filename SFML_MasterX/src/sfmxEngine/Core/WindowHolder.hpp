#pragma once

#include <PCH/sfmxpch.hpp>

namespace masterX
{

    struct WindowProps
    {
        uint32_t width;
        uint32_t height;
        std::string title;
        uint32_t style = sf::Style::Default;
        sf::ContextSettings settings;
    };

    class WindowHolder
    {
    public:
        WindowHolder(const WindowProps& props);
        WindowHolder(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());

        ~WindowHolder() { delete m_window; }

        sf::RenderWindow& get();
    private:
        sf::RenderWindow *m_window;
    };
}