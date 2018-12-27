#include "fft.h"
#include <algorithm>

void fft::cooley_tukey_fft::execute(std::vector<double>& re, std::vector<double>& im,
                                    const std::vector<double>& cos_table,
                                    const std::vector<double>& sin_table)
{
	const auto n = re.size();
	if (n != im.size())
		throw std::invalid_argument("Mismatched lengths");
	auto levels = 0;
	for (auto temp = n; temp > 1U; temp >>= 1)
		levels++;
	if (static_cast<size_t>(1U) << levels != n)
		throw std::domain_error("Length is not a power of 2");

	for (size_t i = 0; i < n; i++)
	{
		const auto j = bit_reverse(i, levels);
		if (j > i)
		{
			std::swap(re[i], re[j]);
			std::swap(im[i], im[j]);
		}
	}

	for (size_t size = 2; size <= n; size *= 2)
	{
		const auto halfsize = size / 2;
		const auto tablestep = n / size;
		for (size_t i = 0; i < n; i += size)
		{
			for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep)
			{
				const auto l = j + halfsize;
				const auto tpre = re[l] * cos_table[k] + im[l] * sin_table[k];
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

size_t fft::cooley_tukey_fft::bit_reverse(size_t x, int n)
{
	size_t result = 0;
	for (auto i = 0; i < n; ++i, x >>= 1)
		result = result << 1 | x & 1U;
	return result;
}

fft::fft_performer::fft_performer(std::unique_ptr<fft> fft, const size_t fft_size) : fft_(std::move(fft))
{
	const auto upper = fft_size / 2;
	cos_table_.resize(upper);
	sin_table_.resize(upper);
	window_coefs_.resize(fft_size);
	for (size_t i = 0; i < upper; ++i)
	{
		cos_table_[i] = std::cos(2 * pi * i / fft_size);
		sin_table_[i] = std::sin(2 * pi * i / fft_size);
		window_coefs_[i] = window_coefs_[fft_size - i - 1] = 0.5 * (1 - cos_table_[i]);
	}
}

void fft::fft_performer::perform(std::vector<double>& re, std::vector<double>& im) const
{
	for (size_t i = 0; i < re.size(); ++i)
	{
		re[i] *= window_coefs_[i];
	}
	fft_->execute(re, im, cos_table_, sin_table_);
}
