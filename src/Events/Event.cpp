#include <src/Events/Event.h>

namespace SOUP {

  static Event TranslateWindowEvent(const SDL_Event &e) {
    Event event{};
    event.header.category = EventCategory::Application;

    switch (e.type) {
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        event.header.type = EventType::WindowClose;
        break;

      case SDL_EVENT_WINDOW_RESIZED:
        event.header.type         = EventType::WindowResize;
        event.windowResize.width  = e.window.data1;
        event.windowResize.height = e.window.data2;
        break;

      case SDL_EVENT_WINDOW_FOCUS_GAINED:
        event.header.type = EventType::WindowFocus;
        break;

      case SDL_EVENT_WINDOW_FOCUS_LOST:
        event.header.type = EventType::WindowLostFocus;
        break;

      case SDL_EVENT_WINDOW_MOVED:
        event.header.type   = EventType::WindowMoved;
        event.windowMoved.x = e.window.data1;
        event.windowMoved.y = e.window.data2;
        break;

      default:
        event.header.type = EventType::None;
        break;
    }

    return event;
  }

  static Event TranslateKeyEvent(const SDL_Event &e) {
    Event event{};
    event.header.category = EventCategory::Input | EventCategory::Keyboard;

    if (e.type == SDL_EVENT_KEY_DOWN) {
      event.header.type = EventType::KeyPressed;
      event.key.repeat  = e.key.repeat;
    } else {
      event.header.type = EventType::KeyReleased;
    }

    event.key.scancode = e.key.scancode;
    event.key.mods     = mapSDLMods(e.key.mod);

    return event;
  }

  static Event TranslateMouseEvent(const SDL_Event &e) {
    Event event{};
    event.header.category = EventCategory::Input | EventCategory::Mouse;

    switch (e.type) {
      case SDL_EVENT_MOUSE_MOTION:
        event.header.type     = EventType::MouseMoved;
        event.mouseMove.state = mapSDLMouseStates(e.motion.state);
        event.mouseMove.x     = e.motion.x;
        event.mouseMove.y     = e.motion.y;
        event.mouseMove.dx    = e.motion.xrel;
        event.mouseMove.dy    = e.motion.yrel;
        break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
        event.header.type = (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                                ? EventType::MouseButtonPressed
                                : EventType::MouseButtonReleased;

        event.mouseButton.button = e.button.button;
        event.mouseButton.clicks = e.button.clicks;
        event.mouseButton.x      = e.button.x;
        event.mouseButton.y      = e.button.y;
        break;

      case SDL_EVENT_MOUSE_WHEEL:
        event.header.type = EventType::MouseScrolled;

        event.mouseWheel.x           = e.wheel.x;
        event.mouseWheel.y           = e.wheel.y;
        event.mouseWheel.pos_x       = e.wheel.mouse_x;
        event.mouseWheel.pos_y       = e.wheel.mouse_y;
        event.mouseWheel.scrl_length = e.wheel.integer_x;
        event.mouseWheel.scrl_height = e.wheel.integer_y;
        break;

      default:
        event.header.type = EventType::None;
        break;
    }

    return event;
  }

  static Event TranslateTextInputEvent(const SDL_Event &e) {
    Event event{};
    event.header.category = EventCategory::Input | EventCategory::Text;
    event.header.type     = EventType::TextInput;

    const char *utf8 = e.text.text;

    event.textInput.codepoint = DecodeFirstUTF8(utf8);
    return event;
  }

  static Event TranslateApplicationEvent(const SDL_Event &e) {
    Event event{};
    event.header.category = EventCategory::Application
    event.header.type     = EventType::Quit;

    return event;
  }

  Event TranslateEvent(const SDL_Event &e) {
    switch (e.type) {
      case SDL_EVENT_QUIT: return TranslateApplicationEvent(e);
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      case SDL_EVENT_WINDOW_RESIZED:
      case SDL_EVENT_WINDOW_FOCUS_GAINED:
      case SDL_EVENT_WINDOW_FOCUS_LOST:
      case SDL_EVENT_WINDOW_MOVED:
        return TranslateWindowEvent(e);
      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        return TranslateKeyEvent(e);
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_MOUSE_WHEEL:
        return TranslateMouseEvent(e);
      case SDL_EVENT_TEXT_INPUT:
        return TranslateTextInputEvent(e);

      default: {
        Event event{};
        event.header.type     = EventType::None;
        event.header.category = EventCategory::None;
        return event;
      }
    }
  }
} // namespace SOUP