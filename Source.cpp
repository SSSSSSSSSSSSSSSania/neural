#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include "cerebrity.cpp"
#define ll long long
using namespace std;
void neur();
void test();
int main() {
	ifstream fin("input.txt");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(9);
	test();
	return 0;
}

Cerebral q;
void test() {
	ifstream fin1("input.txt");
	ifstream fin2("data.txt");
	ifstream fin3("weight.txt");
	ll l, dataSize;
	vector<ll>s;
	vector <double>ans;
	vector<pair<double, double>> in;
	ll weightSize;
	vector<double>weight;
	double coeff, step;

	fin1 >> l;
	s.resize(l);
	for (int i = 0; i < l; i++) {
		fin1 >> s[i];
	}
	q.layers = l;
	q.c = s;

	fin2 >> dataSize;
	in.resize(dataSize);
	ans.resize(dataSize);
	for (int i = 0; i < dataSize; i++) {
		fin2 >> in[i].first >> in[i].second >> ans[i];
	}
	q.scan(dataSize, in, ans);

	cout << "YOU HAVE WEIGHTS? (print Y or N)" << endl;
	string str;
	cin >> str;
	if (str == "Y" || str == "y") {
		fin3 >> weightSize;
		weight.resize(weightSize);
		for (int i = 0; i < weightSize; i++) {
			fin3 >> weight[i];
		}
		q.getWeight(weight);
	}

	cout << "ENTER EDUCATION COEFFICIENT AND STEP" << endl;
	cin >> coeff >> step;
	q.study(coeff, step);

	double first = 0, second = 0;
	while (first != -1 && second != -1) {
		cout << "ENTER A B" << endl;
		cin >> first >> second;
		/*if ((int)(q.tell_answer(first, second) * 1000) == 0) {
			cout << first << " < " << second << endl << endl;
		}
		if()
		else {
			cout << first << " > " << second << endl << endl;
		}*/
		cout << q.tell_answer(first, second) << endl;
		//cout << q.tell_answer(first, second) << endl;
	}

	fin1.close();
	fin2.close();
	fin3.close();
	return;
}