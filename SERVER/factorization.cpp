#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>


#include <map>


using namespace std;

struct polynomial {                 // Структура данных, нужная для хранения многочленов.
    vector<int> monomials;    // Содержит степень многочлена и список одночленов.
    int degree = (int) (monomials.size()) - 1;
};

struct success_and_result {         // Структура данных, хранящая признак успешности проведения операции
    bool success = false;           // и, если операция проведена успешно, её результат.
    polynomial result;
};

struct constant_and_answer {
    int constant;
    vector<polynomial> answer;
};

int calculate(const polynomial &f, int n) { // Считает значение многочлена в целой точке
    int sum = 0;
    int p = 0;
    for (auto i : f.monomials) {
        sum += i * (int) (pow(n, p++));
    }
    return sum;
}

bool equal(double x, double y) { // Сравнивает два числа с плавающей точкой
    return fabs(x - y) < 1e-9;
}

success_and_result divide(polynomial A, polynomial B) { // Делит многочлен на многочлен
    int n = (int) A.monomials.size() - 1;
    int m = (int) B.monomials.size() - 1;
    polynomial Q{vector<int>(n - m + 1)};
    for (int i = n; i >= m; i--) {
        Q.monomials[i - m] = A.monomials[i] / B.monomials[m];
        for (int j = m; j >= 0; j--)
            A.monomials[i - m + j] -= B.monomials[j] * Q.monomials[i - m];
    }
    while (!A.monomials.empty() && equal(A.monomials.back(), 0))
        A.monomials.pop_back();
    if (A.monomials.empty())
        return success_and_result{true, Q};
    else
        return success_and_result{false};
}

vector<int> find_divisors(int n) { // Находит целые делители целого цисла
    vector<int> ans;
    int i;
    n = abs(n);
    ans.push_back(1);
    ans.push_back(-1);
    for (i = 2; i * i < n; i++) {
        if (n % i == 0) {
            ans.push_back(i);
            ans.push_back(-i);
            ans.push_back(n / i);
            ans.push_back(-n / i);
        }
    }
    if (i * i == n) {
        ans.push_back(i);
        ans.push_back(-i);
    }
    if (n != 1 && n != -1) {
        ans.push_back(n);
        ans.push_back(-n);
    }
    return ans;
}

vector<vector<int>> direct_multiplication(const vector<vector<int>> &A, const vector<int> &B) {
    vector<vector<int>> ans;   // Реализует прямое произведение множеств
    for (const auto &a : A) {
        for (const int &b : B) {
            auto t(a);
            t.push_back(b);
            ans.push_back(t);
        }
    }
    return ans;
}

vector<double> get_lagrange(const vector<double> &x, vector<double> f) {
    int N = x.size();   // Высчитывает интерполяционный многочлен Лагранжа по данному набору точек
    vector<double> c(N), temp(N);

    c[0] = f[0];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N - i; j++) temp[j] = (f[j + 1] - f[j]) / (x[j + i] - x[j]);
        f = temp;
        c[i] = f[0];
    }
    return c;
}

vector<double> standard_polynomial(const vector<double> &c, const vector<double> &x) {
    int N = x.size();   // Приводит многочлен к стандартному виду
    vector<double> a(N, 0.0);
    vector<double> p(N), prev(N);

    p[0] = 1;
    a[0] = c[0] * p[0];
    for (int i = 1; i < N; i++) {
        prev = p;
        p[0] = -x[i - 1] * prev[0];
        a[0] += c[i] * p[0];
        for (int j = 1; j <= i; j++) {
            p[j] = prev[j - 1] - x[i - 1] * prev[j];
            a[j] += c[i] * p[j];
        }
    }

    return a;
}

success_and_result interpol_lagrange(const vector<double> &x, const vector<double> &y) {
    vector<double> c = get_lagrange(x, y);      // Переводит полученный многочлен в виде вектора
    vector<double> arrayp = standard_polynomial(c, x);  // вещественных чисел в многочлен типа polynomial

    polynomial ans;
    for (double i : arrayp) {
        if (!equal(i, int(i))) {
            return success_and_result{false};
        } else {
            ans.monomials.push_back((int) (i));
        }
    }

    while (!ans.monomials.empty() && equal(ans.monomials.back(), 0))
        ans.monomials.pop_back();


    return success_and_result{ans.monomials.size() == x.size(), ans};
}

string str_polynomial(pair<vector<int>, int> a, bool brackets) {  // Красиво и понятно выводит на экран многочлен
    int n = a.first.size() - 1;
    stringstream str_ans;

    if (brackets) str_ans << '(';

    if (n > 1) {
        if (a.first[n] == -1)
            str_ans << "-x^" << n;
        else if (a.first[n] == 1)
            str_ans << "x^" << n;
        else
            str_ans << a.first[n] << "x^" << n;
    }

    for (int i = n - 1; i > 1; --i) {
        if (a.first[i] != 0) {
            if (a.first[i] > 0) {
                str_ans << '+';
                (a.first[i] == 1) ? str_ans << "x^" << i : str_ans << a.first[i] << "x^" << i;
            } else
                (a.first[i] == -1) ? str_ans << "-x^" << i : str_ans << a.first[i] << "x^" << i;
        }
    }

    if (a.first[1] != 0) {
        if (a.first[1] > 0) {
            if (n > 1)
                str_ans << '+';
            (a.first[1] == 1) ? str_ans << "x" : str_ans << a.first[1] << "x";
        } else
            (a.first[1] == -1) ? str_ans << "-x" : str_ans << a.first[1] << "x";
    }

    if (a.first[0] != 0) {
        if (a.first[0] > 0) {
            str_ans << '+';
            str_ans << a.first[0];
        } else
            str_ans << a.first[0];
    }

    if (brackets) str_ans << ")";

    if (a.second > 1) str_ans << "^" << a.second;

    return str_ans.str();
}

success_and_result factorize(const polynomial &f) {  // Факторизует многочлен
    polynomial g;
    vector<int> M;
    vector<vector<int>> U;
    success_and_result interpol;


    for (int i = 0; i * 2 <= f.degree; i++) {  // Поиск линейных делителей вида x - i
        if (calculate(f, i) == 0) {
            g.monomials = vector<int>{-i, 1};
            g.degree = 1;
            return success_and_result{true, g};
        }
    }
    auto f0 = calculate(f, 0);
    auto divisors_f0 = find_divisors(f0);
    U = direct_multiplication(vector<vector<int>>(1), divisors_f0);
    for (int i = 1; i * 2 <= f.degree; i++) {   // Поиск остальных возможных делителей
        auto fi = calculate(f, i);
        M = find_divisors(fi);
        U = direct_multiplication(U, M);
        vector<double> x;
        for (int j = 0; j <= i; j++) {
            x.push_back(j);
        }
        for (const auto &u : U) {
            vector<double> y;
            for (int j = 0; j <= i; j++) {
                y.push_back(double(u.at(j)));
            }

            interpol = interpol_lagrange(x, y);

            if (interpol.success) {
                g = interpol.result;
                if (divide(f, g).success) {
                    g.degree = i;
                    return success_and_result{true, g};
                }
            }
        }
    }
    return success_and_result{false};
}

int count(const string& s, char c) {
    int cnt = 0;
    for (char i : s) {
        if (i == c) cnt++;
    }
    return cnt;
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a%b, b);
    return gcd(a, b%a);
}

constant_and_answer remove_constant(const vector<polynomial>& a) {
    int constant = 1;
    vector<polynomial> b;
    for (auto poly : a) {
        vector<int> monos = poly.monomials;
        int t_constant = gcd(monos[0], monos[1]);
        for (int i = 2; i < monos.size(); ++i) {
            t_constant = gcd(t_constant, monos[i]);
        }
        for (int & mono : monos) {
            mono /= t_constant;
        }
        constant *= t_constant;
        poly.monomials = monos;
        b.push_back(poly);
    }

    return constant_and_answer{constant, b};
}

map<vector<int>, int> get_degrees(const vector<polynomial>& a) {
    map<vector<int>, int> b;
    map<vector<int>, int> :: iterator it;

    for (const auto& poly : a) {
        it = b.find(poly.monomials);
        if (it != b.end()) {
            it->second++;
        }
        else {
            b.insert(make_pair(poly.monomials, 1));
        }
    }


    return b;
}

string get_str_answer(const string& req) {
    int n;
    stringstream ss;
    stringstream str_ans;
    bool brackets = false;

    n = count(req, ' ');
    if (n == 0) {
        return "Неверный формат введенных данных!\n";
    }

    ss << req;
    polynomial a{vector<int>(n + 1), n};

    for (int i = n; i >= 0; --i) {
        ss >> a.monomials[i];
    }

    str_ans << "Введенный многочлен:\n";
    str_ans << str_polynomial(make_pair(a.monomials, 1), brackets) << "\n";

    auto factor = factorize(a);
    brackets = factor.success;
    vector<polynomial> answer;
    while (factor.success) {
        answer.push_back(factor.result);
        a = divide(a, factor.result).result;
        factor = factorize(a);
    }

    if (!a.monomials.empty()) {
        answer.push_back(a);
    }

    int constant;
    auto b = remove_constant(answer);
    constant = b.constant;
    answer = b.answer;
    if (!brackets)
        brackets = (constant != 1);

    map<vector<int>, int> answer_with_degrees;

    answer_with_degrees = get_degrees(answer);

    str_ans << "Разложение на неприводимые множители:\n";

    if (constant > 1) str_ans << constant;
    for (const auto &poly_and_degree : answer_with_degrees) {
        str_ans << str_polynomial(poly_and_degree, brackets);
    }
    return str_ans.str();
}

int main(int argc, char* argv[]) {
    //system("chcp 65001");
    string inputString = argv[1];
    cout << get_str_answer(inputString);
}
