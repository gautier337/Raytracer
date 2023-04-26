/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Raytracer
*/

#pragma once

#include "IFactory.hpp"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// Macros
#define SUCCESS 0
#define ERROR 84

// Prototypes
int raytracer_cylinder(std::string const &sceneFile);
int raytracer_cone(std::string const &sceneFile);