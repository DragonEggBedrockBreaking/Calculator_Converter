#include <string>
#include <tuple>

const double linear(const double& xcoef1, const double& num1, const double& xcoef2, const double& num2);
const std::tuple<double, double> linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& num1_e1,
                                        const double& xcoef2_e1, const double& ycoef2_e1, const double& num2_e1,
                                        const double& xcoef1_e2, const double& ycoef1_e2, const double& num1_e2,
                                        const double& xcoef2_e2, const double& ycoef2_e2, const double& num2_e2);
const std::tuple<double, double, double> linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& zcoef1_e1, const double& num1_e1,
        const double& xcoef2_e1, const double& ycoef2_e1, const double& zcoef2_e1, const double& num2_e1,
        const double& xcoef1_e2, const double& ycoef1_e2, const double& zcoef1_e2, const double& num1_e2,
        const double& xcoef2_e2, const double& ycoef2_e2, const double& zcoef2_e2, const double& num2_e2,
        const double& xcoef1_e3, const double& ycoef1_e3, const double& zcoef1_e3, const double& num1_e3,
        const double& xcoef2_e3, const double& ycoef2_e3, const double& zcoef2_e3, const double& num2_e3);
const std::tuple<double, double, double, double> linear(const double& xcoef1_e1, const double& ycoef1_e1, const double& zcoef1_e1, const double& acoef1_e1, const double& num1_e1,
        const double& xcoef2_e1, const double& ycoef2_e1, const double& zcoef2_e1, const double& acoef2_e1, const double& num2_e1,
        const double& xcoef1_e2, const double& ycoef1_e2, const double& zcoef1_e2, const double& acoef1_e2, const double& num1_e2,
        const double& xcoef2_e2, const double& ycoef2_e2, const double& zcoef2_e2, const double& acoef2_e2, const double& num2_e2,
        const double& xcoef1_e3, const double& ycoef1_e3, const double& zcoef1_e3, const double& acoef1_e3, const double& num1_e3,
        const double& xcoef2_e3, const double& ycoef2_e3, const double& zcoef2_e3, const double& acoef2_e3, const double& num2_e3,
        const double& xcoef1_e4, const double& ycoef1_e4, const double& zcoef1_e4, const double& acoef1_e4, const double& num1_e4,
        const double& xcoef2_e4, const double& ycoef2_e4, const double& zcoef2_e4, const double& acoef2_e4, const double& num2_e4);

const std::tuple<double, double> quad(const double& x2coef1, const double& xcoef1, const double& num1,
                                      const double& x2coef2, const double& xcoef2, const double& num2);
const std::tuple<double, double> quad_tp(const double& x2coef1, const double& xcoef1, const double& num1,
        const double& x2coef2, const double& xcoef2, const double& num2);
const std::tuple<double, double, double> cubic(const double& x3coef1, const double& x2coef1, const double& xcoef1, const double& num1,
        const double& x3coef2, const double& x2coef2, const double& xcoef2, const double& num2);
const std::tuple<double, double, double, double> quartic(const double& x4coef1, const double& x3coef1, const double& x2coef1,
        const double& xcoef1, const double& num1,
        const double& x4coef2, const double& x3coef2, const double& x2coef2,
        const double& xcoef2, const double& num2);


enum unknown_trig { opp, adj, hypo, angle };

const double trig_ra(const double& opp, const double& adj, const double& hypo, const double& angle, const unknown_trig& type);
const double pythag(const double& opp, const double& adj, const double& hypo, const unknown_trig& type);

const std::string diff(const std::string& equ);

const double bin_dist(const double& X, const double& n, const double& p);
