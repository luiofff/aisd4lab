#include <iostream>
#include <ctime>

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    std::srand(std::time(0));

    int n, Range, X;

    std::cout << "Введите размерность одномерного массива: ";
    std::cin >> n;

    std::cout << "Введите диапазон значений элементов массива: ";
    std::cin >> Range;

    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = std::rand() % Range + 1;
    }

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Сортировка массива пузырьком
    bubbleSort(array, n);

    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Введите искомое значение X: ";
    std::cin >> X;

    int position = binarySearch(array, n, X);
    if (position != -1) {
        std::cout << "Значение " << X << " найдено на позиции " << position + 1 << "." << std::endl;
    } else {
        std::cout << "Значение " << X << " не найдено в массиве." << std::endl;
    }

    delete[] array;
    return 0;
}
