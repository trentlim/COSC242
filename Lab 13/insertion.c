static void insertion_sort(int *a, int n)
{
    int p, key, left, i;

    for (p = 1; p < n; p++) {
        key = a[p];
        left = p - 1;

        if (p == n/2){
            for (i = 0; i < n; i++){
                fprintf(stderr,"%d\n", a[i]);
            }
        }

        while (left >= 0 && a[left] > key) {
            a[left + 1] = a[left];
            left --;
        }
        a[left + 1] = key;
    }
}
