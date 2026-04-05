#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char Q[64][64];
int idx;

void queue (char* P) {
    if (idx > 63) {
        printf("\nFila Cheia!!!\n");
        goto exit;
    }

    strcpy(Q[idx], P);
    idx++;

    exit:
}

void dequeue () {
    for (int i = 0; i < idx; i++) {
        strcpy(Q[i], Q[i + 1]);
    }
    idx--;
}

void print_queue() {
    printf("\nFila Atual:\n\n");
    for (int i = 0; i < idx; i++) {
        printf("%s\n", Q[i]);
    }
    printf("\n");
}

int main() {
    idx = 0;

    queue("GAY");
    queue("Cayque");
    queue("Lunim (Meu Herói)");
    queue("Ludvica");
    
    print_queue();

    dequeue();

    print_queue();

    return 0;
}