#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class TQueue {
 public:
  TQueue() : buffer_(4) {}

  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] std::size_t size() const noexcept { return size_; }

  void push(const T& value) { add(value); }
  void push(T&& value) { add(std::move(value)); }

  T pop() {
    if (empty()) {
      throw std::out_of_range("queue is empty");
    }
    T value = std::move(*buffer_[head_]);
    buffer_[head_].reset();
    head_ = (head_ + 1) % buffer_.size();
    --size_;
    return value;
  }

  T& front() {
    if (empty()) {
      throw std::out_of_range("queue is empty");
    }
    return *buffer_[head_];
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("queue is empty");
    }
    return *buffer_[head_];
  }

  void clear() {
    for (std::size_t i = 0; i < size_; ++i) {
      buffer_[(head_ + i) % buffer_.size()].reset();
    }
    head_ = 0;
    size_ = 0;
  }

 private:
  template <typename U>
  void add(U&& value) {
    if (size_ == buffer_.size()) {
      grow();
    }
    buffer_[(head_ + size_) % buffer_.size()].emplace(std::forward<U>(value));
    ++size_;
  }

  void grow() {
    std::vector<std::optional<T>> bigger(buffer_.size() * 2);
    // Переносим элементы в порядке очереди, даже если начало буфера было в середине.
    for (std::size_t i = 0; i < size_; ++i) {
      bigger[i].emplace(std::move(*buffer_[(head_ + i) % buffer_.size()]));
    }
    buffer_ = std::move(bigger);
    head_ = 0;
  }

  std::vector<std::optional<T>> buffer_;
  std::size_t head_ = 0;
  std::size_t size_ = 0;
};
