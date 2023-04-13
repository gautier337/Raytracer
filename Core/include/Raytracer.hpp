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

// Macros
#define SUCCESS 0
#define ERROR 84

// Prototypes
int raytracer(std::string const &sceneFile);
