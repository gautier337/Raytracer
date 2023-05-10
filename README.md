<h1 align="center"> 📐 Raytracer 📐 </h1>

This is our RayTracer project

**Raytracer** **Project**
This project is a Raytracer, which is a computer graphics technique used to create realistic images by simulating the behavior of light in a virtual environment.

**Features**
Our Raytracer project includes the following features:

Primitives: sphere, plane, cone, cylinder, complex object like an ice cream.
Transformations: Translation, Rotation, Scaling.
Lights: Directional light, ambient light, drop shadow.
Material: flat color.
Scene config: add primitives, set up light, set up camera.
Interface: we create a window, you can modify the quality and the colors of object directly inside the program, you can move the camera with Z/Q/S/D/LShift/Space and change rotation of camera with the arrows.

**Architecture**

Our Raytracer project uses an interface throughout its architecture, allowing for easy and intuitive use of the program. We also use plugins, so that users can add additional features to the program by implementing their own plugins.

**Design** **Patterns**

**Factory**: which allows the creation of objects without exposing the instantiation logic to the user.
**Builder**: which separates the construction of a complex object from its representation, allowing the same construction process to create different representations.

**Dependencies**
The project uses the lib imGUI for the SFML in order to add more options during the render.