#include <sfmxEngine/Core/Main.hpp>
#include <SFML_MasterX.hpp>


class TestLayer : public masterX::Layer
{
public:
    TestLayer()
        : m_cameraControler(0.5f, 150.f, 30.f)
    {
    }
    void onAttach() override
    {
        m_rect.setFillColor(sf::Color::Red);
        m_rect.setSize(sf::Vector2f(20.f, 20.f));
        m_rect.setOrigin(m_rect.getSize() / 2.f);

        float winWidth = masterX::Application::get()->windowWidth();
        float winHeight = masterX::Application::get()->windowHeight();
        m_rect.setPosition(m_rect.getSize());

        m_cameraControler.useLetterBoxing = true;
        m_cameraControler.changeSize();
    }

    void onDetach() override
    {
    }

    bool onEvent(sf::Event& event) override
    {
        bool eventHandled = false;
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::F)
            {
                masterX::Application::get()->fullScreenMode();
                m_cameraControler.changeSize();
                eventHandled |= true;
            }
            else if (event.key.code == sf::Keyboard::N)
            {
                masterX::Application::get()->fullScreenMode(false);
                m_cameraControler.changeSize();
                eventHandled |= true;
            }
            eventHandled |= false;
        }

        eventHandled |= m_cameraControler.onEvent(event);
        
        return eventHandled;
    }

    void onUpdate(float dt) override
    {
        m_cameraControler.update(dt);

        masterX::Renderer::setClearColor(sf::Color(20, 20, 20));
        masterX::Renderer::begin();
        masterX::Renderer::setCamera((masterX::Camera*)&m_cameraControler.getCamera());
        //masterX::Renderer::draw(m_rect);
        sf::CircleShape circle(5);
        for (int y = 0; y < 50; y++)
        {
            for (int x = 0; x < 50; x++)
            {
                circle.setPosition(x * 10, y * 10);
                circle.setFillColor(x & y ? sf::Color::Blue : sf::Color::Green);
                masterX::Renderer::draw(circle);
            }
        }
        masterX::Renderer::end<sf::RenderWindow>();

    }

private:
    sf::RectangleShape m_rect;
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
        props.minWidth = 200;
        props.minHeight = 50;
        props.fullScreen = false;

    }
};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}