#include <stdio.h>

int main() {
    int total, n, b;

    printf("Enter total disk blocks: ");
    scanf("%d", &total);

    int blk[total];  // 0 = free, 1 = allocated
    for (int i = 0; i < total; i++)
        blk[i] = 0;

    printf("Enter number of blocks to allocate: ");
    scanf("%d", &n);

    int index[n];

    for (int i = 0; i < n; i++) {
        printf("Enter block number: ");
        scanf("%d", &b);

        if (b >= total || b < 0 || blk[b]) {
            printf("Block not free!\n");
            i--;
            continue;
        }

        blk[b] = 1;
        index[i] = b;
        printf("Block %d allocated.\n", b);
    }

    printf("\nIndexed Allocation Table: ");
    for (int i = 0; i < n; i++)
        printf("%d ", index[i]);
    printf("\n");

    printf("\nBlock Status:\n");
  
  
  for (int i = 0; i < total; i++) {
    if (blk[i] == 1)
        printf("Block %d is Allocated\n", i);
    else
        printf("Block %d is Free\n", i);
}

    int read;
    while (1) {
        printf("\nEnter block to read (-1 to stop): ");
        scanf("%d", &read);
        if (read == -1) break;

        int found = 0;
        for (int i = 0; i < n; i++)
            if (index[i] == read) found = 1;

        if (found)
            printf("Block %d is allocated.\n", read);
        else
            printf("Block %d is not allocated.\n", read);
    }

    return 0;
}
