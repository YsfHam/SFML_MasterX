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

        CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
                        const sf::Vector2f& targetSize);
        CameraControler(float zoomAmount, float cameraSpeed, float rotationSpeed,
        const sf::FloatRect& cameraViewPort, const sf::Vector2f& targetSize);

        void changeCameraViewPort(const sf::FloatRect& newcameraViewPort);
        void changeCameraViewPort(const sf::FloatRect& newcameraViewPort, const sf::Vector2f& targetSize);
        const sf::View& getCameraView();
        const Camera& getCamera() { return m_camera; }

        void focusOn(const sf::Vector2f& target);

        bool onEvent(sf::Event& event);
        void update(float dt);

        void changeSize();
        void changeSize(uint32_t width, uint32_t height);

        void useLetterBoxingEffect(bool use = true);
        void useLetterBoxingEffect(uint32_t width, uint32_t height, bool use = true);

    private:
        Camera m_camera;
        float m_zoomAmount;
        float m_cameraSpeed;
        float m_rotationSpeed;
        bool m_useLetterBoxing = false;
    };
}