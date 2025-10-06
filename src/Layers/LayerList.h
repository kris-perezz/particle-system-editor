#pragma once

#include <src/Layers/Layer.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class LayerList {
  public:
    using ListOfLayers = std::vector<std::unique_ptr<Layer>>;

    LayerList() = default;
    ~LayerList();

    void PushLayer(std::unique_ptr<Layer> layer);
    void PushOverlay(std::unique_ptr<Layer> overlay);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

    void PopLayer(Layer *layer);
    void PopOverlay(Layer *overlay);

    ListOfLayers::iterator begin() { return m_layers.begin(); }
    ListOfLayers::iterator end() { return m_layers.end(); }
    ListOfLayers::reverse_iterator rbegin() { return m_layers.rbegin(); }
    ListOfLayers::reverse_iterator rend() { return m_layers.rend(); }

    ListOfLayers::const_iterator begin() const { return m_layers.begin(); }
    ListOfLayers::const_iterator end() const { return m_layers.end(); }
    ListOfLayers::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
    ListOfLayers::const_reverse_iterator rend() const { return m_layers.rend(); }

  private:
    ListOfLayers m_layers;
    size_t m_layerInsertIndex = 0;
  };
} // namespace SOUP
