#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#include <string>

double pi = acos(-1);

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> vec, bool invert);
std::vector<int> mul(std::vector<int> a, std::vector<int> b);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::string str;
	std::cin >> str;

	int len_str = str.length();
	std::vector<int> a(len_str), b(len_str);
	for (int i = 0; i < len_str; i++) {
		if (str[i] == 'A') {
			a[len_str - i - 1] = 1;
		}
		else b[i] = 1;
	}
	std::vector<int> result = mul(b, a);

	int len_result = result.size();
	if (len_result == 0) {
		for (int i = 0; i < len_str - 1; i++) std::cout << "0\n";
		return 0;
	}
	for (int i = len_str - 2; i >= 0; i--) {
		std::cout << result[i] << "\n";
	}
}

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> vec, bool invert) {
	int n = vec.size();

	//비트 반전 순서 재배치
	for (int index = 1, new_index = 0; index < n; index++) {
		int bit = n >> 1;
		while (new_index & bit) {
			new_index ^= bit;
			bit >>= 1;
		}
		new_index ^= bit;
		if (index > new_index) {
			std::complex<double> swap;
			swap = vec[index];
			vec[index] = vec[new_index];
			vec[new_index] = swap;
		}
	}

	//병합
	for (int len = 2; len <= n; len <<= 1) {
		double angle = 2 * pi / len * (invert ? -1 : 1);
		std::complex<double> wn(cos(angle), sin(angle));

		for (int i = 0; i < n; i += len) {
			std::complex<double> w(1);
			for (int j = 0; j < len / 2; j++) {
				std::complex<double> temp1 = vec[i + j];
				std::complex<double> temp2 = vec[i + j + len / 2];
				vec[i + j] = temp1 + w * temp2; //짝수 데이터
				vec[i + j + len / 2] = temp1 - w * temp2; //홀수 데이터 
				w *= wn;
			}
		}
	}

	if (invert) for (int i = 0; i < n; i++) vec[i] /= n;

	return vec;
}

std::vector<int> mul(std::vector<int> a, std::vector<int> b) {
	//제로 패딩
	int n = 1;
	int size = a.size() + b.size();
	while (size) {
		size >>= 1;
		n <<= 1;
	}
	std::vector<std::complex<double>> tempa(n);
	std::vector<std::complex<double>> tempb(n);

	for (int i = 0; i < a.size(); i++) {
		tempa[i] = a[i];
	}
	for (int i = 0; i < b.size(); i++) {
		tempb[i] = b[i];
	}

	//fft
	tempa = fft(tempa, false);
	tempb = fft(tempb, false);

	//곱셈
	std::vector<std::complex<double>> temp_result(n);
	for (int i = 0; i < n; i++) temp_result[i] = tempa[i] * tempb[i];

	//역변환
	temp_result = fft(temp_result, true);

	//정수화
	std::vector<int> result(n);
	for (int i = 0; i < n; i++) result[i] = std::round(temp_result[i].real()); //정밀도 문제로 반올림

	//제로패딩 제거
	while (result.size() > 0 && result.back() == 0) result.pop_back();

	return result;
}