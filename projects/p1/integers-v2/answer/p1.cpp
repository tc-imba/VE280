//
// Created by liu on 17-5-27.
//

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/**
 * avoid temp variable with std::pair, though it is unnecessary at all
 * @param num
 * @return whether num is a fibonacci number
 */
bool fibonacci(unsigned int num)
{
    pair<unsigned int, unsigned int> queue(0, 1);
    if (num == 0 || num == 1)return true;
    while (true)
    {
        queue = make_pair(queue.second, queue.first + queue.second);
        if (num == queue.second)return true;
        if (num < queue.second)return false;
    }
}

/**
 * normal implementation
 * @param num
 * @return whether num is a fibonacci number
 */
bool fibonacci_2(unsigned int num)
{
    unsigned int a = 0, b = 1;
    if (num == a || num == b)return true;
    while (true)
    {
        unsigned int temp = a;
        a = b;
        b = temp + b;
        if (num == b)return true;
        if (num < b)return false;
    }
}

/**
 * @param num
 * @return whether num is a consecutive number
 */
bool consecutive(unsigned int num)
{
    for (int n = sqrt(num); n >= 0; n--)
    {
        auto sum = n * n;
        if (sum == num)return true;
        for (auto m = n - 1; m >= 0; m--)
        {
            sum += m * m;
            if (sum == num)return true;
            if (sum > num)break;
        }
    }
    return false;
}

/**
 * @param num
 * @return whether num is a repeated number
 */
bool repeated(unsigned int num)
{
    string str;
    while (num > 0)
    {
        str += num % 10 + '0';
        num /= 10;
    }
    // String of length 1 must be false
    if (str.length() < 2)return false;
    for (int i = 1; i <= str.length() / 2; i++)
    {
        // The digits of the repeated string must be a divisor of the total length
        if (str.length() % i > 0)continue;
        // Save the first i digits
        string repeat = str.substr(0, i);
        bool flag = true;
        for (int j = i; j < str.length(); j += i)
        {
            // Set the flag when any of the tests failed
            if (str.substr(j, i) != repeat)
            {
                flag = false;
                break;
            }
        }
        // test passed, it is repeated with i digits
        if (flag) return true;
    }
    // All tests failed
    return false;
}

/**
 * A complex implementation of divisor_sum, but very fast
 * @param num
 * @return whether num is a divisor_sum
 */
bool divisor(unsigned int num)
{
    // Set it bigger if you want to test bigger int.
    // It is always very fast.
    const int MAX_NUM = 10000000;
    const int MAX_NUM_SQRT = sqrt(MAX_NUM) + 1;
    // Print a prime table from 2 to MAX_NUM_SQRT
    int prime_num = MAX_NUM_SQRT - 1;
    bool prime_arr[MAX_NUM_SQRT + 1] = {};
    prime_arr[0] = prime_arr[1] = true;
    for (int i = 2; i <= 57; i++)
    {
        for (int j = i * 2; j <= MAX_NUM_SQRT; j += i)
        {
            if (!prime_arr[j])
            {
                prime_arr[j] = true;
                prime_num--;
            }
        }
    }
    int prime_table[prime_num] = {}, n = 0;
    for (auto i = 2; i <= MAX_NUM_SQRT; i++)
    {
        !prime_arr[i] ? prime_table[n++] = i : 1;
    }
    // Calculate the sum of its proper divisors
    // This algorithm is quite confusing
    // Initialize sum as 1 (all numbers have the divisor 1)
    // i represents the prime we are trying now
    int sum = 1, temp = 0, last = -1, i = 0;
    int num_ = num; // save the number at first
    while (num > 1)
    {
        // Use the next prime in the table if we haven't try them all
        // Otherwise, use the number itself as the divisor
        int divisor = i >= prime_num ? num : prime_table[i];
        if (num % divisor == 0)
        {
            // If the number can be divided by the divisor, divide it.
            num /= divisor;
            // If the divisor is new, sum += sum * divisor.
            // If the divisor is used twice, sum += sum_of_the_first_time * divisor ^ 2,
            // here temp = sum_of_the_first_time * divisor
            // If the divisor is used the third time, sum += sum_of_the_first_time * divisor ^ 3,
            // here temp = sum_of_the_first_time * divisor ^ 2
            // And so on...  Think about the usage of temp carefully.
            temp = (last == i ? temp : sum) * divisor;
            sum += temp;
            // last is used to record the last divisor, and minus i by 1 to reuse the divisor
            last = i--;
        }
        i++;
    }
    // In the above algorithm, actually the number itself is calculated, so subtract it here
    sum -= num_;
    return sum == num_;
}

/**
 * A simple implementation of divisor_sum, slow when MAX_NUM >= 1000000000
 * @param num
 * @return whether num is a divisor_sum
 */
bool divisor_2(unsigned int num)
{
    int sum = 0;
    for (int i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)sum += i;
    }
    return sum == num;
}

int main()
{
    int choice, num;
    bool flag;
    do
    {
        cout << "Please enter the test choice: " << endl;
        cin >> choice;
    } while (choice <= 0 || choice > 4);
    do
    {
        cout << "Please enter the number for test: " << endl;
        cin >> num;
    } while (num < 0 || num > 1e7);
    switch (choice)
    {
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
