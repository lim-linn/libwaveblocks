#include <array>

namespace waveblocks {
namespace propagators {

struct PerturbedSplittingParameters {

	static constexpr auto coefL42 = std::pair<std::array<real_t,3>,std::array<real_t,2>> (
		{0.211324865405187, 0.577350269189626, 0.211324865405187},
		{0.500000000000000, 0.500000000000000}
	);

	static constexpr auto coefL62 = std::pair<std::array<real_t,4>,std::array<real_t,3>> (
		{0.112701665379258, 0.387298334620742, 0.387298334620742, 0.112701665379258},
		{0.277777777777778, 0.444444444444444, 0.277777777777778}
	);

	static constexpr auto coefL82 = std::pair<std::array<real_t,5>,std::array<real_t,4>> (
		{0.069431844202974, 0.260577634004598, 0.339981043584856, 0.260577634004598, 0.069431844202974},
		{0.173927422568727, 0.326072577431273, 0.326072577431273, 0.173927422568727}
	);

	static constexpr auto coefL102 = std::pair<std::array<real_t,6>,std::array<real_t,5>> (
		{0.046910077030668, 0.183855267916490, 0.269234655052842, 0.269234655052842, 0.183855267916490, 0.046910077030668},
		{0.118463442528095, 0.239314335249683, 0.284444444444444, 0.239314335249683, 0.118463442528095}
	);

	static constexpr auto coefL84 = std::pair<std::array<real_t,6>,std::array<real_t,5>> (
		{0.075346960269893, 0.517916854688257, -0.093263814958150, -0.093263814958150, 0.517916854688257, 0.075346960269893},
		{0.190225939373677, 0.846524070443526, -1.073500019634406, 0.846524070443526, 0.190225939373677}
	);

};

} // namespace propagators
} // namespace waveblocks
