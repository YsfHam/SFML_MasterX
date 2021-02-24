#include <sfmxEngine/Core/Main.hpp>
#include <SFML_MasterX.hpp>


class TestLayer : public masterX::Layer
{
public:
    TestLayer()
        :
        m_cameraControler(0.5f, 100.f, 50.f)
    {
    }
    void onAttach() override
    {
        m_rect.setFillColor(sf::Color::Red);
        m_rect.setSize(sf::Vector2f(20.f, 20.f));
        m_rect.setOrigin(m_rect.getSize() / 2.f);

        float winWidth = masterX::Application::get()->windowWidth();
        float winHeight = masterX::Application::get()->windowHeight();
        m_rect.setPosition(winWidth / 2.f, winHeight / 2.f);

        m_currentCamera = (masterX::Camera*)&m_cameraControler.getCamera();
    }

    void onDetach() override
    {
    }

    bool onEvent(sf::Event& event) override
    {
        bool eventHandled = false;
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::C)
            {
                if (m_currentCamera == &m_camera)
                    m_currentCamera = (masterX::Camera*)&m_cameraControler.getCamera();
                else
                    m_currentCamera = &m_camera;

                eventHandled |= true;
            }
        }
        eventHandled |= m_cameraControler.onEvent(event);
        return eventHandled;
    }

    void onUpdate(float dt) override
    {
        m_cameraControler.update(dt);
        masterX::Renderer::setClearColor(sf::Color(20, 20, 20));
        masterX::Renderer::setDrawingView(m_currentCamera->getView());
        masterX::Renderer::draw(m_rect);

    }

private:
    sf::RectangleShape m_rect;
    masterX::Camera m_camera;
    masterX::Camera *m_currentCamera;
    masterX::CameraControler m_cameraControler;
};

class SandBoxApp : public masterX::Application
{
public:
    void init() override
    {
        pushLayer(new TestLayer);
    }

    void initProps(masterX::WindowProps& props) override
    {
        props.width = 700;
        props.height = 500;
        props.title = "SFML App";
    }
};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}