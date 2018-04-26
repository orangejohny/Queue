#include <queue.hpp>
#include <iostream>
#include <fstream>

int main() {
    using std::cout;
    using std::endl;
    using std::boolalpha;

    Queue<int> q1;

    Queue<int> q2 = {1, 2, 3, 4};

    Queue<int> q3{q2};

    cout << q2 << endl;
    cout << q3 << endl;

    q1.swap(q3);
    cout << q1 << endl;

    cout << boolalpha << q3.empty() << endl;

    cout << q1.size() << endl;

    q3.push(5);
    cout << q3 << endl;

    std::ofstream output{"queue.bin"};
    output << q3;
    output.close();

    Queue<int> q4;
    std::ifstream input{"queue.bin"};
    input >> q4;

    cout << (q4 == q3) << endl;

    cout << q4.front() << endl;
    cout << q4.back() << endl;

    q4.pop();
    cout << q4 << endl;

    try {
        q4.front() = 6;
    } catch (std::length_error e) {
        std::cout << e.what() << endl;
    }
}
