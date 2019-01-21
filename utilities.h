#pragma once

#include <string>
#include <vector>

/**
 * \brief Contains various configuration classes
 */
namespace cfg
{
	/**
	 * \brief Base class for all configurators
	 */
	class configurator 
	{
	public:
		configurator(): frame_size_(0), file_names_(0)
		{
		}

		/**
		 * \return Frame size parameter
		 */
		int get_frame_size() const;
		/**
		 * \return Sequence of names of files to be processed
		 */
		std::vector<std::string> get_file_names() const;
	protected:
		int frame_size_;
		std::vector<std::string> file_names_;
	};


	/**
	 * \brief CLI-based (command-line interface) configurator
	 */
	class cli_configurator final : public configurator
	{
	public:
		/**
		 * \brief Special constructor for CLI config
		 * \param argc count of CLI arguments
		 * \param argv array containing CLI arguments
		 */
		cli_configurator(int argc, char* argv[]);
	};
}