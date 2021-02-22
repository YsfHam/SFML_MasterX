#pragma once

#include "Layer.hpp"

#include "PCH/sfmxpch.hpp"

namespace masterX
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();
        void pushLayer(Layer *layer);
        void popLayer();
        void eraseLayer(Layer *layer);

        std::vector<Layer*>::reverse_iterator rbegin() { return m_layerStack.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_layerStack.rend(); }

         std::vector<Layer*>::iterator begin() { return m_layerStack.begin(); }
        std::vector<Layer*>::iterator end() { return m_layerStack.end(); }
    private:
        std::vector<Layer*> m_layerStack;

        uint32_t m_insertPos;
    };
}