#pragma once
#include <inttypes.h>
#include <functional>

enum class Theme
{
  Standard,
  Dark
};

/// @brief Theme manager? Nah. Themeinator.
class Themeinator
{
  uint16_t COLOR_WHITE = 0xFFFF;
  uint16_t COLOR_CALM = 0x4DA4;
  uint16_t COLOR_BLACK = 0x0000;

public:
  Theme CurrentTheme;

  uint16_t GetTextColor()
  {
    switch (CurrentTheme)
    {
      case Theme::Standard:
        return COLOR_BLACK;
      case Theme::Dark:
        return COLOR_CALM; 
      default:
        return COLOR_BLACK;
    }
  }

  uint16_t GetBgColor()
  {
    switch (CurrentTheme)
    {
      case Theme::Standard:
        return COLOR_WHITE;
      case Theme::Dark:
        return COLOR_BLACK;
      default:
        return COLOR_WHITE;
    }
  }
};