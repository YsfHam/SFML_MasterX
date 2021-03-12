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
        m_cameraControler.useLetterBoxingEffect();

        masterX::Application::get()->setOnCloseEvent([](){
            MASTER_WARN("You are trying to quit the app");
            return false;
        });

        sf::Vector2<uint32_t> count(10, 10);
        sf::Vector2f startPos(0, 0);
        sf::CircleShape circle(5);
        sf::Vector2f dist(10, 10);
        for (uint32_t y = 0; y < count.y; y++)
        {
            for (uint32_t x = 0; x < count.x; x++)
            {
                circle.setFillColor(x & y ? sf::Color::Green : sf::Color::Blue);
                circle.setPosition(sf::Vector2f(x * dist.x, y * dist.y) + startPos);

                m_circles.emplace_back(circle);
            }
        }
    }

    void onDetach() override
    {
    }

    bool onEvent(sf::Event& event) override
    {
        bool eventHandled = false;
        if (event.type == sf::Event::Closed)
        {
            masterX::Application::get()->shutdown();
            eventHandled |= true;
        }
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
        float framerate = 1.f / dt;
        if (framerate > 30.f)
            MASTER_INFO("Good frame rate {0}", framerate);
        else if (framerate <= 30.f && framerate > 10.f)
            MASTER_WARN("Bad frame rate {0}", framerate);
        else
            MASTER_ERROR("You cannot play with this, can you? {0}", framerate);
        masterX::Renderer::begin();
        masterX::Renderer::setCamera((masterX::Camera*)&m_cameraControler.getCamera());
        for (sf::CircleShape& circle : m_circles)
        {
            masterX::Renderer::draw(circle);              
        }
        masterX::Renderer::end();

    }

private:
    masterX::CameraControler m_cameraControler;

    std::vector<sf::CircleShape> m_circles;
};

class SandBoxApp : public masterX::Application
{
private:
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
        props.frameRate = 120;
        props.vsync = false;

    }
};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}