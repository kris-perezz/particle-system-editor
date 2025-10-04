#include <src/Layers/LayerList.h>

#include <algorithm>

namespace SOUP {

  LayerList::~LayerList() {
    for (auto &l : m_layers) {
      if (l)
        l->onDetach();
    }
    m_layers.clear();
  }

  void LayerList::PushLayer(Layer *layer) { PushLayer(std::unique_ptr<Layer>(layer)); }

  void LayerList::PushOverlay(Layer *overlay) { PushOverlay(std::unique_ptr<Layer>(overlay)); }

  void LayerList::PushLayer(std::unique_ptr<Layer> layer) {
    const int priority = layer->getPriority();

    auto start = m_layers.begin();
    auto end   = m_layers.begin() + m_layerInsertIndex;

    auto position =
        std::upper_bound(start, end, priority, [](int i, const std::unique_ptr<Layer> &l) {
          return i < l->getPriority();
        });
    m_layers.insert(position, std::move(layer));
    m_layerInsertIndex++;
  }

  void LayerList::PushOverlay(std::unique_ptr<Layer> overlay) {
    m_layers.emplace_back(std::move(overlay));
  }

  void LayerList::PopLayer(Layer *layer) {
    if (!layer)
      return;

    auto start = m_layers.begin();
    auto end   = m_layers.begin() + m_layerInsertIndex;

    auto it = std::find_if(start, end, [layer](const std::unique_ptr<Layer> &l) {
      return l.get() == layer;
    });

    if (it != m_layers.begin() + m_layerInsertIndex) {
      m_layers.erase(it);
      m_layerInsertIndex--;
    }
  }

  void LayerList::PopOverlay(Layer *overlay) {
    if (!overlay)
      return;

    auto start = m_layers.begin() + m_layerInsertIndex;
    auto end   = m_layers.end();

    auto it = std::find_if(start, end, [overlay](const std::unique_ptr<Layer> &l) {
      return l.get() == overlay;
    });

    if (it != m_layers.end()) {
      m_layers.erase(it);
    }
  }

  std::size_t LayerList::size() const noexcept { return m_layers.size(); }

  Layer *LayerList::operator[](std::size_t i) noexcept { return m_layers[i].get(); }

  Layer *LayerList::operator[](std::size_t i) const noexcept { return m_layers[i].get(); }

} // namespace SOUP