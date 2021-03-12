#pragma once

#include "sfmxEngine/Core/WindowHolder.hpp"
#include "sfmxEngine/Core/Asserts.hpp"
#include "PCH/sfmxpch.hpp"
#include "Camera.hpp"

namespace masterX
{
    class Renderer
    {
    public:
        static void init(const Ref<sf::RenderTarget>& target);
        static void setClearColor(const sf::Color& color);
        static void begin();
        static void begin(const Ref<sf::RenderTarget>& target);

        template<typename Func, typename Drawable>
        static void draw(Func func, Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default)
        {
            if (!s_isCleared)
            {
                s_renderTarget->clear(s_clearColor);
                s_isCleared = true;
            }
            sf::FloatRect bound = std::bind(func, drawable)();

            auto cameraViewSize = s_currentCamera->getView().getSize();
            auto cameraViewPos = s_currentCamera->getView().getCenter() - cameraViewSize / 2.f;
            sf::FloatRect view(cameraViewPos.x, cameraViewPos.y, cameraViewSize.x, cameraViewSize.y);
            if (bound.intersects(view))
            {
                s_renderTarget->draw(drawable, states);
            }
        }

        template<typename Drawable>
        static void draw(Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default)
        {
            draw(&Drawable::getGlobalBounds, drawable, states);
        }
        
        static void draw(sf::Vertex *vertices, size_t count, const sf::PrimitiveType& type, const sf::RenderStates& states = sf::RenderStates::Default)
        {
            sf::VertexArray array;
            array.resize(count);
            array.setPrimitiveType(type);

            for (size_t i = 0; i < count; i++)
                array.append(vertices[i]);

            draw(array, states);
        }

        static void draw(sf::VertexArray& vertices, const sf::RenderStates& states = sf::RenderStates::Default)
        {
            draw(&sf::VertexArray::getBounds, vertices, states);
        }

        template<typename ...Args>
        static void draw(sf::VertexBuffer buffer, Args ...args)
        {
            if (!s_isCleared)
            {
                s_renderTarget->clear(s_clearColor);
                s_isCleared = true;
            }

            s_renderTarget->draw(buffer, args...);
        }


        template<typename RenderTargetType>
        static void end()
        {
            end<RenderTargetType>(&RenderTargetType::display);
        }

        template<typename RenderTargetType, typename Func, typename ...Args>
        static void end(Func func, Args ...args)
        {
            MASTER_CORE_ASSERT(s_renderTarget, "No render target");
            if (!s_isCleared)
                s_renderTarget->clear(s_clearColor);
            s_isCleared = false;

            std::bind(func, (RenderTargetType*)s_renderTarget.get(), args...)();

            s_renderTarget = nullptr;
            s_currentCamera = nullptr;
        }
        // default end function (for the window)
        static void end()
        {
            end<sf::RenderWindow>();
        }

        static void setCamera(Camera* camera);

    private:
        static sf::Color s_clearColor;

        static Ref<sf::RenderTarget> s_renderTarget;
        static Ref<sf::RenderTarget> s_defaultRenderTarget; 

        static Camera *s_currentCamera;
        static bool s_isCleared;
    };
}