#include <stdio.h>

int main() {
    int n, total;
    printf("Enter total disk blocks: ");
    scanf("%d", &total);

    int blk[total];
    for (int i = 0; i < total; i++)
        blk[i] = 0;  // all blocks free

    printf("Enter number of files: ");
    scanf("%d", &n);

    char name[20];
    int start, len;

    for (int i = 0; i < n; i++) {
        printf("\nFile name: ");
        scanf("%s", name);
        printf("Start block: ");
        scanf("%d", &start);
        printf("No. of blocks: ");
        scanf("%d", &len);

        printf("%s -> Blocks: ", name);

        for (int j = start; j < start + len && j < total; j++) {
            if (blk[j] == 0) {
                blk[j] = 1;   // allocate the block
                printf("%d ", j);
            } else {
                printf("\nBlock %d already allocated!", j);
            }
        }
        printf("\n");
    }

    printf("\n--- Disk Block Status ---\n");
    for (int i = 0; i < total; i++) {
        if (blk[i] == 1)
            printf("Block %d: Allocated\n", i);
        else
            printf("Block %d: Free\n", i);
    }

    return 0;
}
