// CA_WORKSPACE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
	
using namespace std;

vector<int> kmp(const string& s) {
	vector<int> pi(s.size());
	int i = 1;
	while (i < s.size()) {
		int j = pi[i - 1];
		while (j > 0 && s[j] != s[i])
			j = pi[j - 1];
		if (s[j] == s[i])
			j++;
		pi[i] = j;
		++i;
	}
	return pi;
}

int main()
{
	int size = -1;
	string message = "NO";
	string s = "aca abafdfacaaba"; //000100000000001234000
	//char chs[100];
	//cin >> s;

	vector<int> str = kmp(s);

	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
			size = i;
		if (str[i] == size)
			message = "YES";
	}

	for (int i = 0; i < s.size(); i++)
		cout << str[i];
	cout << endl;

	for (int i = 0; i < message.size(); ++i)
		cout << message[i];

	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
