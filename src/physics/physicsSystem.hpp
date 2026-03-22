#pragma once
#include "contact.hpp"
#include "world/components/collider.hpp"

class PhysicsSystem
{
public:
    bool sphereAndSphere(const SphereCollider& one, const SphereCollider& two);
    bool sphereAndHalfspace(const SphereCollider& sphere, const PlaneCollider& plane);
    bool boxAndSphere(const BoxCollider& box, const SphereCollider& sphere);
    bool boxAndBox(const BoxCollider& boxA, const BoxCollider& boxB);
    bool boxAndPoint(const BoxCollider& box, const glm::vec3& point);
    bool boxAndHalfspaceSimple(const BoxCollider& box, const PlaneCollider& plane);
    bool boxAndHalfspace(const BoxCollider& box, const PlaneCollider& plane);
    void generateContacts(std::vector<std::unique_ptr<Entity>>& entities);
private:
    std::vector<Contact> m_contacts;

    /// @brief Casts box onto an axis.
    /// @param box box
    /// @param axis axis
    /// @return Bounds of the box on the axis.
    float transformToAxis(const BoxCollider& box, const glm::vec3& axis);

    /// @brief Finds whether two boxes collide on provided axis.
    /// @param boxA first box
    /// @param boxB second box
    /// @param axis axis
    /// @param toCenter vector from second box to first box
    /// @param index index of the axis
    /// @param smallestPenetration smallest penetration that function will compare to
    /// @param smallestCase index of axis with smallest penetration
    /// @return Whether there was a penetration.
    bool tryAxis(
        const BoxCollider& boxA, const BoxCollider& boxB, 
        glm::vec3 axis, const glm::vec3& toCenter, unsigned int index, 
        float& smallestPenetration, unsigned int& smallestCase);

    /// @brief Calculates how much two boxes penetrate on given axis.
    /// @param boxA first box
    /// @param boxB second box
    /// @param axis axis
    /// @param toCenter direction vector from boxB to boxA
    /// @return Penetration between two boxes.
    float penetrationOnAxis(
        const BoxCollider& boxA, const BoxCollider& boxB, 
        const glm::vec3& axis, const glm::vec3& toCenter);

    /// @brief This function is called when there is vertex-face or face-face collision.
    /// @param boxA first box
    /// @param boxB second box
    /// @param toCenter direction vector from boxB to boxA
    /// @param best index of the axis
    /// @param pen penetration
    void fillPointFaceBoxBox(
        const BoxCollider& boxA, const BoxCollider& boxB, 
        const glm::vec3& toCenter, unsigned int best, float pen);
        
    /// @brief Finds closest point between edges of two boxes
    /// @param pOne point one
    /// @param dOne normalized direction vector of edge one
    /// @param oneSize half-size of edge one
    /// @param pTwo point two
    /// @param dTwo normalized direction vector of edge two
    /// @param twoSize half-size of edge two
    /// @param useOne which point to use if the math will go out of bounds
    /// @return point closest between edges of two boxes
    glm::vec3 contactPoint(
        const glm::vec3& pOne, const glm::vec3& dOne, float oneSize, 
        const glm::vec3& pTwo, const glm::vec3& dTwo, float twoSize, 
        bool useOne);

};
