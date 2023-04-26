/*
** EPITECH PROJECT, 2023
** ParseConfig
** File description:
** ParseConfig
*/

#include "parse_config.hpp"
#include "RayTracer.hpp"

ParseConfig::ParseConfig(const std::string& config_file)
{
    try {
        config.readFile(config_file.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "File does not exist." << std::endl;
        exit(ERROR);
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        exit(ERROR);
    }
}

ParseConfig::~ParseConfig() {}

libconfig::Setting &ParseConfig::get_setting(std::string name) const
{
    try {
        libconfig::Setting &camera = config.lookup(name);
        return camera;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting '" << name << "' not found in configuration file." << std::endl;
        exit(ERROR);
    } catch (const libconfig::SettingTypeException &tex) {
        std::cerr << "Setting type mismatch in configuration file." << std::endl;
        exit(ERROR);
    }
}

std::vector<int> ParseConfig::get_window_height_width_from_setting()
{
    std::vector<int> window_height_width;

    libconfig::Setting &window_setting = get_setting("window");
    if (!window_setting.exists("width") || !window_setting.exists("height"))
        throw std::runtime_error("Missing resolution in camera setting. (width and/or height)");
    window_height_width.push_back(static_cast<int>(window_setting["width"]));
    window_height_width.push_back(static_cast<int>(window_setting["height"]));
    return window_height_width;
}

double ParseConfig::getDoubleFromSetting(const libconfig::Setting &setting) const
{
    if (setting.getType() == libconfig::Setting::TypeInt) {
        return static_cast<double>(setting.operator int());
    } else if (setting.getType() == libconfig::Setting::TypeFloat) {
        return setting.operator double();
    } else {
        throw std::runtime_error("Invalid setting type for conversion to double.");
    }
}
