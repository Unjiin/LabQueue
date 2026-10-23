#include <memory>
#include <stdexcept>

#include "TQueue.h"

void check(bool condition) {
  if (!condition) {
    throw std::runtime_error("queue test failed");
  }
}

int main() {
  TQueue<int> queue;
  check(queue.empty() && queue.size() == 0);

  for (int value = 0; value < 4; ++value) {
    queue.push(value);
  }
  check(queue.pop() == 0 && queue.pop() == 1);
  queue.push(4);
  queue.push(5);
  queue.push(6);  // Расширение после перехода конца буфера через начало.
  check(queue.size() == 5 && queue.front() == 2);
  for (int value = 2; value <= 6; ++value) {
    check(queue.pop() == value);
  }
  check(queue.empty());

  try {
    queue.pop();
    check(false);
  } catch (const std::out_of_range&) {
  }
  try {
    queue.front();
    check(false);
  } catch (const std::out_of_range&) {
  }

  queue.push(10);
  TQueue<int> copy = queue;
  queue.clear();
  check(queue.empty() && copy.pop() == 10);

  TQueue<std::unique_ptr<int>> move_only;
  move_only.push(std::make_unique<int>(42));
  check(*move_only.pop() == 42);
}
