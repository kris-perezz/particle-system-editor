#pragma once

#include <src/SOUP_pch.h>

namespace SOUP {
class LayerList {
public:
  using ListOfLayers = std::vector<std::unique_ptr<Layer>>;

  LayerList() = default;
  ~LayerList() = default;

  void PushLayer(std::unique_ptr<Layer> layer);
  void PushOverlay(std::unique_ptr<Layer> overlay);
  std::unique_ptr<Layer> PopLayer(Layer *layer);
  std::unique_ptr<Layer> PopOverlay(Layer *overlay);

  ListOfLayers::iterator begin() { return m_layers.begin(); }
  ListOfLayers::iterator end() { return m_layers.end(); }
  ListOfLayers::reverse_iterator rbegin() { return m_layers.rbegin(); }
  ListOfLayers::reverse_iterator rend() { return m_layers.rend(); }

private:
  ListOfLayers m_layers; // vector of layers
  std::size_t m_layerInsertIndex = 0;
}
} // namespace SOUP
