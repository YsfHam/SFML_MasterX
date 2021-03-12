#ifdef MASTER_VS_COMPILER
#include <PCH/sfmxpch.hpp>
#endif

#include "LayerStack.hpp"
#include "Asserts.hpp"

namespace masterX
{
    LayerStack::LayerStack() : m_insertPos(0)
    {}

    LayerStack::~LayerStack()
    {
        for (Layer *layer : m_layerStack)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer *layer)
    {
        m_layerStack.emplace(m_layerStack.begin() + m_insertPos, layer);
        m_insertPos++;
    }

    void LayerStack::popLayer()
    {
        MASTER_CORE_ASSERT(m_insertPos, "Empty layer stack");
        Layer *topLayer = m_layerStack.at(m_insertPos - 1);
        topLayer->onDetach();
        delete topLayer;
        m_insertPos--;
    }

    void LayerStack::eraseLayer(Layer *layer)
    {
        auto it = std::find(m_layerStack.begin(), m_layerStack.begin() + m_insertPos, layer);

        if (it != m_layerStack.begin() + m_insertPos)
        {
            (*it)->onDetach();
            delete (*it);
            m_layerStack.erase(it);
            m_insertPos--;
        }
    }
}