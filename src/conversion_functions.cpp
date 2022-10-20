#include "conversion_functions.h"

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

