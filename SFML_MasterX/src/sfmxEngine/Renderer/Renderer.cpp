#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "Renderer.hpp"

namespace masterX
{
    Ref<WindowHolder> Renderer::s_window = nullptr;
    sf::Color Renderer::s_clearColor = sf::Color::Black;

    bool Renderer::s_isCleared = false;

    void Renderer::init(const Ref<WindowHolder>& window)
    {
        MASTER_CORE_ASSERT(!s_window, "The renderer is already initialised !");
        s_window = window;

        s_window->get().setView(sf::View(sf::FloatRect(0, 0, 0, 0)));
    }

    void Renderer::setClearColor(const sf::Color& color)
    {
        s_clearColor = color;
    }

    void Renderer::display()
    {
        if (!s_isCleared)
            s_window->get().clear(s_clearColor);
        s_isCleared = false;
        s_window->get().display();
    }

    void Renderer::setDrawingView(const sf::View& view)
    {
        s_window->get().setView(view);
    }

    void Renderer::setDrawingView(const sf::FloatRect& drawingArea)
    {
        setDrawingView(sf::View(drawingArea));
    }

    void Renderer::setDrawingView(float startX, float startY, float width, float height)
    {
        setDrawingView(sf::FloatRect(startX, startY, width, height));
    }
}