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
        bool fullScreen = false;

        uint32_t minWidth = 0;
        uint32_t minHeight = 0;

        uint32_t maxWidth = -1;
        uint32_t maxHeight = -1;
    };

    class WindowHolder
    {
    public:
        WindowHolder(const WindowProps& props);

        Ref<sf::RenderTarget> getRenderTarget();
        bool pollWindowEvents(sf::Event& event);
        void close();
        bool isOpen();

        void create();

        uint32_t getWidth() const { return m_window->getSize().x; }
        uint32_t getHeight() const { return m_window->getSize().y; }

        void setSize(uint32_t width, uint32_t height);

        void setFullScreenMode();
        void setWindowedMode();

        bool isFullScreen() const { return m_isFullScreen; }

        void resizeEvent();

    public:
        std::function<bool()> onCloseEvent;

    private:
        Ref<sf::RenderWindow> m_window;
        bool m_isFullScreen;
        WindowProps m_props;
    };
}