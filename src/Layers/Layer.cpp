#include <src/Layers/Layer.h>

namespace SOUP {

Layer::Layer(const std::string &name) : m_debugName(name) {}

const std::string &Layer::GetName() { return m_debugName; }

} // namespace SOUP