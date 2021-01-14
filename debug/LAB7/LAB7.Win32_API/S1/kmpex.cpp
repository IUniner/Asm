#include <iostream>
#include <vector>

using namespace std;

vector<int> kmp(const string& s) {
	vector<int> pi(s.size());
	for (int i = 1; i < s.size(); i++) {
		int j = pi[i - 1];
		while (j > 0 && s[j] != s[i])
			j = pi[j - 1];
		if (s[j] == s[i])
			j++;
		pi[i] = j;
	}
	return pi;
}

int main()
{
    int size = -1;
	string message = "NO";
    string s= "acaacaaca cacacacaacaacaacaxacac"; //000100000000001234000
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
	cout<< endl;

	for(int i =0; i < message.size();++i)
		cout << message[i];

	system("pause");
}