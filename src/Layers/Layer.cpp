#include <src/Layers/Layer.h>

namespace SOUP {

  Layer::Layer(int priority) : m_priority(priority) {}

  int Layer::getPriority() const { return m_priority; }

} // namespace SOUP