
# SFML_MasterX

A 2D game engine created with **SFML**

## Used libraries

* [SFML](https://www.sfml-dev.org/)[-Github repo](https://github.com/SFML/SFML) : 2D multimedia library. Version 2.5.1

* [Spdlog(Github)](https://github.com/gabime/spdlog) : Logging library

## Clone and build

To clone the project with git type : `git https://github.com/YsfHam/SFML_MasterX.git --recursive`.
The premake file can generate projects for mac, windows and linux.

**Note** : You must have [*premake5*](https://premake.github.io/) to generate the project

* **Build on mac(without xcode)**

If you have not install SFML in your mac run `./scripts/sfml_build` first,
then `premake5 gmake2`. Et voilà your project is generated.
Finally run the script `./scripts/build && ./scripts/run` to launch the executable.

* **Build on windows**

Not tested yet.

* **Build on linux**

Not tested yet

Feel free to try building the project on any other platform.

## Minimal code to run

In order to create a new application with this api you should create an application object.
The code below shows how to create the application

```C++
#include <sfmxEngine/Core/Main.hpp> // this contains the main function, you don't need to write it yourself
#include <SFML_MasterX.hpp>

class App : public masterX::Application
{
    // Here goes the app init code (must be implemented)
    void init()
    {

    }

    // And here you specify the window properties using 'WinProps' struct (must be implemented)
    void initProps(masterX::WinProps& props)
    {

    }
};

// This function is used internally to create Application object
masterX::Application* masterX::createApplication()
{
    return new App;
}
```

Compile and run this code to see your first app window created

## Using Layers

The application is divided into layers logically, each layer handles it's own logic and events.
The application contains references for its layers and handles events propagation.

In order to handle the app's events and update the logic you must create a class wich inherits the class `Layer`

Example

```C++
class MyLayer : public Layer
{
    // These are the layer methods to implement
    virtual void onAttach(); // called when a layer is attached to the application
    virtual void onDetach(); // called when a layer is detached from the application
    // This function handle events, returns true if a event is handled false otherwise
    virtual bool onEvent(sf::Event& event);
    virtual void onUpdate(float dt); // called once per frame
};
```

By default these methods do nothing. They are not pure virtual methods

To attach a layer to your application object you need to use the method

```C++
void pushLayer(Layer* Layer);
```

Example:

```C++
//code
class MyLayer : public Layer
{
    // class def
};
// code

class App : public masterX::Application
{
    // Here goes the app init code (must be implemented)
    void init()
    {
        pushLayer(new MyLayer);
    }

    // And here you specify the window properties using 'WinProps' struct (must be implemented)
    void initProps(masterX::WinProps& props)
    {

    }
};
```

## WindowProps structure

To override the default window properties you need to use `WinProps` structure:

```C++
struct WindowProps
{
    uint32_t width;
    uint32_t height;
    std::string title;
    uint32_t style = sf::Style::Default;
    sf::ContextSettings settings; // SFML context
    uint32_t frameRate;
    bool fullScreen;

    uint32_t minWidth;
    uint32_t minHeight;

    uint32_t maxWidth;
    uint32_t maxHeight;

    sf::Vector2<int32_t> position; // initial window posiiton

    bool vsync;
};
```

## Rendering

`Renderer` a static class, used to render drawable object the parameters are the same as sfml's `RendererTarget` class (if we can draw the object the parameters are forwarded to `draw` method in `RendererTarget` class).

Every draw call should be done between `Renderer::begin()` and `Renderer::end()` calls.

Example:

```C++
Renderer::begin();
Renderer::setCamera(camera);
// render objects
Renderer::draw(object);
Renderer::end();
```

Let's look at these methods signatures:

```C++
static void begin(const Ref<sf::RenderTarget>& target)
```

This method uses `target` to draw object. If no argument provided the default target(window) is used.

```C++
static void setCamera(Camera* camera);
```

To see something you need a pointer to a `Camera` object

```C++
template<typename Func, typename Drawable>
static void draw(Func func, Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default)```

```C++
template<typename Drawable>
static void draw(Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default)```

```C++
static void draw(sf::Vertex *vertices, size_t count, const sf::PrimitiveType& type, const sf::RenderStates& states = sf::RenderStates::Default)
```

```C++
static void draw(sf::VertexArray& vertices, const sf::RenderStates& states = sf::RenderStates::Default)
```

```C++
template<typename ...Args>
static void draw(sf::VertexBuffer buffer, Args ...args)
```

**Note**: templates are used due to some implementation details

this method has the same argument as `draw` method wich SFML uses, except if you are using your `Drawable` class you must either define `getGlobalBound` method or tell the renderer how to compute the bounds of your object. This information is used to determine if the object is visible in the screen with the current camera, if it's not visible it will be ignored for optimisation.

```C++
template<typename RenderTargetType, typename Func, typename ...Args>
static void end(Func func, Args ...args)
```

`RenderTargetType`: is the real type of the renderer's renderTarget object

`func`: is a member function to call when the renderering is finished
`Args`: are `func` arguments.

```C++
template<typename RenderTargetType>
static void end()
```

Equivalent to `end<RenderTargetType>(&RenderTargetType::display)`.

```C++
static void end()
```

Equivalent to `end<sf::RenderWindow>`. `RenderWindow` is the default target type.

## What's next

dear imgui intergration.
