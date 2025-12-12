#include "../include/Four.h"
#include <stdexcept>
#include <algorithm>



// Конструктор по умолчанию
Four::Four() : size_(1), digits_(new unsigned char[1]{0}) {}

// Конструктор с размером и заполнением
Four::Four(const size_t& n, unsigned char fill) {
    if (n == 0) {
        throw std::invalid_argument("Size must be greater than 0");
    }
    if (fill > 3) { // В четверичной системе только цифры 0-3
        throw std::invalid_argument("fill must be between 0 and 3");
    }
    else {
        size_ = n;
        digits_ = new unsigned char[size_];
        std::fill(digits_, digits_ + size_, fill);
    }
}

// Конструктор с initializer_list
Four::Four(const std::initializer_list<unsigned char> &list) : size_(0), digits_(nullptr) {
    if (list.size() == 0) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    size_ = list.size();
    digits_ = new unsigned char[size_];
    std::copy(list.begin(), list.end(), digits_);
    for (size_t i = 0; i < size_; ++i) {
        if (digits_[i] > 3) { // Проверка на допустимые цифры 0-3
            delete[] digits_;
            throw std::invalid_argument("All digits must be between 0 and 3");
        }
    }
}

// Конструктор из строки
Four::Four(const std::string &fourString) {
    if (fourString.empty()) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    
    size_ = fourString.size();
    digits_ = new unsigned char[size_];
    
    for (size_t i = 0; i < size_; ++i) {
        char c = fourString[size_ - 1 - i];
        
        if (c < '0' || c > '3') {
            delete[] digits_;
            throw std::invalid_argument("All digits must be between 0 and 3");
        }
        
        digits_[i] = c - '0';
    }
}

// Копи-конструктор
Four::Four(const Four &other) : size_(other.size_), digits_(new unsigned char[other.size_]) {
    std::copy(other.digits_, other.digits_ + other.size_, digits_);
}

// Конструктор перемещения (ИСПРАВЛЕННЫЙ)
Four::Four(Four &&other) noexcept : size_(other.size_), digits_(other.digits_) {
    other.size_ = 0;
    other.digits_ = nullptr; // Правильное перемещение
}

// Деструктор
Four::~Four() {
    delete[] digits_;
}

// Проверка валидности цифры
bool Four::isValidDigit(unsigned char digit) const {
    return digit >= 0 && digit <= 3;
}

// Нормализация (модифицирует текущий объект)
void Four::normalize() {
    if (size_ == 0) {
        size_ = 1;
        digits_ = new unsigned char[1]{0};
        return;
    }
    
    // Находим первую ненулевую цифру с конца (старший разряд)
    size_t new_size = size_;
    while (new_size > 1 && digits_[new_size - 1] == 0) {
        --new_size;
    }
    
    // Если размер изменился, пересоздаем массив
    if (new_size != size_) {
        unsigned char* new_digits = new unsigned char[new_size];
        std::copy(digits_, digits_ + new_size, new_digits);
        delete[] digits_;
        digits_ = new_digits;
        size_ = new_size;
    }
}

// Прямое сравнение (без создания временных объектов)
int Four::compareDirectly(const Four& other) const {
    // 1. Найдем реальные размеры (без ведущих нулей)
    size_t len1 = size_;
    size_t len2 = other.size_;
    
    // Ищем первую ненулевую цифру с конца
    while (len1 > 0 && digits_[len1 - 1] == 0) len1--;
    while (len2 > 0 && other.digits_[len2 - 1] == 0) len2--;
    
    // 2. Если оба числа нули
    if (len1 == 0 && len2 == 0) return 0;
    
    // 3. Если одно число ноль, а другое нет
    if (len1 == 0) return -1;  // 0 < other
    if (len2 == 0) return 1;   // this > 0
    
    // 4. Сравниваем по длине
    if (len1 < len2) return -1;
    if (len1 > len2) return 1;
    
    // 5. Длины равны, сравниваем цифры от СТАРШЕГО разряда к младшему
    for (size_t i = len1; i > 0; --i) {
        size_t idx = i - 1;  // Индекс в массиве (0-based)
        unsigned char d1 = digits_[idx];
        unsigned char d2 = other.digits_[idx];
        
        if (d1 < d2) return -1;
        if (d1 > d2) return 1;
        // Если равны, продолжаем
    }
    
    return 0;  // Все цифры равны
}

// Сложение
Four Four::add(const Four& other) const {
    size_t max_size = std::max(size_, other.size_);
    Four result(max_size + 1, 0); // +1 на случай переноса в старший разряд
    
    unsigned int carry = 0; // Перенос
    unsigned int temp_sum = 0; // Временная сумма
    
    for (size_t i = 0; i < max_size; ++i) {
        unsigned int digit1 = (i < size_) ? digits_[i] : 0;
        unsigned int digit2 = (i < other.size_) ? other.digits_[i] : 0;
        
        temp_sum = digit1 + digit2 + carry;
        result.digits_[i] = static_cast<unsigned char>(temp_sum % 4); // Основание 4
        carry = temp_sum / 4;
    }
    
    if (carry) {
        result.digits_[max_size] = static_cast<unsigned char>(carry);
        result.size_ = max_size + 1;
    }
    else {
        result.size_ = max_size;
    }
    
    result.normalize();
    return result;
}

// Вычитание
Four Four::subtract(const Four& other) const {
    if (compareDirectly(other) < 0) {
        throw std::underflow_error("Result would be negative");
    }
    
    Four result(size_, 0);
    unsigned char borrow = 0;
    
    for (size_t i = 0; i < size_; ++i) {
        unsigned char digit1 = digits_[i];
        unsigned char digit2 = (i < other.size_) ? other.digits_[i] : 0;
        
        if (digit1 < digit2 + borrow) {
            result.digits_[i] = static_cast<unsigned char>(digit1 + 4 - digit2 - borrow); // Основание 4
            borrow = 1;
        } else {
            result.digits_[i] = static_cast<unsigned char>(digit1 - digit2 - borrow);
            borrow = 0;
        }
    }
    
    result.normalize();
    return result;
}

// Копирование
Four Four::copy() const {
    return Four(*this);
}

// Сравнение
bool Four::equals(const Four& other) const {
    return compareDirectly(other) == 0;
}

bool Four::less_than(const Four& other) const {
    return compareDirectly(other) < 0;
}

bool Four::greater_than(const Four& other) const {
    return compareDirectly(other) > 0;
}

// Преобразование в строку
std::string Four::to_string() const {
    std::string result;
    
    // Находим первую ненулевую цифру
    size_t start = size_;
    while (start > 0 && digits_[start - 1] == 0) {
        --start;
    }
    
    // Если все цифры нули
    if (start == 0) {
        return "0";
    }
    
    // Собираем строку от старших разрядов к младшим
    for (size_t i = start; i > 0; --i) {
        result.push_back(static_cast<char>(digits_[i - 1] + '0'));
    }
    
    return result;
}

// Получение размера
size_t Four::size() const {
    return size_;
}