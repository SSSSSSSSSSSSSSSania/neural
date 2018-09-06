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
#define ll long long
using namespace std;
struct Cerebral {
	Cerebral() {}
	ll layers;
	vector<ll>c;
	double w[100][100][100];
	double koeff[100][100];
	double ans[3000];
	pair<double, double>in[3000];
	ll cnt;
	ll dataSize;

	Cerebral(ll _layers, vector<ll>_c) {
		layers = _layers;
		c = _c;
		cnt = 0;
		for (int lvl = 0; lvl < layers - 1; lvl++) {
			for (int from = 0; from < c[lvl]; from++) {
				for (int to = 0; to < c[lvl + 1]; to++) {
					w[lvl][from][to] = 0.05;//rand() % 11 - 10;
				}
			}
		}
	}

	void getWeight(vector<double>_w) {
		ll k = 0;
		for (int lvl = 0; lvl < layers - 1; lvl++) {
			for (int from = 0; from < c[lvl]; from++) {
				for (int to = 0; to < c[lvl + 1]; to++) {
					w[lvl][from][to] = _w[k];//rand() % 11 - 10;
					k++;
				}
			}
		}
	}

	void scan(ll _dataSize, vector<pair<double, double>>_in, vector<double>_ans) {
		dataSize = _dataSize;
		for (int i = 0; i < _dataSize; i++) {
			in[i].first = _in[i].first;
			in[i].second = _in[i].second;
			ans[i] = _ans[i];
		}
	}

	double LF() {
		ll res;
		res = ans[cnt % dataSize];
		koeff[0][0] = in[cnt % dataSize].first;
		koeff[0][1] = in[cnt % dataSize].second;
		if (cnt == dataSize)
			cnt = 0;
		for (int lvl = 0; lvl < layers - 1; lvl++) {
			for (int to = 0; to < c[lvl + 1]; to++) {
				double sum = 0;
				for (int from = 0; from < c[lvl]; from++) {
					sum += w[lvl][from][to] * koeff[lvl][from];
				}

				//koeff[lvl + 1][to] = sum;
				//if (koeff[lvl + 1][to] < 0) koeff[lvl + 1][to] *= 0.01;

				koeff[lvl + 1][to] = tanh(sum);

				//koeff[lvl + 1][to] = max(sum, 0.0);
			}
		}
		return abs(res - koeff[layers - 1][0]);
	}

	void study(double educationCoefficient, double step) {
		double fail = 111;
		while (fail > educationCoefficient) {
			for (int lvl = 0; lvl < layers - 1; lvl++) {
				for (int from = 0; from < c[lvl]; from++) {
					for (int to = 0; to < c[lvl + 1]; to++) {
						w[lvl][from][to] += step;
						fail = 0;
						for (int i = 0; i < dataSize; i++) {
							fail += LF();
							cnt++;
						}
						fail /= dataSize;
						double up = fail;
						w[lvl][from][to] -= 2 * step;
						fail = 0;
						for (int i = 0; i < dataSize; i++) {
							fail += LF();
							cnt++;
						}
						fail /= dataSize;
						double down = fail;
						if (down > up) {
							w[lvl][from][to] += 2 * step;
							fail = up;
						}
						else {
							fail = down;
						}
						cout << endl << 100 - (fail / 1.0 * 100) << '%' << "           " << fail << endl;
						/*for (int lvl = 0; lvl < layers - 1; lvl++) {
							for (int from = 0; from < c[lvl]; from++) {
								for (int to = 0; to < c[lvl + 1]; to++) {
									cout << w[lvl][from][to] << ' ';
								}
							}
						}*/
					}
				}
			}
		}
		cout << "READY!" << endl;
	}
	ll powTen(double f) {
		ll res = 0;
		while (f > 1) {
			f /= 10;
			res++;
		}
		return res;
	}
	double tell_answer(double a, double b) {
		a /= pow(10, powTen(a));
		b /= pow(10, powTen(b));
		ll res;
		koeff[0][0] = a;
		koeff[0][1] = b;
		for (int lvl = 0; lvl < layers - 1; lvl++) {
			for (int to = 0; to < c[lvl + 1]; to++) {
				double sum = 0;
				for (int from = 0; from < c[lvl]; from++) {
					sum += w[lvl][from][to] * koeff[lvl][from];
				}
				koeff[lvl + 1][to] = tanh(sum);
			}
		}
		return koeff[layers - 1][0];
	}
};