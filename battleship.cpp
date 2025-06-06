#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>

constexpr int ROWS = 10;
constexpr int COLS = 10;

const char EMPTY = '.';
const char HIT = 'X';
const char MISS = 'O';

void initBoard(char board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            board[r][c] = EMPTY;
        }
    }
}

bool parseCoordinate(const std::string &input, int &row, int &col) {
    if (input.size() < 2 || input.size() > 3) return false;
    char rowChar = std::toupper(input[0]);
    if (rowChar < 'A' || rowChar > 'J') return false;
    std::string colStr = input.substr(1);
    int num = 0;
    try {
        num = std::stoi(colStr);
    } catch (...) {
        return false;
    }
    if (num < 1 || num > 10) return false;
    row = rowChar - 'A';
    col = num - 1;
    return true;
}

void writeBoard(const char board[ROWS][COLS], const std::string &filename) {
    std::ofstream out(filename);
    if (!out) return;
    out << "   ";
    for (int c = 1; c <= COLS; ++c) {
        out << std::setw(2) << c;
    }
    out << '\n';
    for (int r = 0; r < ROWS; ++r) {
        out << static_cast<char>('A' + r) << ' ';
        for (int c = 0; c < COLS; ++c) {
            out << std::setw(2) << board[r][c];
        }
        out << '\n';
    }
}

bool placeShip(char board[ROWS][COLS], int length, char symbol) {
    while (true) {
        std::string coord;
        char orient;
        std::cout << "Lutfen gemi " << symbol<< " icin baslangic koordinati giriniz." 
                  << " (uzunluk " << length << ") or. A1: ";
        std::cin >> coord;
        std::cout << "Yon seciniz (H:(yatay)/V:(dikey)): ";
        std::cin >> orient;
        orient = std::toupper(orient);
        int row, col;
        if (!parseCoordinate(coord, row, col) || (orient != 'H' && orient != 'V')) {
            std::cout << "Gecersiz koordinat, tekrar deneyin.\n";
            continue;
        }
        if (orient == 'H' && col + length > COLS) {
            std::cout << "Gemi yatay olarak sigmadi.\n";
            continue;
        }
        if (orient == 'V' && row + length > ROWS) {
            std::cout << "Gemi dikey olarak sigmadi.\n";
            continue;
        }
        bool overlap = false;
        for (int i = 0; i < length; ++i) {
            int r = row + (orient == 'V' ? i : 0);
            int c = col + (orient == 'H' ? i : 0);
            if (board[r][c] != EMPTY) {
                overlap = true;
                break;
            }
        }
        if (overlap) {
            std::cout << "Gemi baska bir gemi ile cakisiyor\n";
            continue;
        }
        for (int i = 0; i < length; ++i) {
            int r = row + (orient == 'V' ? i : 0);
            int c = col + (orient == 'H' ? i : 0);
            board[r][c] = symbol;
        }
        return true;
    }
}

int main() {
    char ships[ROWS][COLS];
    char aim[ROWS][COLS];
    initBoard(ships);
    initBoard(aim);

    int remaining = 0;

    placeShip(ships, 5, 'A'); remaining += 5;
    placeShip(ships, 4, 'B'); remaining += 4;
    for (int i = 0; i < 2; ++i) { placeShip(ships, 3, 'C'); remaining += 3; }
    for (int i = 0; i < 2; ++i) { placeShip(ships, 2, 'D'); remaining += 2; }
    for (int i = 0; i < 3; ++i) { placeShip(ships, 1, 'E'); remaining += 1; }

    writeBoard(ships, "1stships.txt");
    writeBoard(aim, "2ndaim.txt");

    while (remaining > 0) {
        std::string target;
        std::cout << "Hedef koordinati giriniz (or. F6): ";
        std::cin >> target;
        int row, col;
        if (!parseCoordinate(target, row, col)) {
            std::cout << "Gecersiz koordinat.\n";
            continue;
        }
        if (aim[row][col] != EMPTY) {
            std::cout << "Daha once isaretlendi.\n";
            continue;
        }
        if (ships[row][col] >= 'A' && ships[row][col] <= 'E') {
            std::cout << "Isabetli!\n";
            ships[row][col] = HIT;
            aim[row][col] = HIT;
            --remaining;
        } else {
            std::cout << "Kacti.\n";
            ships[row][col] = MISS;
            aim[row][col] = MISS;
        }
        writeBoard(ships, "1stships.txt");
        writeBoard(aim, "2ndaim.txt");
    }

    std::cout << "Tum gemiler batirildi!\n";

   
    
    return 0;
}