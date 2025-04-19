#include "../testing_utils.h"

#include <xsf/stats.h>

namespace fs = std::filesystem;

fs::path tables_path{fs::path(XSREF_TABLES_PATH) / "scipy_special_tests" / "bdtrc"};

TEST_CASE("bdtrc dpd->d scipy_special_tests", "[bdtrc][dpd->d][scipy_special_tests]") {
    SET_FP_FORMAT()
    auto [input, output, tol] = GENERATE(
        xsf_test_cases<std::tuple<double, std::ptrdiff_t, double>, std::tuple<double, bool>, double>(
            tables_path / "In_d_p_d-d.parquet", tables_path / "Out_d_p_d-d.parquet",
            tables_path / ("Err_d_p_d-d_" + get_platform_str() + ".parquet")
        )
    );

    auto [k, n, p] = input;
    auto [desired, fallback] = output;
    auto out = xsf::bdtrc(k, n, p);
    auto error = xsf::extended_relative_error(out, desired);
    tol = adjust_tolerance(tol);
    CAPTURE(k, n, p, out, desired, error, tol, fallback);
    REQUIRE(error <= tol);
}
