#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Structures of the Project
struct table {
  int length;
  struct registry* Next;  
};

struct registry {
    char id[4];
    char title[64];
    int qty;
    struct registry* Next;
};

// Supportive Functions
void Clear_Buffer() {
    int c;
    while ((c = getchar()) != '\n' && (c != EOF)) {}
}

void Clear_String(char* s) {
    if (strchr(s, '\n') == NULL) {
        Clear_Buffer();
    }
    else {
        s[strcspn(s, "\n")] = '\0';
    }
}

void New_Title(struct registry* current) {
    char title[64];

    printf("Type the new title\n>> ");
    fgets(title, sizeof(title), stdin);
    Clear_String(title);

    strcpy(current->title, title);
}

void New_Qty(struct registry* current) {
    char c[4];
    int new_qty;

    printf("Type the new quantity\n>> ");
    
    while (fgets(c, sizeof(c), stdin)) {
        Clear_String(c);

        if (sscanf(c, "%d", &new_qty) == 1) {
            break;
        }

        printf("The quantity must be a positive integer number... Try Again.\n\n");
        printf("Type the new quantity\n>> ");
    }

    current->qty = new_qty;
}

char* Generate_ID(struct table* table) {
    char* new_id = (char*) malloc(4 * sizeof(char));
    if (new_id == NULL) {
        printf("\n\nError: The Heap Failed\n\n");
        exit(1);
    }

    // Finding the next ID
    int n = 0;
    if (table->Next == NULL) {
        n = 1;
    }
    else {
        struct registry* current = table->Next;
        int cID;
        do {
            sscanf(current->id, "%d", &cID);
            if (cID >= n) {
                n = cID + 1;
            }

            current = current->Next;
        } while (current != NULL);
    }

    //Concatenating the new ID with the expected format
    char sNumber[4];
    snprintf(sNumber, sizeof(sNumber), "%d", n);

    for (int i = 0; i < 3; i++) {
        if (i < 3 - strlen(sNumber)) {
            *(new_id + i) = '0';
        }
        else {
            *(new_id + i) = *(sNumber + (i - (3 - strlen(sNumber))));
        }
    }

    *(new_id + 3) = '\0';
    return new_id;
}

// Primary Functions
void show_books(struct table* table) {
    if (table->Next == NULL) {
        printf("No data Found...\n\n");
        goto exit;
    }
    
    printf("ID | Title | QTY\n");
    struct registry* current_node = table->Next;
    do {
        printf("%s | %s | %d\n", current_node->id,
                                current_node->title,
                                current_node->qty);
        
        current_node = current_node->Next;
    } while(current_node != NULL);

    printf("\n");

    exit:
}

void Insert_book(struct table* table) {
    struct registry* new_book = (struct registry*) calloc(1, sizeof(struct registry));
    if (new_book == NULL) {
        printf("\n\nError: The Heap Failed\n\n");
        exit(1);
    }

    char* ptr = Generate_ID(table);
    strcpy(new_book->id, ptr);
    free(ptr);

    fflush(stdin);

    char c[64];
    printf("Type the Title of the Book\n>> ");
    fgets(c, sizeof(c), stdin);
    Clear_String(c);

    char qty[4];
    int fqty;

    printf("\nType the Quantity\n>> ");
    while (fgets(qty, sizeof(qty), stdin)) {
        Clear_String(qty);

        if ((sscanf(qty, "%d", &fqty) == 1) && fqty >= 0) {
            break;
        }
        else {
            system("cls");
            printf("\nYou must type a positive integer number... Try Again.\n");
            printf("\nType the Quantity\n>> ");
        }
    }

    strcpy(new_book->title, c);
    new_book->qty = fqty;

    if (table->Next == NULL) {
        table->Next = new_book;
        goto exit_increment;
    }

    struct registry* current_node = table->Next;
    while (current_node->Next !=  NULL) {
        current_node = current_node->Next;
    }

    current_node->Next = new_book;

    exit_increment:
    table->length++;
    printf("\n");
    
    system("cls");
}

void Edit_book(struct table* table) {
    if (table->Next == NULL) {
        printf("No data Found...\n\n");
        goto exit;
    }

    printf("Type the id of the desired book to edit... (Press 0 to exit)\n>> ");

    char c[4];
    int target;

    while (fgets(c, sizeof(c), stdin)) {
        Clear_String(c);

        if (sscanf(c, "%d", &target) == 1 && target >= 0) {
            break;
        }

        system("cls");
        printf("\nThe id must be a positive integer number... Try again.\n\n");
        printf("Type the id of the desired book to edit... (Press 0 to exit)\n>> ");;
    }

    struct registry* current = table->Next;
    while (current != NULL) {
        int n;
        sscanf(current->id, "%d", &n);
        
        if (n == target) {  
            break;
        }

        current = current->Next;
    }

    if (current == NULL) {
        system("cls");
        printf("Unable to find the entered id...\n\n");
        goto exit;
    }

    printf("\nWhat do you pretend to change?\n1. Change title\n2. Change quantity\n3. Change title and quantity\n0. Cancel\n");
    printf("\nType your choice...\n>> ");
        
    char choice[4];
    int choice_int;
    while (fgets(choice, sizeof(c), stdin)) {
        Clear_String(choice);

        if (sscanf(choice, "%d", &choice_int) == 1 && choice_int >= 0) {
            break;
        }
    }

    printf("\n");
    switch (choice_int) {
        case 1:
            New_Title(current);
            break;
        case 2:
            New_Qty(current);
            break;
        case 3:
            New_Title(current);
            New_Qty(current);
            break;
        case 0:
            break;
    }
    
    printf("\n");
    exit:
    system("cls");
}

void delete_book(struct table* table) {
    if (table->Next == NULL) {
        printf("No data Found...\n\n");
        goto exit;
    }

    printf("Type the id of the desired book to delete... (Press 0 to exit)\n>> ");
    
    char c[4];
    int target;
    while (fgets(c, sizeof(c), stdin)) {
        Clear_String(c);

        if (sscanf(c, "%d", &target) == 1 && target >= 0) {
            break;
        }
        system("cls");
        printf("\nThe id must be a positive integer number... Try again.\n\n");
        printf("Type the id of the desired book to delete... (Press 0 to exit)\n>> ");
    }

    switch (target) {
        case 0:
            system("cls");
            goto exit;
            break;
    }
    
    struct registry* past = NULL;
    struct registry* current = table->Next;
    struct registry* next = NULL;
    int cID;
    bool found = false;
    do {
        next = current->Next;

        sscanf(current->id, "%d", &cID);
        if (cID == target) {
            found = true;
            free(current);

            if (past == NULL) {
                table->Next = next;
            }
            else{
                past->Next = next;
            }

            break;
        }

        past = current;
        current = next;
    } while(current != NULL);


    if (found == true) {
        printf("\nThe book with the id %d was deleted succesfully!\n\n", target);
    }
    else {
        printf("\nFailed to find any book with the id %d...\n\n", target);
    }

    exit:
}

// The Program Itself
int main () {
    system("cls");

    char choice[2];
    int fChoice = 0;

    struct table* table = (struct table*) calloc(1, sizeof(struct table));
    if (table == NULL) {
        printf("\n\nERROR: The Heap Failed\n\n");
        exit(1);
    }

    table->length = 0;
    
    printf("\nWelcome to the Book Registry System!\n\n");

    // Main Loop
    bool loop = true;
    while (loop) {
        printf("Options:\n1. Show Books;\n2. Insert Book;\n3. Edit Book;\n4. Delete Book;\n0. Exit System;\n");
        printf("\nMake your Choice (0 to 4)\n>> ");
        
        while (fgets(choice, sizeof(choice), stdin)) {
            Clear_String(choice);

            if (sscanf(choice, "%d", &fChoice) == 1) {
                break;
            }
            else {
                system("cls");
                printf("\nOption must be an Integer Number, try again!\n\n");
                printf("Options:\n1. Show Books;\n2. Insert Book;\n3. Edit Book;\n4. Delete Book;\n0. Exit System;\n");
                printf("\nMake your Choice (0 to 4)\n>> ");
            }
        }
        
        system("cls");

        printf("\n");
        switch (fChoice) {
            case 1:
                show_books(table);
                break;
            case 2:
                Insert_book(table);
                break;
            case 3:
                Edit_book(table);
                break;
            case 4:
                delete_book(table);
                break;
            case 0:
                loop = false;
                printf("\nThanks for using the program :)\n\n");
                break;
            default:
                printf("This option is not available!! Try Again \n\n");
                break;
        }

    }

    if (table->Next != NULL) {
        struct registry* current_node = table->Next;
        struct registry* next_node;
        while (current_node->Next != NULL) {
            next_node = current_node->Next;
            free(current_node);
            current_node = next_node;
        }
        free(current_node);
    }
    free(table);
}