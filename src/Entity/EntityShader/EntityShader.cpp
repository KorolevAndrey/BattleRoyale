#include "EntityShader.hpp"

bool EntityShader::init() {
    /* Parent init */
    if (!Shader::init()) {
        return false;
    }

    /* Add attributes */
    addAttribute("vertexPos");
    addAttribute("vertexNormal");
    addAttribute("vertexTexture");

    /* Add matrix transforms */
    addUniform("P");
    addUniform("M");
    addUniform("V");

    /* Add texture info */
    addUniform("usesTexture");
    addUniform("textureImage");

    /* Add material properties */
    addUniform("matAmbient");
    addUniform("matDiffuse");
    addUniform("matSpecular");
    addUniform("shine");

    /* Add light */
    addUniform("lightPos");
    addUniform("lightCol");
    addUniform("lightAtt");

    /* Add time */
    addUniform("uTime");

    return true;
}

void EntityShader::loadP(const glm::mat4 *p) {
    this->loadMat4(getUniform("P"), p);
}

void EntityShader::loadM(const glm::mat4 *m) {
    this->loadMat4(getUniform("M"), m);
}

void EntityShader::loadV(const glm::mat4 *v) {
    this->loadMat4(getUniform("V"), v);
}

void EntityShader::loadMaterial(const float ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    this->loadFloat(getUniform("matAmbient"), ambient);
    this->loadVec3(getUniform("matDiffuse"), diffuse);
    this->loadVec3(getUniform("matSpecular"), specular);
}

void EntityShader::loadShine(const float s) {
    this->loadFloat(getUniform("shine"), s);
}

void EntityShader::loadLight(const Light &light) {
    this->loadVec3(getUniform("lightPos"), light.position);
    this->loadVec3(getUniform("lightCol"), light.color);
    this->loadVec3(getUniform("lightAtt"), light.attenuation);
}

void EntityShader::loadUsesTexture(const bool b) {
    this->loadBool(getUniform("usesTexture"), b);
}

void EntityShader::loadTexture(const Texture &texture) {
    glActiveTexture(GL_TEXTURE0 + texture.textureId);
    glUniform1i(getUniform("textureImage"), texture.textureId);
    glBindTexture(GL_TEXTURE_2D, texture.textureId);
}

void EntityShader::loadTime(const float t) {
    this->loadFloat(getUniform("uTime"), t);
}