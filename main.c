#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CHAR 110

typedef struct queue {
    char *letter;
    int size;
    struct queue *next;
    struct queue *prev;
} queue;

void enqueueTail(queue **head, queue **tail, char *letter, int size) {
    queue *new = malloc(sizeof(queue));
    if (*head == NULL) {
        new->next = NULL;
        new->prev = NULL;
        new->letter = letter;
        new->size = size;
        *head = new;
        *tail = new;
    } else {
        queue *temp = *tail;
        new->prev = temp;
        new->next = NULL;
        new->letter = letter;
        new->size = size;
        temp->next = new;
        *tail = new;
    }
}
void enqueueMidQueue(queue **head, queue **tail, queue **newHead,
                     queue **newTail, int pointer_x, int pointer_y) {
    queue *current = *head;
    int char_count = 0;
    for (int i = 0; i < pointer_x; i) {
        if (current->next != NULL) {
            if (current->letter[0] == '\n' || char_count == (MAX_CHAR - 1)) {
                i++;
                char_count = 0;
            }
            current = current->next;
            char_count++;
        } else {
            break;
        }
    }
    int status = 0;
    for (int i = 1; i < pointer_y; i++) {
        if (current->next != NULL) {
            current = current->next;
        } else {
            status = 1;
            break;
        }
    }
    if (pointer_y == 0 && status == 0) {
        if (current->prev != NULL) {
            queue *prev = current->prev;
            prev->next = *newHead;
            (*newHead)->prev = prev;
            (*newTail)->next = current;
            current->prev = *newTail;
        } else {
            (*newTail)->next = current;
            current->prev = *newTail;
            *head = *newHead;
        }
    } else {
        if (status == 1) {
            current->next = *newHead;
            (*newHead)->prev = current;
            *tail = *newTail;

        } else {
            if (current != NULL) {
                if (current->next != NULL) {
                    queue *next = current->next;
                    current->next = *newHead;
                    (*newHead)->prev = current;
                    (*newTail)->next = next;
                    next->prev = *newTail;
                } else {
                    current->next = *newHead;
                    (*newHead)->prev = current;
                    *tail = *newTail;
                }
            } else {
                *head = *newHead;
                *tail = *newTail;
            }
        }
    }
}

void freeQueue(queue **head, queue **tail) {
    queue *current = *head;
    while (current != NULL) {
        queue *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    *tail = NULL;
}

char *getInput() {
    char *input = malloc(MAX_CHAR * sizeof(char));
    for (int i = 0; i < MAX_CHAR; i++) {
        input[i] = '\0';
    }
    int i = 0;
    do {
        scanf("%c", &input[i]);
        i++;
    } while (input[i - 1] != '\n');
    i--;
    if (input[i] == '\n') input[i] = '\0';
    input = realloc(input, i);
    return input;
}

int printHUB(int pointer_x, int pointer_y, int marked_x, int marked_y,
             queue **head) {
    int count = 0;
    if (*head != NULL) {
        queue *current = *head;
        int char_count = 0;
        for (int i = 0; i < pointer_x; i) {
            if (current->next != NULL) {
                if (current->letter[0] == '\n' ||
                    char_count == (MAX_CHAR - 1)) {
                    i++;
                    char_count = 0;
                }
                current = current->next;
                char_count++;
            } else {
                break;
            }
        }
        for (int i = 0; (i + current->size) < MAX_CHAR; i++) {
            if (current->letter[0] == '\n') {
                break;
            }
            for (int j = 0; j < current->size; j++) {
                printf("%c", current->letter[j]);
            }
            count++;
            if (current->next != NULL) {
                current = current->next;
            } else {
                break;
            }
        }
    }
    printf("\n");
    if (pointer_x == marked_x && pointer_y != marked_y) {
        for (int i = 0; i < marked_y; i++) {
            printf(" ");
        }
        printf("M");
        for (int i = marked_y + 1; i < pointer_y; i++) {
            printf(" ");
        }
        printf("^\n");
    } else {
        for (int i = 0; i < pointer_y; i++) {
            printf(" ");
        }
        printf("^\n");
    }
    return count;
}
int countLines(queue **head) {
    int count = 0;
    int char_count = 0;
    if (*head != NULL) {
        queue *current = *head;
        while (current != NULL) {
            if (current->letter[0] == '\n' || char_count == (MAX_CHAR - 1)) {
                count++;
                char_count = 0;
            } else {
                char_count++;
            }
            current = current->next;
        }
    }
    return count;
}
int getMaxOfLine(queue **head, int pointer_x) {
    int count = 0;
    if (*head != NULL) {
        queue *current = *head;
        int char_count = 0;
        for (int i = 0; i < pointer_x; i) {
            if (current->next != NULL) {
                if (current->letter[0] == '\n' ||
                    char_count == (MAX_CHAR - 1)) {
                    i++;
                    char_count = 0;
                }
                current = current->next;
                char_count++;
            }
        }
        for (int i = 0; (i + current->size) < MAX_CHAR; i++) {
            if (current->letter[0] == '\n') {
                break;
            }
            count++;
            if (current->next != NULL) {
                current = current->next;
            } else {
                break;
            }
        }
    }
    return count;
}
void printQueue(queue **head) {
    queue *current = *head;
    while (current != NULL) {
        for (int i = 0; i < current->size; i++) {
            if (current->letter[i] == '\n') {
                printf("ENTER");
            } else {
                printf("%c", current->letter[i]);
            }
        }
        current = current->next;
    }
    printf("\n");
}
int main() {
    setlocale(LC_ALL, "Portuguese");
    queue *head = NULL;
    queue *tail = NULL;
    queue *transfer_area_head = NULL;
    queue *transfer_area_tail = NULL;
    int pointer_x = 0;
    int pointer_y = 0;
    int marked_x = 0;
    int marked_y = 0;
    int max_of_line = 0;
    int num_commands = 0;
    FILE *fp = NULL;
    while (true) {
        max_of_line = printHUB(pointer_x, pointer_y, marked_x, marked_y, &head);
        printf("%i,%i> ", pointer_x, pointer_y);
        char *command = getInput();
        printf("\n");

        if (command != NULL) {
            if (command[0] == 'I' || command[0] == 'A' || command[0] == 'E' ||
                command[0] == 'B' || command[0] == 'S') {
                num_commands = 1;
            } else {
                num_commands = 0;
                while (command[num_commands] != '\0') {
                    num_commands++;
                }
            }

            for (int num_command = 0; num_command < num_commands;
                 num_command++) {
                switch (command[num_command]) {
                    case 'I':
                        if (command[1] != '\0') {
                            char *temp = command + 1;
                            int i = 0;
                            queue *newHead = NULL;
                            queue *newTail = NULL;
                            while (temp[i] != '\0') {
                                char *str;
                                int len = 0;
                                if (temp[i] < 0) {
                                    if (temp[i + 1] < 0) {
                                        str = malloc(sizeof(char) * 3);
                                        str[0] = temp[i];
                                        str[1] = temp[i + 1];
                                        str[2] = temp[i + 2];
                                        len = 3;
                                        i += 3;
                                    } else {
                                        str = malloc(sizeof(char) * 2);
                                        str[0] = temp[i];
                                        str[1] = temp[i + 1];
                                        len = 2;
                                        i += 2;
                                    }
                                } else {
                                    str = malloc(sizeof(char) * 1);
                                    str[0] = temp[i];
                                    len = 1;
                                    i++;
                                }
                                enqueueTail(&newHead, &newTail, str, len);
                            }
                            enqueueMidQueue(&head, &tail, &newHead, &newTail,
                                            pointer_x, pointer_y);
                        }
                        break;
                    case 'A':
                        freeQueue(&head, &tail);
                        fp = fopen(command + 1, "r");
                        if (fp == NULL) {
                            printf("Arquivo não encontrado");
                            break;
                        }
                        pointer_x = 0;
                        pointer_y = 0;
                        char c;
                        while ((c = fgetc(fp)) != EOF) {
                            char *temp;
                            int size_temp = 0;
                            if (c < 0) {
                                char c1 = fgetc(fp);
                                if (c1 < 0) {
                                    char c2 = fgetc(fp);
                                    size_temp = 3;
                                    temp = malloc(sizeof(char) * 3);
                                    temp[0] = c;
                                    temp[1] = c1;
                                    temp[2] = c2;
                                } else {
                                    size_temp = 2;
                                    temp = malloc(sizeof(char) * 2);
                                    temp[0] = c;
                                    temp[1] = c1;
                                }
                            } else {
                                temp = malloc(sizeof(char));
                                size_temp = 1;
                                temp[0] = c;
                            }
                            enqueueTail(&head, &tail, temp, size_temp);
                        }
                        fclose(fp);
                        break;
                    case 'E':
                        if (command[1] != '\0') {
                            fp = fopen(command + 1, "w");
                            if (fp == NULL) {
                                break;
                            }
                            queue *current = head;
                            while (current != NULL) {
                                for (int i = 0; i < current->size; i++) {
                                    fputc(current->letter[i], fp);
                                }
                                current = current->next;
                            }
                            fclose(fp);
                        }
                        break;
                    case 'F':
                        if (pointer_y + 1 >= MAX_CHAR ||
                            pointer_y + 1 >= max_of_line) {
                            if (pointer_x + 1 <= countLines(&head)) {
                                pointer_x++;
                            } else {
                                pointer_x = 0;
                            }
                            pointer_y = 0;
                        } else {
                            pointer_y++;
                        }
                        break;
                    case 'T':
                        if (pointer_y - 1 < 0) {
                            if (pointer_x - 1 < 0) {
                                pointer_x = countLines(&head);
                                max_of_line = getMaxOfLine(&head, pointer_x);
                                pointer_y = max_of_line;
                            } else {
                                pointer_x--;
                                max_of_line = getMaxOfLine(&head, pointer_x);
                                if (max_of_line < MAX_CHAR)
                                    pointer_y = max_of_line;
                                else
                                    pointer_y = MAX_CHAR;
                            }
                        } else {
                            pointer_y--;
                        }
                        break;
                    case 'O':
                        pointer_y = 0;
                        break;
                    case 'P':
                        if (pointer_y >= 0) {
                            int temp_y = 0;

                            queue *current = head;
                            int char_count = 0;
                            for (int i = 0; i < pointer_x; i) {
                                if (current->next != NULL) {
                                    if (current->letter[0] == '\n' ||
                                        char_count == (MAX_CHAR - 1)) {
                                        i++;
                                        char_count = 0;
                                    }
                                    current = current->next;
                                    char_count++;
                                } else {
                                    break;
                                }
                            }
                            int status = 0;
                            for (int i = 0; i < pointer_y; i++) {
                                if (current->next != NULL) {
                                    current = current->next;

                                } else {
                                    while (current->prev != NULL) {
                                        if (current->prev->letter[0] == ' ' ||
                                            current->prev->letter[0] == '\n') {
                                            temp_y = i;
                                            break;
                                        }
                                        i--;
                                        current = current->prev;
                                    }
                                    temp_y = i;
                                    status = 1;
                                    break;
                                }
                            }
                            if (status == 0) {
                                for (int i = pointer_y; i < MAX_CHAR; i++) {
                                    if (current->next->letter[0] == ' ') {
                                        if (current->next->next != NULL) {
                                            temp_y = i + 2;
                                            break;
                                        }
                                    } else if (current->letter[0] == '\n' ||
                                               (i + 1) == MAX_CHAR) {
                                        while (current->prev != NULL) {
                                            if (current->prev->letter[0] ==
                                                    ' ' ||
                                                current->prev->letter[0] ==
                                                    '\n') {
                                                temp_y = i;
                                                break;
                                            }
                                            i--;
                                            current = current->prev;
                                        }
                                        break;
                                    }
                                    if (current->next != NULL) {
                                        current = current->next;
                                    } else {
                                        break;
                                    }
                                }
                            }
                            pointer_y = temp_y;
                        }
                        break;
                    case 'Q':
                        if (pointer_y > 0) {
                            int temp_y = 0;

                            queue *current = head;
                            int char_count = 0;
                            for (int i = 0; i < pointer_x; i) {
                                if (current->next != NULL) {
                                    if (current->letter[0] == '\n' ||
                                        char_count == (MAX_CHAR - 1)) {
                                        i++;
                                        char_count = 0;
                                    }
                                    current = current->next;
                                    char_count++;
                                } else {
                                    break;
                                }
                            }
                            for (int i = 0; i < pointer_y; i++) {
                                if (current->next != NULL) {
                                    current = current->next;
                                    if (current->letter[0] == ' ' &&
                                        current->next != NULL) {
                                        temp_y = i + 2;
                                    }
                                } else {
                                    break;
                                }
                            }
                            pointer_y = temp_y;
                        }
                        break;
                    case '$':
                        max_of_line = getMaxOfLine(&head, pointer_x);
                        pointer_y = max_of_line;
                        break;
                    case ':':
                        if (command[1] == 'F') {
                            pointer_x = countLines(&head);
                            pointer_y = 0;
                        } else {
                            char *temp = command + 1;
                            int len = 0;
                            int x = 0;
                            while (temp[len] != '\0') {
                                len++;
                            }
                            for (int i = len - 1; i >= 0; i--) {
                                x += (temp[i] - '0') * pow(10, len - (i + 1));
                            }
                            pointer_x = x;
                        }
                        break;
                    case 'D':
                        if (head != NULL) {
                            queue *current = head;
                            int char_count = 0;
                            for (int i = 0; i < pointer_x; i) {
                                if (current->next != NULL) {
                                    if (current->letter[0] == '\n' ||
                                        char_count == (MAX_CHAR - 1)) {
                                        i++;
                                        char_count = 0;
                                    }
                                    current = current->next;
                                    char_count++;
                                } else {
                                    break;
                                }
                            }
                            int status = 0;
                            for (int i = 1; i < pointer_y; i++) {
                                if (current->next != NULL) {
                                    current = current->next;
                                } else {
                                    status = 1;
                                    break;
                                }
                            }
                            if (status == 0) {
                                if (pointer_y == 0) {
                                    if (current->prev != NULL) {
                                        current = current->prev;
                                        if (current->prev != NULL) {
                                            current->prev->next = current->next;
                                            current->next->prev = current->prev;
                                            free(current);
                                        } else {
                                            head = current->next;
                                            current->next->prev = NULL;
                                            free(current);
                                        }
                                    }
                                } else {
                                    queue *prev = current->prev;
                                    queue *next = current->next;
                                    prev->next = next;
                                    next->prev = prev;
                                    free(current);
                                }
                            }
                        }
                        break;
                    case 'M':
                        marked_x = pointer_x;
                        marked_y = pointer_y;
                        break;
                    case 'V':
                        if (transfer_area_head != NULL &&
                            transfer_area_tail != NULL) {
                            queue *current = head;
                            int char_count = 0;
                            for (int i = 0; i < pointer_x; i) {
                                if (current->next != NULL) {
                                    if (current->letter[0] == '\n' ||
                                        char_count == (MAX_CHAR - 1)) {
                                        i++;
                                        char_count = 0;
                                    }
                                    current = current->next;
                                    char_count++;
                                } else {
                                    break;
                                }
                            }
                            for (int i = 1; i < pointer_y; i++) {
                                if (current->next != NULL) {
                                    current = current->next;
                                } else {
                                    break;
                                }
                            }
                            if (pointer_y == 0) {
                                if (current->prev != NULL) {
                                    current = current->prev;
                                    current->next = transfer_area_head;
                                    transfer_area_head->prev = current;
                                    transfer_area_tail->next = current->next;
                                    current->next->prev = transfer_area_tail;
                                } else {
                                    head = transfer_area_head;
                                    transfer_area_tail->next = current;
                                    current->prev = transfer_area_tail;
                                }
                            } else {
                                queue *next = current->next;
                                current->next = transfer_area_head;
                                transfer_area_head->prev = current;
                                transfer_area_tail->next = next;
                                next->prev = transfer_area_tail;
                            }
                            transfer_area_head = NULL;
                            transfer_area_tail = NULL;
                        }
                        break;
                    case 'C':
                        freeQueue(&transfer_area_head, &transfer_area_tail);
                        int limit_inferior_x = 0;
                        int limit_inferior_y = 0;
                        int limit_superior_x = 0;
                        int limit_superior_y = 0;
                        if (marked_x > pointer_x) {
                            limit_superior_x = marked_x;
                            limit_inferior_x = pointer_x;
                            limit_superior_y = marked_y;
                            limit_inferior_y = pointer_y;
                        } else if (marked_x == pointer_x) {
                            limit_superior_x = marked_x;
                            limit_inferior_x = pointer_x;
                            if (marked_y > pointer_y) {
                                limit_superior_y = marked_y;
                                limit_inferior_y = pointer_y;
                            } else if (marked_y < pointer_y) {
                                limit_superior_y = pointer_y;
                                limit_inferior_y = marked_y;
                            } else {
                                break;
                            }
                        } else {
                            limit_superior_x = pointer_x;
                            limit_inferior_x = marked_x;
                            limit_superior_y = pointer_y;
                            limit_inferior_y = marked_y;
                        }
                        queue *inferior = head;
                        int char_count = 0;
                        for (int i = 0; i < limit_inferior_x; i) {
                            if (inferior->letter[0] == '\n' ||
                                char_count == (MAX_CHAR - 1)) {
                                i++;
                                char_count = 0;
                            } else {
                                char_count++;
                            }
                            if (inferior->next != NULL) {
                                inferior = inferior->next;
                            } else {
                                break;
                            }
                        }
                        for (int i = 0; i < limit_inferior_y; i++) {
                            if (inferior->next != NULL) {
                                inferior = inferior->next;
                            } else {
                                break;
                            }
                        }
                        queue *superior = inferior;
                        char_count = 0;
                        for (int i = limit_inferior_x; i < limit_superior_x;
                             i) {
                            if (superior->letter[0] == '\n' ||
                                char_count == (MAX_CHAR - 1)) {
                                i++;
                                char_count = 0;
                            } else {
                                char_count++;
                            }
                            if (superior->next != NULL) {
                                superior = superior->next;
                            } else {
                                break;
                            }
                        }
                        for (int i = limit_inferior_y + 1; i < limit_superior_y;
                             i++) {
                            if (superior->next != NULL) {
                                superior = superior->next;
                            } else {
                                break;
                            }
                        }
                        while (inferior != superior->next) {
                            char *temp = malloc(sizeof(char) * inferior->size);
                            for (int i = 0; i < inferior->size; i++) {
                                temp[i] = inferior->letter[i];
                            }
                            enqueueTail(&transfer_area_head,
                                        &transfer_area_tail, temp,
                                        inferior->size);
                            if (inferior->next != NULL) {
                                inferior = inferior->next;
                            } else {
                                break;
                            }
                        }
                        break;
                    case 'X': {
                        freeQueue(&transfer_area_head, &transfer_area_tail);
                        int limit_inferior_x = 0;
                        int limit_inferior_y = 0;
                        int limit_superior_x = 0;
                        int limit_superior_y = 0;
                        if (marked_x > pointer_x) {
                            limit_superior_x = marked_x;
                            limit_inferior_x = pointer_x;
                            limit_superior_y = marked_y;
                            limit_inferior_y = pointer_y;
                        } else if (marked_x == pointer_x) {
                            limit_superior_x = marked_x;
                            limit_inferior_x = pointer_x;
                            if (marked_y > pointer_y) {
                                limit_superior_y = marked_y;
                                limit_inferior_y = pointer_y;
                            } else if (marked_y < pointer_y) {
                                limit_superior_y = pointer_y;
                                limit_inferior_y = marked_y;
                            } else {
                                break;
                            }
                        } else {
                            limit_superior_x = pointer_x;
                            limit_inferior_x = marked_x;
                            limit_superior_y = pointer_y;
                            limit_inferior_y = marked_y;
                        }
                        queue *inferior = head;
                        int char_count = 0;
                        for (int i = 0; i < limit_inferior_x; i) {
                            if (inferior->letter[0] == '\n' ||
                                char_count == (MAX_CHAR - 1)) {
                                i++;
                                char_count = 0;
                            } else {
                                char_count++;
                            }
                            if (inferior->next != NULL) {
                                inferior = inferior->next;
                            } else {
                                break;
                            }
                        }
                        for (int i = 0; i < limit_inferior_y; i++) {
                            if (inferior->next != NULL) {
                                inferior = inferior->next;
                            } else {
                                break;
                            }
                        }
                        queue *superior = inferior;
                        char_count = 0;
                        for (int i = limit_inferior_x; i < limit_superior_x;
                             i) {
                            if (superior->letter[0] == '\n' ||
                                char_count == (MAX_CHAR - 1)) {
                                i++;
                                char_count = 0;
                            } else {
                                char_count++;
                            }
                            if (superior->next != NULL) {
                                superior = superior->next;
                            } else {
                                break;
                            }
                        }
                        for (int i = limit_inferior_y + 1; i < limit_superior_y;
                             i++) {
                            if (superior->next != NULL) {
                                superior = superior->next;
                            } else {
                                break;
                            }
                        }
                        transfer_area_head = inferior;
                        transfer_area_tail = superior;
                        if (inferior->prev != NULL) {
                            inferior->prev->next = superior->next;
                            inferior->prev = NULL;
                        } else {
                            head = superior->next;
                        }
                        if (superior->next != NULL) {
                            superior->next->prev = inferior->prev;
                            superior->next = NULL;
                        } else {
                            tail = inferior->prev;
                        }
                        max_of_line = getMaxOfLine(&head, pointer_x);
                        if (pointer_y > max_of_line) pointer_y = max_of_line;
                    } break;
                    case 'B':
                        if (command[1] != '\0' && head != NULL) {
                            char *temp = command + 1;
                            queue *current = head;
                            queue *search = NULL;
                            int line_count = 0;
                            int char_count = 0;
                            int index = 0;
                            int len = 0;
                            int status = 0;
                            while (temp[len] != '\0') {
                                len++;
                            }
                            for (int i = 0; i < pointer_x; i) {
                                if (current->letter[0] == '\n' ||
                                    char_count == (MAX_CHAR - 1)) {
                                    i++;
                                    line_count++;
                                    char_count = 0;
                                } else {
                                    char_count++;
                                }
                                if (current->next != NULL) {
                                    current = current->next;
                                    index++;
                                } else {
                                    break;
                                }
                            }
                            for (int i = 0; i < pointer_y; i++) {
                                if (current->next != NULL) {
                                    current = current->next;
                                    index++;
                                } else {
                                    break;
                                }
                            }
                            for (int i = 0; i < len && status == 0; i) {
                                for (int j = 0; j < current->size; j++) {
                                    if (current->letter[j] == temp[i]) {
                                        if (i == 0) {
                                            search = current;
                                        }
                                        i++;

                                    } else {
                                        i = 0;
                                        break;
                                    }
                                }
                                if (current->next != NULL) {
                                    current = current->next;
                                    index++;
                                } else {
                                    status = 1;
                                    break;
                                }
                            }
                            if (status == 0) {
                                current = head;
                                char_count = 0;
                                line_count = 0;
                                while (search != current) {
                                    if (char_count == (MAX_CHAR - 2) ||
                                        current->letter[0] == '\n') {
                                        line_count++;
                                        char_count = 0;
                                    } else {
                                        char_count++;
                                    }
                                    if (current->next != NULL) {
                                        current = current->next;
                                    } else {
                                        break;
                                    }
                                }
                                pointer_x = line_count;
                                pointer_y = char_count;
                            }
                        }
                        break;
                    case 'S': {
                        char *temp = command + 1;
                        int len = 0;
                        int pos = 0;
                        while (temp[len] != '\0') {
                            if (temp[len] == '/') {
                                pos = len;
                            }
                            len++;
                        }
                        char *s = malloc(sizeof(char) * (pos));
                        char *r = malloc(sizeof(char) * (len - pos - 1));
                        for (int i = 0; i < len; i++) {
                            if (i < pos) {
                                s[i] = temp[i];
                            } else if (i > pos) {
                                r[i - pos - 1] = temp[i];
                            }
                        }
                        queue *current = head;
                        queue *search = NULL;
                        int status = 0;
                        while (current != NULL && status != 2) {
                            for (int i = 0; i < pos && status != 2; i) {
                                for (int j = 0; j < current->size; j++) {
                                    if (current->letter[j] == s[i]) {
                                        status = 0;
                                        if (i == 0) {
                                            search = current;
                                        }
                                        i++;
                                    } else {
                                        i = 0;
                                        status = 1;
                                    }
                                    if (current->next != NULL) {
                                        current = current->next;
                                    } else {
                                        status = 2;
                                        break;
                                    }
                                }
                            }
                            if (status == 0) {
                                queue *searchStart = search->prev;
                                queue *searchEnd = search;
                                for (int i = 0; i < pos; i++) {
                                    searchEnd = searchEnd->next;
                                }
                                queue *rHead = NULL;
                                queue *rTail = NULL;
                                if ((len - pos - 1) > 0) {
                                    for (int i = 0; i < len - pos - 1; i++) {
                                        char *c;
                                        int size = 0;
                                        if (r[i] < 0) {
                                            if (r[+1] < 0) {
                                                c = malloc(sizeof(char) * 3);
                                                c[0] = r[i];
                                                c[1] = r[i + 1];
                                                c[2] = r[i + 2];
                                                i += 2;
                                                size = 3;
                                            } else {
                                                c = malloc(sizeof(char) * 2);
                                                c[0] = r[i];
                                                c[1] = r[i + 1];
                                                i++;
                                                size = 2;
                                            }
                                        } else {
                                            c = malloc(sizeof(char) * 1);
                                            c[0] = r[i];
                                            size = 1;
                                        }
                                        enqueueTail(&rHead, &rTail, c, size);
                                    }
                                    if (searchStart != NULL) {
                                        searchStart->next = rHead;
                                        rHead->prev = searchStart;
                                    } else {
                                        head = rHead;
                                    }
                                    if (searchEnd != NULL) {
                                        searchEnd->prev = rTail;
                                        rTail->next = searchEnd;
                                    } else {
                                        tail = rTail;
                                    }
                                } else {
                                    if (searchStart != NULL) {
                                        searchStart->next = searchEnd;
                                    } else {
                                        head = searchEnd;
                                    }
                                    if (searchEnd != NULL) {
                                        searchEnd->prev = searchStart;
                                    } else {
                                        tail = searchStart;
                                    }
                                }

                                for (int i = 0; i < pos; i++) {
                                    queue *tempS = search;
                                    search = search->next;
                                    free(tempS);
                                }
                            }
                        }
                    } break;
                    case 'N': {
                        queue *newHead = NULL;
                        queue *newTail = NULL;
                        enqueueTail(&newHead, &newTail, "\n", 1);
                        enqueueMidQueue(&head, &tail, &newHead, &newTail,
                                        pointer_x, pointer_y);
                    } break;
                    case 'U':
                        if (head != NULL) {
                            queue *current = head;
                            while (current->letter[0] != '\n') {
                                if (current->next != NULL) {
                                    current = current->next;
                                } else {
                                    break;
                                }
                            }
                            if (current->next != NULL) {
                                queue *prev = current->prev;
                                queue *next = current->next;
                                prev->next = next;
                                next->prev = prev;
                                free(current);
                            } else {
                                queue *prev = current->prev;
                                prev->next = NULL;
                                free(current);
                            }
                        }
                        break;
                    case '!':
                        exit(0);
                        break;
                    case 'J':
                        pointer_x++;
                        max_of_line = getMaxOfLine(&head, pointer_x);
                        if (pointer_y > max_of_line) pointer_y = max_of_line;
                        break;
                    case 'H':
                        if (pointer_x - 1 >= 0) {
                            pointer_x--;
                            max_of_line = getMaxOfLine(&head, pointer_x);
                            if (pointer_y > max_of_line)
                                pointer_y = max_of_line;
                        }
                        break;
                    case 'Z':
                        if (transfer_area_head != NULL) {
                            queue *current = transfer_area_head;
                            printf(">");
                            int char_count = 0;
                            while (current != NULL) {
                                if (char_count == (MAX_CHAR - 1) ||
                                    current->letter[0] == '\n') {
                                    printf("\n");
                                    char_count = 0;
                                } else {
                                    for (int i = 0; i < current->size; i++) {
                                        printf("%c", current->letter[i]);
                                        char_count++;
                                    }
                                }
                                current = current->next;
                            }
                            printf("<\n");
                        }
                        break;
                    default:
                        num_command = num_commands;
                        break;
                }
            }
        }
    }
    return 0;
}
