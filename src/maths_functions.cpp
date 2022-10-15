#include "maths_functions.h"
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <regex>

const double
linear(const double& xcoef1, const double& num1, const double& xcoef2, const double& num2)
{
    const double left = xcoef1 - xcoef2;
    const double right = num2 - num1;
    return right / left;
}

const std::tuple<double, double>
linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& num1_e1,
       const double& xcoef2_e1, const double& ycoef2_e1, const double& num2_e1,
       const double& xcoef1_e2, const double& ycoef1_e2, const double& num1_e2,
       const double& xcoef2_e2, const double& ycoef2_e2, const double& num2_e2)
{
    const double left_e1 = xcoef1_e1 - xcoef2_e1;
    const double right_y_e1 = (ycoef2_e1 - ycoef1_e1) / left_e1;
    const double right_n_e1 = (num2_e1 - num1_e1) / left_e1;

    const double left_e2 = xcoef1_e2 - xcoef2_e2;
    const double right_y_e2 = (ycoef2_e2 - ycoef1_e2) / left_e2;
    const double right_n_e2 = (num2_e2 - num1_e2) / left_e2;

    const double y_val = linear(right_y_e1, right_n_e1, right_y_e2, right_n_e2);
    const double x_val = linear(xcoef1_e1, ycoef1_e1 * y_val + num1_e1,
                                xcoef2_e1, ycoef2_e1 * y_val + num2_e1);

    return std::tuple {x_val, y_val};
}

const std::tuple<double, double, double>
linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& zcoef1_e1, const double& num1_e1,
       const double& xcoef2_e1, const double& ycoef2_e1, const double& zcoef2_e1, const double& num2_e1,
       const double& xcoef1_e2, const double& ycoef1_e2, const double& zcoef1_e2, const double& num1_e2,
       const double& xcoef2_e2, const double& ycoef2_e2, const double& zcoef2_e2, const double& num2_e2,
       const double& xcoef1_e3, const double& ycoef1_e3, const double& zcoef1_e3, const double& num1_e3,
       const double& xcoef2_e3, const double& ycoef2_e3, const double& zcoef2_e3, const double& num2_e3)
{
    const double left_e1 = xcoef1_e1 - xcoef2_e1;
    const double right_y_e1 = (ycoef2_e1 - ycoef1_e1) / left_e1;
    const double right_z_e1 = (zcoef2_e1 - zcoef1_e1) / left_e1;
    const double right_n_e1 = (num2_e1 - num1_e1) / left_e1;

    const double left_e2 = xcoef1_e2 - xcoef2_e2;
    const double right_y_e2 = (ycoef2_e2 - ycoef1_e2) / left_e2;
    const double right_z_e2 = (zcoef2_e2 - zcoef1_e2) / left_e2;
    const double right_n_e2 = (num2_e2 - num1_e2) / left_e2;

    const double left_e3 = xcoef1_e3 - xcoef2_e3;
    const double right_y_e3 = (ycoef2_e3 - ycoef1_e3) / left_e3;
    const double right_z_e3 = (zcoef2_e3 - zcoef1_e3) / left_e3;
    const double right_n_e3 = (num2_e3 - num1_e3) / left_e3;

    const auto [y, z] = linear(right_y_e1, right_z_e1, right_n_e1,
                               right_y_e2, right_z_e2, right_n_e2,
                               right_y_e1, right_z_e1, right_n_e1,
                               right_y_e3, right_z_e3, right_n_e3);

    const double x = linear(xcoef1_e1, ycoef1_e1 * y + zcoef1_e1 * z + num1_e1,
                            xcoef2_e1, ycoef2_e1 * y + zcoef2_e1 * z + num2_e1);

    return std::tuple {x, y, z};
}

const std::tuple<double, double, double, double>
linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& zcoef1_e1, const double& acoef1_e1, const double& num1_e1,
       const double& xcoef2_e1, const double& ycoef2_e1, const double& zcoef2_e1, const double& acoef2_e1, const double& num2_e1,
       const double& xcoef1_e2, const double& ycoef1_e2, const double& zcoef1_e2, const double& acoef1_e2, const double& num1_e2,
       const double& xcoef2_e2, const double& ycoef2_e2, const double& zcoef2_e2, const double& acoef2_e2, const double& num2_e2,
       const double& xcoef1_e3, const double& ycoef1_e3, const double& zcoef1_e3, const double& acoef1_e3, const double& num1_e3,
       const double& xcoef2_e3, const double& ycoef2_e3, const double& zcoef2_e3, const double& acoef2_e3, const double& num2_e3,
       const double& xcoef1_e4, const double& ycoef1_e4, const double& zcoef1_e4, const double& acoef1_e4, const double& num1_e4,
       const double& xcoef2_e4, const double& ycoef2_e4, const double& zcoef2_e4, const double& acoef2_e4, const double& num2_e4)
{
    const double left_e1 = xcoef1_e1 - xcoef2_e1;
    const double right_y_e1 = (ycoef2_e1 - ycoef1_e1) / left_e1;
    const double right_z_e1 = (zcoef2_e1 - zcoef1_e1) / left_e1;
    const double right_a_e1 = (acoef2_e1 - acoef1_e1) / left_e1;
    const double right_n_e1 = (num2_e1 - num1_e1) / left_e1;

    const double left_e2 = xcoef1_e2 - xcoef2_e2;
    const double right_y_e2 = (ycoef2_e2 - ycoef1_e2) / left_e2;
    const double right_z_e2 = (zcoef2_e2 - zcoef1_e2) / left_e2;
    const double right_a_e2 = (acoef2_e2 - acoef1_e2) / left_e2;
    const double right_n_e2 = (num2_e2 - num1_e2) / left_e2;

    const double left_e3 = xcoef1_e3 - xcoef2_e3;
    const double right_y_e3 = (ycoef2_e3 - ycoef1_e3) / left_e3;
    const double right_z_e3 = (zcoef2_e3 - zcoef1_e3) / left_e3;
    const double right_a_e3 = (acoef2_e3 - acoef1_e3) / left_e3;
    const double right_n_e3 = (num2_e3 - num1_e3) / left_e3;

    const double left_e4 = xcoef1_e4 - xcoef2_e4;
    const double right_y_e4 = (ycoef2_e4 - ycoef1_e4) / left_e4;
    const double right_z_e4 = (zcoef2_e4 - zcoef1_e4) / left_e4;
    const double right_a_e4 = (acoef2_e4 - acoef1_e4) / left_e4;
    const double right_n_e4 = (num2_e4 - num1_e4) / left_e4;

    const auto [y, z, a] = linear(right_y_e1, right_z_e1, right_a_e1, right_n_e1,
                                  right_y_e2, right_z_e2, right_a_e2, right_n_e2,
                                  right_y_e1, right_z_e1, right_a_e1, right_n_e1,
                                  right_y_e3, right_z_e3, right_a_e3, right_n_e3,
                                  right_y_e1, right_z_e1, right_a_e1, right_n_e1,
                                  right_y_e4, right_z_e4, right_a_e4, right_n_e4);

    const double x = linear(xcoef1_e1, ycoef1_e1 * y + zcoef1_e1 * z + acoef1_e1 * a + num1_e1,
                            xcoef2_e1, ycoef2_e1 * y + zcoef2_e1 * z + acoef2_e1 * a + num2_e1);

    return std::tuple {x, y, z, a};
}

const std::tuple<double, double>
quad(const double& x2coef1, const double& xcoef1, const double& num1,
     const double& x2coef2, const double& xcoef2, const double& num2)
{
    const double a = x2coef1 - x2coef2;
    const double b = xcoef1 - xcoef2;
    const double c = num1 - num2;

    const double pos_ans = ((b * -1) + sqrt(b * b - 4 * a * c)) / 2 * a;
    const double neg_ans = ((b * -1) - sqrt(b * b - 4 * a * c)) / 2 * a;

    return std::tuple {pos_ans, neg_ans};
}

const std::tuple<double, double>
quad_tp(const double& x2coef1, const double& xcoef1, const double& num1,
        const double& x2coef2, const double& xcoef2, const double& num2)
{
    const double a = x2coef1 - x2coef2;
    const double b = xcoef1 - xcoef2;
    const double c = num1 - num2;

    const double x_val = (b * -1) / (2 * a);
    const double y_val = (a * x_val * x_val) + (b * x_val) + c;

    return std::tuple {x_val, y_val};
}

const double
fx3(const double& a, const double& b, const double& c, const double& d, const double& g)
{
    return a * g * g * g + b * g * g + c * g + d;
}

const double
dydx3(const double& a, const double& b, const double& c, const double& g)
{
    return 3 * a * g * g + 2 * b * g + c;
}

const std::tuple<double, double, double>
cubic(const double& error, const double& x3coef1, const double& x2coef1,
      const double& xcoef1, const double& num1, const double& x3coef2,
      const double& x2coef2, const double& xcoef2, const double& num2)
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
fx4(const double& a, const double& b, const double& c, const double& d, const double& e, const double& g)
{
    return a * g * g * g * g + b * g * g * g + c * g * g + d * g + e;
}
const double
dydx4(const double& a, const double& b, const double& c, const double& d, const double& g)
{
    return 4 * a * g * g * g + 3 * b * g * g + 2 * c * g + d;
}

const std::tuple<double, double, double, double>
quartic(const double& error, const double& x4coef1, const double& x3coef1, const double& x2coef1,
        const double& xcoef1, const double& num1,
        const double& x4coef2, const double& x3coef2, const double& x2coef2,
        const double& xcoef2, const double& num2)
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

const double
pythag(const double& oppo, const double& adja, const double& hypo, const unknown_side& type)
{
    switch (type) {
    case opp:
        return std::sqrt(hypo * hypo - adja * adja);

    case adj:
        return std::sqrt(hypo * hypo - oppo * oppo);

    case hyp:
        return std::sqrt(adja * adja + oppo * oppo);
    }
}

const std::string
diff(const std::string& equ)
{
    const std::string equ_f = std::regex_replace(equ, std::regex(" "), "");
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
        final = std::regex_replace(final, std::regex(" + "), "");
    }

    return final;
}

const std::string
integr(const std::string& equ)
{
    const std::string equ_f = std::regex_replace(equ, std::regex(" "), "");

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
        final = std::regex_replace(final, std::regex(" + "), "");
    }

    final += " + c";

    return final;
}

const double
factorial(const double& n)
{
    if (n <= 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

const double
npr(const double& n, const double& r)
{
    return factorial(n) / factorial(n - r);
}

const double
ncr(const double& n, const double& r)
{
    return factorial(n) / (factorial(n - r) * factorial(r));
}

const double
bin_dist(const double& X, const double& n, const double& p)
{
    return std::pow(p, X) * std::pow(1 - p, n - X) * ncr(n, X);
}
