//----------------------------------------------------------------------------------------------------
// App.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Game/Framework/App.hpp"
//----------------------------------------------------------------------------------------------------
#include "Game/Framework/GameCommon.hpp"
#include "Game/Gameplay/Game.hpp"
#include "Game/Subsystem/Light/LightSubsystem.hpp"
//----------------------------------------------------------------------------------------------------
#include "Engine/Audio/AudioSystem.hpp"
#include "Engine/Core/Clock.hpp"
#include "Engine/Core/DevConsole.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/Platform/Window.hpp"
#include "Engine/Renderer/BitmapFont.hpp"
#include "Engine/Renderer/DebugRenderSystem.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Resource/ResourceSubsystem.hpp"

//----------------------------------------------------------------------------------------------------
App*            g_app            = nullptr;       // Created and owned by Main_Windows.cpp
Game*           g_game           = nullptr;       // Created and owned by the App
LightSubsystem* g_lightSubsystem = nullptr;       // Created and owned by the App

//----------------------------------------------------------------------------------------------------
STATIC bool App::m_isQuitting = false;

//----------------------------------------------------------------------------------------------------
App::App()
{
    GEngine::Get().Construct();
}

//----------------------------------------------------------------------------------------------------
App::~App()
{
    GEngine::Get().Destruct();
}

//----------------------------------------------------------------------------------------------------
void App::Startup()
{
    GEngine::Get().Startup();

    LoadGameConfig("Data/GameConfig.xml");

    g_eventSystem->SubscribeEventCallbackFunction("OnCloseButtonClicked", OnCloseButtonClicked);
    g_eventSystem->SubscribeEventCallbackFunction("quit", OnCloseButtonClicked);

    // sDevConsoleConfig devConsoleConfig;
    // devConsoleConfig.m_defaultRenderer = g_renderer;
    // devConsoleConfig.m_defaultFontName = "SquirrelFixedFont";
    // devConsoleConfig.m_defaultCamera   = m_devConsoleCamera;
    // g_devConsole                       = new DevConsole(devConsoleConfig);

    // g_devConsole->AddLine(DevConsole::INFO_MAJOR, "Controls");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(Mouse) Aim");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(W/A)   Move");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(S/D)   Strafe");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(Z/C)   Elevate");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(Shift) Sprint");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(1)     Pistol");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(2)     Plasma Rifle");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(P)     Pause");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(O)     Step Frame");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(F)     Toggle Free Camera");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(N)     Possess Next Actor");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(~)     Toggle Dev Console");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(ESC)   Exit Game");
    // g_devConsole->AddLine(DevConsole::INFO_MINOR, "(SPACE) Start Game");


    sLightConfig constexpr lightConfig;
    g_lightSubsystem = new LightSubsystem(lightConfig);

    g_lightSubsystem->StartUp();

    g_game     = new Game();
}

//----------------------------------------------------------------------------------------------------
// All Destroy and ShutDown process should be reverse order of the StartUp
//
void App::Shutdown()
{
    GAME_SAFE_RELEASE(g_game);

    g_eventSystem->UnsubscribeEventCallbackFunction("quit", OnCloseButtonClicked);
    g_eventSystem->UnsubscribeEventCallbackFunction("OnCloseButtonClicked", OnCloseButtonClicked);

    g_lightSubsystem->ShutDown();

    GEngine::Get().Shutdown();
}

//----------------------------------------------------------------------------------------------------
// One "frame" of the game.  Generally: Input, Update, Render.  We call this 60+ times per second.
//
void App::RunFrame()
{
    BeginFrame();   // Engine pre-frame stuff
    Update();       // Game updates / moves / spawns / hurts / kills stuff
    Render();       // Game draws current state of things
    EndFrame();     // Engine post-frame stuff
}

//----------------------------------------------------------------------------------------------------
void App::RunMainLoop()
{
    // Program main loop; keep running frames until it's time to quit
    while (!m_isQuitting)
    {
        // Sleep(16); // Temporary code to "slow down" our app to ~60Hz until we have proper frame timing in
        RunFrame();
    }
}

//----------------------------------------------------------------------------------------------------
STATIC bool App::OnCloseButtonClicked(EventArgs& args)
{
    UNUSED(args)

    RequestQuit();

    return true;
}

//----------------------------------------------------------------------------------------------------
STATIC void App::RequestQuit()
{
    m_isQuitting = true;
}

//----------------------------------------------------------------------------------------------------
void App::BeginFrame() const
{
    g_eventSystem->BeginFrame();
    g_window->BeginFrame();
    g_renderer->BeginFrame();
    DebugRenderBeginFrame();
    g_devConsole->BeginFrame();
    g_input->BeginFrame();
    g_audio->BeginFrame();
    g_lightSubsystem->BeginFrame();
}

//----------------------------------------------------------------------------------------------------
void App::Update()
{
    Clock::TickSystemClock();

    UpdateCursorMode();

    g_game->Update();
}

//----------------------------------------------------------------------------------------------------
// Some simple OpenGL example drawing code.
// This is the graphical equivalent of printing "Hello, world."
//
// Ultimately this function (App::Render) will only call methods on Renderer (like Renderer::DrawVertexArray)
//	to draw things, never calling OpenGL (nor DirectX) functions directly.
//
void App::Render() const
{
    Rgba8 const clearColor = Rgba8::GREY;

    g_renderer->ClearScreen(clearColor);
    g_game->Render();

    // g_renderer->BeginCamera(*m_devConsoleCamera);
    // AABB2 const box = AABB2(Vec2::ZERO, Vec2(1600.f, 30.f));
    //
    // g_devConsole->Render(box);
    // g_renderer->EndCamera(*m_devConsoleCamera);
    AABB2 const box            = AABB2(Vec2::ZERO, Vec2(1600.f, 30.f));

    g_devConsole->Render(box);
}

//----------------------------------------------------------------------------------------------------
void App::EndFrame() const
{
    g_eventSystem->EndFrame();
    g_window->EndFrame();
    g_renderer->EndFrame();
    DebugRenderEndFrame();
    g_devConsole->EndFrame();
    g_input->EndFrame();
    g_audio->EndFrame();
    g_lightSubsystem->EndFrame();
}

//----------------------------------------------------------------------------------------------------
void App::UpdateCursorMode()
{
    bool const doesWindowHasFocus   = GetActiveWindow() == g_window->GetWindowHandle();
    bool const shouldUsePointerMode = !doesWindowHasFocus || g_devConsole->IsOpen() || g_game->GetGameState() == eGameState::ATTRACT;

    if (shouldUsePointerMode == true)
    {
        g_input->SetCursorMode(eCursorMode::POINTER);
    }
    else
    {
        g_input->SetCursorMode(eCursorMode::FPS);
    }
}

//----------------------------------------------------------------------------------------------------
void App::DeleteAndCreateNewGame()
{
    delete g_game;
    g_game = nullptr;

    g_game = new Game();
}

void App::LoadGameConfig(char const* gameConfigXmlFilePath)
{
    XmlDocument     gameConfigXml;
    XmlResult const result = gameConfigXml.LoadFile(gameConfigXmlFilePath);

    if (result == XmlResult::XML_SUCCESS)
    {
        if (XmlElement const* rootElement = gameConfigXml.RootElement())
        {
            g_gameConfigBlackboard.PopulateFromXmlElementAttributes(*rootElement);
        }
        else
        {
            DebuggerPrintf("WARNING: game config from file \"%s\" was invalid (missing root element)\n", gameConfigXmlFilePath);
        }
    }
    else
    {
        DebuggerPrintf("WARNING: failed to load game config from file \"%s\"\n", gameConfigXmlFilePath);
    }
}
