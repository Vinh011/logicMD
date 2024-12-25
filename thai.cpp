#include <iostream>
#include <string>
using namespace std;

// Hàm kiểm tra tính hợp lệ của biểu thức
bool kiem_tra_hop_le(const string& bt) {
    int ngoac = 0;
    bool lastWasOperator = true; // Biến để kiểm tra toán tử liên tiếp hoặc không
    for (char c : bt) {
        if (c == '(') ngoac++;
        else if (c == ')') ngoac--;
        else if (!(isalnum(c) || c == ' ' || c == '&' || c == '|' || c == '!' || c == '>' || c == '(' || c == ')'))
            return false; // Kiểm tra toán tử hợp lệ (bao gồm > cho suy ra)

        // Kiểm tra các toán tử không hợp lệ
        if (c == '&' || c == '|' || c == '>' || c == '!') {
            if (lastWasOperator) return false; // Không thể có hai toán tử liên tiếp
            lastWasOperator = true;
        } else {
            lastWasOperator = false;
        }
        if (ngoac < 0) return false; // Kiểm tra ngoặc đóng quá sớm
    }
    return ngoac == 0 && !lastWasOperator; // Biểu thức hợp lệ nếu số lượng ngoặc mở và đóng bằng nhau
}

// Hàm kiểm tra số lượng biến và giá trị có khớp
bool kiem_tra_su_khop(const string& bien, const string& gia_tri) {
    return bien.size() == gia_tri.size();
}

// Hàm tính toán giá trị biểu thức logic
bool tinh_gia_tri(string bt, const string& bien, const string& gia_tri) {
    // Xử lý biến với giá trị tương ứng
    for (size_t i = 0; i < bien.size(); ++i) {
        for (char &c : bt) {
            if (c == bien[i]) {
                c = (gia_tri[i] == '1') ? '1' : '0'; // '1' => 'True', '0' => 'False'
            }
        }
    }

    string st;
    for (char c : bt) {
        if (c == ' ') continue; // Bỏ qua khoảng trắng

        if (c == '1' || c == '0') { // Thêm giá trị vào stack
            st += c;
        } else if (c == '!') { // Xử lý NOT
            if (st.empty()) return false;
            st.back() = (st.back() == '1') ? '0' : '1';
        } else if (c == '&' || c == '|') { // Xử lý AND và OR
            if (st.size() < 2) return false;
            char b = st.back(); st.pop_back();
            char a = st.back(); st.pop_back();
            char result = (c == '&') ? ((a == '1' && b == '1') ? '1' : '0') : ((a == '1' || b == '1') ? '1' : '0');
            st += result;
        } else if (c == '>') { // Xử lý "→" (Imply) đã thay dấu '→' bằng '>'
            if (st.size() < 2) return false;
            char b = st.back(); st.pop_back();
            char a = st.back(); st.pop_back();
            st += ((a == '0' || b == '1') ? '1' : '0'); // Áp dụng định lý "A → B = ¬A ∨ B"
        }
    }
    if (st.size() != 1) return false;
    return st.back() == '1'; // Kết quả cuối cùng
}

int main() {
    string bt, bien, gia_tri;
    cout << "Nhập biểu thức logic: ";
    getline(cin, bt); // Nhập biểu thức logic

    // Kiểm tra tính hợp lệ của biểu thức
    if (!kiem_tra_hop_le(bt)) {
        cout << "Biểu thức không hợp lệ." << endl;
        return 1;
    }

    // Nhập danh sách biến và giá trị của các biến
    cout << "Nhập danh sách biến (ví dụ: ABC): ";
    cin >> bien;
    cout << "Nhập giá trị cho các biến (True/False): ";
    cin >> gia_tri;

    // Kiểm tra số lượng biến và giá trị có khớp
    if (!kiem_tra_su_khop(bien, gia_tri)) {
        cout << "Số lượng biến và giá trị không khớp.\n";
        return 1;
    }

    // Tính toán giá trị của biểu thức logic
    bool ket_qua = tinh_gia_tri(bt, bien, gia_tri);
    cout << "Biểu thức hợp lệ." << endl;
    cout << "Kết quả: " << (ket_qua ? "True" : "False") << endl;

    return 0;
}
