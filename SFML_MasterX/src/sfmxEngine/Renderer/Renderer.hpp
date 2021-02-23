#pragma once

#include "sfmxEngine/Core/WindowHolder.hpp"
#include "sfmxEngine/Core/Base.hpp"
#include "PCH/sfmxpch.hpp"

namespace masterX
{
    class Renderer
    {
    public:
        static void init(const Ref<WindowHolder>& window);
        static void setClearColor(const sf::Color& color);

        template<typename ...Args>
        static void draw(Args ...args)
        {
            if (!s_isCleared)
            {
                s_window->get().clear(s_clearColor);
                s_isCleared = true;
            }

            s_window->get().draw(std::forward<Args...>(args...));
        }

        static void display();

    private:
        static Ref<WindowHolder> s_window;
        static sf::Color s_clearColor;

        static bool s_isCleared;
    };
}