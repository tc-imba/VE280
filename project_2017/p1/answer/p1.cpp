//
// Created by liu on 17-5-27.
//

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

bool fibonacci(unsigned int num) {
    pair<unsigned int, unsigned int> queue(0, 1);
    if (num == 0 || num == 1)return true;
    while (true) {
        queue = make_pair(queue.second, queue.first + queue.second);
        if (num == queue.second)return true;
        if (num < queue.second)return false;
    }
}

bool consecutive(unsigned int num) {
    for (int n = sqrt(num); n >= 0; n--) {
        auto sum = n * n;
        if (sum == num)return true;
        for (auto m = n - 1; m >= 0; m--) {
            sum += m * m;
            if (sum == num)return true;
            if (sum > num)break;
        }
    }
    return false;
}

bool repeated(unsigned int num) {
    string str;
    while (num > 0) {
        str += num % 10 + '0';
        num /= 10;
    }
    if (str.length() < 2)return false;
    for (int i = 1; i <= str.length() / 2; i++) {
        if (str.length() % i > 0)continue;
        string repeat = str.substr(0, i);
        bool flag = true;
        for (int j = i; j < str.length(); j += i) {
            if (str.substr(j, i) != repeat) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;
}

bool divisor(unsigned int num) {
    int num_ = num;// save the number at first
    // Print a prime table from 2 to 3163
    bool prime_arr[3164] = {};
    prime_arr[0] = prime_arr[1] = true;
    for (int i = 2; i <= 57; i++) {
        for (int j = i * 2; j <= 3163; j += i) {
            prime_arr[j] = true;
        }
    }
    int prime_table[447] = {}, n = 0;
    for (auto i = 2; i <= 3163; i++) {
        !prime_arr[i] ? prime_table[n++] = i : 1;
    }
    // Calculate the sum of its proper divisors
    int sum = 1, temp = 0, last = -1, i = 0;
    while (num > 1) {
        int divisor = i >= 447 ? num : prime_table[i];
        if (num % divisor == 0) {
            num /= divisor;
            temp = (last == i ? temp : sum) * divisor;
            sum += temp;
            last = i--;
        }
        i++;
    }
    sum -= num_;
    return sum == num_;
}

int main() {
    int choice, num;
    do {
        cout << "Please enter the test choice: ";
        cin >> choice;
    } while (choice <= 0 || choice >= 4);
    do {
        cout << "Please enter the number for test: ";
        cin >> num;
    } while (num < 0 || num > 1e7);
    bool flag;
    switch (choice) {
        case 1:
            flag = fibonacci(num);
            break;
        case 2:
            flag = consecutive(num);
            break;
        case 3:
            flag = repeated(num);
            break;
        case 4:
            flag = divisor(num);
            break;
    }
    cout << (flag ? "Pass" : "Fail") << endl;
}