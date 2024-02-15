#include <assert.h>
#include "ordered_array_set.h"
#include "../../algorithms/array/array.h"
#include <stdio.h>

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity){
    return (ordered_array_set) {(at*) malloc(capacity * sizeof(at)), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size21
ordered_array_set ordered_array_set_create_from_array (const int *a, size_t size){
    ordered_array_set set = ordered_array_set_create(size);
    set.size = size;
    copy(set.data, a, size);
    sortByChoice(set.data, set.size);
    return set;
}

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set *set, int value){
    return binarySearch(set->data, set->size, value);
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_is_equal(ordered_array_set set1, ordered_array_set set2){
    if (set1.size != set2.size)
        return false;

    return isEqual(set1.data, set2.data, set1.size);
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_is_subset(ordered_array_set subset, ordered_array_set set){
    size_t subset_index = 0;
    size_t set_index = 0;

    while (subset_index < subset.size && set_index < set.size){
        if (subset.data[subset_index] == set.data[set_index]){
            subset_index++;
            set_index++;
        } else if (subset.data[subset_index] < set.data[set_index])
            return false;
        else
            set_index++;
    }

    return subset_index == subset.size;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_is_able_append(ordered_array_set *set){
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value){
    size_t pos = binarySearchEqualOrMore(set->data, set->size, value);
    if (pos != set->size || set->data[pos] == value)
        return;

    if (set->size >= set->capacity){
        size_t new_capacity = set->capacity << 1;
        int *new_data = realloc(set->data, new_capacity);
        if (new_data == NULL)
            return;
        set->data = new_data;
        set->capacity = new_capacity;
    }

    insert(set->data, &set->size, pos, value);
}

// удаляет элемент value из множества set
void ordered_array_set_delete_element(ordered_array_set *set, int value){
    size_t pos = ordered_array_set_in(set, value);
    if (pos == set->size)
        return;

    deletePosSaveOrder(set->data, &set->size, pos);
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set set = ordered_array_set_create(set1.size + set2.size);
    size_t set1_index = 0;
    size_t set2_index = 0;
    while (set1_index < set1.size && set2_index < set2.size){
        if (set1.data[set1_index] == set2.data[set2_index]){
            set.data[set.size++] = set1.data[set1_index++];
            set2_index++;
        }
        else if (set1.data[set1_index] < set2.data[set2_index]) {
            set.data[set.size++] = set1.data[set1_index++];
        }
        else
            set.data[set.size++] = set2.data[set2_index++];
    }

    size_t copy_amount;
    if (set1_index < set1.size) {
        copy_amount = set1.size - set1_index;
        copy(set.data + set.size, set1.data + set1_index, copy_amount);
    }
    else {
        copy_amount = set2.size - set2_index;
        copy(set.data + set.size, set2.data + set2_index, copy_amount);
    }
    set.size += copy_amount;

    return set;
}

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set set = ordered_array_set_create(set1.size);
    size_t set1_index = 0;
    size_t set2_index = 0;

    while (set1_index < set1.size && set2_index < set2.size){
        if (set1.data[set1_index] == set2.data[set2_index]){
            set.data[set.size++] = set1.data[set1_index++];
            set2_index++;
        }
        else if (set1.data[set1_index] < set2.data[set2_index])
            set1_index++;
        else
            set2_index++;
    }

    return set;
}

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set set = ordered_array_set_create(set1.size);

    size_t set1_index = 0;
    size_t set2_index = 0;
    while(set1_index < set1.size)
        if (set1.data[set1_index] < set2.data[set2_index] || set2_index == set2.size)
            set.data[set.size++] = set1.data[set1_index++];
        else if (set1.data[set1_index] == set2.data[set2_index]){
            set1_index++;
            set2_index++;
        }
        else
            set2_index++;

    return set;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetric_difference(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set set = ordered_array_set_create(set1.size + set2.size);
    size_t set1_index = 0;
    size_t set2_index = 0;
    while (set1_index < set1.size && set2_index < set2.size)
        if (set1.data[set1_index] < set2.data[set2_index])
            set.data[set.size++] = set1.data[set1_index++];
        else if (set1.data[set1_index] > set2.data[set2_index])
            set.data[set.size++] = set2.data[set2_index++];
        else {
            set1_index++;
            set2_index++;
        }

    size_t copy_amount;
    if (set1_index < set1.size) {
        copy_amount = set1.size - set1_index;
        copy(set.data + set.size, set1.data + set1_index, copy_amount);
    }
    else {
        copy_amount = set2.size - set2_index;
        copy(set.data + set.size, set2.data + set2_index, copy_amount);
    }
    set.size += copy_amount;

    return set;
}

// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet){
    return ordered_array_set_difference(universumSet, set);
}

// вывод множества set
void ordered_array_set_print(ordered_array_set set){
    putchar('{');

    outputArray(set.data, set.size, ", ");

    printf("}\n");
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete (ordered_array_set set){
    free(set.data);
}

ordered_array_set ordered_array_set_input(){
    printf("Enter the number of elements in the set: ");

    int n;
    scanf("%i", &n);

    printf("Enter %i of the elements: ", n);

    int a[n];
    inputArray(a, n);

    return ordered_array_set_create_from_array(a, n);
}