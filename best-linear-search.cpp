#include <iostream>
#include <vector>
#include <optional>

/**
 * @brief Performs a linear search on a vector to find the index of a target value.
 *
 * This function iterates through each element of the input vector and returns the
 * index of the first occurrence of the target value. If the value is not found,
 * it returns an empty optional.
 *
 * @tparam T The type of the elements in the vector.
 * @param data The vector of elements to search through.
 * @param target The value to search for.
 * @return An std::optional<size_t> containing the index of the target value if found,
 *         otherwise an empty optional.
 */
template<typename T>
std::optional<size_t> linear_search(const std::vector<T>& data, const T& target) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == target) {
            return i;
        }
    }
    return std::nullopt;
}

int main() {
    std::vector<int> numbers = {4, 2, 7, 1, 9, 5, 3};
    int target = 9;

    std::optional<size_t> result = linear_search(numbers, target);

    if (result.has_value()) {
        std::cout << "Target " << target << " found at index: " << result.value() << std::endl;
    } else {
        std::cout << "Target " << target << " not found in the vector." << std::endl;
    }

    return 0;
}
