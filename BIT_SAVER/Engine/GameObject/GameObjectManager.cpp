/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#include"GameObjectManager.h"
#include"GameObject.h"   // gameobject
#include "../Engine.h"

void GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void GameObjectManager::Add_front(GameObject* obj)
{
	gameObjects.push_front(obj);
}

void GameObjectManager::Unload()
{

	for (GameObject* a : gameObjects)
	{
	    if(a!=nullptr)
		delete a;
	}
	gameObjects.clear();
    

}

GameObject* GameObjectManager::Find(GameObjectType objType)
{
    std::list<GameObject*>::iterator it;

    it = std::find_if(gameObjects.begin(), gameObjects.end(),
	[&, it](GameObject* obj) {return obj->GetObjectType() == objType; });

    if (it != gameObjects.end()) {

	return *it;
    }
    else 
	{
		return nullptr;
    }
}

void GameObjectManager::UpdateAll(double dt)
{
	std::list<GameObject* > removelist;
	for (GameObject* a : gameObjects)
	{
		a->Update(dt);
		collision_check(a);
		if (a->Destroy() == true)
		{
			removelist.push_back(a);
		}
	}
	for (GameObject* remove : removelist)
	{
		gameObjects.remove(remove);
		
		delete remove;
	}
}

void GameObjectManager::DrawAll(glm::mat3 camera_matrix)
{
	for (GameObject* a : gameObjects)
	{
		a->Draw(camera_matrix);
	}
}

void GameObjectManager::collision_check(GameObject* object)
{
	AABB Box1 = object->GetCollisionbox();

	for (auto& test_object : gameObjects)
	{
		bool is_collided = true;
		AABB Box2 = test_object->GetCollisionbox();
		if (Box1.max.x < Box2.min.x || Box1.min.x > Box2.max.x)
		{
			is_collided = false;
		}
		if ((Box1.max.y < Box2.min.y || Box1.min.y > Box2.max.y))
		{
			is_collided = false;
		}
		if (is_collided == true)
		{
			object->ResolveCollision(test_object);
		}
	}
}

