#pragma once
#include <memory>
#include <Arduino_GFX_Library.h>

class ScreenAPI
{
    std::shared_ptr<Arduino_DataBus> bus;
    std::shared_ptr<Arduino_GFX> gfx;

    int32_t pos_x = 0, pos_y = 0;
    uint32_t text_size = 1;
    uint32_t letter_width = 6, letter_height = 8;
    uint16_t bg_color_565RGB = 0x0000;
    uint16_t fg_color_565RGB = 0x0000;
public:
    ScreenAPI(std::shared_ptr<Arduino_DataBus> bus, std::shared_ptr<Arduino_GFX> arduino_gfx);
    uint32_t GetScreenSizeX();
    uint32_t GetScreenSizeY();
    
    void SetLetterSize(uint32_t w, uint32_t h);
    void SetTextPosition(int32_t x, int32_t y);
    void SetTextScale(uint32_t size);
    void SetFgColor(uint16_t color);
    void SetBgColor(uint16_t color);
    void DrawText(std::string text, uint32_t textSizeOverride);
    void DrawText(std::string text);
    void DrawProgressBar(int32_t x, int32_t y, int32_t w, int32_t h, float fillPercent);

    void FillScreen(uint16_t color);
};