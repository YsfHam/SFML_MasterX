#include <sfmxEngine/Core/Main.hpp>
#include <SFML_MasterX.hpp>


class TestLayer : public masterX::Layer
{
public:
    void onAttach() override
    {
        MASTER_INFO("TestLayer starts {0}", ++s_counter);
        instanceNum = s_counter;
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
private:
    static int s_counter;
    int instanceNum;
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