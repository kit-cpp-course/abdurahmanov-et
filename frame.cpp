#include "frame.h"

int frame::get_sample_rate() const
{
	return sample_rate_;
}

std::vector<double> frame::get_samples() const
{
	return samples_;
}

double frame::get_samples_size() const
{
	return samples_.size();
}

std::vector<double>::iterator frame::begin()
{
	return samples_.begin();
}

std::vector<double>::iterator frame::end()
{
	return samples_.end();
}

std::vector<double>::const_iterator frame::cbegin() const
{
	return samples_.cbegin();
}

std::vector<double>::const_iterator frame::cend() const
{
	return samples_.cend();
}
