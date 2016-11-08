// WindowOptions.hpp

#ifndef __HGF_WINDOWOPTIONS_HPP__
#define __HGF_WINDOWOPTIONS_HPP__

// HGF Includes
#include <HGF/WindowAttributes.hpp>
#include <HGF/WindowMode.hpp>
// STL Includes
#include <string>

namespace HGF
{
  struct WindowOptions
  {
    static const std::string DefaultTitle;
    static const int DefaultWidth;
    static const int DefaultHeight;
    static const WindowMode DefaultMode;
    static const bool DefaultIsVerticalSyncEnabled;
    static const bool DefaultIsHidden;

    static const WindowOptions DefaultOptions;

    std::string Title;
    int Width;
    int Height;
    WindowMode Mode;
    WindowAttributes Attributes;
    bool IsVerticalSyncEnabled;
    bool IsHidden;

    WindowOptions();

    static bool LoadFromFile(const std::string& p_Filename, WindowOptions& p_WindowOptions);
    static bool SaveToFile(const std::string& p_Filename, const WindowOptions& p_WindowOptions);
  };
}

#endif
