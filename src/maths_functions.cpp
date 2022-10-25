#include <regex>
#include "maths_functions.h"
#include <boost/algorithm/string.hpp>
#include "muParser.h"
#include "lib/nml.h"

const double
basic(const std::string& expression)
{
    try {
        const std::string expr = std::regex_replace(expression, std::regex(" "), "");
        mu::Parser p;
        p.SetExpr(expression);
        return p.Eval();
    }
    catch (mu::Parser::exception_type &e) {
        return NAN;
    }
}

const double
linear1(const double& xcoef1, const double& num1, const double& xcoef2, const double& num2)
{
    const double left = xcoef1 - xcoef2;
    const double right = num2 - num1;
    return right / left;
}

const std::tuple<double, double>
linear2(const double& xcoef1_e1, const double& ycoef1_e1, const double& num1_e1,
        const double& xcoef2_e1, const double& ycoef2_e1, const double& num2_e1,
        const double& xcoef1_e2, const double& ycoef1_e2, const double& num1_e2,
        const double& xcoef2_e2, const double& ycoef2_e2, const double& num2_e2)
{
    std::tuple<double, double> return_value = std::tuple {NAN, NAN};

    const double xcoef_e1 = xcoef1_e1 - xcoef2_e1;
    const double ycoef_e1 = ycoef1_e1 - ycoef2_e1;
    const double num_e1 = num2_e1 - num1_e1;

    const double xcoef_e2 = xcoef1_e2 - xcoef2_e2;
    const double ycoef_e2 = ycoef1_e2 - ycoef2_e2;
    const double num_e2 = num2_e2 - num1_e2;

    double small_matrix[4] {
        xcoef_e1, ycoef_e1,
        xcoef_e2, ycoef_e2
    };

    nml_mat *sm_mat = nml_mat_from(2, 2, 4, small_matrix);
    nml_mat_lup *mat_lup = nml_mat_lup_solve(sm_mat);

    if (nml_mat_det(mat_lup) != 0) {
        double matrix[6] {
            xcoef_e1, ycoef_e1, num_e1,
            xcoef_e2, ycoef_e2, num_e2
        };

        nml_mat *mat = nml_mat_from(2, 3, 6, matrix);
        nml_mat *rrefm = nml_mat_rref(mat);

        if (rrefm->data[0][0] == 1 && rrefm->data[1][1] == 1) {
            return_value = {rrefm->data[0][2], rrefm->data[1][2]};
        }

        nml_mat_free(mat);
        nml_mat_free(rrefm);
    }

    nml_mat_free(sm_mat);
    nml_mat_lup_free(mat_lup);

    return return_value;
}

const std::tuple<double, double, double>
linear3(const double& xcoef1_e1, const double& ycoef1_e1, const double& zcoef1_e1, const double& num1_e1,
        const double& xcoef2_e1, const double& ycoef2_e1, const double& zcoef2_e1, const double& num2_e1,
        const double& xcoef1_e2, const double& ycoef1_e2, const double& zcoef1_e2, const double& num1_e2,
        const double& xcoef2_e2, const double& ycoef2_e2, const double& zcoef2_e2, const double& num2_e2,
        const double& xcoef1_e3, const double& ycoef1_e3, const double& zcoef1_e3, const double& num1_e3,
        const double& xcoef2_e3, const double& ycoef2_e3, const double& zcoef2_e3, const double& num2_e3)
{
    std::tuple<double, double, double> return_value = std::tuple {NAN, NAN, NAN};

    const double xcoef_e1 = xcoef1_e1 - xcoef2_e1;
    const double ycoef_e1 = ycoef1_e1 - ycoef2_e1;
    const double zcoef_e1 = zcoef1_e1 - zcoef2_e1;
    const double num_e1 = num2_e1 - num1_e1;

    const double xcoef_e2 = xcoef1_e2 - xcoef2_e2;
    const double ycoef_e2 = ycoef1_e2 - ycoef2_e2;
    const double zcoef_e2 = zcoef1_e2 - zcoef2_e2;
    const double num_e2 = num2_e2 - num1_e2;

    const double xcoef_e3 = xcoef1_e3 - xcoef2_e3;
    const double ycoef_e3 = ycoef1_e3 - ycoef2_e3;
    const double zcoef_e3 = zcoef1_e3 - zcoef2_e3;
    const double num_e3 = num2_e3 - num1_e3;

    double small_matrix[9] {
        xcoef_e1, ycoef_e1, zcoef_e1,
        xcoef_e2, ycoef_e2, zcoef_e2,
        xcoef_e3, ycoef_e3, zcoef_e3
    };

    nml_mat *sm_mat = nml_mat_from(2, 2, 4, small_matrix);
    nml_mat_lup *mat_lup = nml_mat_lup_solve(sm_mat);

    if (nml_mat_det(mat_lup) != 0) {
        double matrix[12] {
            xcoef_e1, ycoef_e1, zcoef_e1, num_e1,
            xcoef_e2, ycoef_e2, zcoef_e2, num_e2,
            xcoef_e3, ycoef_e3, zcoef_e3, num_e3
        };

        nml_mat *mat = nml_mat_from(3, 4, 12, matrix);
        nml_mat *rrefm = nml_mat_rref(mat);

        if (rrefm->data[0][0] == 1 && rrefm->data[1][1] == 1 && rrefm->data[2][2] == 1) {
            return_value = {rrefm->data[0][3], rrefm->data[1][3], rrefm->data[2][3]};
        }

        nml_mat_free(mat);
        nml_mat_free(rrefm);
    }

    nml_mat_free(sm_mat);
    nml_mat_lup_free(mat_lup);

    return return_value;
}

const std::tuple<double, double, double, double>
linear4(const double & xcoef1_e1, const double & ycoef1_e1, const double & zcoef1_e1, const double & acoef1_e1, const double & num1_e1,
        const double & xcoef2_e1, const double & ycoef2_e1, const double & zcoef2_e1, const double & acoef2_e1, const double & num2_e1,
        const double & xcoef1_e2, const double & ycoef1_e2, const double & zcoef1_e2, const double & acoef1_e2, const double & num1_e2,
        const double & xcoef2_e2, const double & ycoef2_e2, const double & zcoef2_e2, const double & acoef2_e2, const double & num2_e2,
        const double & xcoef1_e3, const double & ycoef1_e3, const double & zcoef1_e3, const double & acoef1_e3, const double & num1_e3,
        const double & xcoef2_e3, const double & ycoef2_e3, const double & zcoef2_e3, const double & acoef2_e3, const double & num2_e3,
        const double & xcoef1_e4, const double & ycoef1_e4, const double & zcoef1_e4, const double & acoef1_e4, const double & num1_e4,
        const double & xcoef2_e4, const double & ycoef2_e4, const double & zcoef2_e4, const double & acoef2_e4, const double & num2_e4)
{
    std::tuple<double, double, double, double> return_value = std::tuple {NAN, NAN, NAN, NAN};

    const double xcoef_e1 = xcoef1_e1 - xcoef2_e1;
    const double ycoef_e1 = ycoef1_e1 - ycoef2_e1;
    const double zcoef_e1 = zcoef1_e1 - zcoef2_e1;
    const double acoef_e1 = acoef1_e1 - acoef2_e1;
    const double num_e1 = num2_e1 - num1_e1;

    const double xcoef_e2 = xcoef1_e2 - xcoef2_e2;
    const double ycoef_e2 = ycoef1_e2 - ycoef2_e2;
    const double zcoef_e2 = zcoef1_e2 - zcoef2_e2;
    const double acoef_e2 = acoef1_e2 - acoef2_e2;
    const double num_e2 = num2_e2 - num1_e2;

    const double xcoef_e3 = xcoef1_e3 - xcoef2_e3;
    const double ycoef_e3 = ycoef1_e3 - ycoef2_e3;
    const double zcoef_e3 = zcoef1_e3 - zcoef2_e3;
    const double acoef_e3 = acoef1_e3 - acoef2_e1;
    const double num_e3 = num2_e3 - num1_e3;

    const double xcoef_e4 = xcoef1_e4 - xcoef2_e4;
    const double ycoef_e4 = ycoef1_e4 - ycoef2_e4;
    const double zcoef_e4 = zcoef1_e4 - zcoef2_e4;
    const double acoef_e4 = acoef1_e4 - acoef2_e4;
    const double num_e4 = num2_e4 - num1_e4;

    double small_matrix[16] {
        xcoef_e1, ycoef_e1, zcoef_e1, acoef_e1,
        xcoef_e2, ycoef_e2, zcoef_e2, acoef_e2,
        xcoef_e3, ycoef_e3, zcoef_e3, acoef_e3,
        xcoef_e4, ycoef_e4, zcoef_e4, acoef_e4
    };

    nml_mat *sm_mat = nml_mat_from(2, 2, 4, small_matrix);
    nml_mat_lup *mat_lup = nml_mat_lup_solve(sm_mat);

    if (nml_mat_det(mat_lup) != 0) {
        double matrix[20] {
            xcoef_e1, ycoef_e1, zcoef_e1, acoef_e1, num_e1,
            xcoef_e2, ycoef_e2, zcoef_e2, acoef_e2, num_e2,
            xcoef_e3, ycoef_e3, zcoef_e3, acoef_e3, num_e3,
            xcoef_e4, ycoef_e4, zcoef_e4, acoef_e4, num_e4
        };

        nml_mat *mat = nml_mat_from(4, 5, 12, matrix);
        nml_mat *rrefm = nml_mat_rref(mat);

        if (rrefm->data[0][0] == 1 && rrefm->data[1][1] == 1 && rrefm->data[2][2] == 1 && rrefm->data[3][3]) {
            return_value = {rrefm->data[0][4], rrefm->data[1][4], rrefm->data[2][4], rrefm->data[3][4]};
        }

        nml_mat_free(mat);
        nml_mat_free(rrefm);
    }

    nml_mat_free(sm_mat);
    nml_mat_lup_free(mat_lup);

    return return_value;
}

const std::tuple<double, double>
quad(const double & x2coef1, const double & xcoef1, const double & num1,
     const double & x2coef2, const double & xcoef2, const double & num2)
{
    const double a = x2coef1 - x2coef2;
    const double b = xcoef1 - xcoef2;
    const double c = num1 - num2;

    const double pos_ans = ((b * -1) + sqrt(b * b - 4 * a * c)) / 2 * a;
    const double neg_ans = ((b * -1) - sqrt(b * b - 4 * a * c)) / 2 * a;

    return std::tuple {pos_ans, neg_ans};
}

const std::tuple<double, double>
quad_tp(const double & x2coef1, const double & xcoef1, const double & num1,
        const double & x2coef2, const double & xcoef2, const double & num2)
{
    const double a = x2coef1 - x2coef2;
    const double b = xcoef1 - xcoef2;
    const double c = num1 - num2;

    const double x_val = (b * -1) / (2 * a);
    const double y_val = (a * x_val * x_val) + (b * x_val) + c;

    return std::tuple {x_val, y_val};
}

const double
fx3(const double & a, const double & b, const double & c, const double & d, const double & g)
{
    return a * g * g * g + b * g * g + c * g + d;
}

const double
dydx3(const double & a, const double & b, const double & c, const double & g)
{
    return 3 * a * g * g + 2 * b * g + c;
}

const std::tuple<double, double, double>
cubic(const double & error, const double & x3coef1, const double & x2coef1,
      const double & xcoef1, const double & num1, const double & x3coef2,
      const double & x2coef2, const double & xcoef2, const double & num2)
{
    int count = 1;
    double g = 0.01;
    double a = x3coef1 - x3coef2;
    double b = x2coef1 - x2coef2;
    double c = xcoef1 - xcoef2;
    double d = num1 - num2;

    while (std::abs(fx3(a, b, c, d, g)) > error && count <= 100) {
        count ++;

        if (dydx3(a, b, c, g) == 0) {
            g += 0.001;
        }

        g -= fx3(a, b, c, d, g) / dydx3(a, b, c, g);
    }

    if (a != 1) {
        b /= a;
        c /= a;
        a = 1;
    }

    b += g;
    c += (b * g);

    const auto [ans2, ans3] = quad(a, b, c, 0, 0, 0);

    return std::tuple {g, ans2, ans3};
}

const double
fx4(const double & a, const double & b, const double & c, const double & d, const double & e, const double & g)
{
    return a * g * g * g * g + b * g * g * g + c * g * g + d * g + e;
}
const double
dydx4(const double & a, const double & b, const double & c, const double & d, const double & g)
{
    return 4 * a * g * g * g + 3 * b * g * g + 2 * c * g + d;
}

const std::tuple<double, double, double, double>
quartic(const double & error, const double & x4coef1, const double & x3coef1, const double & x2coef1,
        const double & xcoef1, const double & num1,
        const double & x4coef2, const double & x3coef2, const double & x2coef2,
        const double & xcoef2, const double & num2)
{
    int count = 1;
    double g = 0.01;
    double a = x4coef1 - x4coef2;
    double b = x3coef1 - x3coef2;
    double c = x2coef1 - x2coef2;
    double d = xcoef1 - xcoef2;
    double e = num1 - num2;

    while (std::abs(fx4(a, b, c, d, e, g)) > error && count <= 100) {
        count ++;

        if (dydx4(a, b, c, d, g) == 0) {
            g += 0.001;
        }

        g -= fx4(a, b, c, d, e, g) / dydx4(a, b, c, d, g);
    }

    if (a != 1) {
        b /= a;
        c /= a;
        d /= a;
        a = 1;
    }

    b += g;
    c += (b * g);
    d += (c * g);

    const auto [ans2, ans3, ans4] = cubic(error, a, b, c, d, 0, 0, 0, 0);

    return std::tuple {g, ans2, ans3, ans4};
}

const std::string
diff(const std::string & equ)
{
    std::string equ_f = std::regex_replace(equ, std::regex(" "), "");
    equ_f = std::regex_replace(equ_f, std::regex("\\+x"), " 1x");
    equ_f = std::regex_replace(equ_f, std::regex("\\-x"), " 1x");

    if (equ_f.starts_with("x")) {
        equ_f = "1" + equ_f;
    }

    std::string final;
    std::vector<std::string> parts;
    split(parts, equ_f, boost::is_any_of("+"));

    for (std::string part : parts) {
        if (part.find("x^") != std::string::npos) {
            part = std::regex_replace(part, std::regex("\\^"), "");
            std::vector<std::string> numbers;
            split(numbers, part, boost::is_any_of("x"));

            double first = std::stod(numbers.at(0));
            double second = std::stod(numbers.at(1));

            first *= second;
            second--;

            if (second != 1) {
                final += std::to_string(first) + "x^" + std::to_string(second) + " + ";
            }
            else {
                final += std::to_string(first) + "x + ";
            }
        }
        else if (part.find("x") != std::string::npos) {
            std::vector<std::string> numbers;
            split(numbers, part, boost::is_any_of("x"));

            final = final + numbers.at(0);

        }
    }

    if (final.ends_with(" + ")) {
        final.pop_back();
        final.pop_back();
        final.pop_back();
    }

    return final;
}

const std::string
integr(const std::string & equ)
{
    std::string equ_f = std::regex_replace(equ, std::regex(" "), "");
    equ_f = std::regex_replace(equ_f, std::regex("\\+x"), " 1x");
    equ_f = std::regex_replace(equ_f, std::regex("\\-x"), " 1x");

    if (equ_f.starts_with("x")) {
        equ_f = "1" + equ_f;
    }

    if (equ_f.find("^-1+") != std::string::npos) {
        return "Invalid (contains 1/x)";
    }

    std::string final;
    std::vector<std::string> parts;
    split(parts, equ_f, boost::is_any_of("+"));

    for (std::string part : parts) {
        if (part.find("x^") != std::string::npos) {
            part = std::regex_replace(part, std::regex("\\^"), "");
            std::vector<std::string> numbers;
            split(numbers, part, boost::is_any_of("x"));

            double first = std::stod(numbers.at(0));
            double second = std::stod(numbers.at(1));

            second++;
            first /= second;

            final += std::to_string(first) + "x^" + std::to_string(second) + " + ";
        }
        else if (part.find("x") != std::string::npos) {
            std::vector<std::string> numbers;
            split(numbers, part, boost::is_any_of("x"));

            double first = std::stod(numbers.at(0)) / 2;

            final += std::to_string(first) + "x^2 + ";
        }
        else {
            final += part + "x + ";
        }
    }

    if (final.ends_with(" + ")) {
        final.pop_back();
        final.pop_back();
        final.pop_back();
    }

    final += " + c";

    return final;
}

const double
factorial(const double & n)
{
    if (n <= 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

const double
npr(const double & n, const double & r)
{
    return factorial(n) / factorial(n - r);
}

const double
ncr(const double & n, const double & r)
{
    return factorial(n) / (factorial(n - r) * factorial(r));
}

const double
bin_dist(const double & X, const double & n, const double & p)
{
    return std::pow(p, X) * std::pow(1 - p, n - X) * ncr(n, X);
}
