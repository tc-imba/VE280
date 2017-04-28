#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
	string worldStr, round;
	cin >> worldStr >> round;
	string cmd = "Project3 species " + worldStr + " " + round + " ";
	string path = ">world-tests//" + worldStr;
	system((cmd + path + "-concise.result").c_str());
	cmd += "v ";
	system((cmd + path + "-verbose.result").c_str());
	
	ifstream c1("world-tests//" + worldStr + "-concise.result");
	ifstream c2("world-tests//" + worldStr + "-concise.answer");
	int line = 1;
	while (!c1.eof() && !c2.eof())
	{
		string s1, s2;
		getline(c1, s1);
		getline(c2, s2);
		if (s1 != s2)
		{
			cout << line << endl;
			cout << s1 << endl << s2 << endl << endl;
		}
		line++;
	}
	c1.close();
	c2.close();
	c1.open("world-tests//" + worldStr + "-verbose.result");
	c2.open("world-tests//" + worldStr + "-verbose.answer");
	line = 1;
	while (!c1.eof() && !c2.eof())
	{
		string s1, s2;
		getline(c1, s1);
		getline(c2, s2);
		if (s1 != s2)
		{
			cout << line << endl;
			cout << s1 << endl << s2 << endl << endl;
		}
		line++;
	}
	c1.close();
	c2.close();
	cout << "END" << endl;
	cin.get();
	return 0;
}