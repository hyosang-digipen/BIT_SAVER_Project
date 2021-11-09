/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.cpp
Project: 
Author: 
Creation date: 3/14/2021
-----------------------------------------------------------------*/

#include"Notes.h"
#include"../../Engine/Engine.h"
Note::Note(glm::vec2 startPos, glm::vec2 velocity) :
    moveUpKey(InputKey::Keyboard::Up),
    moveDownKey(InputKey::Keyboard::Down),
    isMiss(false),
GameObject(startPos, glm::vec2{ 0.5,1 })
{
	AddGOComponent(new Sprite("../images/hit_star.png", this));
	SetVelocity(velocity);
}

void Note::Update(double dt)
{
	GameObject::Update(dt);
	if (GetPosition().x < -10)
	{
		set_destroy(true);
	}
	Hit_Check();
}

void Note::Draw(glm::mat3 camera_matrix)
{
	GameObject::Draw(camera_matrix);
}

glm::vec2 Note::Getposition()
{
	return GameObject::GetPosition();
}

void Note::Hit_Check()
{
    if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.3
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.3
	&& GetPosition().y > 0)
    {
	if (moveUpKey.IsKeyDown() == true)
	{
	    std::cout << "Perfect";
	    set_destroy(true);
	}
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.4
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.4
	&& GetPosition().y > 0)
    {
	if (moveUpKey.IsKeyDown() == true)
	{
	    std::cout << "Good";

	    set_destroy(true);
	}
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.5
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.5
	&& GetPosition().y > 0)
    {
	if (moveUpKey.IsKeyDown() == true)
	{
	    std::cout << "BAD";
	    set_destroy(true);
	}
    }

    if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.3
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.3
	&& GetPosition().y < 0)
    {
	if (moveDownKey.IsKeyDown() == true)
	{
	    set_destroy(true);
	}
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.4
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.4
	&& GetPosition().y < 0)
    {
	if (moveDownKey.IsKeyDown() == true)
	{
	    set_destroy(true);
	}
    }
    else if (GetPosition().x - Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x < 0.5
	&& Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x < 0.5
	&& GetPosition().y < 0)
    {
	if (moveDownKey.IsKeyDown() == true)
	{
	    set_destroy(true);
	}
    }

    if (Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x > 0.5)
    {
	isMiss = true;
	std::cout << "Miss";

    }
}

bool Note::GetisMiss()
{
    return isMiss;
}
