/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Factory.hpp"
#include "Rectangle3D.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "DirectionalLight.hpp"
#include "AmbientLight.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "parse_config.hpp"
#include <vector>
#include <memory>

namespace RayTracer {
    class Scene {
        public:
            Scene();
            Scene(const ParseConfig &config);
            ~Scene();
            void addPrimitive(std::unique_ptr<IPrimitives> primitive);
            void addLight(std::unique_ptr<ILights> light);
            void setCamera(std::unique_ptr<View::Camera> camera);
            std::vector<std::vector<Render::Color>> getPixels() const;
            void render(int pixelSize, int width, int height);
            View::Camera getCamera() const;
            void translateCamera(Math::Vector3D translation);
            void rotateCamera(Math::Vector3D rotation, double angle);
            Factory getFactory() const;

        private:
            Factory factory;
            std::unique_ptr<View::Camera> camera;
            std::vector<std::unique_ptr<IPrimitives>> primitives;
            std::vector<std::unique_ptr<ILights>> lights;
            std::vector<std::vector<Render::Color>> pixels;
    };
};
