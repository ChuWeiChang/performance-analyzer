#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct list_node {
    int val;
    struct list_node *next;
};

struct list_node *middle_node_twopass(struct list_node *head) {
    struct list_node *cur = head;
    int n = 0;
    while (cur) {
        ++n;
        cur = cur->next;
    }
    int k = 0;
    cur = head;
    while (k < n / 2) {
        ++k;
        cur = cur->next;
    }
    return cur;
}

struct list_node *middle_node_onepass(struct list_node *head) {
    struct list_node *slow, *fast;
    slow = fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct list_node* create_list(int length) {
    if (length <= 0) return NULL;
    struct list_node *head = malloc(sizeof(struct list_node));
    head->val = 0;
    
    struct list_node *cur = head;
    for (int i = 1; i < length; i++) {
        cur->next = malloc(sizeof(struct list_node));
        cur = cur->next;
        cur->val = i;
    }
    cur->next = NULL;
    return head;
}

struct list_node* shuffle_list(struct list_node *head, int length) {
    if (length <= 1 || head == NULL) return head;

    struct list_node **pointers = malloc(length * sizeof(struct list_node*));
    if (!pointers) return head; 

    struct list_node *temp = head;
    for (int i = 0; i < length; i++) {
        pointers[i] = temp;
        temp = temp->next;
    }

    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct list_node *t = pointers[i];
        pointers[i] = pointers[j];
        pointers[j] = t;
    }

    for (int i = 0; i < length - 1; i++) {
        pointers[i]->next = pointers[i + 1];
    }
    pointers[length - 1]->next = NULL;
    
    struct list_node *new_head = pointers[0];
    free(pointers);

    return new_head;
}

void free_list(struct list_node *head) {
    struct list_node *cur = head;
    while (cur) {
        struct list_node *next = cur->next;
        free(cur);
        cur = next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <mode> <length>\n", argv[0]);
        printf("Mode 0: Two-pass\n");
        printf("Mode 1: One-pass\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    int length = atoi(argv[2]);
    int iterations = 1000; 

    srand(time(NULL));

    struct list_node *head = create_list(length);

    head = shuffle_list(head, length);

    struct list_node *mid = NULL;

    for (int i = 0; i < iterations; i++) {
        if (mode == 0) {
            mid = middle_node_twopass(head);
        } else if (mode == 1) {
            mid = middle_node_onepass(head);
        }
    }
    if (mid) {
        volatile int dummy = mid->val; 
    }
    free_list(head);
    return 0;
}