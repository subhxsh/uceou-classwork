#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
    int length;
};

struct LinkedList* create_list(void) {
    struct LinkedList* list = malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

struct Node* create_node(int value, struct Node* next) {
    struct Node* node = malloc(sizeof(struct Node));
    node->value = value;
    node->next = next;
    return node;
}

void insert_front(struct LinkedList* list, int value) {
    list->head = create_node(value, list->head);
    if (list->tail == NULL) list->tail = list->head;
    list->length++;
}

void insert_back(struct LinkedList* list, int value) {
    if (list->tail == NULL) list->head = list->tail = create_node(value, NULL);
    else list->tail = list->tail->next = create_node(value, NULL);
    list->length++;
}

void insert_at(struct LinkedList* list, int value, int index) {
    if (index <= 0) insert_front(list, value);
    else if (index >= list->length) insert_back(list, value);
    else {
        struct Node* temp_node = list->head;
        for (int i = 0; i < index - 1; i++)
            temp_node = temp_node->next;
        temp_node->next = create_node(value, temp_node->next);
        list->length++;
    }
}

void delete_front(struct LinkedList* list) {
    if (list->head == NULL) return;
    struct Node* temp_node = list->head;
    list->head = list->head->next;
    free(temp_node);
    if (list->head == NULL) list->tail = NULL;
    list->length--;
}

void delete_back(struct LinkedList* list) {
    if (list->head == NULL) return;
    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        struct Node* temp_node = list->head;
        while (temp_node->next != list->tail)
            temp_node = temp_node->next;
        free(temp_node->next);
        temp_node->next = NULL;
        list->tail = temp_node;
    }
    list->length--;
}

void reverse_list(struct LinkedList* list) {
    if (list->head == list->tail) return;
    struct Node* prev_node = NULL;
    struct Node* curr_node = list->tail = list->head;
    while (curr_node != NULL) {
        struct Node* next = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next;
    }
    list->head = prev_node;
}

void destroy_list(struct LinkedList* list) {
    struct Node* temp_node = list->head;
    while (temp_node != NULL) {
        struct Node* next = temp_node->next;
        free(temp_node);
        temp_node = next;
    }
    free(list);
}

void display_list(struct LinkedList* list) {
    printf("list: ");
    if (list->head == NULL) printf("<empty>\n");
    else {
        struct Node* temp_node = list->head;
        while (temp_node->next != NULL) {
            printf("%d -> ", temp_node->value);
            temp_node = temp_node->next;
        }
        printf("%d\nvalue(head): %d\nvalue(tail): %d\n", temp_node->value, list->head->value, list->tail->value);
    }
    printf("length: %d\n", list->length);
}

void clear_screen(void) {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
    #endif

    #if defined(_WIN32)
    system("cls");
    #endif
}

int main(void) {
    clear_screen();
    struct LinkedList* list = create_list();
    int option, value, index = 0;
    do {
        display_list(list);
        printf("\n=== Linked List Operations ===\n\n1. Insert at front\n2. Insert at back\n3. Insert at index\n4. Delete from front\n5. Delete from back\n6. Reverse list\n7. Reset list\n8. Exit\n\nEnter choice: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_front(list, value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insert_back(list, value);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter index: ");
                scanf("%d", &index);
                insert_at(list, value, index);
                break;
            case 4:
                delete_front(list);
                break;
            case 5:
                delete_back(list);
                break;
            case 6:
                reverse_list(list);
                break;
            case 7:
                destroy_list(list);
                list = create_list();
                break;
            case 8:
                destroy_list(list);
                break;
            default:
                break;
        }
        clear_screen();
    } while (option != 8);
    return 0;
}
