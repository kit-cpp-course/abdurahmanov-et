#pragma once

#include <vector>

/**
 * \brief Holding methods to perform various (in future) FFT algorithms
 */
namespace fft
{
	/**
	 * \brief Performs Cooley-Tukey FFT on values obtained from split real and imaginary parts
	 * \param re real part of input
	 * \param im imaginary part of input
	 */
	void transform(std::vector<double>& re, std::vector<double>& im);

	/**
	 * \brief Applies window to and performs Cooley-Tukey FFT on real values obtained from split real and imaginary parts
	 * \param re real part of input
	 * \param im imaginary part of input
	 */
	void real_windowed_transform(std::vector<double>& re, std::vector<double>& im);

	size_t bit_reverse(size_t x, int n);

	double hanning_window(int frame_size, int pos);
}