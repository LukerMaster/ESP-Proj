#include "ScreenController.h"

ScreenController::ScreenController(std::shared_ptr<Arduino_DataBus> bus, std::shared_ptr<Arduino_GFX> gfx, std::shared_ptr<TextPrinter> printer, std::shared_ptr<Themeinator> themeinator)
{
    Serial.println("Screen controller starting.");
    this->bus = bus;
    this->gfx = gfx;
    this->textPrinter = printer;
    this->themeinator = themeinator;
    textPrinter = std::make_shared<TextPrinter>(themeinator, gfx);

    gfx->begin();
    gfx->fillScreen(themeinator->GetBgColor());
}

void ScreenController::RedrawEverything()
{
    gfx->fillScreen(themeinator->GetBgColor());
}

void ScreenController::Tick(uint64_t millisDelta)
{
    textPrinter->SetPosition(20, 20);
    textPrinter->SetTextScale(3);
    textPrinter->DrawText("Hello!");
}
