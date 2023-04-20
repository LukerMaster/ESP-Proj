#include "ScreenAPI.h"

ScreenAPI::ScreenAPI(std::shared_ptr<Arduino_DataBus> bus, std::shared_ptr<Arduino_GFX> arduino_gfx)
{
    Serial.println("Screen API starting.");
    this->bus = bus;
    this->gfx = arduino_gfx;
    gfx->begin();
}

uint32_t ScreenAPI::GetScreenSizeX()
{
    return gfx->width();
}

uint32_t ScreenAPI::GetScreenSizeY()
{
    return gfx->height();
}

void ScreenAPI::SetLetterSize(uint32_t w, uint32_t h)
{
    letter_width = w;
    letter_height = h;
}

void ScreenAPI::SetTextPosition(int32_t x, int32_t y)
{
    pos_x = x;
    pos_y = y;
}

void ScreenAPI::SetTextScale(uint32_t size)
{
    text_size = size;
}

void ScreenAPI::SetFgColor(uint16_t color)
{
    this->fg_color_565RGB = color;
}

void ScreenAPI::SetBgColor(uint16_t color)
{
    this->bg_color_565RGB = color;
}

void ScreenAPI::DrawText(std::string text)
{
    gfx->fillRect(pos_x, pos_y, letter_width*text_size*text.size(), letter_height*text_size, bg_color_565RGB);
    gfx->setCursor(pos_x, pos_y);
    gfx->setTextColor(fg_color_565RGB);
    gfx->setTextSize(text_size);
    gfx->println(text.c_str());
}

void ScreenAPI::DrawProgressBar(int32_t x, int32_t y, int32_t w, int32_t h, float fillPercent)
{
    fillPercent = std::max(0.0f, std::min(1.0f, fillPercent));
    gfx->fillRect(x, y, w, h, bg_color_565RGB);
    gfx->drawRect(x, y, w, h, fg_color_565RGB);
    gfx->fillRect(x+2, y+2, (w-4) * fillPercent, h-4, fg_color_565RGB);
}

void ScreenAPI::FillScreen(uint16_t color)
{
    gfx->fillScreen(color);
}
