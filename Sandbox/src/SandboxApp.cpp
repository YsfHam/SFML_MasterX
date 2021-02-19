#include <Main.hpp>
#include <SFML_MasterX.hpp>


class SandBoxApp : public masterX::Application
{
public:
    SandBoxApp()
    {
    }

    void initWindowProps(masterX::WindowProps& props) override
    {
        props.width = 800;
        props.height = 700;
        props.title = "Hello SFML";
    }

};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}