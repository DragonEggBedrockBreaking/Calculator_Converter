#include <deque>
#include <fstream>
#include <iostream>
#include <regex>
#include <tuple>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <fmt/core.h>
#include "maths_functions.h"
#include "scripting.h"
#include <toml.hpp>

void modify_string(std::string& val)
{
    val = std::regex_replace(val, std::regex(" "), "");

    val = std::regex_replace(val, std::regex("x\\^2"), "x");
    val = std::regex_replace(val, std::regex("x2"), "x");
    val = std::regex_replace(val, std::regex("x\\^3"), "x");
    val = std::regex_replace(val, std::regex("x3"), "x");
    val = std::regex_replace(val, std::regex("x\\^4"), "x");
    val = std::regex_replace(val, std::regex("x4"), "x");

    val = std::regex_replace(val, std::regex("\\-"), "+-");
    val = std::regex_replace(val, std::regex("\\+\\+"), "+");
    val = std::regex_replace(val, std::regex("\\,\\+"), ",");

    if (val.starts_with("+")) {
        val.erase(0, 1);
    }

    val = std::regex_replace(val, std::regex("\\,x"), ",1x");
    val = std::regex_replace(val, std::regex("\\+y"), "+1y");
    val = std::regex_replace(val, std::regex("\\-y"), "-1y");
    val = std::regex_replace(val, std::regex("\\+z"), "+1z");
    val = std::regex_replace(val, std::regex("\\-z"), "-1z");
    val = std::regex_replace(val, std::regex("\\+a"), "+1a");
    val = std::regex_replace(val, std::regex("\\-a"), "-1a");

    if (val.starts_with("x")) {
        val = "1" + val;
    }

}

void only_nums(std::string& s)
{
    std::string t;

    for (const char& c : s) {
        if (std::isdigit(c) || c != '.' || c != '-') {
            t += c;
        }
    }


    s = t;
}

std::vector<double> convert_to_double(std::vector<std::string>& vec1)
{
    std::vector<double> vec2;

    for (std::string& val : vec1) {
        vec2.push_back(std::stod(val));
    }

    return vec2;
}

template <typename T, std::size_t... Indices>
auto vector_to_tuple_helper(const std::vector<T>& v, std::index_sequence<Indices...>)
{
    return std::make_tuple(v[Indices]...);
}

template <std::size_t N, typename T>
auto vector_to_tuple(const std::vector<T>& v)
{
    assert(v.size() >= N);
    return vector_to_tuple_helper(v, std::make_index_sequence<N>());
}

bool scripting(const std::string& inpath, const std::string& outpath)
{
    try {
        auto data = toml::parse(inpath);

        std::deque<double> output_doubles;
        std::deque<std::string> output_strings;

        std::vector<std::string> basicv = toml::find<std::vector<std::string>>(data, "basic");
        std::for_each(basicv.begin(), basicv.end(), [&output_doubles](std::string & val) {
            output_doubles.push_back(basic(val));
        });
        basicv = toml::find<std::vector<std::string>>(data, "basic");
        std::vector<std::string> linear1v = toml::find<std::vector<std::string>>(data, "linear1");

        for (std::string val : linear1v) {
            modify_string(val);

            std::vector<std::string> around, before, after;
            split(around, val, boost::is_any_of("="));
            split(before, around[0], boost::is_any_of("+"));
            split(after, around[1], boost::is_any_of("+"));

            std::for_each(before.begin(), before.end(), only_nums);
            std::for_each(after.begin(), after.end(), only_nums);

            auto before_t = vector_to_tuple<2>(convert_to_double(before));
            auto after_t = vector_to_tuple<2>(convert_to_double(after));

            output_doubles.push_back(std::apply(linear1, std::tuple_cat(before_t, after_t)));
        }

        linear1v = toml::find<std::vector<std::string>>(data, "linear1");
        std::vector<std::string> linear2v = toml::find<std::vector<std::string>>(data, "linear2");

        for (std::string val : linear2v) {
            modify_string(val);

            std::vector<std::string> equations, around1, around2, before1, before2, after1, after2;

            split(equations, val, boost::is_any_of(","));
            split(around1, equations[0], boost::is_any_of("="));
            split(around2, equations[1], boost::is_any_of("="));
            split(before1, around1[0], boost::is_any_of("+"));
            split(before2, around2[0], boost::is_any_of("+"));
            split(after1, around1[1], boost::is_any_of("+"));
            split(after2, around2[1], boost::is_any_of("+"));

            std::for_each(before1.begin(), before1.end(), only_nums);
            std::for_each(before2.begin(), before2.end(), only_nums);
            std::for_each(after1.begin(), after1.end(), only_nums);
            std::for_each(after2.begin(), after2.end(), only_nums);

            auto before1_t = vector_to_tuple<3>(convert_to_double(before1));
            auto before2_t = vector_to_tuple<3>(convert_to_double(before2));
            auto after1_t = vector_to_tuple<3>(convert_to_double(after1));
            auto after2_t = vector_to_tuple<3>(convert_to_double(after2));

            auto [ans1, ans2] = std::apply(linear2, std::tuple_cat(before1_t, after1_t, before2_t, after2_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
        }

        linear2v = toml::find<std::vector<std::string>>(data, "linear2");
        std::vector<std::string> linear3v = toml::find<std::vector<std::string>>(data, "linear3");

        for (std::string val : linear3v) {
            modify_string(val);

            std::vector<std::string> equations, around1, around2, around3, before1, before2, before3, after1, after2, after3;

            split(equations, val, boost::is_any_of(","));
            split(around1, equations[0], boost::is_any_of("="));
            split(around2, equations[1], boost::is_any_of("="));
            split(around3, equations[2], boost::is_any_of("="));
            split(before1, around1[0], boost::is_any_of("+"));
            split(before2, around2[0], boost::is_any_of("+"));
            split(before3, around3[0], boost::is_any_of("+"));
            split(after1, around1[1], boost::is_any_of("+"));
            split(after2, around2[1], boost::is_any_of("+"));
            split(after3, around3[1], boost::is_any_of("+"));

            std::for_each(before1.begin(), before1.end(), only_nums);
            std::for_each(before2.begin(), before2.end(), only_nums);
            std::for_each(before3.begin(), before3.end(), only_nums);
            std::for_each(after1.begin(), after1.end(), only_nums);
            std::for_each(after2.begin(), after2.end(), only_nums);
            std::for_each(after3.begin(), after3.end(), only_nums);

            auto before1_t = vector_to_tuple<4>(convert_to_double(before1));
            auto before2_t = vector_to_tuple<4>(convert_to_double(before2));
            auto before3_t = vector_to_tuple<4>(convert_to_double(before3));
            auto after1_t = vector_to_tuple<4>(convert_to_double(after1));
            auto after2_t = vector_to_tuple<4>(convert_to_double(after2));
            auto after3_t = vector_to_tuple<4>(convert_to_double(after3));

            auto [ans1, ans2, ans3] = std::apply(linear3, std::tuple_cat(before1_t, after1_t, before2_t, after2_t, before3_t, after3_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
            output_doubles.push_back(ans3);
        }

        linear3v = toml::find<std::vector<std::string>>(data, "linear3");
        std::vector<std::string> linear4v = toml::find<std::vector<std::string>>(data, "linear4");

        for (std::string val : linear4v) {
            modify_string(val);

            std::vector<std::string> equations, around1, around2, around3, around4, before1, before2,
                before3, before4, after1, after2, after3, after4;

            split(equations, val, boost::is_any_of(","));
            split(around1, equations[0], boost::is_any_of("="));
            split(around2, equations[1], boost::is_any_of("="));
            split(around3, equations[2], boost::is_any_of("="));
            split(around4, equations[3], boost::is_any_of("="));
            split(before1, around1[0], boost::is_any_of("+"));
            split(before2, around2[0], boost::is_any_of("+"));
            split(before3, around3[0], boost::is_any_of("+"));
            split(before4, around4[0], boost::is_any_of("+"));
            split(after1, around1[1], boost::is_any_of("+"));
            split(after2, around2[1], boost::is_any_of("+"));
            split(after3, around3[1], boost::is_any_of("+"));
            split(after4, around4[1], boost::is_any_of("+"));

            std::for_each(before1.begin(), before1.end(), only_nums);
            std::for_each(before2.begin(), before2.end(), only_nums);
            std::for_each(before3.begin(), before3.end(), only_nums);
            std::for_each(before4.begin(), before4.end(), only_nums);
            std::for_each(after1.begin(), after1.end(), only_nums);
            std::for_each(after2.begin(), after2.end(), only_nums);
            std::for_each(after3.begin(), after3.end(), only_nums);
            std::for_each(after4.begin(), after4.end(), only_nums);

            auto before1_t = vector_to_tuple<5>(convert_to_double(before1));
            auto before2_t = vector_to_tuple<5>(convert_to_double(before2));
            auto before3_t = vector_to_tuple<5>(convert_to_double(before3));
            auto before4_t = vector_to_tuple<5>(convert_to_double(before4));
            auto after1_t = vector_to_tuple<5>(convert_to_double(after1));
            auto after2_t = vector_to_tuple<5>(convert_to_double(after2));
            auto after3_t = vector_to_tuple<5>(convert_to_double(after3));
            auto after4_t = vector_to_tuple<5>(convert_to_double(after4));

            auto [ans1, ans2, ans3, ans4] = std::apply(linear4, std::tuple_cat(before1_t, after1_t, before2_t, after2_t, before3_t, after3_t, before4_t, after4_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
            output_doubles.push_back(ans3);
            output_doubles.push_back(ans4);
        }

        linear4v = toml::find<std::vector<std::string>>(data, "linear4");
        std::vector<std::string> quadraticv = toml::find<std::vector<std::string>>(data, "quadratic");

        for (std::string val : quadraticv) {
            modify_string(val);

            std::vector<std::string> around, before, after;

            split(around, val, boost::is_any_of("="));
            split(before, around[0], boost::is_any_of("+"));
            split(after, around[1], boost::is_any_of("+"));

            std::for_each(before.begin(), before.end(), only_nums);
            std::for_each(after.begin(), after.end(), only_nums);

            auto before_t = vector_to_tuple<3>(convert_to_double(before));
            auto after_t = vector_to_tuple<3>(convert_to_double(after));

            auto [ans1, ans2] = std::apply(quad, std::tuple_cat(before_t, after_t));
            auto [ans3, ans4] = std::apply(quad_tp, std::tuple_cat(before_t, after_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
            output_doubles.push_back(ans3);
            output_doubles.push_back(ans4);
        }

        quadraticv = toml::find<std::vector<std::string>>(data, "quadratic");
        std::vector<std::string> cubicv = toml::find<std::vector<std::string>>(data, "cubic");

        for (std::string val : cubicv) {
            modify_string(val);

            std::vector<std::string> around, before, after;

            split(around, val, boost::is_any_of("="));
            split(before, around[0], boost::is_any_of("+"));
            split(after, around[1], boost::is_any_of("+"));

            std::for_each(before.begin(), before.end(), only_nums);
            std::for_each(after.begin(), after.end(), only_nums);

            auto before_t = vector_to_tuple<4>(convert_to_double(before));
            auto after_t = vector_to_tuple<4>(convert_to_double(after));

            auto [ans1, ans2, ans3] = std::apply(cubic, std::tuple_cat(std::make_tuple(0.0), before_t, after_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
            output_doubles.push_back(ans3);
        }

        cubicv = toml::find<std::vector<std::string>>(data, "cubic");
        std::vector<std::string> quarticv = toml::find<std::vector<std::string>>(data, "quartic");

        for (std::string val : quarticv) {
            modify_string(val);

            std::vector<std::string> around, before, after;

            split(around, val, boost::is_any_of("="));
            split(before, around[0], boost::is_any_of("+"));
            split(after, around[1], boost::is_any_of("+"));

            std::for_each(before.begin(), before.end(), only_nums);
            std::for_each(after.begin(), after.end(), only_nums);

            auto before_t = vector_to_tuple<5>(convert_to_double(before));
            auto after_t = vector_to_tuple<5>(convert_to_double(after));

            auto [ans1, ans2, ans3, ans4] = std::apply(quartic, std::tuple_cat(std::make_tuple(0.0), before_t, after_t));
            output_doubles.push_back(ans1);
            output_doubles.push_back(ans2);
            output_doubles.push_back(ans3);
            output_doubles.push_back(ans4);
        }

        quarticv = toml::find<std::vector<std::string>>(data, "quartic");
        std::vector<std::string> differentiatev = toml::find<std::vector<std::string>>(data, "differentiate");
        std::for_each(differentiatev.begin(), differentiatev.end(), [&output_strings](std::string & val) {
            output_strings.push_back(diff(val));
        });
        differentiatev = toml::find<std::vector<std::string>>(data, "differentiate");

        std::vector<std::string> integratev = toml::find<std::vector<std::string>>(data, "integrate");
        std::for_each(integratev.begin(), integratev.end(), [&output_strings](std::string & val) {
            output_strings.push_back(integr(val));
        });
        integratev = toml::find<std::vector<std::string>>(data, "integrate");

        std::ofstream file;
        file.open(outpath);

        file << "# Basic\n";

        for (std::string& val : basicv) {
            file << val << " = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        file << "# Linear equations\n";

        for (std::string& val : linear1v) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        for (std::string& val : linear2v) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "y = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        for (std::string& val : linear3v) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "y = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "z = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        for (std::string& val : linear4v) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "y = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "z = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "a = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        file << "# Non-linear equations\n";

        for (std::string& val : quadraticv) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "tp = (" << fmt::format("{}", output_doubles.front()) << ", ";
            output_doubles.pop_front();
            file << fmt::format("{}", output_doubles.front()) << ")\n\n";
            output_doubles.pop_front();
        }

        for (std::string& val : cubicv) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        for (std::string& val : quarticv) {
            file << val << "\n";
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n";
            output_doubles.pop_front();
            file << "x = " << fmt::format("{}", output_doubles.front()) << "\n\n";
            output_doubles.pop_front();
        }

        file << "# Calculus\n";

        for (std::string& val : differentiatev) {
            file << "f(x) = " << val << "\n";
            file << "f'(x) = " << fmt::format("{}", output_strings.front()) << "\n\n";
            output_strings.pop_front();
        }

        for (std::string& val : integratev) {
            file << "f'(x) = " << val << "\n";
            file << "f(x) = " << fmt::format("{}", output_strings.front()) << "\n\n";
            output_strings.pop_front();
        }

        file.close();
    }
    catch (const toml::syntax_error& err) {
        std::cerr << err.what() << "\n";
        return false;
    }

    return true;
}
