#include<iostream>
using namespace std;

int steps = 0; 

void haNoiTower(int n, char A, char B, char C) {
    if (n == 1) {
        steps++;
        cout << "第" << steps << "步: " << A << " -> " << C << endl;
        return;
    }

    haNoiTower(n - 1, A, C, B);

    steps++;
    cout << "第" << steps << "步: " << A << " -> " << C << endl;

    haNoiTower(n - 1, B, A, C);
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) return 0;
    haNoiTower(n, 'A', 'B', 'C');
    cout << "总步数: " << steps << endl;
    return 0;
}