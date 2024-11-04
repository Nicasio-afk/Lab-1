#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

list_t *list_alloc() { 
    list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
    mylist->head = NULL;  // Initialize head to NULL
    return mylist;        // Return the allocated list
}

void list_free(list_t *l) {
    node_t* curr = l->head;
    node_t* next_node;

    // Traverse the list and free each node
    while (curr != NULL) {
        next_node = curr->next;  // Save the next node
        free(curr);              // Free the current node
        curr = next_node;        // Move to the next node
    }

    // After freeing all nodes, set the list's head to NULL
    l->head = NULL;
}

void list_print(list_t *l) {
    node_t* curr = l->head;

    // Traverse the list and print each element
    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }

    // Print the null terminator at the end
    printf("NULL\n");
}

char *listToString(list_t *l) {
    char* buf = (char *) malloc(sizeof(char) * 1024);
    buf[0] = '\0';  // Initialize the buffer to an empty string
    char tbuf[20];

    node_t* curr = l->head;
    while (curr != NULL) {
        sprintf(tbuf, "%d->", curr->value);
        curr = curr->next;
        strcat(buf, tbuf);
    }
    strcat(buf, "NULL");
    return buf;
}

int list_length(list_t *l) {
    int count = 0;
    node_t* curr = l->head;

    // Traverse the list and count the nodes
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    return count;
}

void list_add_to_back(list_t *l, elem value) {
    // Create a new node
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;

    // If the list is empty, the new node becomes the head
    if (l->head == NULL) {
        l->head = new_node;
        return;
    }

    // Traverse to the last node
    node_t* curr = l->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // Attach the new node to the last node
    curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
    // Allocate memory for the new node
    node_t* cur_node = (node_t *) malloc(sizeof(node_t));
    cur_node->value = value;

    // Set the new node's next pointer to the current head
    cur_node->next = l->head;

    // Update the list's head to be the new node
    l->head = cur_node;
}

node_t* create_node(elem value) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
    node_t* new_node = create_node(value);
    if (index == 0) {
        new_node->next = l->head;
        l->head = new_node;
        return;
    }

    node_t* curr = l->head;
    int i;  // Declare the loop variable outside
    for (i = 0; i < index - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Index out of bounds\n");
        free(new_node);
        return;
    }

    new_node->next = curr->next;
    curr->next = new_node;
}

// Remove a node from the back of the list
elem list_remove_from_back(list_t *l) {
    if (l->head == NULL) {
        printf("List is empty\n");
        return -1;  // Special error value
    }

    node_t* curr = l->head;
    if (curr->next == NULL) {  // Only one element
        elem val = curr->value;
        free(curr);
        l->head = NULL;
        return val;
    }

    node_t* prev = NULL;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    elem val = curr->value;
    prev->next = NULL;
    free(curr);
    return val;
}

// Remove a node from the front of the list
elem list_remove_from_front(list_t *l) {
    if (l->head == NULL) {
        printf("List is empty\n");
        return -1;
    }

    node_t* to_remove = l->head;
    elem val = to_remove->value;
    l->head = l->head->next;
    free(to_remove);
    return val;
}

// Remove a node at a specific index
elem list_remove_at_index(list_t *l, int index) {
    if (l->head == NULL) {
        printf("List is empty\n");
        return -1;
    }

    if (index == 0) {
        return list_remove_from_front(l);
    }

    node_t* curr = l->head;
    node_t* prev = NULL;
    int i;  // Declare the loop variable outside
    for (i = 0; i < index && curr != NULL; i++) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Index out of bounds\n");
        return -1;
    }

    elem val = curr->value;
    prev->next = curr->next;
    free(curr);
    return val;
}

// Check if a value is in the list
bool list_is_in(list_t *l, elem value) {
    node_t* curr = l->head;
    while (curr != NULL) {
        if (curr->value == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Get the element at a specific index
elem list_get_elem_at(list_t *l, int index) {
    node_t* curr = l->head;
    int i;  // Declare the loop variable outside
    for (i = 0; i < index && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Index out of bounds\n");
        return -1;
    }

    return curr->value;
}

// Get the index of a value in the list
int list_get_index_of(list_t *l, elem value) {
    node_t* curr = l->head;
    int index = 0;
    while (curr != NULL) {
        if (curr->value == value) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;  // Return -1 if value is not found
}