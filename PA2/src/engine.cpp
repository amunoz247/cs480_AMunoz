
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }

    // Checks button to pause/resume everything
    if (m_pauseCube == true)
    {
      m_graphics->pauseCube(m_DT);
      m_graphics->Render();
    }

    if (m_pauseCube == false)
    {
      m_graphics->Update(m_DT);
      m_graphics->Render();
    }

    // Checks button to stop/start rotation
    if (m_pauseRotation == true)
    {
      m_graphics->stopCubeRotation(m_DT);
      m_graphics->Render();
    }

    // Checks button to change direction of rotation
    if (m_reverseRotation == true)
    {
      m_graphics->reverseRotation(m_DT);
      m_graphics->Render();
    }

    // Checks button to stop/start orbit
    /*if (m_pauseOrbit == true)
    {
      m_graphics->stopCubeRotation(m_DT);
      m_graphics->Render();
    }*/

    // Checks button to change direction of orbit
    if (m_reverseOrbit == true)
    {
      m_graphics->reverseOrbit(m_DT);
      m_graphics->Render();
    }

    // Update and render the graphics
    //m_graphics->Update(m_DT);
    //m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  m_DT = getDT();

  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }

  else if(m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    // Button to close the program
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }

    // Button to pause/resume everything
    if (m_event.key.keysym.sym == SDLK_SPACE)
    {
      m_pauseCube = true;
    }

    // Button to stop/start rotation
    if (m_event.key.keysym.sym == SDLK_DOWN)
    {
      m_pauseRotation = true;
    }

    // Button to change direction of rotation
    if (m_event.key.keysym.sym == SDLK_LEFT)
    {
      m_reverseRotation = true;
    }

    // Left Mouse click to stop/start orbit
    /*if (m_event.button.MouseButtonEvent.button == SDL_BUTTON_LEFT)
    {
      m_pauseOrbit = true;
    }*/

    // Button to change direction of orbit
    if (m_event.key.keysym.sym == SDLK_SLASH)
    {
      m_reverseOrbit = true;
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
