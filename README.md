### 1. Struktur Node
```c
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
```
Struct `Node` mendefinisikan node dalam sirkular double linked list, yang memiliki:
- `data`: nilai integer yang disimpan dalam node.
- `next`: pointer ke node berikutnya.
- `prev`: pointer ke node sebelumnya.

### 2. Fungsi untuk Membuat Node Baru
```c
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode; // Circular link
    return newNode;
}
```
Fungsi `createNode`:
- Menerima nilai `data`.
- Mengalokasikan memori untuk node baru.
- Menginisialisasi `data` dengan nilai yang diterima.
- Menetapkan `next` dan `prev` dari node baru menunjuk ke dirinya sendiri untuk membuatnya sirkular.

### 3. Fungsi untuk Mencetak List
```c
void printList(Node* head) {
    if (!head) return;

    Node* temp = head;
    do {
        printf("Address: %p, Data: %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}
```
Fungsi `printList`:
- Mencetak alamat memori dan data dari setiap node dalam list.
- Jika list kosong, fungsi segera kembali.
- Menggunakan `do-while` loop untuk menelusuri list dan mencetak setiap node hingga kembali ke `head`.

### 4. Fungsi untuk Menambahkan Node ke List
```c
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
```
Fungsi `insertEnd`:
- Menerima pointer ke pointer `head` dan nilai `data`.
- Membuat node baru dengan data tersebut.
- Jika list kosong, node baru menjadi `head`.
- Jika list tidak kosong, node baru ditambahkan di akhir list, dan pointer `next` serta `prev` diperbarui untuk menjaga sirkularitas.

### 5. Fungsi untuk Mengurutkan List
```c
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
```
Fungsi `sortList`:
- Mengurutkan node dalam list secara ascending dengan hanya mengubah posisi data.
- Jika list kosong atau hanya berisi satu node, fungsi segera kembali.
- Menggunakan dua pointer (`current` dan `index`) untuk menelusuri list dan membandingkan data di antara node.
- Jika data di `current` lebih besar dari data di `index`, data ditukar.
- Loop berlanjut hingga seluruh list diurutkan.

### 6. Fungsi Utama
```c
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
```
Fungsi `main`:
- Meminta pengguna untuk memasukkan jumlah data (`N`).
- Menginput data ke dalam list.
- Mencetak list sebelum pengurutan.
- Mengurutkan list dengan fungsi `sortList`.
- Mencetak list setelah pengurutan.
- Membebaskan memori yang dialokasikan untuk node sebelum program berakhir.

Dengan program ini, pengguna dapat menginput data ke dalam sirkular double linked list, melihat list sebelum dan sesudah pengurutan, dan memastikan bahwa posisi node diubah tanpa memanipulasi data dalam node.
