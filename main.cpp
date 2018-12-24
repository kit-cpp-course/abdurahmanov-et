#include <fstream>

#include "AudioFile.h"
#include "frame_track.h"

using namespace std;

// main version just for testing
// extracts newline-separated list of spectral centroid values of 4096-frames
// and writes them to out.txt

int main()
{
	const string wav_file_path = "wav/longsweep.wav"; // path to wav
	const int frame_size = 1 << 12;

	AudioFile<double> audio_file;
	audio_file.load(wav_file_path);

	frame_track ft(audio_file.getSampleRate(), audio_file.samples[0], frame_size);
	
	// output setup
	ofstream out("out.txt");
	out.precision(14);
	out << fixed;

	const auto sc = ft.spectral_centroid();
	for (auto it: sc)
	{
		out << it << '\n';
	}

	system("pause");
	return 0;
}