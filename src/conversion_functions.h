#pragma once

#include <string>

const double convert_from_unit(const double& val, const std::string& unit);
const double convert_to_unit(const double& val, const std::string& unit);

const double celcius_fahrenheit(const double& val);
const double fahrenheit_celcius(const double& val);
const double celcius_kelvin(const double& val);
const double kelvin_celcius(const double& val);

const double convert_currency(const double& val, const std::string& from, const std::string& to, const bool& ignore_date);
