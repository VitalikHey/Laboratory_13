#include "bitset.h"
#include "../../algorithms/gfunc/gfunc.h"
#include <stdio.h>

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create (unsigned maxValue){
    return (bitset){0, maxValue};
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in (bitset set, unsigned int value){
    return (set.values & (1 << value)) != 0;
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual (bitset set1, bitset set2){
    return set1.maxValue = set2.maxValue && set1.values == set2.values;
}

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset (bitset subset, bitset set){
    return ((set.values ^ subset.values) & subset.values) == 0;
}

// добавляет элемент value в множество set
void bitset_insert (bitset * set, unsigned int value){
    set->values |= 1 << value;
}

// удаляет элемент value из множества set
void bitset_deleteElement (bitset * set, unsigned int value){
    set->values &= ~(1 << value);
}

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2){
    bitset res = {set1.values | set2.values, max(set1.maxValue, set2.maxValue)};
    return res;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection (bitset set1, bitset set2){
    bitset res = {set1.values & set2.values, min(set1.maxValue, set2.maxValue)};
    return res;
}

// возвращает разность множеств set1 и set2
bitset bitset_difference (bitset set1, bitset set2){
    bitset res = {set1.values & ~set2.values, set1.maxValue};
    return res;
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetric_difference (bitset set1, bitset set2){
    bitset res = {set1.values ^ set2.values,
                  max(set1.maxValue, set2.maxValue)};
    return res;
}
// возвращает дополнение до универсума множества set
bitset bitset_complement (bitset set){
    bitset result_set = bitset_create(set.maxValue);

    for (int i = 0; i <= set.maxValue; i++)
        bitset_insert(&result_set, i);

    return bitset_difference(result_set, set);;
}
// вывод множества set
void bitset_print (bitset set){
    printf("{%i", bitset_in(set, 0));
    for (int i = 1; i <= set.maxValue; i++)
        printf(", %i", bitset_in(set, i));

    printf("}\n");
}

bitset bitset_input(){
    printf("Введите число элементов в множестве и максимальный элемент: ");

    int n, max_val;
    scanf("%i%i", &n, &max_val);

    bitset set = bitset_create(max_val);

    printf("Введите %i элементов: ", n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%i", &x);

        if (x > max_val)
            max_val = x;

        bitset_insert(&set, x);
    }

    set.maxValue = max_val;

    return set;
}