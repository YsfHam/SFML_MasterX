#pragma once

#include "PCH/sfmxpch.hpp"

namespace masterX
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        
        virtual void onAttach() {}
        virtual void onDetach() {}
        // This function handle events, returns true if a event is handled false otherwise
        virtual bool onEvent(sf::Event& event) { return false; }
        virtual void onUpdate(float dt) {}
    private:
    };
}