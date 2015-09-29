#pragma once

// Automatically generated by scripts/create_tables.py.

#include <vector>

#include "quadrature_rule.hpp"

namespace waveblocks {

// Gauss-Hermite quadrature nodes and weights for different orders.
const std::vector<QuadratureRule> gauss_hermite_rules{
    QuadratureRule(1, {
        0.0
    }, {
        1.77245385091
    }),
    QuadratureRule(2, {
        -0.707106781187,
        0.707106781187
    }, {
        1.46114118266,
        1.46114118266
    }),
    QuadratureRule(3, {
        -1.22474487139,
        0.0,
        1.22474487139
    }, {
        1.32393117521,
        1.1816359006,
        1.32393117521
    }),
    QuadratureRule(4, {
        -1.65068012389,
        -0.524647623275,
        0.524647623275,
        1.65068012389
    }, {
        1.2402258177,
        1.05996448289,
        1.05996448289,
        1.2402258177
    }),
    QuadratureRule(5, {
        -2.02018287046,
        -0.958572464614,
        0.0,
        0.958572464614,
        2.02018287046
    }, {
        1.18148862554,
        0.986580996751,
        0.945308720483,
        0.986580996751,
        1.18148862554
    }),
    QuadratureRule(6, {
        -2.35060497367,
        -1.33584907401,
        -0.436077411928,
        0.436077411928,
        1.33584907401,
        2.35060497367
    }, {
        1.13690833267,
        0.935580557631,
        0.876401334436,
        0.876401334436,
        0.935580557631,
        1.13690833267
    }),
    QuadratureRule(7, {
        -2.65196135684,
        -1.67355162877,
        -0.816287882859,
        0.0,
        0.816287882859,
        1.67355162877,
        2.65196135684
    }, {
        1.10133072961,
        0.897184600225,
        0.828687303284,
        0.810264617557,
        0.828687303284,
        0.897184600225,
        1.10133072961
    }),
    QuadratureRule(8, {
        -2.93063742026,
        -1.9816567567,
        -1.15719371245,
        -0.381186990207,
        0.381186990207,
        1.15719371245,
        1.9816567567,
        2.93063742026
    }, {
        1.07193014425,
        0.866752606563,
        0.792890048386,
        0.764544128652,
        0.764544128652,
        0.792890048386,
        0.866752606563,
        1.07193014425
    }),
    QuadratureRule(9, {
        -3.19099320178,
        -2.26658058453,
        -1.46855328922,
        -0.723551018753,
        0.0,
        0.723551018753,
        1.46855328922,
        2.26658058453,
        3.19099320178
    }, {
        1.04700358098,
        0.841752701479,
        0.764608125095,
        0.730302452745,
        0.720235215606,
        0.730302452745,
        0.764608125095,
        0.841752701479,
        1.04700358098
    })
};

}