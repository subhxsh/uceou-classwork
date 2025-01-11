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

struct LinkedList* create_list() {
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

    if (list->tail == NULL)
        list->tail = list->head;

    list->length++;
}

void insert_back(struct LinkedList* list, int value) {
    if (list->head == NULL) {
        insert_front(list, value);
        return;
    }

    list->tail->next = create_node(value, NULL);
    list->tail = list->tail->next;
    list->length++;
}

void insert_at(struct LinkedList* list, int value, int index) {
    if (index <= 0) {
        insert_front(list, value);
    }
    else if (index >= list->length) {
        insert_back(list, value);
    }
    else {
        struct Node* temp_node = list->head;

        for (int i = 0; i < index - 1; i++)
            temp_node = temp_node->next;

        temp_node->next = create_node(value, temp_node->next);
        list->length++;
    }
}

void delete_front(struct LinkedList* list) {
    if (list->head == NULL)
        return;
    
    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
        list->length--;
        return;
    }

    struct Node* next = list->head->next;
    free(list->head);
    list->head = next;
    list->length--;
}

void delete_back(struct LinkedList* list) {
    if (list->head == NULL)
        return;

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
        list->length--;
        return;
    }

    struct Node* temp_node = list->head;
    while (temp_node->next != list->tail)
        temp_node = temp_node->next;
    
    free(temp_node->next);
    temp_node->next = NULL;
    list->tail = temp_node;
    list->length--;
}

void reverse_list(struct LinkedList* list) {
    if (list->head == list->tail) return;

    struct Node* head_node = list->head;
    list->head = list->tail;
    list->tail = head_node;

    struct Node* prev_node = NULL;
    struct Node* curr_node = head_node;

    while (curr_node != NULL) {
        struct Node* next = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next;
    }
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
    if (list == NULL || list->head == NULL) return;

    struct Node* temp_node = list->head;

    while (temp_node->next != NULL) {
        printf("%d -> ", temp_node->value);
        temp_node = temp_node->next;
    }

    printf("%d\n", temp_node->value);
    printf("value(head) = %d\n", list->head->value);
    printf("value(tail) = %d\n", list->tail->value);
    printf("length = %d\n", list->length);
}

int main(void) {
    struct LinkedList* list = create_list();
    insert_front(list, 10);
    insert_front(list, 20);
    insert_front(list, 30);
    insert_back(list, 40);
    insert_back(list, 50);
    insert_at(list, 60, 2);
    insert_back(list, 100);
    insert_front(list, 200);
    delete_front(list);
    delete_back(list);
    reverse_list(list);
    display_list(list);
    destroy_list(list);
    return 0;
}