#include "TextPrinter.h"

TextPrinter::TextPrinter(std::shared_ptr<Themeinator> themeinator, std::shared_ptr<Arduino_GFX> arduino_gfx)
{
    Serial.println("Text printer starting.");
    this->themeinator = themeinator;
    this->gfx = arduino_gfx;
}

void TextPrinter::SetLetterSize(uint32_t w, uint32_t h)
{
    letter_width = w;
    letter_height = h;
}

void TextPrinter::SetPosition(int32_t x, int32_t y)
{
    pos_x = x;
    pos_y = y;
}

void TextPrinter::SetTextScale(uint32_t size)
{
    text_size = size;
}

void TextPrinter::DrawText(std::string text)
{
    gfx->fillRect(pos_x, pos_y, letter_width*text_size*text.size(), letter_height*text_size, themeinator->GetBgColor());
    gfx->setCursor(pos_x, pos_y);
    gfx->setTextColor(themeinator->GetTextColor());
    gfx->setTextSize(text_size);
    gfx->println(text.c_str());
}
