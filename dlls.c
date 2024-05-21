#include <stdio.h>
#include <stdlib.h>

// Definisi struct untuk node dalam circular double linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Fungsi untuk membuat node baru
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode; // Circular link
    return newNode;
}

// Fungsi untuk mencetak list
void printList(Node* head) {
    if (!head) return;

    Node* temp = head;
    do {
        printf("Address: %p, Data: %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

// Fungsi untuk menambahkan node ke list
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
    } else {
        Node* tail = (*head)->prev;

        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

// Fungsi untuk mengurutkan list dengan hanya mengubah posisi node
void sortList(Node** head) {
    if (!*head || (*head)->next == *head) return;

    Node* current = *head;
    Node* index = NULL;
    int temp;

    do {
        index = current->next;
        while (index != *head) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    } while (current->next != *head);
}

int main() {
    int N, data;
    Node* head = NULL;

    // Input jumlah data
    printf("Masukkan jumlah data: ");
    scanf("%d", &N);

    // Input data ke dalam list
    printf("Masukkan %d data:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    // Cetak list sebelum pengurutan
    printf("List sebelum pengurutan:\n");
    printList(head);

    // Urutkan list
    sortList(&head);

    // Cetak list setelah pengurutan
    printf("List setelah pengurutan:\n");
    printList(head);

    // Bebaskan memori
    if (head) {
        Node* temp = head;
        do {
            Node* next = temp->next;
            free(temp);
            temp = next;
        } while (temp != head);
    }

    return 0;
}
