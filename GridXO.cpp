#include <iostream>
#include <vector>
#include <string>

// ��������, �� ��������� ������� � ������ ������� � ����������
bool isValid(const std::vector<std::vector<char> >& grid, int row, int col, char symbol, int size) {
    // ��������� ��������� ���� ���� ��� ��������
    std::vector<std::vector<char> > tempGrid = grid;
    tempGrid[row][col] = symbol;

    // �������� �������������� �������������
    for (int c = 0; c <= col; c++) {
        if (c + 3 >= size) continue; // ����������, ���� ���� ���� ��� 4 �������
        if (c <= col && col <= c + 3) {
            bool sequence = true;
            for (int j = 0; j < 4; j++) {
                int checkCol = c + j;
                if (tempGrid[row][checkCol] != symbol) {
                    sequence = false;
                    break;
                }
            }
            if (sequence) return false;// �������� ������������ - ��������� �����������
        }
    }

    // �������� ������������ �������������
    for (int r = 0; r <= row; r++) {
        if (r + 3 >= size) continue; // ����������, ���� ���� ���� ��� 4 �������
        if (r <= row && row <= r + 3) {
            bool sequence = true;
            for (int j = 0; j < 4; j++) {
                int checkRow = r + j;
                if (tempGrid[checkRow][col] != symbol) {
                    sequence = false;
                    break;
                }
            }
            if (sequence) return false;// �������� ������������ - ��������� �����������
        }
    }

    // �������� ����������� ������������� (����-�������, ������-����)
    for (int r = 0; r <= row; r++) {
        int c = col - (row - r);
        if (c < 0 || c + 3 >= size || r + 3 >= size) continue;// ���������� ���
        if (c <= col && col <= c + 3 && r <= row && row <= r + 3) {
            bool sequence = true;
            for (int j = 0; j < 4; j++) {
                if (tempGrid[r + j][c + j] != symbol) {
                    sequence = false;
                    break;
                }
            }
            if (sequence) return false;// �������� ������������ - ��������� �����������
        }
    }

    // �������� ����������� ������������� (������-�����, ������-����)
    for (int r = 0; r <= row; r++) {
        int c = col + (row - r);
        if (c >= size || c - 3 < 0 || r + 3 >= size) continue;// ���������� ���
        if (c - 3 <= col && col <= c && r <= row && row <= r + 3) {
            bool sequence = true;
            for (int j = 0; j < 4; j++) {
                if (tempGrid[r + j][c - j] != symbol) {
                    sequence = false;
                    break;
                }
            }
            if (sequence) return false;// �������� ������������ - ��������� �����������
        }
    }
    return true;// ��������� ���������
}

// ��������� �������� ������� ��� ���������� ��������� �������
void findBestCell(const std::vector<std::vector<char> >& grid, int size, int& bestRow, int& bestCol) {
    int minOptions = 3;
    bestRow = -1;
    bestCol = -1;

    // ���������� �� ������� ����
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == ' ') {
                int options = 0;
                // ����������, �� ������� ����� ���������
                if (isValid(grid, i, j, 'X', size)) options++;
                if (isValid(grid, i, j, 'O', size)) options++;

                // �������� ������� � ��������� ������� ������� (���������)
                if (options < minOptions && options > 0) {
                    minOptions = options;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
}

// ���������� ����� ������ ���������� ����
bool solve(std::vector<std::vector<char> >& grid, int size) {
    int row = -1, col = -1;
    // ��������� �������� ������� ��� ����������
    findBestCell(grid, size, row, col);

    if (row == -1) return true;

    // �������� ��������� ������� 'X' �� 'O'
    char symbols[2] = { 'X', 'O' };
    for (int s = 0; s < 2; s++) {
        char symbol = symbols[s];
        if (isValid(grid, row, col, symbol, size)) {
            grid[row][col] = symbol;
            if (solve(grid, size)) return true;// ���������� ������� ��� �������� ����
            grid[row][col] = ' ';
        }
    }
    return false;
}

// �������� ���� � �������
void printGrid(const std::vector<std::vector<char> >& grid, int size) {
    // �������� ������ ����
    std::cout << "+";
    for (int j = 0; j < size; j++) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    // �������� ����� ���� 
    for (int i = 0; i < size; i++) {
        std::cout << "|";
        for (int j = 0; j < size; j++) {
            std::cout << " ";
            if (grid[i][j] == ' ') {
                std::cout << " ";
            }
            else {
                std::cout << grid[i][j];
            }
            std::cout << " |";
        }
        std::cout << std::endl;
        // �������� ������������� ���� ���� ������� �����
        std::cout << "+";
        for (int j = 0; j < size; j++) {
            std::cout << "---+";
        }
        std::cout << std::endl;
    }
}

// ��������� ����� ������� ����
void initializeGrid1(std::vector<std::vector<char> >& grid, int size) {
    // ����������� �� ������� �� �������
    for (int i = 0; i < size; i++) {
        grid[i].resize(size, ' ');
    }
    // ������ �������� ������� �������
    grid[0][1] = 'O'; grid[0][2] = 'X'; grid[0][6] = 'O'; grid[0][8] = 'O'; grid[0][9] = 'X';
    grid[1][1] = 'O'; grid[1][7] = 'O'; grid[1][9] = 'O';
    grid[2][0] = 'X'; grid[2][3] = 'X'; grid[2][4] = 'X';
    grid[3][2] = 'X'; grid[3][4] = 'X'; grid[3][9] = 'O';
    grid[4][0] = 'O'; grid[4][5] = 'X'; grid[4][6] = 'X'; grid[4][8] = 'X';
    grid[5][2] = 'X'; grid[5][3] = 'X';
    grid[6][0] = 'O'; grid[6][4] = 'X'; grid[6][9] = 'X';
    grid[7][2] = 'X'; grid[7][5] = 'X'; grid[7][7] = 'X';
    grid[8][0] = 'X'; grid[8][1] = 'X'; grid[8][4] = 'O'; grid[8][9] = 'X';
    grid[9][1] = 'X'; grid[9][2] = 'X'; grid[9][3] = 'O'; grid[9][4] = 'O'; grid[9][9] = 'O';
}

void initializeGrid2(std::vector<std::vector<char> >& grid, int size) {
    for (int i = 0; i < size; i++) {
        grid[i].resize(size, ' ');
    }
    grid[0][2] = 'X'; grid[0][7] = 'O'; grid[0][8] = 'O'; grid[0][9] = 'O';
    grid[1][1] = 'O'; grid[1][3] = 'O'; grid[1][4] = 'X'; grid[1][6] = 'O'; grid[1][7] = 'X'; grid[1][8] = 'O';
    grid[2][0] = 'O'; grid[2][3] = 'O'; grid[2][8] = 'X'; grid[2][9] = 'O';
    grid[3][1] = 'O'; grid[3][3] = 'O';
    grid[4][7] = 'O'; grid[4][9] = 'X';
    grid[5][0] = 'O'; grid[5][1] = 'O'; grid[5][5] = 'O'; grid[5][8] = 'X';
    grid[6][0] = 'O'; grid[6][6] = 'O'; grid[6][9] = 'X';
    grid[7][1] = 'X'; grid[7][4] = 'X';
    grid[8][0] = 'O'; grid[8][3] = 'X';
    grid[9][0] = 'O'; grid[9][1] = 'O'; grid[9][3] = 'O'; grid[9][4] = 'X'; grid[9][5] = 'X'; grid[9][7] = 'X'; grid[9][8] = 'O'; grid[9][9] = 'X';
}

// ����� �� �������� ��������� ��� ������� ����
void solveAndPrintGrid(int gridNumber) {
    const int size = 10;
    std::vector<std::vector<char> > grid(size);
    // ���� �� ������������ ����
    if (gridNumber == 1) {
        initializeGrid1(grid, size);
        std::cout << "Initial grid #1:" << std::endl;
    }
    else {
        initializeGrid2(grid, size);
        std::cout << "Initial grid #2:" << std::endl;
    }
    printGrid(grid, size);
    std::cout << std::endl;

    // ������� ������
    bool solutionFound = solve(grid, size);
    if (solutionFound) {
        std::cout << "Solution:" << std::endl;
        printGrid(grid, size);
    }
    else {
        std::cout << "The solution does not exist." << std::endl;
    }
    std::cout << "\n--------------------------------------------------\n" << std::endl;
}

// ������� ������� ��������
int main() {
    int choice;
    bool validChoice = false;

    // ���� ������ 䳿
    std::cout << "Choose an action:" << std::endl;
    std::cout << "1 - Solve grid #1" << std::endl;
    std::cout << "2 - Solve grid #2" << std::endl;
    std::cout << "3 - Solve both grids" << std::endl;
    std::cout << "4 - Enter your own grid" << std::endl;
    std::cout << "Enter the number (1-4): ";

    // �������� ���������� ��������
    while (!validChoice) {
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 4) {
                validChoice = true;
            }
            else {
                std::cout << "Invalid input. Enter a number from 1 to 4: ";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter a number from 1 to 4: ";
        }
    }

    switch (choice) {
    case 1:
        solveAndPrintGrid(1);
        break;
    case 2:
        solveAndPrintGrid(2);
        break;
    case 3:
        solveAndPrintGrid(1);
        solveAndPrintGrid(2);
        break;
    case 4:
    {
        const int size = 10;  // ����� ���� 10x10
        std::vector<std::vector<char>> grid(size);
        for (int i = 0; i < size; i++) {
            grid[i].resize(size, ' ');
        }
        std::cout << "\nEnter the initial 10x10 grid configuration." << std::endl;
        std::cout << "Use 'X', 'O' or '.' for an empty cell." << std::endl;
        std::cout << "Enter lines one at a time(10 characters per line) :\n" << std::endl;
        std::string line;
        std::cin.ignore();
        // ���������� ����� ����
        for (int i = 0; i < size; i++) {
            bool validLine = false;
            while (!validLine) {
                std::cout << "Line " << (i + 1) << ": ";
                std::getline(std::cin, line);

                // �������� ����������� �������� �����
                if (line.length() == size) {
                    validLine = true;
                    for (int j = 0; j < size; j++) {
                        if (line[j] == 'X' || line[j] == 'x') {
                            grid[i][j] = 'X';
                        }
                        else if (line[j] == 'O' || line[j] == 'o' || line[j] == '0') {
                            grid[i][j] = 'O';
                        }
                        else {
                            grid[i][j] = ' ';
                        }
                    }
                }
                else {
                    std::cout << "The string must contain exactly " << size << " characters. Try again." << std::endl;
                }
            }
        }
        // ��������� �� �������� ������� ����
        std::cout << "\nYour initial grid:" << std::endl;
        printGrid(grid, size);
        std::cout << std::endl;

        bool solutionFound = solve(grid, size);
        if (solutionFound) {
            std::cout << "Solution:" << std::endl;
            printGrid(grid, size);
        }
        else {
            std::cout << "The solution does not exist." << std::endl;
        }
    }
    break;
    }
    return 0;
}