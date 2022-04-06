/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Notes.cpp
Project: BIT_SAVER
Author: Jaewoo.choi, Hyosang Jung 

-----------------------------------------------------------------*/
#include"../../Engine/Engine.h"
#include "NoteHard.h"
#include"../../Engine/Sprite/GameParticles.h"
#include "EnergyBar.h"
//#include "../../Engine/Music/music.h"
//#include "../../Game/Levels/State.h"
//#include "../../Engine/Window/Window.h"
#include"Score.h"
//#include"../../Engine/Physics/Camera.h"
//#include"../Levels/MainOption.h"
//#include"obstacle.h"
#include "Score Enum.h"
#include "../Objects/Hero.h"

HardNote::HardNote(glm::vec2 startPos, glm::vec2 velocity, double time) :
    isMiss(false),
	UpAttackKey(InputKey::Keyboard::None),
	DownAttackKey(InputKey::Keyboard::None),
	life_time(time),
GameObject(startPos, glm::vec2{ 2,1 })
{
	timer = 0.0;
	start_timer = false;

	if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
	{
		energy = (static_cast<EnergyBar*>(Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Energy_bar)));
	}
	AddGOComponent(new Sprite("../images/Hit_star.png", this));
	SetVelocity(velocity);

}

void HardNote::Update(double dt)
{
	if (start_timer == true)
	{
		timer += dt;
	}

	if (timer > life_time)
	{
		set_destroy(true);
	}

	GameObject::Update(dt);

	UpAttackKey = Engine::GetAttack_Key().UpAttackKey;
	DownAttackKey = Engine::GetAttack_Key().DownAttackKey;
	if (GetPosition().x < -10)
	{
		set_destroy(true);
	}
	Hit_Check();
	
	if (isMiss == true)
	{
	    if (energy->GetScale().x > 0)
	    {
		energy->SetScale(glm::vec2{ energy->GetScale().x - (dt / 10),energy->GetScale().y });
		energy->UpdatePosition(glm::vec2{ -(dt / 10),0 });
	    }
	}	
}

void HardNote::Draw(glm::mat3 camera_matrix)
{
	glm::mat3 trans_mat
	{
		1,0,0,
		0,1,0,
		-0.25,0,1
	};
	GameObject::Draw(camera_matrix * trans_mat);
}

glm::vec2 HardNote::Getposition()
{
    return GameObject::GetPosition();
}

void HardNote::Hit_Check()
{
	if (Score_check()== static_cast<int>(SCORE::PERFECT) && GetPosition().y > 0)
	{
		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<HitEmitter>() != nullptr)
			{

			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::GOOD) && GetPosition().y > 0)
	{
		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<HitEmitter>() != nullptr)
			{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::BAD) && GetPosition().y > 0)
	{
		if ((UpAttackKey.IsKeyDown() == true && UpAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<HitEmitter>() != nullptr)
			{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);
		}
	}

	if (Score_check() == static_cast<int>(SCORE::PERFECT) && GetPosition().y < 0)
	{
		if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<HitEmitter>() != nullptr)
			{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<PerfectEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);
		}
	}

	else if (Score_check() == static_cast<int>(SCORE::GOOD) && GetPosition().y < 0)
	{
		if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<HitEmitter>() != nullptr)
			{
			Engine::GetGSComponent<HitEmitter>()->Emit(1, GetPosition(), { 0,0 }, { 0,0 }, 0);
			Engine::GetGSComponent<GoodEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);
		}
	}
	else if (Score_check() == static_cast<int>(SCORE::BAD)	&& GetPosition().y < 0)
	{
		if ((DownAttackKey.IsKeyDown() == true && DownAttackKey.IsKeyReapeated() == false))
		{
			if (Engine::GetGSComponent<BadEmitter>() != nullptr)
			{
			Engine::GetGSComponent<BadEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
			Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
			set_destroy(true);

		}
	}
	if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
	{
		if (Score_check() == static_cast<int>(SCORE::MISS) && isMiss == false && Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x - GetPosition().x > 1)
		{
			isMiss = true;
			if (Engine::GetGSComponent<MissEmitter>() != nullptr)
			{
				Engine::GetGSComponent<MissEmitter>()->Emit(1, GetPosition(), { -4,2 }, { 0,0 }, 0);
				Engine::GetGSComponent<Score>()->AddScore(Score_check());
			}
		}
	}
}

int HardNote::Score_check()
{
	float HeroPostion = 0;
	if (Engine::GetGameStateManager().GetCurrstate()->GetName() != "Offset")
	{
		 HeroPostion = Engine::GetGSComponent<GameObjectManager>()->Find(GameObjectType::Hero)->GetPosition().x;
	}

    if (GetPosition().x - HeroPostion <= 0.85 && HeroPostion - GetPosition().x <= 0.65)//0.4
    {
        return static_cast<int>(SCORE::PERFECT);
    }
    else if (GetPosition().x - HeroPostion <= 1.45 && GetPosition().x - HeroPostion > 0.85 ||
        HeroPostion - GetPosition().x <= 1.45 && HeroPostion - GetPosition().x > 0.85)//0.6
    {
        return static_cast<int>(SCORE::GOOD);
    }
    else if (GetPosition().x - HeroPostion < 1.85 && GetPosition().x - HeroPostion > 1.45 ||
        HeroPostion - GetPosition().x < 1.85 && HeroPostion - GetPosition().x > 1.45)//0.8
    {
        return static_cast<int>(SCORE::BAD);
    }
    return static_cast<int>(SCORE::MISS);
}

