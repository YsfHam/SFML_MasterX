#include <sfmxEngine/Core/Main.hpp>
#include <SFML_MasterX.hpp>


class TestLayer : public masterX::Layer
{
public:
    void onAttach() override
    {
        MASTER_INFO("TestLayer starts {0}", ++s_counter);
        instanceNum = s_counter;

        m_rect.setFillColor(sf::Color::Red);
        m_rect.setSize(sf::Vector2f(20, 20));
    }

    void onDetach() override
    {
        MASTER_INFO("TestLayer detached {0}", s_counter--);
    }

    bool onEvent(sf::Event& event) override
    {
        if (event.type == sf::Event::KeyPressed)
        {
            MASTER_TRACE("The instance {0} received the event", instanceNum);

            return true;
        }
        return false;
    }

    void onUpdate(float dt) override
    {
        masterX::Renderer::setClearColor(sf::Color(20, 30, 40));
        masterX::Renderer::draw(m_rect);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            m_rect.move(0, 10 * dt);

        MASTER_TRACE("Frame rate {0}", 1.f / dt);
    }

private:
    static int s_counter;
    int instanceNum;

    sf::RectangleShape m_rect;
};

int TestLayer::s_counter = 0;

class SandBoxApp : public masterX::Application
{
public:
    SandBoxApp()
    {
        pushLayer(new TestLayer);
    }

    void initWindowProps(masterX::WindowProps& props) override
    {
        props.width = 400;
        props.height = 300;
        props.title = "Hello SFML";
    }

};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}