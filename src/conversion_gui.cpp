#include <algorithm>
#include <vector>
#include <fmt/core.h>
#include "imgui.h"
#include "lib/imgui_stdlib.h"
#include "conversion_functions.h"
#include "guis.h"

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

void temperature_gui(double& value, std::string& text)
{
    static int convert_from;
    static int convert_to;
    ImGui::Combo("Convert from", &convert_from, temperature_units, IM_ARRAYSIZE(temperature_units));
    ImGui::Combo("Convert to", &convert_to, temperature_units, IM_ARRAYSIZE(temperature_units));

    if (convert_from != convert_to) {
        ImGui::InputDouble("Input value##foo1", &value);

        if (ImGui::Button("Convert")) {
            if (convert_from == 0 && convert_to == 1) {
                text = fmt::format("{}", celcius_fahrenheit(value));
            }
            else if (convert_from == 1 && convert_to == 0) {
                text = fmt::format("{}", fahrenheit_celcius(value));
            }
            else if (convert_from == 0 && convert_to == 2) {
                text = fmt::format("{}", celcius_kelvin(value));
            }
            else if (convert_from == 2 && convert_to == 0) {
                text = fmt::format("{}", kelvin_celcius(value));
            }
            else if (convert_from == 1 && convert_to == 2) {
                double celcius = fahrenheit_celcius(value);
                text = fmt::format("{}", celcius_kelvin(celcius));
            }
            else {
                double celcius = kelvin_celcius(value);
                text = fmt::format("{}", celcius_fahrenheit(celcius));
            }
        }

        ImGui::SameLine();
        ImGui::Text("%s", text.c_str());
    }
}

void general_gui(const int& selected_conversion_opt, double& value, std::string& text)
{
    std::vector<std::string> dropdown;

    switch (selected_conversion_opt) {
    case 0:
        for (const char*& item : length_units) {
            dropdown.push_back(item);
        }

        break;

    case 1:
        for (const char*& item : mass_units) {
            dropdown.push_back(item);
        }

        break;

    case 2:
        for (const char*& item : time_units) {
            dropdown.push_back(item);
        }

        break;

    case 4:
        for (const char*& item : velocity_units) {
            dropdown.push_back(item);
        }

        break;

    case 5:
        for (const char*& item : acceleration_units) {
            dropdown.push_back(item);
        }

        break;

    case 6:
        for (const char*& item : pressure_units) {
            dropdown.push_back(item);
        }

        break;

    case 7:
        for (const char*& item : energy_units) {
            dropdown.push_back(item);
        }

        break;

    case 8:
        for (const char*& item : area_units) {
            dropdown.push_back(item);
        }

        break;

    case 9:
        for (const char*& item : volume_units) {
            dropdown.push_back(item);
        }

        break;

    case 10:
        for (const char*& item : density_units) {
            dropdown.push_back(item);
        }

        break;
    }

    const char* dropdown_arr[dropdown.size()];
    std::transform(dropdown.begin(), dropdown.end(), dropdown_arr, [](std::string & element) {
        return element.c_str();
    });

    static int convert_from;
    static int convert_to;
    ImGui::Combo("Convert from", &convert_from, dropdown_arr, IM_ARRAYSIZE(dropdown_arr));
    ImGui::Combo("Convert to", &convert_to, dropdown_arr, IM_ARRAYSIZE(dropdown_arr));

    if (convert_from != convert_to) {
        ImGui::InputDouble("Input value##foo2", &value);

        if (ImGui::Button("Convert")) {
            if (convert_from == 0) {
                text = fmt::format("{}", convert_to_unit(value, dropdown_arr[convert_to]));
            }
            else if (convert_to == 0) {
                text = fmt::format("{}", convert_from_unit(value, dropdown_arr[convert_from]));
            }
            else {
                double si = convert_from_unit(value, dropdown_arr[convert_from]);
                text = fmt::format("{}", convert_to_unit(si, dropdown_arr[convert_to]));
            }
        }

        ImGui::SameLine();
        ImGui::Text("%s", text.c_str());
    }
}

void run_conversion_gui(const int& selected_conversion_int, double& value, std::string& text)
{
    if (selected_conversion_int == 3) {
        temperature_gui(value, text);
    }
    else {
        general_gui(selected_conversion_int, value, text);
    }
}
