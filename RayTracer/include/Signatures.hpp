/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Signatures
*/

#pragma once
#include <memory>
#include "DirectionalLight.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Rectangle3D.hpp"
#include "Sphere.hpp"
#include "Color.hpp"
#include "Cone.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

// Lights
using DirectionalLightSignature = std::unique_ptr<RayTracer::Lights::DirectionalLight>(
    RayTracer::Math::Point3D,
    RayTracer::Math::Vector3D,
    double,
    RayTracer::Render::Color
);
using AmbientLightSignature = std::unique_ptr<RayTracer::Lights::AmbientLight>(
    double brightness,
    RayTracer::Render::Color color
);

// Math
using Point3DSignature = std::unique_ptr<RayTracer::Math::Point3D>(
    double,
    double,
    double
);
using Vector3DSignature = std::unique_ptr<RayTracer::Math::Vector3D>(
    double,
    double,
    double
);

// Primitives
using PlaneSignature = std::unique_ptr<RayTracer::Primitives::Plane>(
    std::string axis,
    double position,
    RayTracer::Render::Color color
);
using Rectangle3DSignature = std::unique_ptr<RayTracer::Primitives::Rectangle3D>(
    RayTracer::Math::Point3D,
    RayTracer::Math::Vector3D,
    RayTracer::Math::Vector3D,
    RayTracer::Render::Color
);
using SphereSignature = std::unique_ptr<RayTracer::Primitives::Sphere>(
    RayTracer::Math::Point3D,
    double,
    RayTracer::Render::Color
);
using ConeSignature = std::unique_ptr<RayTracer::Primitives::Cone>(
    RayTracer::Math::Point3D,
    RayTracer::Math::Vector3D,
    double,
    double,
    double
);

// Render
using ColorSignature = std::unique_ptr<RayTracer::Render::Color>(
    double,
    double,
    double,
    double
);

// View
using CameraSignature = std::unique_ptr<RayTracer::View::Camera>(
    RayTracer::Math::Point3D,
    RayTracer::Primitives::Rectangle3D
);
using RaySignature = std::unique_ptr<RayTracer::View::Ray>(
    RayTracer::Math::Point3D,
    RayTracer::Math::Vector3D
);
