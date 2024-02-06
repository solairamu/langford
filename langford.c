#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_langford_pairing(int size, const int sequence[]);
bool create_langford_pairing(int n, int sequence[], int position);
bool can_place(int number, int sequence[], int position, int n);
void print_sequence(int sequence[], int size);

int main(int argc, char *argv[]) {
    if (argc == 1 || (argc > 1 && strcmp(argv[1], "-h") == 0)) {
        fprintf(stderr, "usage: %s [-h] -c n | num...\n", argv[0]);
        exit(argc == 1 ? 1 : 0);
    }

    if (strcmp(argv[1], "-c") == 0) {
        if (argc == 2) {
            fprintf(stderr, "%s: -c option requires an argument.\n", argv[0]);
            exit(1);
        } else if (argc > 3) {
            fprintf(stderr, "%s: -c option received too many arguments.\n", argv[0]);
            exit(1);
        }

        char *endptr;
        long n = strtol(argv[2], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "error: %s is not an integer.\n", argv[2]);
            exit(1);
        }

        int *sequence = calloc(2 * n, sizeof(int));
        if (create_langford_pairing(n, sequence, 1)) {
            print_sequence(sequence, 2 * n);
        } else {
            printf("No results found.\n");
        }
        free(sequence);
        exit(0);
    } else {
        int sequence[argc - 1];
        for (int i = 1; i < argc; i++) {
            char *endptr;
            sequence[i - 1] = strtol(argv[i], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "error: %s is not an integer.\n", argv[i]);
                exit(1);
            }
        }
        print_sequence(sequence, argc - 1);
        if (is_langford_pairing(argc - 1, sequence)) {
            printf("It is a langford pairing!\n");
        } else {
            printf("It is NOT a langford pairing.\n");
        }
        exit(0);
    }
    return 0;
}

bool is_langford_pairing(int size, const int sequence[]) {
    if (size % 2 != 0) return false;

    int n = size / 2;
    int positions[n + 1];

    for (int i = 1; i <= n; i++) {
        positions[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        int num = sequence[i];

        if (num < 1 || num > n) return false;

        if (positions[num] == -1) {
            positions[num] = i; 
        } else {
            int correct_position = positions[num] + num + 1;
            if (correct_position != i) return false;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (positions[i] == -1) return false;
    }

    return true;
}

bool create_langford_pairing(int n, int sequence[], int num) {
    if (num > n) {
        return true;
    }

    for (int i = 0; i < 2 * n - num - 1; ++i) {
        if (sequence[i] == 0 && sequence[i + num + 1] == 0) {
            sequence[i] = num;
            sequence[i + num + 1] = num;

            if (create_langford_pairing(n, sequence, num + 1)) {
                return true;
            }

            sequence[i] = 0;
            sequence[i + num + 1] = 0;
        }
    }

    return false;
}


bool can_place(int number, int sequence[], int position, int n) {
    if (position + number + 1 >= 2 * n) {
        return false;
    }
    return sequence[position] == 0 && sequence[position + number + 1] == 0;
}

void print_sequence(int sequence[], int size) {
    printf("Your sequence: [");
    for (int i = 0; i < size; i++) {
        printf("%d", sequence[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }   
    printf("]\n");
}
