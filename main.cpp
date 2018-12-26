#include <iostream>
#include <fstream>

#include "cxxopts.hpp"
#include "AudioFile.h"

#include "frame_track.h"
#include "utilities.h"

using namespace std;

int main(const int argc, char* argv[])
{
	cfg::cli_configurator config(argc, argv);

	const auto  frame_size = config.get_frame_size();
	const auto& file_names = config.get_file_names();

	for (const auto& file_path : file_names)
	{
		clog << "processing \"" << file_path << "\"..." << endl;

		AudioFile<double> audio_file;
		audio_file.load(file_path);

		auto track_counter = 0;
		for (const auto& smp_it : audio_file.samples)
		{
			frame_track ft(audio_file.getSampleRate(), audio_file.samples[0], frame_size);
			// fix samples[0] -> several tracks

			ofstream out(file_path + "-ch" + to_string(track_counter) + ".csv");
			out << fixed;

			const auto spectrogram_data = ft.power_spectrum();

			for (const auto& sp_row : spectrogram_data)
			{
				for (auto sp_col = sp_row.begin(); sp_col < sp_row.end() - 1; ++sp_col)
				{
					out << *sp_col << ',';
				}
				out << endl;
			}

			out.close();

			track_counter++;
		}
	}

	system("pause");
	return 0;
}
