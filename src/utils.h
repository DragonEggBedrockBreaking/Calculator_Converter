#pragma once

#include <string>
#include <vector>

void input_double(const char* id, double* var, const char* decimals, const bool& same_line);
void split(std::vector<std::string>& output, std::string string, const std::string& delimiter);
std::string replace(std::string string, const std::string& from, const std::string& to);
std::string double_to_string(const double& input);
