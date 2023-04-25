/*
** EPITECH PROJECT, 2023
** ParseConfig
** File description:
** ParseConfig
*/

#include "parse_config.hpp"

ParseConfig::ParseConfig(const std::string& config_file)
{
    try {
        config.readFile(config_file.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "File does not exist." << std::endl;
        exit(EXIT_FAILURE);
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

ParseConfig::~ParseConfig() {}

libconfig::Setting &ParseConfig::get_config(std::string name)
{
    try {
        libconfig::Setting &camera = config.lookup(name);
        return camera;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found in configuration file." << std::endl;
        exit(EXIT_FAILURE);
    } catch (const libconfig::SettingTypeException &tex) {
        std::cerr << "Setting type mismatch in configuration file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

