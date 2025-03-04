#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define TITLE_LEN 100
#define AUTHOR_LEN 100

typedef struct {
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int issued;
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

int main() {
    Library lib = {0};
    int choice;

    do {
        printf("\nLibrary System\n"
               "1. Add Book\n2. Display Books\n3. Remove Book\n"
               "4. Sort Books\n5. Find Book\n6. Total Books\n"
               "7. Issued Books\n8. Borrow Book\n9. Return Book\n"
               "10. Exit\nChoice: ");
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
        printf("%s by %s - %s\n", lib->books[i].title, lib->books[i].author,
               lib->books[i].issued ? "Issued" : "Available");
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
            if(lib->books[i].issued){
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
            printf("Found: %s by %s - %s\n", lib->books[i].title, lib->books[i].author,
                   lib->books[i].issued ? "Issued" : "Available");
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
                printf("Book borrowed.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void returnBook(Library *lib) {
    char title[TITLE_LEN];
    printf("Title to return: ");
    fgets(title, TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = 0;
    toTitleCase(title);

    for (int i = 0; i < lib->count; i++) {
        if (strcmp(lib->books[i].title, title) == 0) {
            if (lib->books[i].issued) {
                lib->books[i].issued = 0;
                lib->issuedCount--;
                printf("Book returned.\n");
            } else {
                printf("Book is not issued.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void toTitleCase(char *str) {
    int capitalize = 1;
    for (int i = 0; str[i]; i++) {
        if (isspace(str[i])) {
            capitalize = 1;
        } else if (capitalize) {
            str[i] = toupper(str[i]);
            capitalize = 0;
        } else {
            str[i] = tolower(str[i]);
        }
    }
}
