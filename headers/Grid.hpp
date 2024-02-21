#include <vector>
#include <iostream>

template<typename T>
class Grid
{
private:
    std::vector<std::vector<T>> data;
public:
    // Create
    Grid(size_t rows, size_t cols, const T& defaultValue = T()) : data(rows, std::vector<T>(cols, defaultValue)) {}

    // Value at a specific position
    T& at(size_t row, size_t col) {
        return data.at(row).at(col);
    }

    // Set value at a specific position
    void set(size_t row, size_t col, const T& value) {
        data.at(row).at(col) = value;
    }

    // Destruct
    ~Grid() {}
};
