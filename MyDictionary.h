#ifndef MY_DICTIONARY_H
#define MY_DICTIONARY_H

#include <utility>  // для std::pair

/**
 * @brief Шаблонный класс словаря с уникальными ключами.
 * 
 * Реализован вручную на динамическом массиве пар ключ-значение.
 * При добавлении пары с уже существующим ключом добавление не происходит.
 * 
 * @tparam Key тип ключа.
 * @tparam Value тип значения.
 */
template <typename Key, typename Value>
class MyDictionary {
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    MyDictionary() : data_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Конструктор копирования.
     * 
     * @param other словарь для копирования.
     */
    MyDictionary(const MyDictionary& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new std::pair<Key, Value>[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    /**
     * @brief Оператор присваивания.
     * 
     * @param other словарь для копирования.
     * @return ссылка на текущий словарь.
     */
    MyDictionary& operator=(const MyDictionary& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new std::pair<Key, Value>[capacity_];
            for (int i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    /**
     * @brief Деструктор.
     */
    ~MyDictionary() {
        delete[] data_;
    }

    /**
     * @brief Добавляет пару ключ-значение в словарь.
     * 
     * @param key ключ.
     * @param value значение.
     * @return true если пара добавлена, false если ключ уже существует.
     */
    bool Add(const Key& key, const Value& value) {
        if (ContainsKey(key)) {
            return false;
        }
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::make_pair(key, value);
        return true;
    }

    /**
     * @brief Удаляет элемент по ключу.
     * 
     * @param key ключ удаляемого элемента.
     * @return true если элемент удалён, false если ключ не найден.
     */
    bool Remove(const Key& key) {
        int index = FindIndex(key);
        if (index == -1) {
            return false;
        }
        // сдвигаем все последующие элементы влево
        for (int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        return true;
    }

    /**
     * @brief Проверяет наличие ключа в словаре.
     * 
     * @param key ключ.
     * @return true если ключ существует, false в противном случае.
     */
    bool ContainsKey(const Key& key) const {
        return FindIndex(key) != -1;
    }

    /**
     * @brief Пытается получить значение по ключу.
     * 
     * @param key ключ.
     * @param value сюда будет записано значение, если ключ найден.
     * @return true если ключ найден, false в противном случае.
     */
    bool TryGetValue(const Key& key, Value& value) const {
        int index = FindIndex(key);
        if (index == -1) {
            return false;
        }
        value = data_[index].second;
        return true;
    }

    /**
     * @brief Возвращает количество элементов в словаре.
     * 
     * @return размер словаря.
     */
    int Size() const {
        return size_;
    }

private:
    std::pair<Key, Value>* data_;  ///< Динамический массив пар.
    int size_;                      ///< Текущее количество элементов.
    int capacity_;                  ///< Вместимость массива.

    /**
     * @brief Изменяет вместимость массива.
     * 
     * @param new_capacity новая вместимость (должна быть >= size_).
     */
    void Reserve(int new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        auto new_data = new std::pair<Key, Value>[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    /**
     * @brief Находит индекс элемента по ключу.
     * 
     * @param key ключ.
     * @return индекс элемента или -1, если ключ не найден.
     */
    int FindIndex(const Key& key) const {
        for (int i = 0; i < size_; ++i) {
            if (data_[i].first == key) {
                return i;
            }
        }
        return -1;
    }
};

#endif // MY_DICTIONARY_H