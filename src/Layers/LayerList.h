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

    std::size_t size() const noexcept;
    Layer *operator[](std::size_t i) noexcept;
    Layer *operator[](std::size_t i) const noexcept;

  private:
    ListOfLayers m_layers;
    size_t m_layerInsertIndex = 0;
  };
} // namespace SOUP
