#pragma once
#include <memory>
#include <Arduino_GFX_Library.h>
#include <Themeinator.h>

class TextPrinter
{
    std::shared_ptr<Arduino_GFX> gfx;
    std::shared_ptr<Themeinator> themeinator;

    int32_t pos_x, pos_y;
    uint32_t text_size;
    uint32_t letter_width = 6, letter_height = 8;
public:
    TextPrinter(std::shared_ptr<Themeinator> themeinator, std::shared_ptr<Arduino_GFX> arduino_gfx);
    void SetLetterSize(uint32_t w, uint32_t h);
    void SetPosition(int32_t x, int32_t y);
    void SetTextScale(uint32_t size);
    void SetColors(uint16_t txtColor, uint16_t bgColor);
    void DrawText(std::string text);
};