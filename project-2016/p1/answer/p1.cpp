#include <iostream>
#include <cmath>

using namespace std;

#define MAX_NUM 10000000

/**
 * judge whether a number is a triangle number
 * @param  int 	num		number
 * @return bool
 */
bool triangle(int num)
{
	int n = sqrt(num * 2);
	return n * (n + 1) == num * 2;
}

/**
 * judge whether a number is a palindrome
 * @param  int 	num		number
 * @return bool
 */
bool palindrome(int num)
{
	int arr[8] = {}, n = 0;
	while (num != 0)
	{
		arr[n++] = num % 10;
		num /= 10;
	}
	for (int i = 0; i < n / 2; i++)
	{
		if (arr[i] != arr[n - 1 - i])
		{
			return 0;
		}
	}
	return 1;
}

/**
 * judge whether a number is a power number
 * @param  int 	num		number
 * @return bool
 */
bool power(int num)
{
	double err = 1e-8;
	for (int i = 2; i <= log(num) / log(2) + 2; i++)
	{
		double n = pow(num, 1.0 / i);
		if (abs(int(n + 0.5) - n) < err)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * judge whether a number is an abundant number
 * @param  int 	num		number
 * @return bool
 */
bool abundant(int num)
{
	int num_ = num;// save the number at first
	// Print a prime table from 2 to 3163
	bool f[3164] = {};
	f[0] = f[1] = 1;
	for (int i = 2; i <= 57; i++)
	{
		for (int j = i * 2; j <= 3163; j += i)
		{
			f[j] = 1;
		}
	}
	int table[447] = {}, n = 0;
	for (int i = 2; i <= 3163; i++)
	{
		!f[i] ? table[n++] = i : 1;
	}
	// Calculate the sum of its proper divisors
	int sum = 1, temp = 0, last = -1, i = 0;
	while(num > 1)
	{
		int divisor = i >= 447 ? num : table[i];
		if (num % divisor == 0)
		{
			num /= divisor;
			temp = (last == i ? temp : sum) * divisor;
			sum += temp;
			last = i--;
		}
		i++;
	}
	sum -= num_;	
	return sum > num_;
}

int main()
{
	begin:
	
	cout << "Please enter the integer and the test number: ";
	int num, type;
	cin >> num >> type;

	if (num <= 0 || num > MAX_NUM)
	{
		goto begin;
	}
	
	switch (type)
	{
	case 1:
		cout << triangle(num);
		break;
	case 2:
		cout << palindrome(num);
		break;
	case 3:
		cout << power(num);
		break;
	case 4:
		cout << abundant(num);
		break;
	default:
		goto begin;
	}
	cout << endl;
	return 0;
}
