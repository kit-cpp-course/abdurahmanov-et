#include "feature_extractor.h"
#include "fft.h"
#include <algorithm>

feature_extractor::feature_extractor(frame& frame) : frame_(frame)
{
	execute_fft();
}

void feature_extractor::execute_fft()
{
	auto real = frame_.get_samples();
	std::vector<double> imag(real.size(), 0.0);
	const auto power_spectrum_size = real.size() / 2;
	power_spectrum_.resize(power_spectrum_size);
	fft::real_windowed_transform(real, imag);
	std::transform(real.begin(), real.begin() + power_spectrum_size, imag.begin(), power_spectrum_.begin(),
	               [](const double re, const double im) { return re * re + im * im; });
}

std::vector<double> feature_extractor::power_spectrum() const
{
	return power_spectrum_;
}

double feature_extractor::spectral_centroid() const
{
	auto sum = 0.0;
	auto weighted_sum = 0.0;
	const auto freq_delta = frame_.get_sample_rate() / frame_.get_samples_size();
	for (auto it = power_spectrum_.begin(); it != power_spectrum_.end(); ++it)
	{
		sum += *it;
		weighted_sum += freq_delta * *it * (it - power_spectrum_.begin());
	}
	return weighted_sum / sum;
}