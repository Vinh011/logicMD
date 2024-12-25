#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Hàm predicate mặc định
bool P(int x) {
    return x > 1;  // P(x) = x > 1
}

bool Q(int x) {
    return x % 2 == 0;  // Q(x) = x % 2 == 0
}

// Kiểm tra ∀x (P(x) → Q(x))
bool forall_x(const vector<int>& domain) {
    for (int x : domain) {
        if (P(x) && !Q(x)) {
            return false;  // Nếu P(x) đúng mà Q(x) sai, công thức sai
        }
    }
    return true;  // Nếu tất cả các x thỏa mãn, công thức đúng
}

// Kiểm tra ∃y P(y)
bool exists_y(const vector<int>& domain) {
    for (int y : domain) {
        if (P(y)) {
            return true;  // Nếu tồn tại y thỏa mãn P(y), công thức đúng
        }
    }
    return false;  // Nếu không có y nào thỏa mãn, công thức sai
}

// Kiểm tra công thức logic
bool verifyFormula(const vector<int>& domain) {
    return forall_x(domain) && exists_y(domain);
}

int main() {
    // Nhập miền giá trị (domain) của các biến
    int n;
    cout << "Nhập số lượng phần tử trong miền giá trị: ";
    cin >> n;
    
    vector<int> domain(n);
    cout << "Nhập các giá trị trong miền (các số nguyên): ";
    for (int i = 0; i < n; i++) {
        cin >> domain[i];
    }

    // Nhập định nghĩa cho các predicate
    char choice;
    cout << "Có muốn thay đổi định nghĩa của P(x) và Q(x)? (y/n): ";
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        cout << "Nhập định nghĩa cho P(x) (ví dụ: x > 1): ";
        // Có thể thêm mã để nhập và áp dụng định nghĩa tùy ý từ người dùng
        cout << "P(x) mặc định: x > 1" << endl;
        
        cout << "Nhập định nghĩa cho Q(x) (ví dụ: x % 2 == 0): ";
        // Có thể thêm mã để nhập và áp dụng định nghĩa tùy ý từ người dùng
        cout << "Q(x) mặc định: x % 2 == 0" << endl;
    }

    // Kiểm tra công thức ∀x (P(x) → Q(x)) ∧ ∃y P(y)
    if (verifyFormula(domain)) {
        cout << "Công thức đúng." << endl;
    } else {
        cout << "Công thức sai." << endl;
    }

    return 0;
}
