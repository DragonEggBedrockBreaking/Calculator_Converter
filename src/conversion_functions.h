#pragma once

#include <cmath>
#include <unordered_map>
#include <string>

static const char* unit_types[] {
    "length",
    "mass",
    "time",
    "temperature",
    "velocity",
    "acceleration",
    "pressure",
    "energy",
    "area",
    "volume",
    "density",
};
static const char* length_units[] {
    "meter",
    "foot",
    "inch",
    "mile",
    "nautical mile",
    "light year",
    "yard"
};
static const char* mass_units[] {
    "gram",
    "tonne",
    "pound",
    "long_ton",
    "short_ton",
    "stone",
    "ounce",
    "carrat"
};
static const char* time_units[] {
    "second",
    "minute",
    "hour",
    "day",
    "week",
    "year"
};
static const char* angle_units[] {
    "radian",
    "degree",
    "gradian"
};
static const char* temperature_units[] {
    "celcius",
    "fahrenheit",
    "kelvin"
};
static const char* velocity_units[] {
    "meters_per_second",
    "feet_per_second",
    "miles_per_hour",
    "kilometers_per_hour",
    "knot"
};
static const char* acceleration_units[] {
    "meters_per_second_squared",
    "feet_per_second_squared",
    "standard_gravity"
};
static const char* pressure_units[] {
    "pascal",
    "bar",
    "mbar",
    "atmosphere",
    "pounds_per_square_inch",
    "torr"
};
static const char* energy_units[] {
    "joule",
    "calorie",
    "kilowatt_hour",
    "watt_hour"
};
static const char* area_units[] {
    "square_meter",
    "square_foot",
    "square_inch",
    "square_mile",
    "square_yard",
    "square_kilometer",
    "hectare",
    "acre"
};
static const char* volume_units[] {
    "cubic_meter",
    "cubic_millimeter",
    "cubic_kilometer",
    "liter",
    "cubic_inch",
    "cubic_foot",
    "cubic_yard",
    "cubic_mile",
    "us_gallon",
    "us_quart",
    "us_pint",
    "us_cup",
    "fluid ounce",
    "imperial_gallon",
    "imperial_quart",
    "imperial_pint",
    "imperial_cup",
    "tablespoon",
    "teaspoon"
};
static const char* density_units[] {
    "kilograms_per_cubic_meter",
    "grams_per_cubic_millimeter",
    "kilograms_per_liter",
    "ounces_per_cubic_foot",
    "ounces_per_cubic_inch",
    "ounces_per_gallon",
    "pounds_per_cubic_foot",
    "pounds_per_cubic_inch",
    "pounds_per_gallon"
};
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

const double convert_from_unit(const double& val, const std::string& unit);
const double convert_to_unit(const double& val, const std::string& unit);

const double celcius_fahrenheit(const double& val);
const double fahrenheit_celcius(const double& val);
const double celcius_kelvin(const double& val);
const double kelvin_celcius(const double& val);
