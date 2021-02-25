#pragma once

#include "PCH/sfmxpch.hpp"

namespace masterX
{
    class Camera
    {
    public:
        Camera();
        Camera(const sf::FloatRect& cameraViewPort);
        Camera(const sf::Vector2f& renderTargetSize);
        Camera(const sf::FloatRect& cameraViewPort, const sf::Vector2f& renderTargetSize);

        void resize(float width, float height);
        void resize(const sf::Vector2f& size);
        void changeViewPort(const sf::FloatRect& newViewPort);
        void changeViewPort(const sf::FloatRect& newViewPort, const sf::Vector2f& renderTargetSize);
        void zoom(float factor);
        void focusOn(const sf::Vector2f& position);
        void move(const sf::Vector2f& offset);
        void rotate(float rotation);

        const sf::View& getView();
    private:
        sf::View m_cameraView;

        float m_zoomFactor;
    };
}