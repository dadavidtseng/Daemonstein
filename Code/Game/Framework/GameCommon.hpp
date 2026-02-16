//----------------------------------------------------------------------------------------------------
// GameCommon.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

//----------------------------------------------------------------------------------------------------
class App;
class Game;
class LightSubsystem;

// one-time declaration
extern App*            g_app;
extern Game*           g_game;
extern LightSubsystem* g_lightSubsystem;

//----------------------------------------------------------------------------------------------------
template <typename T>
void GAME_SAFE_RELEASE(T*& pointer)
{
    delete pointer;
    pointer = nullptr;
}

void PlaySoundClicked(char const* keyName);
