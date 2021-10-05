/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include<iostream>
#include <chrono>   
#include "..\Engine\GameState\GameStateManager.h"
#include "..\Engine\input\Input.h"
#include "..\Engine\Window\Window.h"
#include "..\Engine\Logger\Logger.h"
#include"..\Engine\GLModel\GLModel.h"
#include"..\Engine\GLShader\glslshader.h"
#include"..\Engine\Texture\TextureManager.h"
#include<map>
//#include"TextureManager.h"
//#include "SpriteFont.h"
class Engine 
{
public:
    static Engine& Instance() 
    { 
        static Engine instance; return instance; 
    }
    static Logger& GetLogger() { return Instance().logger; };
    static Input& GetInput() { return Instance().input; }
    static Window& GetWindow() { return Instance().window; }
    static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
    static TextureManager& GetTextureManager() { return Instance().texturemanager; }
    static  std::map<std::string, GLModel>& GetGLModel () { return Instance().models; }
    static  std::map<std::string, GLSLShader>& GetGLShader() { return Instance().shdrpgms; }
    //static CS230::TextureManager& GetTextureManager() { return Instance().texturemanager; }
    //static CS230::SpriteFont& GetSpriteFont(int index) { return Instance().fonts[index]; }

    void Init(std::string windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();
    void init_shdrpgms();
 //   void AddSpriteFont(const std::filesystem::path& fileName);
   // template<typename T>
   // static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }

public:
    Engine();
    ~Engine();

    std::chrono::system_clock::time_point lastTick;
    std::chrono::system_clock::time_point fpsCalcTime;
    int frameCount;

   Logger logger;
   GameStateManager gameStateManager;
   Input input;
   Window window;
   std::map<std::string, GLModel> models;
   std::map<std::string, GLSLShader> shdrpgms;
   TextureManager texturemanager;
 //   CS230::TextureManager texturemanager;
    static constexpr double Target_FPS = 60.0;
    static constexpr int FPS_IntervalSec = 5;
    static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
   // std::vector<CS230::SpriteFont> fonts;

};
