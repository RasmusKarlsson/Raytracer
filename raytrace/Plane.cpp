#include "Plane.h"
#include <glm.hpp>


Plane::Plane(void)
{
}

Plane::Plane(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
	pos0 = p0;
	pos1 = p1;
	pos2 = p2;
	pos3 = p3;
    
	normal = glm::normalize(glm::cross(pos1 - pos0, pos2 - pos0));

}

bool Plane::intersect(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos,float &t)
{
	
	    static const float eps = float(10e-6);
 
        glm::vec3 V00 = pos3;
        glm::vec3 V10 = pos0;
        glm::vec3 V11 = pos1;
        glm::vec3 V01 = pos2;
 
        // Rejects rays that are parallel to Q, and rays that intersect the plane of
        // Q either on the left of the line V00V01 or on the right of the line V00V10.
 
        glm::vec3 E_01 = V10 - V00;
        glm::vec3 E_03 = V01 - V00;
        glm::vec3 P = glm::cross(rayDirection, E_03);
        float det = glm::dot(E_01, P);
       // if (std::abs(det) < eps) return false;
		float inv_det = float(1.0) / det;
        glm::vec3 T = rayOrigPos - V00;
        float alpha = glm::dot(T, P) * inv_det;
        if (alpha < float(0.0)) return false;
        // if (alpha > real(1.0)) return false; // Uncomment if VR is used.
        glm::vec3 Q = glm::cross(T, E_01);
        float beta = glm::dot(rayDirection, Q) * inv_det;
        if (beta < float(0.0)) return false;
        // if (beta > real(1.0)) return false; // Uncomment if VR is used.
 
        if ((alpha + beta) > float(1.0)) {
 
                // Rejects rays that intersect the plane of Q either on the
                // left of the line V11V10 or on the right of the line V11V01.
 
                glm::vec3 E_23 = V01 - V11;
                glm::vec3 E_21 = V10 - V11;
                glm::vec3 P_prime = glm::cross(rayDirection, E_21);
                float det_prime = glm::dot(E_23, P_prime);
                if (std::abs(det_prime) <= eps) return false;
                float inv_det_prime = float(1.0) / det_prime;
                glm::vec3 T_prime = rayOrigPos - V11;
                float alpha_prime = glm::dot(T_prime, P_prime) * inv_det_prime;
                if (alpha_prime < float(0.0)) return false;
                glm::vec3 Q_prime = glm::cross(T_prime, E_23);
                float beta_prime = glm::dot(rayDirection, Q_prime) * inv_det_prime;
                if (beta_prime < float(0.0)) return false;
        }
 
        // Compute the ray parameter of the intersection point, and
        // reject the ray if it does not hit Q.
 
        t = glm::dot(E_03, Q) * inv_det;
        if (t < float(0.0))
                return false;
 
        return true;
}
glm::vec3 Plane::getNormal(glm::vec3 intersect){

	return normal;
}
