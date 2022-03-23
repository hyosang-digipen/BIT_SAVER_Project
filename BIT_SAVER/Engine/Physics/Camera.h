/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#pragma once
#include <glm/glm.hpp>
#include "..\Component.h"
class Camera : public Component 
{
public:
	Camera(glm::vec2 newPosition);
	void SetPosition(glm::vec2 newPosition);
	void Update(const glm::vec2& followObjPos,double dt);
	const glm::vec2& GetPosition() const;
	glm::mat3 GetMatrix();
	void shake();
	void generate_shake_value();
private:
	glm::mat3 mdl_to_ndc_xform;
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	bool is_shaking;
	
	double target_time = 0;
	float shake_per_sec = 5;
	double timer = 10;
};
