/*
** EPITECH PROJECT, 2023
** B-OOP-400-BDX-4-1-raytracer-max.peixoto
** File description:
** Scene
*/

#include "DLLoader.hpp"
#include "LightsFactory.hpp"
#include "MathFactory.hpp"
#include "PrimitivesFactory.hpp"
#include "RenderFactory.hpp"
#include "ViewFactory.hpp"
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
            void initFactories();
            void addPrimitive(std::shared_ptr<IPrimitives> primitive);
            void addLight(std::shared_ptr<ILights> light);
            void setCamera(std::unique_ptr<View::Camera> camera);
            std::vector<std::vector<Render::Color>> getPixels() const;
            void render(int pixelSize, int width, int height);
            View::Camera getCamera() const;
            void translateCamera(Math::Vector3D translation);
            void rotateCamera(Math::Vector3D rotation, double angle);
            std::unique_ptr<Math::MathFactory> getMathFactory();

        private:
            Core::DLLoader lightsLoader;
            Core::DLLoader mathLoader;
            Core::DLLoader primitivesLoader;
            Core::DLLoader renderLoader;
            Core::DLLoader viewLoader;
            std::unique_ptr<Lights::LightsFactory> lightsFactory;
            std::unique_ptr<Math::MathFactory> mathFactory;
            std::unique_ptr<Primitives::PrimitivesFactory> primitivesFactory;
            std::unique_ptr<Render::RenderFactory> renderFactory;
            std::unique_ptr<View::ViewFactory> viewFactory;
            std::unique_ptr<View::Camera> camera;
            std::vector<std::shared_ptr<IPrimitives>> primitives;
            std::vector<std::shared_ptr<ILights>> lights;
            std::vector<std::vector<Render::Color>> pixels;
    };
};
