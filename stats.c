#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Sorting (used by median and mode) --- */
int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sort_array(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare_ints);
}

/* --- Mean --- */
double calculate_mean(int *arr, int n) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (double)sum / n;
}

/* --- Median --- */
double calculate_median(int *arr, int n) {
    int *sorted = malloc(n * sizeof(int));
    memcpy(sorted, arr, n * sizeof(int));
    sort_array(sorted, n);

    double median;
    if (n % 2 == 0) {
        median = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    } else {
        median = sorted[n / 2];
    }

    free(sorted);
    return median;
}

/* --- Mode --- */
/* Returns all modes via out_modes (caller must free). Sets *out_count. */
int *calculate_mode(int *arr, int n, int *out_count) {
    int *sorted = malloc(n * sizeof(int));
    memcpy(sorted, arr, n * sizeof(int));
    sort_array(sorted, n);

    /* Find maximum frequency */
    int max_freq = 1, cur_freq = 1;
    for (int i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            cur_freq++;
            if (cur_freq > max_freq) max_freq = cur_freq;
        } else {
            cur_freq = 1;
        }
    }

    /* Collect all values that appear max_freq times */
    int *modes = malloc(n * sizeof(int));
    int count = 0;
    cur_freq = 1;
    for (int i = 1; i <= n; i++) {
        if (i < n && sorted[i] == sorted[i - 1]) {
            cur_freq++;
        } else {
            if (cur_freq == max_freq) {
                modes[count++] = sorted[i - 1];
            }
            cur_freq = 1;
        }
    }

    free(sorted);
    *out_count = count;
    return modes;
}

/* --- Main --- */
int main(void) {
    int data[] = {4, 1, 2, 2, 3, 5, 3, 3, 7, 1};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Data: ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", data[i], i < n - 1 ? ", " : "\n");
    }

    printf("Mean:   %.2f\n", calculate_mean(data, n));
    printf("Median: %.2f\n", calculate_median(data, n));

    int mode_count;
    int *modes = calculate_mode(data, n, &mode_count);
    printf("Mode:   ");
    for (int i = 0; i < mode_count; i++) {
        printf("%d%s", modes[i], i < mode_count - 1 ? ", " : "\n");
    }
    free(modes);

    return 0;
}
