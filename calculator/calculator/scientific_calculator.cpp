#include <iostream>
#include <math.h>
#include <windows.h>
#include <cmath>        // Для математических функций
#include <iostream>
#include <math.h>
#include <windows.h>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

#define PLAIN_WIDTH 129
#define PLAIN_HEIGHT 65
#define PI 3.14159265358979323846

char plain[PLAIN_HEIGHT][PLAIN_WIDTH];

// Функции
void printPlain(char* arrayStart);
void drawFunction(double (*func)(double), char symbol, double x_start, double x_end);
double cube(double x);
double squareFunc(double x);
double ctg(double x);

// Функция для ввода чисел
vector<double> inputNumbers() {
    int count;
    double temp;
    vector<double> numbers;

    cout << "Сколько чисел вы хотите ввести? ";
    cin >> count;

    cout << "Введите числа: ";
    for (int i = 0; i < count; i++) {
        cin >> temp;
        numbers.push_back(temp);
    }
    return numbers;
}

// Главная функция
void mainMenu() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int modeChoice;
    do {
        cout << "\n=== Главное меню ===" << endl;
        cout << "1. Научный калькулятор" << endl;
        cout << "2. Построение графиков функций" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите режим: ";
        cin >> modeChoice;

        if (modeChoice == 1) {
            // Логика калькулятора
            int choice;
            double result;
            vector<double> numbers;

            do {
                cout << "\n===== Калькулятор =====" << endl;
                cout << "1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление\n5. Степень\n6. Квадратный корень\n";
                cout << "7. Синус\n8. Косинус\n9. Тангенс\n10. Логарифм\n0. Назад" << endl;
                cout << "Выберите операцию: ";
                cin >> choice;

                switch (choice) {
                case 1: numbers = inputNumbers(); result = 0; for (double num : numbers) result += num; break;
                case 2: numbers = inputNumbers(); result = numbers[0]; for (size_t i = 1; i < numbers.size(); i++) result -= numbers[i]; break;
                case 3: numbers = inputNumbers(); result = 1; for (double num : numbers) result *= num; break;
                case 4: numbers = inputNumbers(); result = numbers[0]; for (size_t i = 1; i < numbers.size(); i++) result /= numbers[i]; break;
                case 5: { double base, exp; cout << "Введите число и степень: "; cin >> base >> exp; result = pow(base, exp); } break;
                case 6: cout << "Введите число: "; cin >> result; result = sqrt(result); break;
                case 7: cout << "Введите угол (градусы): "; cin >> result; result = sin(result * PI / 180); break;
                case 8: cout << "Введите угол (градусы): "; cin >> result; result = cos(result * PI / 180); break;
                case 9: cout << "Введите угол (градусы): "; cin >> result; result = tan(result * PI / 180); break;
                case 10: cout << "Введите число: "; cin >> result; result = log(result); break;
                case 0: continue;
                default: cout << "Ошибка ввода!" << endl; continue;
                }
                cout << "Результат: " << result << endl;
            } while (choice != 0);

        }
        else if (modeChoice == 2) {
            // Логика построения графиков
            for (int y = 0; y < PLAIN_HEIGHT; y++) {
                for (int x = 0; x < PLAIN_WIDTH; x++) {
                    plain[y][x] = '.';
                    plain[PLAIN_HEIGHT / 2 - 1][x] = '-';
                }
                plain[y][PLAIN_WIDTH / 2 - 1] = '|';
            }

            int choice;
            cout << "Сколько функций вы хотите видеть? (до 5): ";
            cin >> choice;

            for (int i = 0; i < choice; i++) {
                string funcName;
                char symbol;

                cout << "Введите функцию (cos, sin, tg, ctg, log, abs, square, cube): ";
                cin >> funcName;
                cout << "Символ для графика: ";
                cin >> symbol;

                if (funcName == "cos") drawFunction(cos, symbol, -PI, PI);
                else if (funcName == "sin") drawFunction(sin, symbol, -PI, PI);
                else if (funcName == "tg") drawFunction(tan, symbol, -PI / 2, PI / 2);
                else if (funcName == "ctg") drawFunction(ctg, symbol, -PI, PI);
                else if (funcName == "log") drawFunction(log, symbol, 0.1, 10);
                else if (funcName == "abs") drawFunction(abs, symbol, -10, 10);
                else if (funcName == "square") drawFunction(squareFunc, symbol, -10, 10);
                else if (funcName == "cube") drawFunction(cube, symbol, -10, 10);
                else cout << "Функция не поддерживается!" << endl;
            }
            printPlain(&(plain[0][0]));
        }

    } while (modeChoice != 0);

    cout << "До свидания!" << endl;
}

int main() {
    mainMenu();
    return 0;
}

// Дополнительные функции
void printPlain(char* arrayStart) {
    int i = 1;
    while (i <= PLAIN_WIDTH * PLAIN_HEIGHT) {
        cout << *(arrayStart + i - 1);
        if (i % PLAIN_WIDTH == 0) cout << endl;
        i++;
    }
}

void drawFunction(double (*func)(double), char symbol, double x_start, double x_end) {
    for (double x = x_start; x <= x_end; x += 0.1) {
        double y = func(x);
        int screenX = static_cast<int>((x + PI) * (PLAIN_WIDTH / (2 * PI)));
        int screenY = static_cast<int>(-y * 10 + PLAIN_HEIGHT / 2);

        if (screenX >= 0 && screenX < PLAIN_WIDTH && screenY >= 0 && screenY < PLAIN_HEIGHT) {
            if (plain[screenY][screenX] == '.') plain[screenY][screenX] = symbol;
        }
    }
}

double cube(double x) { return x * x * x; }
double squareFunc(double x) { return x * x - 2; }
double ctg(double x) { return cos(x) / sin(x); }