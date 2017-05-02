#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

struct MyCamera
{
public:
	MyCamera()
	{
	}

	void loadCamera(const vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = vec3(0.0f, 0.0f, 1.0f);
		this->up = vec3(0.0f, 1.0f, 0.0f);
		this->projection = perspective(fov, aspect, nearClip, farClip);
	}

	inline mat4 GetViewProjection() const
	{
		return projection * lookAt(pos, pos + forward, up);
	}

protected:
private:
	mat4 projection;
	vec3 pos;
	vec3 forward;
	vec3 up;
};


