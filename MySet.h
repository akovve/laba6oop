#ifndef MY_SET_H
#define MY_SET_H

#include <vector>
#include <algorithm>

/**
 * @brief Шаблонный класс, реализующий множество уникальных элементов на основе массива.
 * 
 * Элементы хранятся в std::vector. При добавлении повторяющегося элемента ничего не происходит.
 * 
 * @tparam T тип элементов множества.
 */
template <typename T>
class MySet {
public:
    /**
     * @brief Конструктор по умолчанию создаёт пустое множество.
     */
    MySet() = default;

    /**
     * @brief Добавляет элемент во множество, если его там ещё нет.
     * 
     * @param item добавляемый элемент.
     * @return true если элемент был добавлен, false если он уже присутствовал.
     */
    bool Add(const T& item) {
        if (Contains(item)) {
            return false;
        }
        data_.push_back(item);
        return true;
    }

    /**
     * @brief Удаляет элемент из множества.
     * 
     * @param item удаляемый элемент.
     * @return true если элемент был удалён, false если он отсутствовал.
     */
    bool Remove(const T& item) {
        auto it = std::find(data_.begin(), data_.end(), item);
        if (it != data_.end()) {
            data_.erase(it);
            return true;
        }
        return false;
    }

    /**
     * @brief Проверяет наличие элемента во множестве.
     * 
     * @param item проверяемый элемент.
     * @return true если элемент присутствует, false в противном случае.
     */
    bool Contains(const T& item) const {
        return std::find(data_.begin(), data_.end(), item) != data_.end();
    }

    /**
     * @brief Возвращает объединение текущего множества с другим.
     * 
     * @param other другое множество.
     * @return новое множество, содержащее все элементы обоих множеств.
     */
    MySet Union(const MySet& other) const {
        MySet result = *this;  // копируем текущие элементы
        for (const auto& item : other.data_) {
            result.Add(item);   // Add автоматически не добавит дубликаты
        }
        return result;
    }

    /**
     * @brief Возвращает разность текущего множества и другого (элементы, которые есть в текущем, но отсутствуют в other).
     * 
     * @param other другое множество.
     * @return новое множество с элементами текущего, не входящими в other.
     */
    MySet Except(const MySet& other) const {
        MySet result;
        for (const auto& item : data_) {
            if (!other.Contains(item)) {
                result.Add(item);
            }
        }
        return result;
    }

    /**
     * @brief Возвращает пересечение текущего множества с другим.
     * 
     * @param other другое множество.
     * @return новое множество, содержащее только общие элементы.
     */
    MySet Intersect(const MySet& other) const {
        MySet result;
        for (const auto& item : data_) {
            if (other.Contains(item)) {
                result.Add(item);
            }
        }
        return result;
    }

    /**
     * @brief Возвращает количество элементов во множестве.
     * 
     * @return размер множества.
     */
    size_t Size() const {
        return data_.size();
    }

    // Для удобства итерации (необязательно)
    typename std::vector<T>::const_iterator begin() const { return data_.begin(); }
    typename std::vector<T>::const_iterator end() const { return data_.end(); }

private:
    std::vector<T> data_;  ///< Внутреннее хранилище элементов.
};

#endif // MY_SET_H