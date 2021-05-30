static void selection_sort(int *a, int n){
    int p = 0, key = 0, smallest = 0, temp = 0, i;

    for (p = 0; p < n-1; p++){
        smallest = p;

        if (p == n/2){
            for (i = 0; i < n; i++){
                fprintf(stderr,"%d\n", a[i]);
            }
        }

        for (key = p+1; key < n; key++){
            if (a[key] < a[smallest]){
                smallest = key;
            }
        }
        temp = a[smallest];
        a[smallest] = a[p];
        a[p] = temp;
    }
}
