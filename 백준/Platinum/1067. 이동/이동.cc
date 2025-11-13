#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#include <string>

double pi = acos(-1);

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> vec, bool invert);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n;
	std::cin >> n;

	std::vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) std::cin >> a[i];
	for (int i = n - 1; i >= 0; i--) std::cin >> b[i];

	//제로 패딩
	int size = 1;
	while (size <= n * 2) size <<= 1;
	std::vector<std::complex<double>> tempa(size);
	std::vector<std::complex<double>> tempb(size);

	for (int i = 0; i < n; i++) {
		tempa[i] = a[i];
		tempa[n + i] = a[i];
	}
	for (int i = 0; i < n; i++) {
		tempb[i] = b[i];
	}

	//fft
	tempa = fft(tempa, false);
	tempb = fft(tempb, false);

	//점별 곱셈
	std::vector<std::complex<double>> temp_result(size);
	for (int i = 0; i < size; i++) temp_result[i] = tempa[i] * tempb[i];

	//역변환
	temp_result = fft(temp_result, true);

	//정수화
	std::vector<int> result(size);
	for (int i = 0; i < size; i++) result[i] = std::round(temp_result[i].real());

	int max = 0;
	for (int i = 0; i < size; i++) if (max < result[i]) max = result[i];

	std::cout << max;
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