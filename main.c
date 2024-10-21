#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Customer Node (Linked List)
typedef struct Customer {
    char name[100];
    char book_rented[100];
    int return_period;
    struct Customer *next;
} Customer;

// Define Book Node (Double Linked List)
typedef struct Book {
    char name[100];
    char author[100];
    int shelf_no;
    float price;
    struct Book *prev;
    struct Book *next;
} Book;

// Define Book Node (Binary Search Tree)
typedef struct BookNode {
    char name[100];
    char author[100];
    int shelf_no;
    float price;
    struct BookNode *left;
    struct BookNode *right;
} BookNode;

// Function declarations
Customer* addCustomer(Customer *head, char *name, char *book_rented, int return_period);
Customer* deleteCustomer(Customer *head, char *name);
void displayCustomers(Customer *head);
Book* addBook(Book *head, char *name, char *author, int shelf_no, float price);
Book* deleteBook(Book *head, char *name);
void displayBooks(Book *head);
BookNode* insertBookNode(BookNode *root, char *name, char *author, int shelf_no, float price);
BookNode* deleteBookNode(BookNode *root, char *name);
void displayBookTree(BookNode *root);
BookNode* searchBook(BookNode *root, char *name);
void displayMenu(Customer **customerList, Book **bookList, BookNode **bookTree);

int main() {
    Customer *customerList = NULL;
    Book *bookList = NULL;
    BookNode *bookTree = NULL;

    displayMenu(&customerList, &bookList, &bookTree);

    return 0;
}

// Function to display the interactive menu
void displayMenu(Customer **customerList, Book **bookList, BookNode **bookTree) {
    int choice;
    char name[100], author[100], book_rented[100];
    int return_period, shelf_no;
    float price;

    while (1) {
        printf("\n---- Library Management System ----\n");
        printf("1. Add Customer\n");
        printf("2. Delete Customer\n");
        printf("3. Display Customers\n");
        printf("4. Add Book (Double Linked List)\n");
        printf("5. Delete Book (Double Linked List)\n");
        printf("6. Display Books (Double Linked List)\n");
        printf("7. Add Book (Binary Search Tree)\n");
        printf("8. Delete Book (Binary Search Tree)\n");
        printf("9. Display Books (Binary Search Tree)\n");
        printf("10. Search Book (Binary Search Tree)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                printf("Enter book rented: ");
                fgets(book_rented, 100, stdin);
                book_rented[strcspn(book_rented, "\n")] = '\0'; // Remove newline character
                printf("Enter return period (in days): ");
                scanf("%d", &return_period);
                *customerList = addCustomer(*customerList, name, book_rented, return_period);
                break;
            case 2:
                printf("Enter customer name to delete: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                *customerList = deleteCustomer(*customerList, name);
                break;
            case 3:
                displayCustomers(*customerList);
                break;
            case 4:
                printf("Enter book name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                printf("Enter author name: ");
                fgets(author, 100, stdin);
                author[strcspn(author, "\n")] = '\0'; // Remove newline character
                printf("Enter shelf number: ");
                scanf("%d", &shelf_no);
                printf("Enter price: ");
                scanf("%f", &price);
                *bookList = addBook(*bookList, name, author, shelf_no, price);
                break;
            case 5:
                printf("Enter book name to delete: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                *bookList = deleteBook(*bookList, name);
                break;
            case 6:
                displayBooks(*bookList);
                break;
            case 7:
                printf("Enter book name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                printf("Enter author name: ");
                fgets(author, 100, stdin);
                author[strcspn(author, "\n")] = '\0'; // Remove newline character
                printf("Enter shelf number: ");
                scanf("%d", &shelf_no);
                printf("Enter price: ");
                scanf("%f", &price);
                *bookTree = insertBookNode(*bookTree, name, author, shelf_no, price);
                break;
            case 8:
                printf("Enter book name to delete: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                *bookTree = deleteBookNode(*bookTree, name);
                break;
            case 9:
                displayBookTree(*bookTree);
                break;
            case 10:
                printf("Enter book name to search: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                BookNode *foundBook = searchBook(*bookTree, name);
                if (foundBook) {
                    printf("Book Found: %s by %s, Shelf No: %d, Price: %.2f\n", foundBook->name, foundBook->author, foundBook->shelf_no, foundBook->price);
                } else {
                    printf("Book not found.\n");
                }
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Customer operations

Customer* addCustomer(Customer *head, char *name, char *book_rented, int return_period) {
    Customer *newCustomer = (Customer*)malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->book_rented, book_rented);
    newCustomer->return_period = return_period;
    newCustomer->next = head;
    return newCustomer;
}

Customer* deleteCustomer(Customer *head, char *name) {
    Customer *temp = head, *prev = NULL;
    if (temp != NULL && strcmp(temp->name, name) == 0) {
        head = temp->next;
        free(temp);
        return head;
    }
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return head;
    prev->next = temp->next;
    free(temp);
    return head;
}

void displayCustomers(Customer *head) {
    Customer *temp = head;
    while (temp != NULL) {
        printf("Name: %s, Book Rented: %s, Return Period: %d days\n", temp->name, temp->book_rented, temp->return_period);
        temp = temp->next;
    }
}

// Book operations (Double Linked List)

Book* addBook(Book *head, char *name, char *author, int shelf_no, float price) {
    Book *newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->name, name);
    strcpy(newBook->author, author);
    newBook->shelf_no = shelf_no;
    newBook->price = price;
    newBook->next = head;
    newBook->prev = NULL;
    if (head != NULL) {
        head->prev = newBook;
    }
    return newBook;
}

Book* deleteBook(Book *head, char *name) {
    Book *temp = head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) return head;
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    return head;
}

void displayBooks(Book *head) {
    Book *temp = head;
    while (temp != NULL) {
        printf("Book Name: %s, Author: %s, Shelf No: %d, Price: %.2f\n", temp->name, temp->author, temp->shelf_no, temp->price);
        temp = temp->next;
    }
}

// Book operations (Binary Search Tree)

BookNode* insertBookNode(BookNode *root, char *name, char *author, int shelf_no, float price) {
    if (root == NULL) {
        BookNode *newNode = (BookNode*)malloc(sizeof(BookNode));
        strcpy(newNode->name, name);
        strcpy(newNode->author, author);
        newNode->shelf_no = shelf_no;
        newNode->price = price;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insertBookNode(root->left, name, author, shelf_no, price);
    } else {
        root->right = insertBookNode(root->right, name, author, shelf_no, price);
    }
    return root;
}

BookNode* deleteBookNode(BookNode *root, char *name) {
    if (root == NULL) return root;
    if (strcmp(name, root->name) < 0) {
        root->left = deleteBookNode(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = deleteBookNode(root->right, name);
    } else {
        if (root->left == NULL) {
            BookNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BookNode *temp = root->left;
            free(root);
            return temp;
        }
        BookNode *temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        strcpy(root->name, temp->name);
        strcpy(root->author, temp->author);
        root->shelf_no = temp->shelf_no;
        root->price = temp->price;
        root->right = deleteBookNode(root->right, temp->name);
    }
    return root;
}

void displayBookTree(BookNode *root) {
    if (root != NULL) {
        displayBookTree(root->left);
        printf("Book Name: %s, Author: %s, Shelf No: %d, Price: %.2f\n", root->name, root->author, root->shelf_no, root->price);
        displayBookTree(root->right);
    }
}

BookNode* searchBook(BookNode *root, char *name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return searchBook(root->left, name);
    }
    return searchBook(root->right, name);
}
