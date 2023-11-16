#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[100];
    char author[100];
    int isIssued; // 0 for not issued, 1 for issued
};

struct Library {
    struct Book books[MAX_BOOKS];
    int numBooks;
    int numIssuedBooks;
};

void addBook(struct Library *library);
void showBooks(struct Library *library);
void deleteBook(struct Library *library);
void sortBooks(struct Library *library);
void searchBook(struct Library *library);
void totalBooks(struct Library *library);
void totalIssuedBooks(struct Library *library);
void issueBook(struct Library *library);
void returnBook(struct Library *library);
void clearInputBuffer();

int main() {
    struct Library library;
    library.numBooks = 0;
    library.numIssuedBooks = 0;

    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Show All Books\n");
        printf("3. Delete Book\n");
        printf("4. Sort Books\n");
        printf("5. Search Book\n");
        printf("6. Total Books\n");
        printf("7. Total Issued Books\n");
        printf("8. Issue Book\n");
        printf("9. Return Book\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                showBooks(&library);
                break;
            case 3:
                deleteBook(&library);
                break;
            case 4:
                sortBooks(&library);
                break;
            case 5:
                searchBook(&library);
                break;
            case 6:
                totalBooks(&library);
                break;
            case 7:
                totalIssuedBooks(&library);
                break;
            case 8:
                issueBook(&library);
                break;
            case 9:
                returnBook(&library);
                break;
            case 10:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 10);

    return 0;
}

void addBook(struct Library *library) {
    if (library->numBooks < MAX_BOOKS) {
        printf("Enter book title: ");
        clearInputBuffer();
        fgets(library->books[library->numBooks].title, sizeof(library->books[library->numBooks].title), stdin);
        strtok(library->books[library->numBooks].title, "\n"); // remove newline character

        printf("Enter author: ");
        fgets(library->books[library->numBooks].author, sizeof(library->books[library->numBooks].author), stdin);
        strtok(library->books[library->numBooks].author, "\n"); // remove newline character

        library->books[library->numBooks].isIssued = 0; // Book is not issued initially

        library->numBooks++;
        printf("Book added successfully!\n");
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}

void showBooks(struct Library *library) {
    if (library->numBooks == 0) {
        printf("No books available.\n");
    } else {
        printf("All Books:\n");
        for (int i = 0; i < library->numBooks; ++i) {
            printf("%s by %s - %s\n", library->books[i].title, library->books[i].author,
                   (library->books[i].isIssued ? "Issued" : "Available"));
        }
    }
}

void deleteBook(struct Library *library) {
    char title[100];
    int found = 0;

    printf("Enter the title of the book to delete: ");
    clearInputBuffer();
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n"); // remove newline character

    for (int i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, title) == 0) {
            found = 1;
            for (int j = i; j < library->numBooks - 1; ++j) {
                library->books[j] = library->books[j + 1];
            }
            library->numBooks--;
            printf("Book deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void sortBooks(struct Library *library) {
    // Bubble sort based on title
    for (int i = 0; i < library->numBooks - 1; ++i) {
        for (int j = 0; j < library->numBooks - i - 1; ++j) {
            if (strcmp(library->books[j].title, library->books[j + 1].title) > 0) {
                // Swap
                struct Book temp = library->books[j];
                library->books[j] = library->books[j + 1];
                library->books[j + 1] = temp;
            }
        }
    }

    printf("Books sorted successfully!\n");
}

void searchBook(struct Library *library) {
    char title[100];
    char author[100];
    int found = 0;

    printf("Enter book title: ");
    clearInputBuffer();
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n"); // remove newline character

    printf("Enter author: ");
    fgets(author, sizeof(author), stdin);
    strtok(author, "\n"); // remove newline character

    for (int i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, title) == 0 && strcmp(library->books[i].author, author) == 0) {
            found = 1;
            printf("Book Found: %s by %s - %s\n", library->books[i].title, library->books[i].author,
                   (library->books[i].isIssued ? "Issued" : "Available"));
            break;
        }
    }

    if (!found) {
        printf("No matching book found.\n");
    }
}

void totalBooks(struct Library *library) {
    printf("Total number of books: %d\n", library->numBooks);
}

void totalIssuedBooks(struct Library *library) {
    printf("Total number of issued books: %d\n", library->numIssuedBooks);
}

void issueBook(struct Library *library) {
    char title[100];
    int found = 0;

    printf("Enter the title of the book to issue: ");
    clearInputBuffer();
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n"); // remove newline character

    for (int i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, title) == 0) {
            found = 1;
            if (library->books[i].isIssued) {
                printf("Book is already issued.\n");
            } else {
                library->books[i].isIssued = 1;
                library->numIssuedBooks++;
                printf("Book issued successfully!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void returnBook(struct Library *library) {
    char title[100];
    int found = 0;

    printf("Enter the title of the book to return: ");
    clearInputBuffer();
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n"); // remove newline character

    for (int i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, title) == 0) {
            found = 1;
            if (library->books[i].isIssued) {
                library->books[i].isIssued = 0;
                library->numIssuedBooks--;
                printf("Book returned successfully!\n");
            } else {
                printf("Book is not issued.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void clearInputBuffer() {
    while (getchar() != '\n');
}