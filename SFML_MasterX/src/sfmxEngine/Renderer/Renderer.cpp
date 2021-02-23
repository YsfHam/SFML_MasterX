#include "Renderer.hpp"

namespace masterX
{
    Ref<WindowHolder> Renderer::s_window = nullptr;
    sf::Color Renderer::s_clearColor = sf::Color::Black;

    bool Renderer::s_isCleared = false;

    void Renderer::init(const Ref<WindowHolder>& window)
    {
        MASTER_CORE_ASSERT(!s_window, "The renderer is already intialised !");
        s_window = window;
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
}