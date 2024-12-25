#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

// Hàm kiểm tra giá trị của một mệnh đề
bool evaluateExpression(const string& expr, const unordered_map<char, bool>& values) {
    // Đánh giá mệnh đề logic
    // Duyệt qua từng ký tự trong mệnh đề
    for (char c : expr) {
        if (isalpha(c)) { // Nếu là biến (A, B, C...)
            if (values.find(c) != values.end()) {
                return values.at(c); // Trả về giá trị của biến từ map
            }
        }
    }
    return false;
}

// Hàm tạo bảng chân trị
bool createTruthTable(const vector<string>& premises, const string& conclusion) {
    unordered_map<char, bool> values;
    vector<char> variables = {'P', 'Q', 'R'}; // Các biến trong biểu thức (có thể thêm các biến khác nếu cần)
    int numVariables = variables.size();
    int numRows = pow(2, numVariables);  // Tổng số tổ hợp giá trị của các biến

    // Tạo bảng chân trị
    for (int i = 0; i < numRows; i++) {
        // Gán giá trị cho các biến
        for (int j = 0; j < numVariables; j++) {
            values[variables[j]] = (i & (1 << j)) > 0;  // Kiểm tra bit j trong số i
        }

        // Kiểm tra xem tất cả các tiền đề có đúng không
        bool premisesValid = true;
        for (const string& premise : premises) {
            if (!evaluateExpression(premise, values)) {
                premisesValid = false;
                break;
            }
        }

        // Nếu các tiền đề đúng mà kết luận sai, thì công thức sai
        if (premisesValid && !evaluateExpression(conclusion, values)) {
            return false;
        }
    }
    return true;  // Nếu tất cả các tổ hợp thỏa mãn, kết luận đúng
}

int main() {
    // Nhập các mệnh đề (premises) và kết luận cần chứng minh
    int n;
    cout << "Nhập số lượng mệnh đề: ";
    cin >> n;

    vector<string> premises(n);
    cout << "Nhập các mệnh đề: ";
    for (int i = 0; i < n; i++) {
        cin >> premises[i];
    }

    string conclusion;
    cout << "Nhập kết luận cần chứng minh: ";
    cin >> conclusion;

    // Kiểm tra sự đúng/sai của công thức logic
    if (createTruthTable(premises, conclusion)) {
        cout << "Chứng minh đúng." << endl;
    } else {
        cout << "Chứng minh sai." << endl;
    }

    return 0;
}
