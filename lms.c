#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BOOKS 100
#define TITLE_LEN 100
#define AUTHOR_LEN 100
#define BORROWER_LEN 50
#define DUE_DATE_LEN 20

typedef struct {
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int issued;
    char borrower[BORROWER_LEN];
    char dueDate[DUE_DATE_LEN];
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
    int issuedCount;
} Library;

void toTitleCase(char *str);
void clearInput();
void add(Library *lib);
void display(const Library *lib);
void removeBook(Library *lib);
void sort(Library *lib);
void find(const Library *lib);
void showTotal(const Library *lib);
void showIssued(const Library *lib);
void borrow(Library *lib);
void returnBook(Library *lib);
void saveLibrary(const Library *lib, const char *filename);
void loadLibrary(Library *lib, const char *filename);
void displayIssued(const Library *lib);
void displayAvailable(const Library *lib);

int main() {
    Library lib = {0};
    int choice;
    char filename[] = "library.dat";

    loadLibrary(&lib, filename);

    do {
        printf("\nLibrary System\n"
               "1. Add Book\n2. Display Books\n3. Remove Book\n"
               "4. Sort Books\n5. Find Book\n6. Total Books\n"
               "7. Issued Books\n8. Borrow Book\n9. Return Book\n"
               "10. Exit\n11. Save Library\n12. Display Issued Books\n13. Display Available Books\nChoice: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: add(&lib); break;
            case 2: display(&lib); break;
            case 3: removeBook(&lib); break;
            case 4: sort(&lib); break;
            case 5: find(&lib); break;
            case 6: showTotal(&lib); break;
            case 7: showIssued(&lib); break;
            case 8: borrow(&lib); break;
            case 9: returnBook(&lib); break;
            case 10: printf("Exiting...\n"); break;
            case 11: saveLibrary(&lib, filename); break;
            case 12: displayIssued(&lib); break;
            case 13: displayAvailable(&lib); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 10);

    return 0;
}

void add(Library *lib) {
    if (lib->count >= MAX_BOOKS) {
        printf("Library is full.\n");
        return;
    }
    Book *book = &lib->books[lib->count];
    printf("Title: ");
    fgets(book->title, TITLE_LEN, stdin);
    book->title[strcspn(book->title, "\n")] = 0;
    toTitleCase(book->title);

    printf("Author: ");
    fgets(book->author, AUTHOR_LEN, stdin);
    book->author[strcspn(book->author, "\n")] = 0;
    toTitleCase(book->author);

    book->issued = 0;
    memset(book->borrower, 0, sizeof(book->borrower));
    memset(book->dueDate, 0, sizeof(book->dueDate));
    lib->count++;
    printf("Book added.\n");
}

void display(const Library *lib) {
    if (lib->count == 0) {
        printf("No books.\n");
        return;
    }
    printf("Books:\n");
    for (int i = 0; i < lib->count; i++) {
        printf("%s by %s - %s", lib->books[i].title, lib->books[i].author, lib->books[i].issued ? "Issued" : "Available");
        if(lib->books[i].issued){
            printf(" - Borrower: %s, Due: %s\n", lib->books[i].borrower, lib->books[i].dueDate);
        } else {
            printf("\n");
        }
    }
}

void removeBook(Library *lib) {
    char title[TITLE_LEN];
    printf("Title to remove: ");
    fgets(title, TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    toTitleCase(title);

    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->books[i].title, title) == 0) {
            if (lib->books[i].issued) {
                lib->issuedCount--;
            }
            memmove(&lib->books[i], &lib->books[i + 1], (lib->count - i - 1) * sizeof(Book));
            lib->count--;
            printf("Book removed.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void sort(Library *lib) {
    for (int i = 0; i < lib->count - 1; i++) {
        for (int j = 0; j < lib->count - i - 1; j++) {
            if (strcmp(lib->books[j].title, lib->books[j + 1].title) > 0) {
                Book temp = lib->books[j];
                lib->books[j] = lib->books[j + 1];
                lib->books[j + 1] = temp;
            }
        }
    }
    printf("Books sorted.\n");
}

void find(const Library *lib) {
    char title[TITLE_LEN], author[AUTHOR_LEN];
    printf("Title: ");
    fgets(title, TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    toTitleCase(title);

    printf("Author: ");
    fgets(author, AUTHOR_LEN, stdin);
    author[strcspn(author, "\n")] = 0;
    toTitleCase(author);

    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->books[i].title, title) == 0 && strcmp(lib->books[i].author, author) == 0) {
            printf("Found: %s by %s - %s", lib->books[i].title, lib->books[i].author, lib->books[i].issued ? "Issued" : "Available");
            if(lib->books[i].issued){
                printf(" - Borrower: %s, Due: %s\n", lib->books[i].borrower, lib->books[i].dueDate);
            } else {
                printf("\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void showTotal(const Library *lib) {
    printf("Total books: %d\n", lib->count);
}

void showIssued(const Library *lib) {
    printf("Issued books: %d\n", lib->issuedCount);
}

void borrow(Library *lib) {
    char title[TITLE_LEN];
    printf("Title to borrow: ");
    fgets(title, TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    toTitleCase(title);

    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->books[i].title, title) == 0) {
            if (lib->books[i].issued) {
                printf("Book already issued.\n");
            } else {
                lib->books[i].issued = 1;
                lib->issuedCount++;
                printf("Borrower Name: ");
                fgets(lib->books[i].borrower, BORROWER_LEN, stdin);
                lib->books[i].borrower[strcspn(lib->books[i].borrower, "\n")] = 0;
                printf("Due Date (YYYY-MM-DD): ");
                fgets(lib->books[i].dueDate, DUE_DATE_LEN, stdin);
                lib
