#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "CameraControler.hpp"
#include "sfmxEngine/Core/Log.hpp"
#include "sfmxEngine/Core/Application.hpp"

namespace masterX
{
    CameraControler::CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed)
        : m_zoomAmount(zoomAmount), 
        m_cameraSpeed(cameraSpeed),
        m_rotationSpeed(rotationSpeed)
    {}

    CameraControler::CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
    const sf::FloatRect& cameraViewPort)
        : m_camera(cameraViewPort), 
        m_zoomAmount(zoomAmount), 
        m_cameraSpeed(cameraSpeed),
        m_rotationSpeed(rotationSpeed)
    {}

    CameraControler::CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
                        const sf::Vector2f& targetSize)
        : m_zoomAmount(zoomAmount), 
        m_cameraSpeed(cameraSpeed),
        m_rotationSpeed(rotationSpeed),
        m_camera(targetSize)
    {}

    CameraControler::CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
        const sf::FloatRect& cameraViewPort, const sf::Vector2f& targetSize)
        : m_camera(cameraViewPort, targetSize), 
        m_zoomAmount(zoomAmount), 
        m_cameraSpeed(cameraSpeed),
        m_rotationSpeed(rotationSpeed)
    {}

    void CameraControler::changeCameraViewPort(const sf::FloatRect& newcameraViewPort)
    {
        m_camera.changeViewPort(newcameraViewPort);
    }

    void CameraControler::changeCameraViewPort(const sf::FloatRect& newcameraViewPort, const sf::Vector2f& targetSize)
    {
        m_camera.changeViewPort(newcameraViewPort, targetSize);
    }

    const sf::View& CameraControler::getCameraView()
    {
        return m_camera.getView();
    }

    void CameraControler::focusOn(const sf::Vector2f& target)
    {
        m_camera.focusOn(target);
    }

    bool CameraControler::onEvent(sf::Event& event)
    {
        if (event.type == sf::Event::Resized)
        {
            changeSize(event.size.width, event.size.height);
            return true;
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0)
                    m_camera.zoom(m_zoomAmount);
                else
                    m_camera.zoom(1.f / m_zoomAmount);

                return true;
            }
            return false;
        }

        return false;
    }

    void CameraControler::update(float dt)
    {
        float offset = m_cameraSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            m_camera.move({0, -offset});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            m_camera.move({0, offset});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            m_camera.move({-offset, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_camera.move({offset, 0});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            m_camera.rotate(-m_rotationSpeed * dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            m_camera.rotate(m_rotationSpeed * dt);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            m_camera.zoom(m_zoomAmount);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_camera.zoom(1.f / m_zoomAmount);
    }

    void CameraControler::changeSize()
    {
        changeSize(Application::get()->windowWidth(), Application::get()->windowHeight());
    }

    void CameraControler::changeSize(uint32_t width, uint32_t height)
    {
        if (!m_useLetterBoxing)
            m_camera.resize(width, height);
        else
            m_camera.letterBoxEffect(sf::Vector2f(width, height));
    }

    void CameraControler::useLetterBoxingEffect(bool use)
    {
        m_useLetterBoxing = use;
        changeSize();
    }

    void CameraControler::useLetterBoxingEffect(uint32_t width, uint32_t height, bool use)
    {
        m_useLetterBoxing = use;
        changeSize(width, height);
    }
}