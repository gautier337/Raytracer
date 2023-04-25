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

namespace RayTracer {
    class Scene {
        public:
            Scene();
            ~Scene();
            void addObject(Rectangle3D object);
            void addObject(Sphere object);
            void addLight(DirectionalLight light);
            void setCamera(Camera camera);
            std::vector<std::vector<Color>> getPixels() const;
            void render(int pixelSize, int width, int height);

        private:
            Camera camera;
            std::vector<Rectangle3D> rectangles;
            std::vector<Sphere> spheres;
            std::vector<DirectionalLight> lights;
            std::vector<std::vector<Color>> pixels;
    };
};
