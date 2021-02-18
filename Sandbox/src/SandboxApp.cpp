#include <Main.hpp>
#include <SFML_MasterX.hpp>
#if defined(MASTER_MACOSX)
    #define TITLE "SFML MACOSX"
#else
    #define TITLE "Hello SFML"
#endif

class SandBoxApp : public masterX::Application
{
public:
    SandBoxApp()
    {
        m_window = new sf::RenderWindow(sf::VideoMode(1024, 900), TITLE);
    }

};

masterX::Application* masterX::createApplication()
{
    return new SandBoxApp;
}