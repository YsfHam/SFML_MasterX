#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "Camera.hpp"
#include "sfmxEngine/Core/Application.hpp"
#include "sfmxEngine/Core/Log.hpp"

namespace masterX
{

    Camera::Camera() : m_zoomFactor(1.f)
    {
        float windowWidth = Application::get()->windowWidth();
        float windowHeight = Application::get()->windowHeight();

        changeViewPort(sf::FloatRect(0, 0, windowWidth, windowHeight));
    }

    Camera::Camera(const sf::FloatRect& cameraViewPort) : m_zoomFactor(1.f)
    {
        changeViewPort(cameraViewPort);
    }

    Camera::Camera(const sf::Vector2f& renderTargetSize) : m_zoomFactor(1.f)
    {
        changeViewPort(sf::FloatRect(0, 0, renderTargetSize.x, renderTargetSize.y), renderTargetSize);
    }

    Camera::Camera(const sf::FloatRect& cameraViewPort, const sf::Vector2f& renderTargetSize)
        : m_zoomFactor(1.f)
    {
        changeViewPort(cameraViewPort, renderTargetSize);
    }

    void Camera::resize(float width, float height)
    {
        resize(sf::Vector2f(width, height));
    }

    void Camera::resize(const sf::Vector2f& size)
    {
        m_cameraView.setSize(size);
        m_cameraView.zoom(m_zoomFactor);
    }
    void Camera::changeViewPort(const sf::FloatRect& newViewPort)
    {
        float windowWidth = Application::get()->windowWidth();
        float windowHeight = Application::get()->windowHeight();

        changeViewPort(newViewPort, {windowWidth, windowHeight});
    }

    void Camera::changeViewPort(const sf::FloatRect& newViewPort, const sf::Vector2f& renderTargetSize)
    {
        resize(newViewPort.getSize());
        focusOn(m_cameraView.getSize() / 2.f);
        m_renderTargetSize = renderTargetSize;

        float widthFactor = newViewPort.width / renderTargetSize.x;
        float heightFactor = newViewPort.height / renderTargetSize.y;

        float leftFactor = newViewPort.left / renderTargetSize.x;
        float topFactor = newViewPort.top / renderTargetSize.y;

        m_cameraView.setViewport(sf::FloatRect(leftFactor, topFactor, widthFactor, heightFactor));
    }

    void Camera::zoom(float factor)
    {
        m_zoomFactor *= factor;
        m_cameraView.zoom(factor);
    }

    void Camera::focusOn(const sf::Vector2f& position)
    {
        m_cameraView.setCenter(position);
    }

    void Camera::move(const sf::Vector2f& offset)
    {
        m_cameraView.move(offset);
    }

    void Camera::rotate(float rotation)
    {
        m_cameraView.rotate(rotation);
    }

    void Camera::letterBoxEffect(const sf::Vector2f& rendertargetSize)
    {
        auto size = sf::Vector2f(1, 1);
        auto pos = sf::Vector2f(0, 0);

        float renderTargetRatio = rendertargetSize.x / rendertargetSize.y;
        float viewRatio = (float)m_cameraView.getSize().x / (float)m_cameraView.getSize().y;

        if (renderTargetRatio >= viewRatio)
        {
            size.x = viewRatio / renderTargetRatio;
            pos.x = (1 - size.x) / 2.f;
        }
        else
        {
            size.y = renderTargetRatio / viewRatio;
            pos.y = (1 - size.y) / 2.f;
        }
        m_cameraView.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
    }
    
    const sf::View& Camera::getView()
    {
        return m_cameraView;
    }
}