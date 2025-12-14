FROM ubuntu:22.04

# Установка переменных для автоматической установки
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Установка зависимостей включая Git (для GoogleTest)
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Копирование исходного кода
COPY . /project
WORKDIR /project

# Создание директории сборки и сборка проекта
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    cmake --build .

# Запуск тестов
CMD ["sh", "-c", "cd build && ./Laboratory_2_tests"]