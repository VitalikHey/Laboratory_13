#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "libs/algorithms/testing/testing.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


typedef struct unordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} unordered_array_set;


//компаратор
int compareInts(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


void deleteByPosUnsaveOrder_(int *a, size_t *n, size_t pos) {
    a[pos] = a[*n - 1];
    (*n)--;
}


size_t linearSearch_(const int *a, const size_t n, int x) {
    for (size_t i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return n;
}


void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}


void append_(int *const a, size_t *const n, const int value) {
    a[*n] = value;
    (*n)++;
}


unordered_array_set unorderedArraySetCreate(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}


size_t unorderedArraySetIn(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}


void unorderedArraySetIsAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}


void unorderedArraySetInsert(unordered_array_set *set, int value) {
    if (unorderedArraySetIn(*set, value) == set->size) {
        unorderedArraySetIsAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}


void unorderedArraySetDelete(unordered_array_set set) {
    free(set.data);
    set.size = 0;
    set.capacity = 0;
}


unordered_array_set unorderedArraySetIntersection(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size < set2.size ? set1.size : set2.size;
    unordered_array_set set = unorderedArraySetCreate(new_capacity);

    for (size_t i = 0; i < set1.size; i++)
        if (unorderedArraySetIn(set2, set1.data[i]) != set2.size)
            unorderedArraySetInsert(&set, set1.data[i]);

    return set;
}


void unorderedArraySetPrint(unordered_array_set set) {
    outputArray_(set.data, set.size);
}


void task1(){

    int n;
    scanf("%d", &n);

    int m;
    scanf("%d", &m);

    unordered_array_set set1 = unorderedArraySetCreate(m);
    for (int j = 0; j < m; ++j) {
        int x;
        scanf("%d", &x);
        unorderedArraySetInsert(&set1, x);
    }

    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &m);
        unordered_array_set set2 = unorderedArraySetCreate(m);
        for (int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);
            unorderedArraySetInsert(&set2, x);
        }

        set1 = unorderedArraySetIntersection(set1, set2);

        unorderedArraySetDelete(set2);
    }

    unorderedArraySetPrint(set1);

    unorderedArraySetDelete(set1);

}


void task2() {
    int n;
    scanf("%i", &n);

    char *set = (char *) malloc(n + 1);
    memset(set, 0, n + 1);

    for (int i = 1; i < n; i++) {
        int index;
        scanf("%i", &index);
        set[index] = 1;
    }

    for (int i = 1; i <= n; i++)
        if (!set[i]) {
            printf("%i", i);
            break;
        }

    free(set);
}

int countPairs(int n) {
    return n * (n - 1) / 2;
}

void task3() {

}

void task4() {
    int n;
    scanf("%i", &n);
    const int BUF_SIZE = 28;
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    char s[22];

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        buf[s[0] - 'a']++;
    }

    int pairs_amount = 0;
    for (int i = 0; i < BUF_SIZE; i++) {
        int half = buf[i] / 2;
        pairs_amount += countPairs(half) + countPairs(half + buf[i] % 2);
    }

    printf("%i", pairs_amount);
}

void task06() {
    int n;
    scanf("%i", &n);

    if (n > 26 || n == 1)
        printf("Yes");
    else {
        const int BUF_SIZE = 28;
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE);

        char s[BUF_SIZE];
        scanf("%s", s);

        int i;
        for (i = 0; i < n && !buf[s[i] - 'a']; i++)
            buf[s[i] - 'a'] = 1;

        printf(i == n ? "No" : "Yes");
    }
}

void task08() {
    int n;
    scanf("%i", &n);
    const int BUF_SIZE = 1001;
    int buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE * sizeof(int));

    for (int i = 0; i < n; i++) {
        int length;
        scanf("%i", &length);
        buf[length]++;
    }

    int max_height = 1;
    int tower_amount = 0;
    for (int i = 1; i < BUF_SIZE; i++)
        if (buf[i]) {
            tower_amount++;
            if (buf[i] > max_height)
                max_height = buf[i];
        }
    printf("%i %i", max_height, tower_amount);
}

void task10() {
    int n;
    scanf("%i", &n);

    if (n > 26)
        printf("-1");
    else {
        const int BUF_SIZE = 28;
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE);

        char s[BUF_SIZE];
        scanf("%s", s);

        int amount = 0;
        for (int i = 0; i < n; i++)
            if (buf[s[i] - 'a'])
                amount++;
            else
                buf[s[i] - 'a'] = 1;

        printf("%i", amount);
    }
}

void inputDigitsFromString(int *digits, int n) {
    int c;
    do {
        c = getchar();
    } while (c > '9' || c < '0');
    digits[c - '0']++;
    for (int i = 1; i < n; i++) {
        c = getchar();
        digits[c - '0']++;
    }
}

void task11() {
    int n;
    scanf("%i", &n);

    int sherlock_digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int moriarty_digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    inputDigitsFromString(sherlock_digits, n);
    inputDigitsFromString(moriarty_digits, n);

    int min_receive = 0;
    int greater_digits = 0;
    for (int i = 9; i >= 0; i--) {
        int difference = moriarty_digits[i] - sherlock_digits[i];
        int new_greater_digits = difference + greater_digits;
        if (new_greater_digits >= 0)
            greater_digits = new_greater_digits;
        else {
            min_receive += -greater_digits - difference;
            greater_digits = 0;
        }
    }

    int max_send = 0;
    greater_digits = 0;
    for (int i = 9; i > 0; i--) {
        greater_digits += moriarty_digits[i];
        int cur_sherlock_digits = sherlock_digits[i - 1];
        if (greater_digits >= cur_sherlock_digits) {
            greater_digits -= cur_sherlock_digits;
            max_send += cur_sherlock_digits;
        } else {
            max_send += greater_digits;
            greater_digits = 0;
        }
    }

    printf("%i\n%i", min_receive, max_send);

}

long long countPairsLl(int n) {
    return (n * (long long) (n - 1)) / 2;
}

void task12() {
    int n;
    scanf("%i", &n);
    const int BUF_SIZE = 21;
    int buf[BUF_SIZE];
    int *mid_buf = buf + 10;
    memset(buf, 0, BUF_SIZE * sizeof(int));

    for (int i = 0; i < n; i++) {
        int t;
        scanf("%i", &t);
        mid_buf[t]++;
    }

    long long amount = countPairsLl(mid_buf[0]);
    for (int i = 1; i <= 10; i++)
        amount += mid_buf[i] * (long long) mid_buf[-i];

    printf("%lli", amount);
}

int main() {
    auto_test_bitset();
    auto_test_ordered_array();
    hand_ordered_set_testing();
    //task11();
    return 0;
}
