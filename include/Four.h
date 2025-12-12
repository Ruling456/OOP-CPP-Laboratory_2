#pragma once
#include <string>
#include <initializer_list>

class Four {
public:
    // Конструкторы
    Four();
    Four(const size_t& n, unsigned char fill = 0);
    Four(const std::initializer_list<unsigned char>& list);
    Four(const std::string& fourString);
    Four(const Four& other);
    Four(Four&& other) noexcept;
    virtual ~Four();

    // Операции (требуются по заданию)
    Four add(const Four& other) const;
    Four subtract(const Four& other) const;
    Four copy() const; // Для задания

    // Сравнение (требуется по заданию)
    bool equals(const Four& other) const;
    bool less_than(const Four& other) const;
    bool greater_than(const Four& other) const;

    // Вспомогательные методы
    std::string to_string() const;
    size_t size() const;

    // Операции с присваиванием (требуются по заданию как методы класса)
    // Возвращают новый объект, так как класс иммутабельный
    Four add_assign(const Four& other) const { return add(other); }
    Four subtract_assign(const Four& other) const { return subtract(other); }

private:
    size_t size_;
    unsigned char* digits_;
    
    // Вспомогательные приватные методы
    void normalize(); // Теперь модифицирует текущий объект
    bool isValidDigit(unsigned char digit) const;
    int compareDirectly(const Four& other) const; // Сравнение без нормализации
};