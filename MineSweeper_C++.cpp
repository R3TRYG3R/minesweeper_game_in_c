#include <iostream>

const int WIDTH = 10, HEIGHT = 10;
char field[WIDTH][HEIGHT];
int mines_quantity, counter;
unsigned int move_x, move_y;

void display_field() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == '*') {
                field[i][j] = '*';
                std::cout << ' ' << ' ';
            }
            else if ((j == 0 or j == WIDTH - 1) or (i == 0 or i == HEIGHT - 1)) {
                field[i][j] = '#';
                std::cout << field[i][j] << ' ';
            }
            else if (field[i][j] == '.') {
                field[i][j] = '.';
                std::cout << field[i][j] << ' ';
            }
            else {
                field[i][j] = ' ';
                std::cout << field[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void display_lose_field() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == '*') {
                field[i][j] = '*';
            }
            else if ((j == 0 or j == WIDTH - 1) or (i == 0 or i == HEIGHT - 1)) {
                field[i][j] = '#';
            }
            else if (field[i][j] == '.') {
                field[i][j] = '.';
            }
            else {
                field[i][j] = ' ';
            }
            std::cout << field[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void add_mines(int mines_quantity) {
    srand(time(NULL));

    while (true) {
        while (mines_quantity >= 64) {
            std::cout << "You can't add more mines." << std::endl;
            break;
        }
        if (mines_quantity < 64) {
            for (int i = 0; i < mines_quantity; i++) {
                field[rand() % 8 + 1][rand() % 8 + 1] = '*';
            }

            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    if (field[i][j] == '*') {
                        counter++;
                    }
                }
            }

            while (counter != mines_quantity) {
                counter = 0;
                field[rand() % 8 + 1][rand() % 8 + 1] = '*';

                for (int i = 0; i < WIDTH; i++) {
                    for (int j = 0; j < HEIGHT; j++) {
                        if (field[i][j] == '*') {
                            counter++;
                        }
                    }
                }
            }
            break;
        }
    }
}

void open_cage() {
    int around_mines_quantity = 0;
    int cages = ((WIDTH - 2) * (HEIGHT - 2));
    unsigned int open_cages = 0;

    while (open_cages != cages - counter) {
        std::cout << "Choose which cage u want do open?[x]: ";
        std::cin >> move_x;
        if (move_x >= 1 and move_x <= 8) {
            std::cout << "Choose which cage u want do open?[y]: ";
            std::cin >> move_y;
            if (move_y >= 1 and move_y <= 8) {
                if (field[move_y][move_x] == '*') {
                    std::cout << std::endl;
                    std::cout << "You can't do anything! U lose!" << std::endl;
                    std::cout << "Field wtih bombs: " << std::endl;
                    display_lose_field();
                    break;
                }
                if (field[move_y][move_x] == ' ') {
                    field[move_y][move_x] = '.';
                    counter++;
                    std::cout << std::endl;
                    if (field[move_y][move_x + 1] == '*') {
                        around_mines_quantity++;
                    }
                    if (field[move_y][move_x - 1] == '*') {
                        around_mines_quantity++;
                    }
                    if (field[move_y + 1][move_x] == '*') {
                        around_mines_quantity++;
                    }
                    if (field[move_y - 1][move_x] == '*') {
                        around_mines_quantity++;
                    }
                    std::cout << "Mines around your choice: " << around_mines_quantity << std::endl;
                    std::cout << std::endl;
                    std::cout << "Field:" << std::endl;
                    display_field();
                    std::cout << std::endl;
                    around_mines_quantity = 0;
                }
                else if (field[move_y][move_x] == '.') {
                    std::cout << std::endl;
                    std::cout << "U already checked this cage!" << std::endl;
                }
            }
        }
    }

    if (open_cages == cages - counter) {
        std::cout << std::endl;
        std::cout << "U won! Congratulations!";
    }
}

int main() {
    std::cout << "Your field:" << std::endl;
    display_field();
    std::cout << std::endl;
    std::cout << "How much mines do u want?" << std::endl;
    std::cin >> mines_quantity;
    add_mines(mines_quantity);
    open_cage();
}