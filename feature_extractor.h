#pragma once

#include "frame.h"
#include "fft.h"

/**
 * \brief Implements spectral audio feature extractor based of fft
 */
class feature_extractor final
{
public:
	/**
	 * \brief Builds spectral feature extractor by precalculating power spectrum
	 * \param frame frame for further usage
	 */
	explicit feature_extractor(frame& frame);

	// Features generators and getters
	/**
	 * \return Power spectrum
	 */
	std::vector<double> power_spectrum() const;
	/**
	 * \return Spectral centroid value in Hz
	 */
	double spectral_centroid() const;

private:
	std::vector<double> power_spectrum_;
	frame&              frame_;
	fft::fft_performer  fft_performer_;

	/**
	 * \brief Wrapper to unload constructor code
	 */
	void execute_fft();
};
