#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char stack[64];
int idx;

char top() {
    switch (idx) {
        case 0:
            return -1;
            break;
        default:
            return stack[idx - 1];
            break;
    }
}

void pop() {
    idx--;
    stack[idx] = '\0';
}

void push(char c) {
    stack[idx] = c;
    idx++;
    stack[idx] = '\0';
}

bool is_balanced(char* S) {
    for (int i = 0; i < strlen(S); i++) {
        switch (S[i]) {
            case '(':
                push('(');
                break;
            case ')':
                if (top() != -1) {pop();} else {return false;}
                break;
        }
    }

    switch (top()) {
        case -1:
            return true;
            break;
        default:
            return false;
            break;
    }
}

int main () {
    stack[0] = '\0';
    idx = 0;

    char S[64] = "((3+4)*(2-1)";

    if (is_balanced(S)) {
        printf("\nTa balanceado!!\n\n");
    }
    else {
        printf("\nNao ta balanceado :(\n\n");
    }

    return 0;
}