
#include "screen.h"

using namespace ftxui;

const auto CANVAS_WITDH = 100, CANVAS_HEIGHT = 100, GRID_SIZE = 10;
const auto TOP = 1, LEFT = 10, RIGHT = 20, BOTTOM = 5;

void UIScreen::initialize() {
  auto c = Canvas(CANVAS_WITDH, CANVAS_HEIGHT);
  for (auto x = 0; x <= CANVAS_WITDH; x += GRID_SIZE) {
    for (auto y = 0; y <= CANVAS_HEIGHT; y += GRID_SIZE) {
      c.DrawPoint(x, y, true);
    }
  }

  auto middle = Renderer([&c] { return canvas(&c); });
  auto left = Renderer([] { return text("Left") | center; });
  auto right = Renderer([] { return text("right") | center; });
  auto top = Renderer([] { return text("top") | center; });
  auto bottom = Renderer([] { return text("bottom") | center; });

  int left_size = LEFT;
  int right_size = RIGHT;
  int top_size = TOP;
  int bottom_size = BOTTOM;

  auto container = middle;
  container = ResizableSplitLeft(left, container, &left_size);
  container = ResizableSplitRight(right, container, &right_size);
  container = ResizableSplitTop(top, container, &top_size);
  container = ResizableSplitBottom(bottom, container, &bottom_size);

  auto renderer =
      Renderer(container, [&] { return container->Render() | border; });

  _screen.Loop(renderer);
}

void UIScreen::render() { _screen.PostEvent(Event::Custom); }