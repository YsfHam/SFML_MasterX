#pragma once

#include "sfmxEngine/Core/WindowHolder.hpp"
#include "sfmxEngine/Core/Base.hpp"
#include "PCH/sfmxpch.hpp"

namespace masterX
{
    class Renderer
    {
    public:
        static void init(const Ref<sf::RenderTarget>& target);
        static void setClearColor(const sf::Color& color);
        static void begin();
        static void begin(const Ref<sf::RenderTarget>& target);

        template<typename ...Args>
        static void draw(Args ...args)
        {
            if (!s_isCleared)
            {
                s_renderTarget->clear(s_clearColor);
                s_isCleared = true;
            }

            s_renderTarget->draw(std::forward<Args...>(args...));
        }
        template<typename RenderTargetType>
        static void end()
        {
            if (!s_isCleared)
                s_renderTarget->clear(s_clearColor);
            s_isCleared = false;
            ((RenderTargetType*)s_renderTarget.get())->display();

            s_renderTarget = nullptr;
        }

        template<typename RenderTargetType, typename Func>
        static void end(Func func)
        {
            if (!s_isCleared)
                s_renderTarget->clear(s_clearColor);
            s_isCleared = false;
            ((RenderTargetType*)s_renderTarget.get())->func();

            s_renderTarget = nullptr;
        }

        static void setDrawingView(const sf::View& view);
        static void setDrawingView(const sf::FloatRect& drawingArea);
        static void setDrawingView(float startX, float startY, float width, float height);

    private:
        static sf::Color s_clearColor;

        static Ref<sf::RenderTarget> s_renderTarget;
        static Ref<sf::RenderTarget> s_defaultRenderTarget;

        static bool s_isCleared;
    };
}