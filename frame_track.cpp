#include "frame_track.h"

frame_track::frame_track(const unsigned int sample_rate, const std::vector<double>& samples, const size_t frame_size)
{
	auto frames = split_into_frames(sample_rate, samples, frame_size);
	for (auto &it: frames)
	{
		frame_features_.emplace_back(it, feature_extractor(it));
	}
}

std::vector<std::vector<double>> frame_track::power_spectrum()
{
	std::vector<std::vector<double>> result;
	for (const auto& it: frame_features_)
	{
		result.push_back(it.second.power_spectrum());
	}
	return result;
}

std::vector<double> frame_track::spectral_centroid()
{
	std::vector<double> result;
	for (const auto& it: frame_features_)
	{
		result.push_back(it.second.spectral_centroid());
	}
	return result;
}

std::vector<frame> frame_track::split_into_frames(const unsigned int sample_rate, const std::vector<double>& samples, const size_t frame_size)
{
	std::vector<frame> result;
	for (auto it = samples.begin(); it < samples.end() - frame_size; it += frame_size)
	{
		result.emplace_back(sample_rate, std::vector<double>(it, it + frame_size));
	}
	return result;
}
