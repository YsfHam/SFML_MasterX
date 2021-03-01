#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "Renderer.hpp"

namespace masterX
{
    sf::Color Renderer::s_clearColor = sf::Color::Black;
    Ref<sf::RenderTarget> Renderer::s_renderTarget = nullptr;
    Ref<sf::RenderTarget> Renderer::s_defaultRenderTarget = nullptr;
    bool Renderer::s_isCleared = false;
    Camera *Renderer::s_currentCamera = nullptr;

    void Renderer::init(const Ref<sf::RenderTarget>& target)
    {
        MASTER_CORE_ASSERT(!s_defaultRenderTarget, "The renderer is already initialised !");
        s_defaultRenderTarget = target;
    }

    void Renderer::setClearColor(const sf::Color& color)
    {
        s_clearColor = color;
    }

    void Renderer::begin()
    {
        begin(s_defaultRenderTarget);
    }

    void Renderer::begin(const Ref<sf::RenderTarget>& target)
    {
        MASTER_CORE_ASSERT(!s_renderTarget, "The target is already setup");

        s_renderTarget = target;
        s_renderTarget->setView(sf::View(sf::FloatRect(0, 0, 0, 0)));
    }

    void Renderer::setCamera(Camera* camera)
    {
        s_currentCamera = camera;
        s_renderTarget->setView(s_currentCamera->getView());
    }
}