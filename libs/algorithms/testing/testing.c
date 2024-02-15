#include <stdio.h>
#include <assert.h>
#include "testing.h"
#include "../../data_structure/bitset/bitset.h"
#include "../../algorithms/ordered_array/ordered_array_set.h"

void test_bitset_create(){
    bitset firstBitset = {0, 30};
    bitset secondBitset = bitset_create(30);
    assert(firstBitset.values == secondBitset.values);
    assert(firstBitset.maxValue == secondBitset.maxValue);
}


void test_bitset_in(){
    bitset set = {2, 5};
    assert(bitset_in(set, 1) == true);
    assert(bitset_in(set, 0) == false);
}


void test_bitset_isEqual(){
    bitset set1 = {11, 20};
    bitset set2 = {12, 20};
    bitset set3 = {11, 20};

    assert(bitset_isEqual(set1, set2) == false);
    assert(bitset_isEqual(set2, set3) == false);
    assert(bitset_isEqual(set1, set3) == true);
}


void test_bitset_isSubset(){
    // 00101010
    bitset set1 = {42, 7};
    // 00001010
    bitset set2 = {10, 7};
    // 10101010
    bitset set3 = {170, 7};
    // 00101010
    bitset set4 = {42, 7};

    assert(bitset_isSubset(set1, set4) == true);
    assert(bitset_isSubset(set2, set1) == true);
    assert(bitset_isSubset(set3, set1) == false);
}

void test_bitset_insert(){
    bitset set1 = {42, 7};
    bitset set2 = {11, 7};
    bitset_insert(&set1, 0);
    bitset_insert(&set2, 2);

    bitset set3 = {43, 7};
    bitset set4 = {15, 7};

    assert(set1.values == set3.values);
    assert(set2.values == set4.values);
}


void test_bitset_deleteElement(){
    bitset set1 = {43, 8};
    bitset set2 = {15, 8};
    bitset_deleteElement(&set1, 0);
    bitset_deleteElement(&set2, 2);

    bitset set3 = {42, 8};
    bitset set4 = {11, 8};

    assert(set1.values == set3.values);
    assert(set2.values == set4.values);
}


void test_bitset_union(){
    bitset set1 = {43, 8};
    bitset set2 = {15, 8};
    bitset set3 = {47, 8};

    bitset set4 = bitset_union(set1, set2);
    assert(set3.values == set4.values);
}


void test_bitset_intersection(){
    bitset set1 = {43, 7};
    bitset set2 = {15, 7};
    bitset set3 = {11, 7};

    bitset set4 = bitset_intersection(set1, set2);
    assert(set3.values == set4.values);
}


void test_bitset_difference(){
    bitset set1 = {43, 7};
    bitset set2 = {15, 7};
    bitset set3 = {32, 7};

    bitset set4 = bitset_difference(set1, set2);
    assert(set3.values == set4.values);
}


void test_bitset_symmetricDifference(){
    bitset set1 = {43, 7};
    bitset set2 = {15, 7};
    bitset set3 = {36, 7};

    bitset set4 = bitset_symmetric_difference(set1, set2);
    assert(set3.values == set4.values);
}


void test_bitset_complement(){
    bitset set1 = {42, 7};
    bitset set2 = {213, 7};

    bitset set3 = bitset_complement(set1);
    assert(set3.values == set2.values);
}


void auto_test_bitset(){
    test_bitset_create();
    test_bitset_in();
    test_bitset_isEqual();
    test_bitset_isSubset();
    test_bitset_insert();
    test_bitset_deleteElement();
    test_bitset_union();
    test_bitset_intersection();
    test_bitset_difference();
    test_bitset_symmetricDifference();
    test_bitset_complement();
}

void auto_test_ordered_array(){
    // Множества
    int set1_data[] = {2, 4, 6, 8, 10};
    ordered_array_set set1 = ordered_array_set_create_from_array(set1_data, 5);
    int set2_data[] = {3, 4, 5, 8, 9, 11};
    ordered_array_set set2 = ordered_array_set_create_from_array(set2_data, 6);
    int set3_data[] = {4, 8, 9};
    ordered_array_set set3 = ordered_array_set_create_from_array(set3_data, 3);
    int set4_data[] = {0, 1, 7, 8, 9, 15, 18 };
    ordered_array_set set4 = ordered_array_set_create_from_array(set4_data, 7);

    // Мультиверсум
    int multiversum_set1_set2_data[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ordered_array_set multiversum_set1_set2 =
            ordered_array_set_create_from_array(multiversum_set1_set2_data, 10);

    // Пересечение
    int set1_set2_intersection_data[] = {4, 8};
    ordered_array_set set1_set2_intersection_set =
            ordered_array_set_create_from_array(set1_set2_intersection_data, 2);
    assert(ordered_array_set_is_equal(
            ordered_array_set_intersection(set1, set2),
            set1_set2_intersection_set));

    int set2_set4_intersection_data[] = {8, 9};
    ordered_array_set set2_set4_intersection_set =
            ordered_array_set_create_from_array(set2_set4_intersection_data, 2);
    assert(ordered_array_set_is_equal(
            ordered_array_set_intersection(set2, set4),
            set2_set4_intersection_set));

    // Объединение
    int set1_set2_union_data[] = {2, 3, 4, 5, 6, 8, 9, 10, 11};
    ordered_array_set set1_set2_union_set =
            ordered_array_set_create_from_array(set1_set2_union_data, 9);
    assert(ordered_array_set_is_equal(
            ordered_array_set_union(set1, set2),
            set1_set2_union_set));

    int set2_set4_union_data[] = {0, 1, 3, 4, 5, 7, 8, 9, 11, 15, 18};
    ordered_array_set set2_set4_union_set =
            ordered_array_set_create_from_array(set2_set4_union_data, 11);
    assert(ordered_array_set_is_equal(
            ordered_array_set_union(set2, set4),
            set2_set4_union_set));

    // Разность
    int set1_set2_difference_data[] = {2, 6, 10};
    ordered_array_set set1_set2_difference_set =
            ordered_array_set_create_from_array(set1_set2_difference_data, 3);
    assert(ordered_array_set_is_equal(
            ordered_array_set_difference(set1, set2),
            set1_set2_difference_set));

    int set4_set2_difference_data[] = {0, 1, 7, 15, 18};
    ordered_array_set set4_set2_difference_set =
            ordered_array_set_create_from_array(set4_set2_difference_data, 5);
    assert(ordered_array_set_is_equal(
            ordered_array_set_difference(set4, set2),
            set4_set2_difference_set));

    // Симметрическая разность
    int set1_set2_symmetric_difference_data[] = {2, 3, 5, 6, 9, 10, 11};
    ordered_array_set set1_set2_symmetric_difference_set =
            ordered_array_set_create_from_array(set1_set2_symmetric_difference_data, 7);
    assert(ordered_array_set_is_equal(
            ordered_array_set_symmetric_difference(set1, set2),
            set1_set2_symmetric_difference_set));

    int set4_set2_symmetric_difference_data[] = {0, 1, 3, 4, 5, 7, 11, 15, 18};
    ordered_array_set set4_set2_symmetric_difference_set =
            ordered_array_set_create_from_array(set4_set2_symmetric_difference_data, 9);
    assert(ordered_array_set_is_equal(
            ordered_array_set_symmetric_difference(set4, set2),
            set4_set2_symmetric_difference_set));

    // Дополнение
    int set1_complement_data[] = {3, 5, 7, 9, 11};
    ordered_array_set set1_complement_set =
            ordered_array_set_create_from_array(set1_complement_data, 5);
    assert(ordered_array_set_is_equal(
            ordered_array_set_complement(set1, multiversum_set1_set2),
            set1_complement_set));

    int set2_complement_data[] = {2, 6, 7, 10};
    ordered_array_set set2_complement_set =
            ordered_array_set_create_from_array(set2_complement_data, 4);
    assert(ordered_array_set_is_equal(
            ordered_array_set_complement(set2, multiversum_set1_set2),
            set2_complement_set));

    int set3_complement_data[] = {2, 3, 5, 6, 7, 10, 11};
    ordered_array_set set3_complement_set =
            ordered_array_set_create_from_array(set3_complement_data, 7);
    assert(ordered_array_set_is_equal(
            ordered_array_set_complement(set3, multiversum_set1_set2),
            set3_complement_set));

    // Является ли подмножеством
    assert(ordered_array_set_is_subset(set1, set2) == false);
    assert(ordered_array_set_is_subset(set3, set2) == true);
}

void hand_bitset_testing(){
    bitset set1 = bitset_input();
    bitset set2 = bitset_input();

    printf("Intersection of sets: ");
    bitset_print(bitset_intersection(set1, set2));

    printf("Combining sets: ");
    bitset_print(bitset_union(set1, set2));

    printf("Sets ");
    printf(bitset_isEqual(set1, set2) ? "" : "not");
    printf(" equal\n");

    printf("Set 1 is a subset of set 2: ");
    printf(bitset_isSubset(set1, set2) ? "yes\n" : "no\n");

    printf("The difference of sets: ");
    bitset_print(bitset_difference(set1, set2));

    printf("The symmetric difference of sets: ");
    bitset_print(bitset_symmetric_difference(set1, set2));

    printf("Addition to the universe of the set 1: ");
    bitset_print(bitset_complement(set1));

    printf("Addition to the universe of the set 2: ");
    bitset_print(bitset_complement(set2));
}

void gen_range_array(int *a, int start, int end){
    for (int i = start; i < end; i++){
        *a = i;
        a++;
    }
}

int min_int(int a, int b){
    return a <= b ? a : b;
}

int max_int(int a, int b){
    return a >= b ? a : b;
}

void hand_ordered_set_testing(){
    //ordered_array_set set1 = ordered_array_set_input();
    //ordered_array_set set2 = ordered_array_set_input();
    int set1_data[] = {0, 1, 7, 8, 9, 15, 18 };
    ordered_array_set set1 = ordered_array_set_create_from_array(set1_data, 7);
    int set2_data[] = {3, 4, 5, 8, 9, 11};
    ordered_array_set set2 = ordered_array_set_create_from_array(set2_data, 6);

    int max_val = max_int(set1.data[set1.size - 1], set2.data[set2.size - 1]);
    int min_val = min_int(set1.data[0], set2.data[0]);
    ordered_array_set multiversum_set = ordered_array_set_create(max_val - min_val + 1);
    gen_range_array(multiversum_set.data, min_val, max_val + 1);
    multiversum_set.size = multiversum_set.capacity;

    printf("Multiverse: ");
    ordered_array_set_print(multiversum_set);

    printf("Intersection of sets: ");
    ordered_array_set_print(ordered_array_set_intersection(set1, set2));

    printf("Combining sets: ");
    ordered_array_set_print(ordered_array_set_union(set1, set2));

    printf("Sets ");
    printf(ordered_array_set_is_equal(set1, set2) ? "" : "not");
    printf(" equal\n");

    printf("Set 1 is a subset of set 2: ");
    printf(ordered_array_set_is_subset(set1, set2) ? "yes\n" : "no\n");

    printf("Difference sets ");
    ordered_array_set_print(ordered_array_set_difference(set1, set2));

    printf("Symmetric difference sets: ");
    ordered_array_set_print(ordered_array_set_symmetric_difference(set1, set2));

    printf("Addition to the universe of the set 1: ");
    ordered_array_set_print(ordered_array_set_complement(set1, multiversum_set));

    printf("Addition to the universe of the set 2: ");
    ordered_array_set_print(ordered_array_set_complement(set2, multiversum_set));
}