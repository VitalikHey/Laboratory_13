#include "unordered_array_set.h"
#include "../../algorithms/array/array.h"

// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create (size_t capacity){
    return (unordered_array_set) {(at*) malloc(capacity * sizeof(at)), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size21
unordered_array_set unordered_array_set_create_from_array (const int *a, size_t size){
    unordered_array_set set = unordered_array_set_create(size);
    copy(set.data, a, size);
    return set;
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_in (unordered_array_set set, int value){
    return linearSearch(set.data, set.size, value);
}


bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (size_t subset_index = 0; subset_index < subset.size; subset_index++){
        size_t set_index = 0;
        while (set_index < set.size && subset.data[subset_index] != set.data[set_index])
            set_index++;

        if (set_index == set.size)
            return false;
    }

    return true;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual (unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size)
        return false;

    for (int set1_index = 0; set1_index < set1.size; set1_index++) {
        size_t set2_index = 0;
        while (set1.data[set1_index] != set2.data[set2_index] && set2_index < set2.size)
            set2_index++;

        if (set2_index == set2.size)
            return false;
    }
    return true;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend (unordered_array_set *set){
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void unordered_array_set_insert (unordered_array_set * set, int value){
    if (unordered_array_set_in(*set, value))
        return;

    if (set->size >= set->capacity){
        size_t new_capacity = set->capacity << 1;
        int *new_data = realloc(set->data, new_capacity);
        if (new_data == NULL)
            return;
        set->data = new_data;
        set->capacity = new_capacity;
    }

    set->data[set->size++] = value;
}

// удаляет элемент value из множества set
void unordered_array_set_deleteElement (unordered_array_set * set, int value){
    deletePos(set->data, &set->size, linearSearch(set->data, set->size, value));
}

// возвращает объединение множеств set1 и set2 .
unordered_array_set unordered_array_set_union (unordered_array_set set1, unordered_array_set set2){
    unordered_array_set set = unordered_array_set_create(set1.size + set2.size);
    copy(set.data, set1.data, set.size);
    set.size = set1.size;

    for (size_t set2_index = 0, set1_index; set2_index < set2.size; set2_index++) {
        if (!unordered_array_set_in(set1, set2.data[set2_index]))
            set.data[set.size++] = set2.data[set2_index];
    }

    return set;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection (unordered_array_set set1 , unordered_array_set set2){
    unordered_array_set set = unordered_array_set_create(set1.size);

    for (size_t set1_index = 0; set1_index < set1.size; set1_index++)
            if (unordered_array_set_in(set2, set1.data[set1_index]))
                set.data[set.size++] = set1.data[set1_index];

    return set;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference (unordered_array_set set1, unordered_array_set set2){
    unordered_array_set set = unordered_array_set_create(set1.size);

    for (size_t set1_index = 0; set1_index < set1.size; set1_index++) {
        if (!unordered_array_set_in(set2, set1.data[set1_index]))
            set.data[set.size++] = set1.data[set1_index];
    }

    return set;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference (unordered_array_set set1, unordered_array_set set2){
    unordered_array_set set = unordered_array_set_create(set1.size + set2.size);
    size_t size = 0;

    for (size_t set1_index = 0; set1_index < set1.size; set1_index++) {
        if (!unordered_array_set_in(set2, set1.data[set1_index]))
            set.data[size++] = set1.data[set1_index];
    }

    for (size_t set2_index = 0; set2_index < set2.size; set2_index++) {
        if (!unordered_array_set_in(set1, set2.data[set2_index]))
            set.data[size++] = set2.data[set2_index];
    }

    set.size = size;

    return set;
}

// возвращает дополнение до универсума множества set
unordered_array_set unordered_array_set_complement (unordered_array_set set, unordered_array_set universumSet){
    return unordered_array_set_difference(universumSet, set);
}

// вывод множества set
void unordered_array_set_print(unordered_array_set set){
    putchar('{');
    outputArray(set.data, set.size, ", ");
    printf("}\n");
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete (unordered_array_set set){
    free(set.data);
}
