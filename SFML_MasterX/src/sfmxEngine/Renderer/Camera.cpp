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
        resize(newViewPort.getSize());

        float windowWidth = Application::get()->windowWidth();
        float windowHeight = Application::get()->windowHeight();

        float widthFactor = newViewPort.width / windowWidth;
        float heightFactor = newViewPort.height / windowHeight;

        float leftFactor = newViewPort.left / windowWidth;
        float topFactor = newViewPort.top / windowHeight;


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