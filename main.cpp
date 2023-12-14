#include <iostream>
#include <ctime>
#include <cmath> 

class Vector
{
private:
    int* array;
    int size;
    int comparisons;
    int permutations;
public:

    Vector() : size(0), array(nullptr) {}

    Vector(int newSize) : size(newSize) {
		array = new int[size];
		srand(time(0));
		for (int i = 0; i < size; ++i) {
			array[i] = rand() % 21;
		}
	}

 
    void resize(int n, int value=0) {

        if (n > size) {
            int* resizedArray = new int[n];


            for (int i=0; i<n; i++) {
                if (i < size) resizedArray[i] = array[i];
                else resizedArray[i] = value;
            }

            delete[] array;

            size = n;
            array = new int[size];

            for (int m=0; m<size; m++) {
                array[m] = resizedArray[m];
            }

            delete[] resizedArray;
        } else {
            int* resizedArray = new int[n];
            
            for (int i=0; i<n; i++) {
                if (i != size) resizedArray[i] = array[i];
                else break;
            }

            delete[] array;

            size = n;
            array = new int[size];

            for (int m=0; m<size; m++) {
                array[m] = resizedArray[m];
            }

            delete[] resizedArray;
        }

    }

    void push_back(int el) {
        std::cout << "\n" << std::endl;
        std::cout << "Добавлен элемент в конец: " << el << std::endl;
        resize(size+1, el);
    }

    void pop_back() {
        std::cout << "\n" << std::endl;
        std::cout << "Удален элeмент в конце"<< std::endl;
        resize(size-1);
    }

    void insert(int el) {
        int* newArray = new int[size+1];
        std::cout << "\n" << std::endl;
        std::cout << "Добавлен элемент в начало: " << el << std::endl;

        newArray[0] = el;
        for (int i=0; i<size; i++) {
            newArray[i+1] = array[i];
        }

        delete[] array;

        size = size + 1;
        array = new int[size];

        for (int m=0; m<size; m++) {
            array[m] = newArray[m];
        }

        delete[] newArray; 
    }

    void optionInsert(int it, int n, int value) {
        std::cout << "\n" << std::endl;
        std::cout << "Вставленно: " << n << "\n" << "Элемент: " << value << "\n" << "С позиции: " << it << "\n" << std::endl;


        for (int i=it-1; i<(it+n)-1; i++) {
            array[i] = value;
        }
    }

    void front() {
        std::cout << "\n" << std::endl;
        std::cout << "Первый элемент: " << array[0] << std::endl;
    }

    void back() {
        std::cout << "\n" << std::endl;
        std::cout << "Первый элемент: " << array[size] << std::endl;
    }

    void erase(int position) {
        int* newArray = new int[size-1];
        std::cout << "\n" << std::endl;
        std::cout << "Удален элемент с позиции: " << position << std::endl;
		
        for (int left = 0; left < position - 1; left++) {
            newArray[left] = array[left];
        }

        for (int right = position; right < size; right++) {
            newArray[right - 1] = array[right];
        }



        delete[] array;

        size = size - 1;
        array = new int[size];

        for (int m=0; m<size; m++) {
            array[m] = newArray[m];
        }

        delete[] newArray; 
	}

    void clear() {
        std::cout << "\n" << std::endl;
        std::cout << "Удален массив" << std::endl;
        size = 0;
        array = new int[size];
        delete[] array;
    }

    void swap(int index1, int index2) {
        int temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }

    void shakeSort() {
        int low=0, up=size-1;
        int last;

        comparisons = 0;
        permutations = 0;

        clock_t start_time = clock();

        while (low < up) {
            last = -1;

            for (int i=low; i < up; i++) {
                if (array[i] > array[i+1]) {
                    swap(i, i+1);
                    last=i;
                    comparisons++;
                    permutations++;
                }
            }

            up = last;
            if(last == -1) break;
            last = size;

            for (int i = up-1; i >= low; i--) {
                if (array[i] > array[i+1]) {
                    swap(i, i+1);
                    last=i;
                    comparisons++;
                    permutations++;
                }
            }

            low = last + 1;
        }

        clock_t end_time = clock();
        double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

        std::cout << " " << size << " " << comparisons << " " << permutations << " " << execution_time << (size*(log(size))) << std::endl;
        
    }

    void quickSort(int low, int high) {
        int i = low;
        int j = high;
        int pivot = array[(low + high) / 2];

        while (i <= j) {
            while (array[i] < pivot) {
                i++;
                comparisons++;
            }
            while (array[j] > pivot) {
                j--;
                comparisons++;
            }
            if (i <= j) {
                swap(i, j);
                i++;
                j--;
                permutations++;
            }
        }

        if (low < j) {
            quickSort(low, j);
        }
        if (i < high) {
            quickSort(i, high);
        }
    }

    void quickSort() {
        comparisons = 0;
        permutations = 0;

        if (size > 0) {
            clock_t start_time = clock();
            quickSort(0, size - 1);
            clock_t end_time = clock();

            double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

            std::cout << " " << size << " " << comparisons
                      << " " << permutations << " " << execution_time
                      << (size*(log(size))) << std::endl;
        }
    }
 
    void print() {
        for (int j=0; j<size; j++) {
            std::cout<< array[j] << std::endl;
        }
    }
};





int main() {
    int size;

    std::cout << "Введите размер массива: " << std::endl;
    std::cin >> size;
    std::cout << "\n" << std::endl;

    Vector vec(size);
    std::cout << "Обычный массив: \n" << std::endl;
    vec.print();
    std::cout << "\n" << std::endl;
    std::cout << "Массив после шейкерной соритровки: " << std::endl;
    vec.shakeSort();

    Vector vec1(size);
    std::cout << "Обычный массив: \n" << std::endl;
    vec.print();
    std::cout << "\n" << std::endl;
    std::cout << "Массив после быстрой соритровки: " << std::endl;
    vec1.shakeSort();



    std::cout << "\n" << std::endl;

    std::cout << "шейкерная сортировка сортировка хаотичный массив \n" << std::endl;
    std::cout << "n | сравн| прест | врем| сложн" << std::endl;
    for (int i=30000; i<51000; i = i + 1000) {
        Vector vec(i);
        vec.shakeSort();
    }

    std::cout << "\n" << std::endl;

    std::cout << "Быстрая сортировка хаотичный массив \n" << std::endl;
    std::cout << "n | сравн| прест | врем| сложн" << std::endl;
    for (int i=30000; i<51000; i = i + 1000) {
        Vector vec(i);
        vec.quickSort();
    }
    


    return 0;
}