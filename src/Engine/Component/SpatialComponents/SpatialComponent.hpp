#pragma once



#include "glm/glm.hpp"

#include "Component/Component.hpp"

#include "Positionable.hpp"
#include "Scaleable.hpp"
#include "Orientable.hpp"



class SpatialSystem;



class SpatialComponent : public Component {

    friend Scene;
    friend SpatialSystem;

    protected: // only scene or friends can create component

    SpatialComponent(GameObject & gameObject, SpatialComponent * parent = nullptr);
    SpatialComponent(GameObject & gameObject, const glm::vec3 & relativePosition, SpatialComponent * parent = nullptr);
    SpatialComponent(GameObject & gameObject, const glm::vec3 & relativePosition, const glm::vec3 & relativeScale, SpatialComponent * parent = nullptr);
    SpatialComponent(GameObject & gameObject, const glm::vec3 & relativePosition, const glm::vec3 & relativeScale, const glm::mat3 & relativeOrient, SpatialComponent * parent = nullptr);
    SpatialComponent(GameObject & gameObject, const glm::vec3 & relativePosition, const glm::vec3 & relativeScale, const glm::quat & relativeOrient, SpatialComponent * parent = nullptr);

    public:

    SpatialComponent(SpatialComponent && other) = default;

    ~SpatialComponent();

    public:

    virtual void update(float dt) override;

    void orphan(SpatialComponent & child);

    // sets the absolute position
    void setRelativePosition(const glm::vec3 & relativePosition, bool silently = false);

    // moves current position by delta
    void move(const glm::vec3 & delta, bool silently = false);

    // sets the absolute scale
    void setRelativeScale(const glm::vec3 & relativeScale, bool silently = false);

    // multiplies current scale by factor
    void scaleBy(const glm::vec3 & factor, bool silently = false);

    // sets the absolute orientation
    void setRelativeOrientation(const glm::quat & relativeOrientation, bool silently = false);
    void setRelativeOrientation(const glm::mat3 & relativeOrientation, bool silently = false);
    
    // rotates current orientation
    void rotate(const glm::quat & rotation, bool silently = false);
    void rotate(const glm::mat3 & rotation, bool silently = false);

    // set the orthonormal basis vectors
    void setRelativeUVW(const glm::vec3 & relativeU, const glm::vec3 & relativeV, const glm::vec3 & relativeW, bool silently = false);

    const glm::vec3 & relativePosition() const { return m_relPosition; }
    const glm::vec3 & prevRelativePosition() const { return m_prevRelPosition; }
    glm::vec3 relativePosition(float interpP) const;

    glm::vec3 position() const;
    glm::vec3 prevPosition() const;
    glm::vec3 position(float interpP) const;

    const glm::vec3 & relativeScale() const { return m_relScale; }
    const glm::vec3 & prevRelativeScale() const { return m_prevRelScale; }
    glm::vec3 relativeScale(float interpP) const;

    glm::vec3 scale() const;
    glm::vec3 prevScale() const;
    glm::vec3 scale(float interpP) const;

    const glm::vec3 & relativeU() const { return m_relOrientMatrix[0]; }
    const glm::vec3 & relativeV() const { return m_relOrientMatrix[1]; }
    const glm::vec3 & relativeW() const { return m_relOrientMatrix[2]; }
    const glm::vec3 & prevRelativeU() const { return m_prevRelOrientMatrix[0]; }
    const glm::vec3 & prevRelativeV() const { return m_prevRelOrientMatrix[1]; }
    const glm::vec3 & prevRelativeW() const { return m_prevRelOrientMatrix[2]; }
    glm::vec3 relativeU(float interpP) const;
    glm::vec3 relativeV(float interpP) const;
    glm::vec3 relativeW(float interpP) const;

    glm::vec3 u() const;
    glm::vec3 v() const;
    glm::vec3 w() const;
    glm::vec3 prevU() const;
    glm::vec3 prevV() const;
    glm::vec3 prevW() const;
    glm::vec3 u(float interpP) const;
    glm::vec3 v(float interpP) const;
    glm::vec3 w(float interpP) const;

    const glm::quat & relativeOrientation() const { return m_relOrientation; }
    const glm::quat & prevRelativeOrientation() const { return m_prevRelOrientation; }
    glm::quat relativeOrientation(float interpP) const;

    const glm::mat3 & relativeOrientMatrix() const { return m_relOrientMatrix; }
    const glm::mat3 & prevRelativeOrientMatrix() const { return m_prevRelOrientMatrix; };
    glm::mat3 relativeOrientMatrix(float interpP) const;

    glm::quat orientation() const;
    glm::quat prevOrientation() const;
    glm::quat orientation(float interpP) const;

    glm::mat3 orientMatrix() const;
    glm::mat3 prevOrientMatrix() const;
    glm::mat3 orientMatrix(float interpP) const;

    bool isRelativeChange() const { return m_isRelPositionChange || m_isRelScaleChange || m_isRelOrientationChange; }
    bool isChange() const { return isRelativeChange() || m_parent && m_parent->isChange(); }

    glm::mat4 modelMatrix() const;
    glm::mat4 prevModelMatrix() const;
    glm::mat4 modelMatrix(float interpP) const;

    glm::mat3 normalMatrix() const;
    glm::mat3 prevNormalMatrix() const;
    glm::mat3 normalMatrix(float interpP) const;

    // This is not a true velocity, only a rough estimation based on just one frame
    // Use NewtonianComponent for "physics" velocity
    glm::vec3 effectiveVelocity() const;

    const SpatialComponent * parent() const { return m_parent; }

    private:

    void broadcast() const;

    private:

    glm::vec3 m_relPosition, m_prevRelPosition;
    bool m_isRelPositionChange;
    glm::vec3 m_relScale, m_prevRelScale;
    bool m_isRelScaleChange;
    glm::quat m_relOrientation, m_prevRelOrientation;
    glm::mat3 m_relOrientMatrix, m_prevRelOrientMatrix;
    bool m_isRelOrientationChange;
    SpatialComponent * m_parent;
    Vector<SpatialComponent *> m_children;
    float m_dt;

};