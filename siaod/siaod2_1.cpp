#include <iostream>
#include <ctime>
#include <cstdlib>

void fill_array(int*, int);
void print_array(int*, int);
void fill_random_array(int*, int);
int first_search(int*, int, int);
int first_negative(int*, int);
int all_search(int*, int, int);
void insert_array(int*, int&, int, int);
void delete_item(int*, int&, int);
void delete_all_items_quadratic(int*, int&, int);
void delete_all_items_linear(int*, int&, int);


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int length;
    std::cout << "Length = "; std::cin >> length;
    if (length < 1 || length > 1000)
        return -1;

    int arr[1000], value;

    std::cout << "Fill: "; fill_array(arr, length);
    std::cout << "Value = "; std::cin >> value;
    //std::cout << first_search(arr, length, value);
    //std::cout << first_negative(arr, length);
    //std::cout << all_search(arr, length, value);
    //int key; std::cout << "Key = "; std::cin >> key;
    //if (key < 1 || key > length)
    //    return -2;
    //insert_array(arr, length, key, value);
    //if (key < 0 || key >= length)
    //    return -2;
    //delete_item(arr, length, key);
    delete_all_items_linear(arr, length, value);
    print_array(arr, length);
        
    return 0;
}

void fill_array(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
}

void print_array(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

void fill_random_array(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 11;
}

int first_search(int* arr, int n, int value) {
    for (int i = 0; i < n; ++i)
        if (value == arr[i])
            return i;
    return -1;
}

int first_negative(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        if (arr[i] < 0)
            return i;
    return -1;
}

int all_search(int* arr, int n, int value) {
    int amount = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] == value)
            ++amount;
    return amount;
}

void insert_array(int* arr, int &n, int key, int value) {
    for (int i = n - 1; i >= key; --i)
        arr[i + 1] = arr[i];
    ++n;
    arr[key] = value;
}

void delete_item(int* arr, int& n, int key) {
    --n;
    for (int i = key; i < n; ++i)
        arr[i] = arr[i + 1];
}

void delete_all_items_quadratic(int* arr, int& n, int value) {
    int i = 0;
    while (i < n) {
        if (arr[i] == value) {
            for (int j = i; j < n - 1; ++j)
                arr[j] = arr[j + 1];
            --n;
        }
        else
            ++i;
    }
}

void delete_all_items_linear(int* arr, int& n, int value) {
    int offset = 0;
    for (int i = 0; i < n; ++i) {
        arr[offset] = arr[i];
        if (arr[i] != value)
            ++offset;
    }
    n = offset;
}
