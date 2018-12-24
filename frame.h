#pragma once

#include <vector>

/**
 * \brief Implements audio frame based on sequence of samples
 */
class frame final
{
public:
	/**
	 * \brief Preferred constructor
	 * \param sample_rate sample rate of the frame
	 * \param samples samples sequence
	 */
	frame(const unsigned int sample_rate, std::vector<double> samples)
		: sample_rate_(sample_rate),
		  samples_(std::move(samples))
	{
	}

	// Default getters
	/**
	 * \return Sample rate of the frame
	 */
	int get_sample_rate() const;
	/**
	 * \return Copy of samples sequence
	 */
	std::vector<double> get_samples() const;

	// Utility getters
	/**
	 * \return Track length in seconds
	 */
	double get_samples_size() const;

	// Iterator bindings
	/**
	 * \return Iterator to the beginning of mutable samples sequence
	 */
	std::vector<double>::iterator begin();
	/**
	 * \return Iterator to the end of mutable samples sequence
	 */
	std::vector<double>::iterator end();
	/**
	 * \return Iterator to the beginning of immutable samples sequence
	 */
	std::vector<double>::const_iterator cbegin() const;
	/**
	 * \return Iterator to the end of immutable samples sequence
	 */
	std::vector<double>::const_iterator cend() const;

private:
	unsigned int        sample_rate_;
	std::vector<double> samples_;
};