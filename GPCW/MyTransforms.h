#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "MyCamera.h"

struct MyTransforms
{
public:
	MyTransforms(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 positionMatrix = glm::translate(pos);
		glm::mat4 scaleMatrix = glm::scale(scale);
		glm::mat4 rotationX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotationY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotationZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rototationMat = rotationX * rotationY * rotationZ;

		return positionMatrix * rototationMat * scaleMatrix;
	}

	
	inline glm::vec3* GetPos() { return &pos; } //getters
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->pos = pos; } // setters
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};


