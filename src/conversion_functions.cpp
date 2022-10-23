#include <filesystem>
#include "rapidcsv.h"
#include "conversion_functions.h"

static std::unordered_map <std::string, double> multiplier_map {
    {"foot", 3.28084},
    {"inch", 39.3701},
    {"mile", 0.000621371},
    {"nautical mile", 0.000539957},
    {"light year", 1.057 * std::pow(10, -16)},
    {"yard", 1.09361},

    {"tonne", std::pow(10, -6)},
    {"pound", 0.00220462},
    {"long_ton", 9.84207 * std::pow(10, -7)},
    {"short_ton", 1.10231 * std::pow(10, -6)},
    {"stone", 0.000157473},
    {"ounce", 0.035274},
    {"carrat", 5},

    {"minute", 1 / 60},
    {"hour", 1 / 3600},
    {"day", 1 / 86400},
    {"week", 1 / 604800},
    {"year", 3.17098 * std::pow(10, -8)},

    {"feet_per_second", 3.28084},
    {"miles_per_hour", 2.23694},
    {"kilometers_per_hour", 3.6},
    {"knot", 1.94384},

    {"feet_per_second_squared", 3.28084},
    {"standard_gravity", 1 / 9.80664},

    {"bar", std::pow(10, -5)},
    {"mbar", 0.01},
    {"atmosphere", 1 / 101300},
    {"pounds_per_square_inch", 1 / 6895},
    {"torr", 1 / 133.3},

    {"calorie", 1 / 4184},
    {"kilowatt_hour", 1 / (3.6 * std::pow(10, 6))},
    {"watt_hour", 1 / 3600},

    {"square_foot", 10.7639},
    {"square_inch", 1550},
    {"square_mile", 1 / (2.59 * std::pow(10, 6))},
    {"square_yard", 1.19599},
    {"square_kilometer", std::pow(10, -6)},
    {"hectare", 0.0001},
    {"acre", 1 / 4047},

    {"cubic_millimeter", std::pow(10, 9)},
    {"cubic_kilometer", std::pow(10, -9)},
    {"liter", 1000},
    {"cubic_inch", 61023.7},
    {"cubic_foot", 35.3147},
    {"cubic_yard", 1.30795},
    {"cubic_mile", 1 / (4.168 * std::pow(10, 9))},
    {"us_gallon", 264.172},
    {"us_quart", 1056.69},
    {"us_pint", 2113.38},
    {"us_cup", 4226.75},
    {"us_tablespoon", 67628},
    {"us_teaspoon", 202884},
    {"fluid ounce", 33814},
    {"imperial_gallon", 219.969},
    {"imperial_quart", 879.877},
    {"imperial_pint", 1759.75},
    {"imperial_cup", 3519.51},
    {"imperial_tablespoon", 56412.1},
    {"imperial_teaspoon", 168936},

    {"grams_per_cubic_millimeter", std::pow(10, -6)},
    {"kilograms_per_liter", 0.001},
    {"ounces_per_cubic_foot", 1 / 1.001},
    {"ounces_per_cubic_inch", 1 / 1730},
    {"ounces_per_gallon", 1 / 6.236},
    {"pounds_per_cubic_foot", 1 / 16.018},
    {"pounds_per_cubic_inch", 1 / 27680},
    {"pounds_per_gallon", 1 / 119.8}
};

const double convert_from_unit(const double& val, const std::string& unit)
{
    return val / multiplier_map[unit];
}
const double convert_to_unit(const double& val, const std::string& unit)
{
    return val * multiplier_map[unit];
}

const double celcius_fahrenheit(const double& val)
{
    return val * 1.8 + 32;
}
const double fahrenheit_celcius(const double& val)
{
    return (val - 32) / 1.8;
}
const double celcius_kelvin(const double& val)
{
    return val - 273.15;
}
const double kelvin_celcius(const double& val)
{
    return val + 273.15;
}

const double convert_currency(const double& val, const std::string& from, const std::string& to, const bool& ignore_date)
{
    if (!std::filesystem::exists("eurofxref.zip") && !std::filesystem::exists("eurofxref.csv")) {
        system("wget -nv https://www.ecb.europa.eu/stats/eurofxref/eurofxref.zip");
    }

    if (!std::filesystem::exists("eurofxref.csv")) {
        system("unzip eurofxref.zip");
    }

    std::remove("eurofxref.zip");

    rapidcsv::Document doc("eurofxref.csv");

    if (!ignore_date) {
        std::vector<std::string> date_column = doc.GetColumn<std::string>("Date");
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "%d %B %Y", timeinfo);

        if (date_column[0] != buffer) {
            std::remove("eurofxref.csv");
            return convert_currency(val, from, to, true);
        }
    }

    if (from == " EUR") {
        std::vector<std::string> rate = doc.GetColumn<std::string>(to);
        return val * std::stod(rate[0]);
    }
    else if (to == " EUR") {
        std::vector<std::string> rate = doc.GetColumn<std::string>(from);
        return val / std::stod(rate[0]);
    }

    std::vector<std::string> rate1 = doc.GetColumn<std::string>(from);
    std::vector<std::string> rate2 = doc.GetColumn<std::string>(to);

    return val / std::stod(rate1[0]) * std::stod(rate2[0]);
}
