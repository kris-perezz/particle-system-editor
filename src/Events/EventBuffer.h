#pragma once

#include <src/SOUP_pch.h>

#include <src/Events/Event.h>
namespace SOUP {
  class EventBuffer {
  public:
    EventBuffer(std::size_t capacity)
        : m_buffer(std::unique_ptr<Event[]>(new Event[capacity])), m_maxCapacity(capacity) {}

    ~EventBuffer() = default;

    void enqueue(Event event);
    Event dequeue();

    void flush();
    bool isEmpty() const;
    bool isFull() const;

    size_t capacity() const;
    size_t size() const;

  private:
    std::unique_ptr<Event[]> m_buffer;
    size_t m_head = 0;
    size_t m_tail = 0;
    const size_t m_maxCapacity;
    bool m_full = false;
  };
} // namespace SOUP
