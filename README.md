# Очередь

Отдельный CMake-проект с реализацией очереди. Элементы извлекаются в порядке FIFO: первым добавлен — первым извлечён.

## Сборка и проверка

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

`QueueApp` показывает работу основных операций. `QueueTests` проверяет поведение структуры.
