#include "fft.h"

using std::vector;
using std::swap;

constexpr double pi = 3.14159265358979323846;

void fft::transform(std::vector<double>& re, std::vector<double>& im)
{
	const auto n = re.size();
	if (n != im.size())
		throw std::invalid_argument("Mismatched lengths");
	auto levels = 0;
	for (auto temp = n; temp > 1U; temp >>= 1)
		levels++;
	if (static_cast<size_t>(1U) << levels != n)
		throw std::domain_error("Length is not a power of 2");
	
	vector<double> cos_table(n / 2);
	vector<double> sin_table(n / 2);
	for (size_t i = 0; i < n / 2; i++) {
		cos_table[i] = std::cos(2 * pi * i / n);
		sin_table[i] = std::sin(2 * pi * i / n);
	}
	
	for (size_t i = 0; i < n; i++) {
		const auto j = bit_reverse(i, levels);
		if (j > i) {
			std::swap(re[i], re[j]);
			std::swap(im[i], im[j]);
		}
	}
	
	for (size_t size = 2; size <= n; size *= 2) {
		const auto halfsize = size / 2;
		const auto tablestep = n / size;
		for (size_t i = 0; i < n; i += size) {
			for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {
				const auto l = j + halfsize;
				const auto tpre =  re[l] * cos_table[k] + im[l] * sin_table[k];
				const auto tpim = -re[l] * sin_table[k] + im[l] * cos_table[k];
				re[l] = re[j] - tpre;
				im[l] = im[j] - tpim;
				re[j] += tpre;
				im[j] += tpim;
			}
		}
		if (size == n)
			break;
	}
}

void fft::real_windowed_transform(std::vector<double>& re, std::vector<double>& im)
{
	for (size_t i = 0; i < re.size(); ++i)
	{
		re[i] *= hanning_window(re.size(), i);
	}
	transform(re, im);
}

size_t fft::bit_reverse(size_t x, int n)
{
	size_t result = 0;

	for (auto i = 0; i < n; ++i, x >>= 1)
		result = (result << 1) | (x & 1U);

	return result;
}

double fft::hanning_window(const int frame_size, const int pos)
{
	return 0.5 * (1 - cos(2 * pi * pos / (frame_size - 1)));
}