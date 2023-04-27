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
#include <vector>
#include "parse_config.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene();
            Scene(const ParseConfig &config);
            ~Scene();
            void addObject(Primitives::Rectangle3D object);
            void addObject(Primitives::Sphere object);
            void addLight(Lights::DirectionalLight light);
            void setCamera(View::Camera camera);
            std::vector<std::vector<Render::Color>> getPixels() const;
            void render(int pixelSize, int width, int height);
            View::Camera getCamera() const;
            void translateCamera(Math::Vector3D translation);
            void rotateCamera(Math::Vector3D rotation, double angle);

        private:
            View::Camera camera;
            std::vector<Primitives::Rectangle3D> rectangles;
            std::vector<Primitives::Sphere> spheres;
            std::vector<Lights::DirectionalLight> lights;
            std::vector<std::vector<Render::Color>> pixels;
    };
};
