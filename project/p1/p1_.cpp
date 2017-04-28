#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

bool IsTriangleNum(int Num) {
	int i;
	for (i = 0; i <= Num; i++) {
		if (i * (i + 1) / 2 == Num) {
			return 1;
		}
	}
	return 0;
}

bool IsPlindrome(int Num) { // OriginNum == ReverseNum.
	int NumLength = log(Num) / log(10) + 1;
	int i, NewNum = 0, NumTemp = Num, Remain;
	for (i = NumLength; i >= 1; i--) {
		Remain = NumTemp % 10; // The number of that figure.
		NumTemp /= 10;
		NewNum += Remain * pow(10, i - 1);
	}
	if (NewNum == Num) {
		return 1;
	}
	return 0;
}

bool IsPowerNum(int Num) {
	int i;
	double Temp;
	for (i = 2; i <= log(Num) / log(2) + 2; i++) {
		Temp = pow(Num, 1.0 / i);
		if (abs(Temp-int(Temp+0.5))<1e-10) {
			return 1;
		}
	}
	return 0;
}

bool IsAbundantNum(int Num) {
	int i, Sum = 0;
	for (i = 1; i <= Num / 2; i++) {
		if (Num % i == 0) {
			Sum += i;
		}
	}
	if (Sum > Num) {
		return 1;
	}
	return 0;
}


int main() {
	int Num, Type;
	for (;;) {
		cout << "Please enter the integer and the test number: ";
		cin >> Num >> Type;
		if (Num > 0 && Num <= 1e7 && Type >= 1 && Type <= 4) {
			break;
		}
	}
	if (Type == 1 && IsTriangleNum(Num) || Type == 2 && IsPlindrome(Num) || Type == 3 && IsPowerNum(Num) || Type == 4 && IsAbundantNum(Num)) {
		cout << "1" << endl;
	}
	else {
		cout << "0" << endl;
	}
	return 0;
}
