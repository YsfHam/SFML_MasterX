#pragma once

#include "Camera.hpp"

namespace masterX
{
    class CameraControler
    {
    public:
        CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed);
        CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
        const sf::FloatRect& cameraViewPort);

        void changeCameraViewPort(const sf::FloatRect& newcameraViewPort);
        const sf::View& getCameraView();
        const Camera& getCamera() { return m_camera; }

        bool onEvent(sf::Event& event);
        void update(float dt);
    private:
        Camera m_camera;
        float m_zoomAmount;
        float m_cameraSpeed;
        float m_rotationSpeed;
    };
}