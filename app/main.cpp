#include <iostream>

#include "TQueue.h"

int main() {
  TQueue<int> queue;
  queue.push(10);
  queue.push(20);
  queue.push(30);

  while (!queue.empty()) {
    std::cout << queue.pop() << ' ';
  }
  std::cout << '\n';
}
