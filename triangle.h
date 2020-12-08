#pragma once

#include <vector>
#include <string>
#include "scaling.h"
#include "triangular.h"
#include "vector3f.h"
using namespace std;
namespace fst
{
    class Ray;
    struct HitRecord;

    class Triangle : public Triangular
    {
    public:
        Triangle(const math::Vector3f& v0, const math::Vector3f& edge1, const math::Vector3f& edge2, std::string transforms, int texture_id);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const override;
        bool intersectShadowRay(const Ray& ray, float max_distance) const override;
        void make_transformations(std::vector<Triangle> triangles);
        void rotate(int index);
        void scale(int index);
        void translate(int index);
        std::string transform;
        int texture_id;
    private:
        math::Vector3f m_v0, m_edge1, m_edge2;
        math::Vector3f m_normal;
    };
}
