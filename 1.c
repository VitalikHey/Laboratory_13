int main() {
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
    return 0;
}