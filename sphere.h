#pragma once

#include <vector>
#include <string>
#include "vector3f.h"

namespace fst
{
    class Ray;
    struct HitRecord;

    class Sphere
    {
    public:
        Sphere(const math::Vector3f& center, float radius, int material_id, std::string transforms, int texture_id);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray& ray, float max_distance) const;
        std::string get_transform();
        int get_texture();
        std::string transforms;
        int texture_id;
    private:
        math::Vector3f m_center;
        float m_radius;
        int m_material_id;
        
    };
}