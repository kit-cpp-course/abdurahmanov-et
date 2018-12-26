#include "utilities.h"
#include "cxxopts.hpp"

int cfg::configurator::get_frame_size() const
{
	return frame_size_;
}

std::vector<std::string> cfg::configurator::get_file_names() const
{
	return file_names_;
}

cfg::cli_configurator::cli_configurator(int argc, char* argv[])
{
	cxxopts::Options options(argv[0]);
	options.add_options()
		("s", "Frame size", cxxopts::value<int>())
		("positional", "Files to process", cxxopts::value<std::vector<std::string>>());
	options.parse_positional({"positional"});
	const auto result = options.parse(argc, argv);
	try
	{
		frame_size_ = result["s"].as<int>();
		file_names_ = result["positional"].as<std::vector<std::string>>();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
