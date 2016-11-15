// Window.cpp

// OpenGL Includes
#ifdef __APPLE__
  #include <OpenGL/gl3.h>
  #include <OpenGL/gl3ext.h>
#else
  #include <GL/glew.h>
#endif
// HGF Includes
#include <HGF/Window.hpp>

namespace HGF
{
  Window::Window()
  {
    m_IsInitialized = false;
    m_Window = nullptr;
    m_Context = nullptr;
  }

  Window::~Window()
  {
    if (m_IsInitialized)
    {
      Finalize();
    }
  }

  bool Window::Initialize(const WindowOptions& p_Options)
  {
    if (m_IsInitialized)
    {
      SDL_Log("[HGF::Window::Initialize] Window already initialized. Use Reinitialize to make changes to an existing Window.");
      return false;
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to initialize the video subsystem: %s", SDL_GetError());
      return false;
    }

    // Set OpenGL attributes.
    if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, p_Options.Attributes.RedSize) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute red size to %i: %s", p_Options.Attributes.RedSize, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, p_Options.Attributes.GreenSize) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute green size to %i: %s", p_Options.Attributes.GreenSize, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, p_Options.Attributes.BlueSize) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute blue size to %i: %s", p_Options.Attributes.BlueSize, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, p_Options.Attributes.AlphaSize) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute alpha size to %i: %s", p_Options.Attributes.AlphaSize, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, p_Options.Attributes.DepthSize) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute depth size to %i: %s", p_Options.Attributes.DepthSize, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, p_Options.Attributes.MultisampleBuffers) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute multisample buffers to %i: %s", p_Options.Attributes.MultisampleBuffers, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, p_Options.Attributes.MultisampleSamples) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute multisample samples to %i: %s", p_Options.Attributes.MultisampleSamples, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute OpenGL context major version to %i: %s", 3, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute OpenGL context minor version to %i: %s", 2, SDL_GetError());
      return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to set attribute OpenGL context profile mask: %s", SDL_GetError());
      return false;
    }

    // Setup window flags.
    Uint32 flags = static_cast<Uint32>(p_Options.Mode) | SDL_WINDOW_OPENGL;
    if (p_Options.IsHidden)
    {
      flags |= SDL_WINDOW_HIDDEN;
    }

    // Create the window.
    m_Window = SDL_CreateWindow(p_Options.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_Options.Width, p_Options.Height, flags);
    if (m_Window == nullptr)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to create window: %s", SDL_GetError());
      return false;
    }

    // Create the context and make it current to the window.
    m_Context = SDL_GL_CreateContext(m_Window);
    if (m_Context == nullptr)
    {
      SDL_Log("[HGF::Window::Initialize] Failed to create OpenGL context: %s", SDL_GetError());
      return false;
    }
    SDL_GL_MakeCurrent(m_Window, m_Context);

    // Configure vertical sync.
    if (!SetVerticalSyncEnabled(p_Options.IsVerticalSyncEnabled))
    {
      return false;
    }

    // Set viewport.
    glViewport(0, 0, p_Options.Width, p_Options.Height);

    // Set OpenGL properties.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return (m_IsInitialized = true);
  }

  bool Window::Reinitialize(const WindowOptions& p_Options)
  {
    if (!m_IsInitialized)
    {
      SDL_Log("[HGF::Window::Reinitialize] Window has yet to be initialized.");
      return false;
    }

    // Set title and resize.
    SetTitle(p_Options.Title);
    SetSize(p_Options.Width, p_Options.Height);

    // Adjust mode.
    Uint32 flags = 0;
    if (p_Options.Mode == WindowMode::Fullscreen || p_Options.Mode == WindowMode::FullscreenWindowed)
    {
      flags = static_cast<Uint32>(p_Options.Mode);
    }
    SDL_SetWindowBordered(m_Window, p_Options.Mode == WindowMode::Windowed ? SDL_TRUE : SDL_FALSE);
    if (SDL_SetWindowFullscreen(m_Window, flags) < 0)
    {
      SDL_Log("[HGF::Window::Reinitialize] Failed to adjust fullscreen: %s", SDL_GetError());
      return false;
    }

    // Adjust vertical sync.
    if (!SetVerticalSyncEnabled(p_Options.IsVerticalSyncEnabled))
    {
      return false;
    }

    // Check if hidden.
    if (p_Options.IsHidden)
    {
      Hide();
    }

    return true;
  }

  void Window::Finalize()
  {
    if (!m_IsInitialized)
    {
      SDL_Log("[HGF::Window::Finalize] Window already finalized. Doing nothing.");
    }
    else
    {
      // Delete the context.
      if (m_Context != nullptr)
      {
        SDL_GL_DeleteContext(m_Context);
      }

      // Destroy the window.
      if (m_Window != nullptr)
      {
        SDL_DestroyWindow(m_Window);
      }

      SDL_QuitSubSystem(SDL_INIT_VIDEO);

      m_IsInitialized = false;
    }
  }

  void Window::GetTitle(std::string& p_Title)
  {
    p_Title = SDL_GetWindowTitle(m_Window);
  }

  void Window::GetPosition(int& p_X, int& p_Y)
  {
    SDL_GetWindowPosition(m_Window, &p_X, &p_Y);
  }

  void Window::GetSize(int& p_Width, int& p_Height)
  {
    SDL_GetWindowSize(m_Window, &p_Width, &p_Height);
  }

  void Window::SetTitle(const std::string& p_Title)
  {
    SDL_SetWindowTitle(m_Window, p_Title.c_str());
  }

  void Window::SetPosition(int p_X, int p_Y)
  {
    SDL_SetWindowPosition(m_Window, p_X, p_Y);
  }

  void Window::SetSize(int p_Width, int p_Height)
  {
    SDL_SetWindowSize(m_Window, p_Width, p_Height);
    glViewport(0, 0, p_Width, p_Height);
  }

  void Window::SetClearColor(const Color& p_Color)
  {
    glClearColor(p_Color.GetRed(), p_Color.GetGreen(), p_Color.GetBlue(), p_Color.GetAlpha());
  }

  bool Window::SetVerticalSyncEnabled(bool p_Enabled)
  {
    //  0 = immediate
    //  1 = synchronized
    // -1 = late swap tearing (not supporting)
    if (SDL_GL_SetSwapInterval(p_Enabled ? 1 : 0) < 0)
    {
      SDL_Log("[HGF::Window::SetVerticalSyncEnabled] Error setting vertical sync: %s", SDL_GetError());
      return false;
    }

    return true;
  }

  void Window::Show()
  {
    SDL_ShowWindow(m_Window);
  }

  void Window::Hide()
  {
    SDL_HideWindow(m_Window);
  }

  void Window::Focus()
  {
    SDL_RaiseWindow(m_Window);
  }

  void Window::Restore()
  {
    SDL_RestoreWindow(m_Window);
  }

  void Window::Maximize()
  {
    SDL_MaximizeWindow(m_Window);
  }

  void Window::Minimize()
  {
    SDL_MinimizeWindow(m_Window);
  }

  void Window::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Window::Flip()
  {
    SDL_GL_SwapWindow(m_Window);
  }

  void Window::ShowSimpleMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxLevel p_Level)
  {
    if (SDL_ShowSimpleMessageBox(static_cast<Uint32>(p_Level), p_Title.c_str(), p_Text.c_str(), m_Window) < 0)
    {
      SDL_Log("[HGF::Window::ShowSimpleMessageBox] Error showing message box: %s", SDL_GetError());
    }
  }

  MessageBoxButton Window::ShowCustomMessageBox(const std::string& p_Title, const std::string& p_Text, const MessageBoxDetails& p_Details)
  {
    int buttonCount = 0;
    SDL_MessageBoxButtonData* buttons = nullptr;

    switch (p_Details.ButtonSet)
    {
      case MessageBoxButtonSet::AbortRetryIgnoreSet:
        buttonCount = 3;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          {                                       0, static_cast<int>(MessageBoxButton::Abort),  "Abort" },
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::Retry),  "Retry" },
          { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(MessageBoxButton::Ignore), "Ignore" }
        };
        break;
      case MessageBoxButtonSet::OKSet:
        buttonCount = 1;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::OK), "OK" }
        };
        break;
      case MessageBoxButtonSet::OKCancelSet:
        buttonCount = 2;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::OK),     "OK" },
          { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(MessageBoxButton::Cancel), "Cancel" }
        };
        break;
      case MessageBoxButtonSet::RetryCancelSet:
        buttonCount = 2;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::Retry),  "Retry" },
          { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(MessageBoxButton::Cancel),  "Cancel" }
        };
        break;
      case MessageBoxButtonSet::YesNoSet:
        buttonCount = 2;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::Yes), "Yes" },
          {                                       0, static_cast<int>(MessageBoxButton::No),  "No" }
        };
        break;
      case MessageBoxButtonSet::YesNoCancelSet:
        buttonCount = 3;
        buttons = new SDL_MessageBoxButtonData[buttonCount] {
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(MessageBoxButton::Yes),    "Yes" },
          {                                       0, static_cast<int>(MessageBoxButton::No),     "No" },
          { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(MessageBoxButton::Cancel), "Cancel" }
        };
        break;
    }

    const SDL_MessageBoxColorScheme scheme = {
      {
        {
          p_Details.Scheme.BackgroundColor.GetRedAsByte(),
          p_Details.Scheme.BackgroundColor.GetGreenAsByte(),
          p_Details.Scheme.BackgroundColor.GetBlueAsByte()
        },
        {
          p_Details.Scheme.TextColor.GetRedAsByte(),
          p_Details.Scheme.TextColor.GetGreenAsByte(),
          p_Details.Scheme.TextColor.GetBlueAsByte()
        },
        {
          p_Details.Scheme.ButtonBorderColor.GetRedAsByte(),
          p_Details.Scheme.ButtonBorderColor.GetGreenAsByte(),
          p_Details.Scheme.ButtonBorderColor.GetBlueAsByte()
        },
        {
          p_Details.Scheme.ButtonBackgroundColor.GetRedAsByte(),
          p_Details.Scheme.ButtonBackgroundColor.GetGreenAsByte(),
          p_Details.Scheme.ButtonBackgroundColor.GetBlueAsByte()
        },
        {
          p_Details.Scheme.ButtonSelectedColor.GetRedAsByte(),
          p_Details.Scheme.ButtonSelectedColor.GetGreenAsByte(),
          p_Details.Scheme.ButtonSelectedColor.GetBlueAsByte()
        }
      }
    };

    const SDL_MessageBoxData data = {
      static_cast<Uint32>(p_Details.Level),
      m_Window,
      p_Title.c_str(),
      p_Text.c_str(),
      buttonCount,
      buttons,
      &scheme
    };

    int retval;
    if (SDL_ShowMessageBox(&data, &retval) < 0)
    {
      SDL_Log("[HGF::Window::ShowCustomMessageBox] Error showing message box: %s", SDL_GetError());
    }

    delete[] buttons;

    return static_cast<MessageBoxButton>(retval);
  }

  void Window::PrintInfo()
  {
    SDL_Log("[HGF::Window::PrintInfo] OpenGL Version: %s", glGetString(GL_VERSION));
    SDL_Log("[HGF::Window::PrintInfo] GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_Log("[HGF::Window::PrintInfo] Vendor: %s", glGetString(GL_VENDOR));
    SDL_Log("[HGF::Window::PrintInfo] Renderer: %s", glGetString(GL_RENDERER));
  }
}
