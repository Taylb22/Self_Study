#include <stdio.h>

int main () {
    FILE* my_file;

    my_file = fopen("files/data.exe", "w");
    if (my_file == NULL) return 1;
    
    fprintf(my_file, "Henrique\n");
    fprintf(my_file, "Jorge\n");

    fclose(my_file);

    my_file = fopen("files/data.exe", "r");
    if (my_file == NULL) return 1;

    char name[128];
    while (fscanf(my_file, "%s", name) != EOF) {
        printf("Name -> %s\n", name);
    }

    fclose(my_file);

    return 0;
}