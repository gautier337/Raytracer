/*
** EPITECH PROJECT, 2023
** ParseConfig
** File description:
** ParseConfig
*/

#pragma once

#include <libconfig.h++>
#include <map>
#include <string>
#include <vector>
#include <iostream>

class ParseConfig {
    public:
        ParseConfig() = default;
        ParseConfig(const std::string& config_file);
        ~ParseConfig();

        libconfig::Setting &get_setting(std::string name) const;
        std::vector<int> get_window_height_width_from_setting();
        double getDoubleFromSetting(const libconfig::Setting &setting) const;

    private:
        libconfig::Config config;
};
