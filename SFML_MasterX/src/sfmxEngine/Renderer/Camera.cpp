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
        focusOn(m_cameraView.getSize() / 2.f);
    }

    Camera::Camera(const sf::FloatRect& cameraViewPort) : m_zoomFactor(1.f)
    {
        changeViewPort(cameraViewPort);
        focusOn(m_cameraView.getSize() / 2.f);
    }

    Camera::Camera(const sf::Vector2f& renderTargetSize) : m_zoomFactor(1.f)
    {
        changeViewPort(sf::FloatRect(0, 0, renderTargetSize.x, renderTargetSize.y), renderTargetSize);
        focusOn(m_cameraView.getSize() / 2.f);   
    }

    Camera::Camera(const sf::FloatRect& cameraViewPort, const sf::Vector2f& renderTargetSize)
        : m_zoomFactor(1.f)
    {
        changeViewPort(cameraViewPort, renderTargetSize);
        focusOn(m_cameraView.getSize() / 2.f);
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

    const sf::View& Camera::getView()
    {
        return m_cameraView;
    }
}