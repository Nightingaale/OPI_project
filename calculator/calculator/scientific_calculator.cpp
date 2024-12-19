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

// Ôóíêöèè
void printPlain(char* arrayStart);
void drawFunction(double (*func)(double), char symbol, double x_start, double x_end);
double cube(double x);
double squareFunc(double x);
double ctg(double x);

// Ôóíêöèÿ äëÿ ââîäà ÷èñåë
vector<double> inputNumbers() {
    int count;
    double temp;
    vector<double> numbers;

    cout << "Ñêîëüêî ÷èñåë âû õîòèòå ââåñòè? ";
    cin >> count;

    cout << "Ââåäèòå ÷èñëà: ";
    for (int i = 0; i < count; i++) {
        cin >> temp;
        numbers.push_back(temp);
    }
    return numbers;
}

// Ãëàâíàÿ ôóíêöèÿ
void mainMenu() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int modeChoice;
    do {
        cout << "\n=== Ãëàâíîå ìåíþ ===" << endl;
        cout << "1. Íàó÷íûé êàëüêóëÿòîð" << endl;
        cout << "2. Ïîñòðîåíèå ãðàôèêîâ ôóíêöèé" << endl;
        cout << "0. Âûõîä" << endl;
        cout << "Âûáåðèòå ðåæèì: ";
        cin >> modeChoice;

        if (modeChoice == 1) {
            // Ëîãèêà êàëüêóëÿòîðà
            int choice;
            double result;
            vector<double> numbers;

            do {
                cout << "\n===== Êàëüêóëÿòîð =====" << endl;
                cout << "1. Ñëîæåíèå\n2. Âû÷èòàíèå\n3. Óìíîæåíèå\n4. Äåëåíèå\n5. Ñòåïåíü\n6. Êâàäðàòíûé êîðåíü\n";
                cout << "7. Ñèíóñ\n8. Êîñèíóñ\n9. Òàíãåíñ\n10. Ëîãàðèôì\n0. Íàçàä" << endl;
                cout << "Âûáåðèòå îïåðàöèþ: ";
                cin >> choice;

                switch (choice) {
                case 1: numbers = inputNumbers(); result = 0; for (double num : numbers) result += num; break;
                case 2: numbers = inputNumbers(); result = numbers[0]; for (size_t i = 1; i < numbers.size(); i++) result -= numbers[i]; break;
                case 3: numbers = inputNumbers(); result = 1; for (double num : numbers) result *= num; break;
                case 4: numbers = inputNumbers(); result = numbers[0]; for (size_t i = 1; i < numbers.size(); i++) result /= numbers[i]; break;
                case 5: { double base, exp; cout << "Ââåäèòå ÷èñëî è ñòåïåíü: "; cin >> base >> exp; result = pow(base, exp); } break;
                case 6: cout << "Ââåäèòå ÷èñëî: "; cin >> result; result = sqrt(result); break;
                case 7: cout << "Ââåäèòå óãîë (ãðàäóñû): "; cin >> result; result = sin(result * PI / 180); break;
                case 8: cout << "Ââåäèòå óãîë (ãðàäóñû): "; cin >> result; result = cos(result * PI / 180); break;
                case 9: cout << "Ââåäèòå óãîë (ãðàäóñû): "; cin >> result; result = tan(result * PI / 180); break;
                case 10: cout << "Ââåäèòå ÷èñëî: "; cin >> result; result = log(result); break;
                case 0: continue;
                default: cout << "Îøèáêà ââîäà!" << endl; continue;
                }
                cout << "Ðåçóëüòàò: " << result << endl;
            } while (choice != 0);

        }
        else if (modeChoice == 2) {
            // Ëîãèêà ïîñòðîåíèÿ ãðàôèêîâ
            for (int y = 0; y < PLAIN_HEIGHT; y++) {
                for (int x = 0; x < PLAIN_WIDTH; x++) {
                    plain[y][x] = '.';
                    plain[PLAIN_HEIGHT / 2 - 1][x] = '-';
                }
                plain[y][PLAIN_WIDTH / 2 - 1] = '|';
            }

            int choice;
            cout << "Ñêîëüêî ôóíêöèé âû õîòèòå âèäåòü? (äî 5): ";
            cin >> choice;

            for (int i = 0; i < choice; i++) {
                string funcName;
                char symbol;

                cout << "Ââåäèòå ôóíêöèþ (cos, sin, tg, ctg, log, abs, square, cube): ";
                cin >> funcName;
                cout << "Ñèìâîë äëÿ ãðàôèêà: ";
                cin >> symbol;

                if (funcName == "cos") drawFunction(cos, symbol, -PI, PI);
                else if (funcName == "sin") drawFunction(sin, symbol, -PI, PI);
                else if (funcName == "tg") drawFunction(tan, symbol, -PI / 2, PI / 2);
                else if (funcName == "ctg") drawFunction(ctg, symbol, -PI, PI);
                else if (funcName == "log") drawFunction(log, symbol, 0.1, 10);
                else if (funcName == "abs") drawFunction(abs, symbol, -10, 10);
                else if (funcName == "square") drawFunction(squareFunc, symbol, -10, 10);
                else if (funcName == "cube") drawFunction(cube, symbol, -10, 10);
                else cout << "Ôóíêöèÿ íå ïîääåðæèâàåòñÿ!" << endl;
            }
            printPlain(&(plain[0][0]));
        }

    } while (modeChoice != 0);

    cout << "Äî ñâèäàíèÿ!" << endl;
}

int main() {
    mainMenu();
    return 0;
}

// Äîïîëíèòåëüíûå ôóíêöèè
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
