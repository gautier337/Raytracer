/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** RayTracer
*/

#pragma once

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
int raytracer(std::string const &sceneFile);
