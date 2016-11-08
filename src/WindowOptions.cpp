// WindowOptions.cpp

// HGF Includes
#include <HGF/WindowOptions.hpp>
// JsonCpp Includes
#include <json/json.h>
// STL Includes
#include <fstream>

namespace HGF
{
  const std::string WindowOptions::DefaultTitle = "Untitled Window";
  const int WindowOptions::DefaultWidth = 1024;
  const int WindowOptions::DefaultHeight = 768;
  const WindowMode WindowOptions::DefaultMode = WindowMode::Windowed;
  const bool WindowOptions::DefaultIsVerticalSyncEnabled = true;
  const bool WindowOptions::DefaultIsHidden = false;

  const WindowOptions WindowOptions::DefaultOptions;

  WindowOptions::WindowOptions()
  {
    Title = DefaultTitle;
    Width = DefaultWidth;
    Height = DefaultHeight;
    Mode = DefaultMode;
    IsVerticalSyncEnabled = DefaultIsVerticalSyncEnabled;
    IsHidden = DefaultIsHidden;
  }

  bool WindowOptions::LoadFromFile(const std::string& p_Filename, WindowOptions& p_WindowOptions)
  {
    // Check for .json extension.
    if (p_Filename.substr(p_Filename.find_last_of('.') + 1) != "json")
    {
      SDL_Log("[WindowOptions::LoadFromFile] Filename does not have a JSON extension.");
      return false;
    }

    // Open the file.
    std::ifstream file(p_Filename, std::ofstream::in);
    if (!file.is_open())
    {
      return false;
    }

    // Parse the JSON document.
    Json::Value root;
    Json::Reader reader;
    bool isParsed = reader.parse(file, root, false);
    if (isParsed)
    {
      // Grab and assign attributes.
      p_WindowOptions.Title = root.get("title", DefaultTitle).asString();
      p_WindowOptions.Width = root.get("width", DefaultWidth).asInt();
      p_WindowOptions.Height = root.get("height", DefaultHeight).asInt();
      p_WindowOptions.Mode = static_cast<WindowMode>(root.get("mode", static_cast<Uint32>(DefaultMode)).asInt());
      // TODO: Deserialize Attributes.
      p_WindowOptions.IsVerticalSyncEnabled = root.get("vsync", DefaultIsVerticalSyncEnabled).asBool();
      p_WindowOptions.IsHidden = root.get("hidden", DefaultIsHidden).asBool();
    }
    else
    {
      SDL_Log("[WindowOptions::LoadFromFile] Failed to read JSON file.");
    }

    // Close the file.
    file.close();

    return isParsed;
  }

  bool WindowOptions::SaveToFile(const std::string& p_Filename, const WindowOptions& p_WindowOptions)
  {
    // Check for .json extension.
    if (p_Filename.substr(p_Filename.find_last_of('.') + 1) != "json")
    {
      SDL_Log("[WindowOptions::SaveToFile] Filename does not have a JSON extension.");
      return false;
    }

    // Open the file.
    std::ofstream file(p_Filename, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
    {
      return false;
    }

    // Construct the JSON.
    Json::Value root;
    root["title"] = p_WindowOptions.Title;
    root["width"] = p_WindowOptions.Width;
    root["height"] = p_WindowOptions.Height;
    root["mode"] = static_cast<int>(p_WindowOptions.Mode);
    // TODO: Serialize Attributes.
    root["vsync"] = p_WindowOptions.IsVerticalSyncEnabled;
    root["hidden"] = p_WindowOptions.IsHidden;

    // Write to the file.
    Json::StyledWriter writer;
    file << writer.write(root);

    // Close the file.
    file.close();

    return true;
  }
}
