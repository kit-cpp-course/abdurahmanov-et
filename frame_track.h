#pragma once

#include "feature_extractor.h"

/**
 * \brief Implements sequence of audio frames based on sequence of samples
 */
class frame_track final
{
public:
	/**
	 * \brief Builds frame track from sequence of samples
	 * \param sample_rate sample rate of the sequence
	 * \param samples samples sequence
	 * \param frame_size size of single frame in track
	 */
	frame_track(unsigned int sample_rate, const std::vector<double>& samples, size_t frame_size);

	// Features generators and getters
	/**
	 * \return sequence of spectral centroid values of track frames
	 */
	std::vector<double> spectral_centroid();
	/**
	 * \return sequence of power spectra sequences of track frames
	 */
	std::vector<std::vector<double>> power_spectrum();

private:
	static std::vector<frame> split_into_frames(unsigned int sample_rate, const std::vector<double>& samples, size_t frame_size);

	std::vector<frame> frames_;
	std::vector<feature_extractor> extractors_;
};
