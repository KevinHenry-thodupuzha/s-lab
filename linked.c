#include <stdio.h>
#include <stdlib.h>

struct Block {
    int data;
    struct Block *next;
};

int main() {
    int total, n, b;
    printf("Enter total disk blocks: ");
    scanf("%d", &total);

    int blk[total];
    for (int i = 0; i < total; i++) blk[i] = 0;  // all blocks free

    printf("Enter number of blocks to allocate: ");
    scanf("%d", &n);

    struct Block *head = NULL, *tail = NULL, *newBlock;

    for (int i = 0; i < n; i++) {
        printf("Enter block number: ");
        scanf("%d", &b);

        if (b < 0 || b >= total || blk[b]) {
            printf("Block not free!\n");
            i--;
            continue;
        }

        blk[b] = 1;
        newBlock = malloc(sizeof(struct Block));
        newBlock->data = b;
        newBlock->next = NULL;

        if (head == NULL)
            head = tail = newBlock;
        else {
            tail->next = newBlock;  // add new block at end
            tail = newBlock;        // update tail
        }
    }

    printf("\nLinked Allocation: ");
    for (newBlock = head; newBlock; newBlock = newBlock->next)
        printf("%d -> ", newBlock->data);
    printf("NULL\n");

    printf("\nBlock Status:\n");
    for (int i = 0; i < total; i++) {
        if (blk[i] == 1)
            printf("Block %d: Allocated\n", i);
        else
            printf("Block %d: Free\n", i);
    }

    return 0;
}
