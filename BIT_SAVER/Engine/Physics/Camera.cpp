/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: BIT_SAVER
Author:	Hyosang Jung
-----------------------------------------------------------------*/
#include "Camera.h"
#include<cmath>
Camera::Camera(glm::vec2 newPosition):position(newPosition)
{
    mdl_to_ndc_xform =
    {
        1,0,0,
        0,1,0,
       -position.x,-position.y,1
    };
}

void Camera::SetPosition(glm::vec2 newPosition)
{
    position = newPosition;
}

void Camera::Update(const glm::vec2& followObjPos,[[maybe_unused]]double dt)
{
    
    mdl_to_ndc_xform =
    {
        1,0,0,
        0,1,0,
       -position.x,-position.y,1
    };
    glm::mat3 view_xform =
    {
        1,0,0,
        0,1,0,
       -followObjPos.x,-followObjPos.y,1
    };

    mdl_to_ndc_xform *= view_xform;
}

const glm::vec2& Camera::GetPosition() const
{
    return position;
}

glm::mat3 Camera::GetMatrix()
{
	return mdl_to_ndc_xform;
}

static glm::vec2 pos = { 0,0.25 };

void Camera::Dynamic_movement(bool start, double dt)
{
    dynamic_move = start;
    static double timer = 0;
    if (dynamic_move == false)
    {
        timer = 0.4;
        pos = { 0.25,0.25 };
        position = { 0,0 };
    }
    timer -= dt;
    if (timer > 0)
    {
        //pos = { 0,0.25 };
        position += pos;
        pos *= -0.9;
        dynamic_move = true;
    }
}
 