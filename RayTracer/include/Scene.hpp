/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Rectangle3D.hpp"
#include "Sphere.hpp"
#include "DirectionalLight.hpp"
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
            void addPrimitive(std::shared_ptr<IPrimitives> primitive);
            void addLight(std::shared_ptr<ILights> light);
            void setCamera(View::Camera camera);
            std::vector<std::vector<Render::Color>> getPixels() const;
            void render(int pixelSize, int width, int height);

        private:
            View::Camera camera;
            std::vector<std::shared_ptr<IPrimitives>> primitives;
            std::vector<std::shared_ptr<ILights>> lights;
            std::vector<std::vector<Render::Color>> pixels;
    };
};
