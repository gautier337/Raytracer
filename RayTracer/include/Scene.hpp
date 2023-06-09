/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "Factory.hpp"
#include "IPrimitive.hpp"
#include "ILights.hpp"
#include "CustomObject.hpp"
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
            void addPrimitive(std::unique_ptr<IPrimitive> primitive);
            void addLight(std::unique_ptr<ILights> light);
            void addCustomObject(std::unique_ptr<CustomObject> customObject);
            void setCamera(std::unique_ptr<View::Camera> camera);
            std::vector<std::vector<Render::Color>> getPixels() const;
            void render(int pixelSize, int width, int height);
            View::Camera getCamera() const;
            void translateCamera(Math::Vector3D translation);
            void rotateCamera(Math::Vector3D rotation, double angle);
            void resetCamera();
            Factory getFactory() const;
            std::vector<std::unique_ptr<IPrimitive>> &getPrimitives();

        private:
            Factory factory;
            std::unique_ptr<View::Camera> camera;
            std::unique_ptr<View::Camera> original_camera;
            std::vector<std::unique_ptr<IPrimitive>> primitives;
            std::vector<std::unique_ptr<ILights>> lights;
            std::vector<std::unique_ptr<CustomObject>> customObjects;
            std::vector<std::vector<Render::Color>> pixels;
    };
};
