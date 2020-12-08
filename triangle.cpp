#include "hit_record.h"
#include "triangle.h"
#include "ray.h"
#include "parser.h"
using namespace std;
namespace fst
{
    Triangle::Triangle(const math::Vector3f& v0, const math::Vector3f& edge1, const math::Vector3f& edge2, std::string transforms, int texture_id)
        : m_v0(v0)
        , m_edge1(edge1)
        , m_edge2(edge2)
        , m_normal(math::normalize(math::cross(edge1, edge2)))
        , transform(transforms)
        , texture_id(texture_id)
    {}

    bool Triangle::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        //M�ller-Trumbore algorithm
        auto pvec = math::cross(ray.get_direction(), m_edge2);
        auto inv_det = 1.0f / math::dot(m_edge1, pvec);

        auto tvec = ray.get_origin() - m_v0;
        auto w1 = math::dot(tvec, pvec) * inv_det;

        if (w1 < 0.0f || w1 > 1.0f)
        {
            return false;
        }

        auto qvec = math::cross(tvec, m_edge1);
        auto w2 = math::dot(ray.get_direction(), qvec) * inv_det;

        if (w2 < 0.0f || (w1 + w2) > 1.0f)
        {
            return false;
        }

        auto distance = math::dot(m_edge2, qvec) * inv_det;
        if (distance > 0.0f && distance < max_distance)
        {
            //Fill the intersection record.
            hit_record.normal = m_normal;
            hit_record.distance = distance;

            return true;
        }
        return false;
    }

    bool Triangle::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        //M�ller-Trumbore algorithm
        auto pvec = math::cross(ray.get_direction(), m_edge2);
        auto inv_det = 1.0f / math::dot(m_edge1, pvec);

        auto tvec = ray.get_origin() - m_v0;
        auto w1 = math::dot(tvec, pvec) * inv_det;

        if (w1 < 0.0f || w1 > 1.0f)
        {
            return false;
        }

        auto qvec = math::cross(tvec, m_edge1);
        auto w2 = math::dot(ray.get_direction(), qvec) * inv_det;

        if (w2 < 0.0f || (w1 + w2) > 1.0f)
        {
            return false;
        }

        auto distance = math::dot(m_edge2, qvec) * inv_det;
        return distance > 0.0f && distance < max_distance;
    } 
    
    void Triangle::scale(int index)
    {
        vec3f point = scalings[index-1] 
        m_v0 = m_v0 * point.x; 
        m_v1 = m_v1 * point.y; 
        m_v2 = m_v2 * point.z; 
        return;
    }
    
    void Triangle::translate(int index)
    {
        vec3f point = translations[index-1] 
        m_v0 = m_v0 + point.x; 
        m_v1 = m_v1 + point.y; 
        m_v2 = m_v2 + point.z; 
        return;
    }
    
    void Triangle::rotate(int index)
    {
        // rotate w.r.t. given vector
        return;
    }
    // according to the transformations string do transformations 
    void Triangle::make_transformations(std::vector<Triangle> triangles)
    {
        // parse transforms string 
        std::vector<int> translate;
        std::vector<int> rotate;
        std::vector<int> scale;
        std::string delimeter = " ";
        size_t pos = 0;
        std::string token;
        while((pos = transform.find(delimeter)) != std::string::npos)
        {
            token = transform.substr(0, pos);
            // scale
            if(token[0] == 's')
            {
                char *p = &token[1];
                scale.push_back(atoi(p));
            }
            else if(token[0] == 't')
            {
                char *p = &token[1];
                translate.push_back(atoi(p));
            }
            else if(token[0] == 'r')
            {
                char *p = &token[1];
                rotate.push_back(atoi(p));
            }
        }
        // if scale not empty do scale
        for(auto& index : scale)
        {
            Triangle::scale(index);
        }
        // if rotate not empty do scale
        for(auto& index : scale)
        {
            Triangle::rotate(index);
        }
        // if translate not empty do scale
        for(auto& index : scale)
        {
            Triangle::translate(index);
        }
    }
}
