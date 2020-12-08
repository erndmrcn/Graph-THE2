#pragma once

#include "camera.h"
#include "material.h"
#include "mesh.h"
#include "parser.h"
#include "point_light.h"
#include "ray.h"
#include "sphere.h"
#include "vector2f.h"
#include "vector3f.h"
#include "translation.h"
#include "scaling.h"
#include "rotation.h"
#include "texture.h"

#include <vector>

namespace fst
{
    struct Scene
    {
        //Data
        std::vector<Camera> cameras;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<math::Vector3f> vertex_data;
        std::vector<math::Vector2f> tex_coord_data;
        std::vector<Mesh> meshes;
        std::vector<Sphere> spheres;
        std::vector<Translation> translations;
        std::vector<Scaling> scalings;
        std::vector<Rotation> rotations;
        std::vector<Texture> textures;
        math::Vector3f background_color;
        math::Vector3f ambient_light;
        float shadow_ray_epsilon;
        int max_recursion_depth;

        //Functions
        void loadFromParser(const parser::Scene &parser);
        bool intersect(const Ray &ray, HitRecord &hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray &ray, float max_distance) const;
        /*    ********** Model Transformations **********    */
        /* *** scaling *** */
        void triangle_scale(const Scaling matrix_s, Triangle tri) const;
        void mesh_scale(const Scaling matrix_s, Mesh mesh) const;
        void sphere_scale(const Scaling matrix_s, Sphere sphere) const;
        /* *** rotation *** */
        void triangle_rotation(const Rotation matrix_r, Triangle tri) const;
        void mesh_rotation(const Scaling matrix_r, Mesh mesh) const;
        void sphere_rotation(const Scaling matrix_r, Sphere sphere) const;
        /* *** translation *** */
        void triangle_translation(const Scaling matrix_t, Triangle tri) const;
        void mesh_translation(const Scaling matrix_t, Mesh mesh) const;
        void sphere_translation(const Scaling matrix_t, Sphere sphere) const;
        
        /*    ********** texture mapping **********    */
        void triangle_mapping();
        void mesh_mapping();
        void sphere_mapping();

        /*    ********** viewing transformations? **********    */
    };
} // namespace fst
