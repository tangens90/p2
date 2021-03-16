#include <iostream>
#include <stack>

using std::cout;
using std::endl;

class Struktura {
public:
    int *tab;
    int n;
    std::stack<int> s;

    Struktura(int n) {
        tab = new int[n]{0};
        this->n = n;
    }

    ~Struktura() {
        delete [] tab;
    }
};

void insert(int i, Struktura &s) {
    if (s.tab[i - 1] == 0) {
        s.tab[i - 1] = 1;
        s.s.push(i - 1);
    }
}

bool search(int i, Struktura &s) {
    return s.tab[i - 1] == 1;
}

void select(Struktura &s) {
    if (s.s.empty())
        return;

    s.tab[s.s.top()] = 0;
    s.s.pop();
}

int main(void) {
    cout << std::boolalpha;
    Struktura s(5);
    select(s);
    insert(1, s);
    select(s);
    select(s);
    insert(2, s);
    insert(3, s);
    cout << search(2, s) << endl;
    cout << search(3, s) << endl;
    cout << search(5, s) << endl;
    select(s);

    cout << search(2, s) << endl;
    cout << search(3, s) << endl;
    cout << search(5, s) << endl;
    select(&s);

    cout << search(2, s) << endl;
    cout << search(3, s) << endl;
    cout << search(5, s) << endl;
    select(&s);

    insert(4, s);
    insert(4, s);
    cout << search(4, s) << endl;
    select(s);
    cout << search(4, s) << endl;
    select(s);
}
