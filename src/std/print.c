#include "print.h"

const static size_t NUM_ROWS = 25;
const static size_t NUM_COLS = 80;

struct Char {
    uint8_t character;
    uint8_t colour;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t colour = PRINT_COLOUR_WHITE | PRINT_COLOUR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        colour: colour
    };
    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void cls() {
    for (size_t i = 0; i < NUM_ROWS; i++){
        clear_row(i);
    }
    col = 0;
    row = 0;
}

void screen_colour(uint8_t colour) {
    for (size_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
        buffer[i].colour = colour;
    }
}

void print_newline(){
    col = 0;

    if (row < NUM_ROWS - 1){
        row++;
        return;
    } else {
        cls();
    }

    for (size_t row = 1; row < NUM_ROWS; row++){
        for (size_t col = 1; col < NUM_COLS; col++){
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS){
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        character: (uint8_t) character,
        colour: colour
    };

    col++;
}

void prints(char* string) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) string[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void remove_chars(size_t num_chars) {
    if (num_chars == 0 || row >= NUM_ROWS || col >= NUM_COLS) {
        return;
    }

    size_t remove_count = 0;

    while (remove_count < num_chars) {
        if (col > 0) {
            col--;
        } else {
            if (row > 0) {
                row--;
                col = NUM_COLS - 1;
            } else {
                break;
            }
        }

        buffer[col + NUM_COLS * row].character = ' ';
        buffer[col + NUM_COLS * row].colour = colour;

        remove_count++;
    }
}

void printi(int number) {
    char buffer[12];
    int i = 0;

    if (number == 0) {
        print_char('0');
        return;
    }

    if (number < 0) {
        print_char('-');
        number = -number;
    }

    while (number > 0) {
        buffer[i++] = '0' + (number % 10);
        number /= 10;
    }

    while (i > 0) {
        print_char(buffer[--i]);
    }
}

void print_set_colour(uint8_t foreground, uint8_t background){
    colour = foreground + (background << 4);
}