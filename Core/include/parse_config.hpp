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
        ParseConfig(const std::string& config_file);
        ~ParseConfig();

        libconfig::Setting &get_config(std::string name);

    private:
        libconfig::Config config;
};
