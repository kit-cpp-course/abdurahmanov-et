#pragma once

#include <vector>
#include <memory>

namespace fft
{
	constexpr double pi = 3.14159265358979323846;

	/**
	 * \brief Interface to FFT algorithm implementations
	 */
	class fft
	{
	public:
		virtual ~fft() = default;
		/**
		 * \brief Executes FFT on given real & imaginary values sequence
		 * \param re real values sequence
		 * \param im imaginary values sequence
		 * \param cos_table special precalculated table of cosines
		 * \param sin_table special precalculated table of sines
		 */
		virtual void execute(std::vector<double>& re, std::vector<double>& im,
		                     const std::vector<double>& cos_table,
		                     const std::vector<double>& sin_table) = 0;
	};

	/**
	 * \brief Cooley-Tukey base-2 FFT implementation
	 */
	class cooley_tukey_fft final : public fft
	{
	public:
		/**
		 * \brief Executes Cooley-Tukey base-2 FFT on given real & imaginary values sequence
		 * \param re real values sequence
		 * \param im imaginary values sequence
		 * \param cos_table special precalculated table of cosines
		 * \param sin_table special precalculated table of sines
		 */
		void execute(std::vector<double>& re, std::vector<double>& im,
		             const std::vector<double>& cos_table,
		             const std::vector<double>& sin_table) override;
	private:
		static size_t bit_reverse(size_t x, int n);
	};

	/**
	 * \brief Performer wrapper for FFT executing (based on strategy pattern)
	 */
	class fft_performer final
	{
	public:
		fft_performer(std::unique_ptr<fft> fft, size_t fft_size);

		/**
		 * \brief Performs FFT on given real & imaginary values sequence
		 * \param re real values sequence
		 * \param im imaginary values sequence
		 */
		void perform(std::vector<double>& re, std::vector<double>& im) const;
	private:
		std::unique_ptr<fft> fft_;

		// some precalculations
		std::vector<double> cos_table_;
		std::vector<double> sin_table_;
		/**
		 * \brief Precalculated Hanning window function values
		 */
		std::vector<double> window_coefs_;
	};
}
