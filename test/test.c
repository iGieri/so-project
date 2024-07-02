#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>

#define MATRIX_SIZE 20
#define PLAYER_CHAR '*'
#define EMPTY_CHAR ' '

typedef struct {
    int x;
    int y;
} player_position;

char** matrix;
player_position* pp;

int matrix_init() {
    matrix = malloc(MATRIX_SIZE*sizeof(char*));

    pp = malloc(sizeof(player_position));

    for (int i=0; i<MATRIX_SIZE; i++) {
        matrix[i] = malloc(MATRIX_SIZE*sizeof(char));
    }

    for (int i=0; i<MATRIX_SIZE; i++) {
        for (int j=0; j<MATRIX_SIZE; j++) {
            if (i == 0 && j == 0) matrix[0][0] = PLAYER_CHAR;
            else matrix[i][j] = EMPTY_CHAR;
        }
    }
    
    pp->x = 0;
    pp->y = 0;

    return 0;
}

void matrix_print() {
    for (int i=0; i<MATRIX_SIZE; i++) {
        for (int j=0; j<MATRIX_SIZE; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    printf("X: %d\tY: %d\n", pp->x, pp->y);
}

void matrix_update() {
    for (int i=0; i<MATRIX_SIZE; i++) {
        for (int j=0; j<MATRIX_SIZE; j++) {
            if (i == pp->x && j == pp->y) matrix[i][j] = PLAYER_CHAR;
            else matrix[i][j] = EMPTY_CHAR;
        }
    }
}

int main() {
    int fd;
    int ret;
    struct js_event js;

    fd = open("/dev/input/js1", O_RDONLY);
    if (fd == -1) {
        perror("Error connecting joystick");
        return -1;
    }

    matrix_init();
    system("clear");
    matrix_print();

    while (1) {
        ret = read(fd, &js, sizeof(struct js_event));
        if (ret != sizeof(struct js_event)) {
            perror("Error reading joystick");
            return -1;
        }

        if (js.type == JS_EVENT_AXIS) {
            // x axis
            if (js.number == 1) {
                if (js.value < -1000 && pp->x > 0) pp->x--; // left
                if (js.value > 1000 && pp->x < MATRIX_SIZE - 1) pp->x++; // right
            }

            // y axis
            if (js.number == 0) {
                if (js.value < -1000 && pp->y > 0) pp->y--; // up
                if (js.value > 1000 && pp->y < MATRIX_SIZE - 1) pp->y++; // down
            }

            matrix_update();
            system("clear");
            matrix_print();
        }


    }
}