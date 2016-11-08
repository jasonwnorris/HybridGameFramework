// Window.hpp

#ifndef __HGF_WINDOW_HPP__
#define __HGF_WINDOW_HPP__

// HGF Includes
#include <HGF/MessageBoxButton.hpp>
#include <HGF/MessageBoxDetails.hpp>
#include <HGF/WindowOptions.hpp>
// STL Includes
#include <string>

namespace HGF
{
  class Window
  {
    public:
      Window();
      ~Window();

      bool Initialize(const WindowOptions& p_Options = WindowOptions::DefaultOptions);
      bool Reinitialize(const WindowOptions& p_Options = WindowOptions::DefaultOptions);
      bool Finalize();

      void GetTitle(std::string& p_Title);
      void GetPosition(int& p_X, int& p_Y);
      void GetSize(int& p_Width, int& p_Height);

      void SetTitle(const std::string& p_Title);
      void SetPosition(int p_X, int p_Y);
      void SetSize(int p_Width, int p_Height);
      bool SetVerticalSyncEnabled(bool p_Enabled);
      void SetClearColor(const Color& p_Color);

      void Show();
      void Hide();
      void Focus();
      void Restore();
      void Maximize();
      void Minimize();

      void Clear();
      void Flip();

      void ShowSimpleMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxLevel p_Level = MessageBoxLevel::Information);
      MessageBoxButton ShowCustomMessageBox(const std::string& p_Title, const std::string& p_Text, const MessageBoxDetails& p_Details = MessageBoxDetails::DefaultDetails);

      void PrintInfo();

    private:
      bool m_IsInitialized;
      SDL_Window* m_Window;
      SDL_GLContext m_Context;
  };
}

#endif
