#include "ScreenController.h"

ScreenController::ScreenController(std::shared_ptr<Configuration> cfg, std::shared_ptr<Themeinator> themeinator)
{
    Serial.println("Screen controller starting.");
    bus = std::make_shared<Arduino_HWSPI>(
        cfg->PIN_DC_TFT,
        cfg->PIN_CS_TFT,
        cfg->PIN_SCK_TFT,
        cfg->PIN_MOSI_TFT,
        cfg->PIN_MISO_TFT);

    gfx = std::make_shared<Arduino_ILI9341>(bus.get(), cfg->PIN_RST_TFT);
    this->themeinator = themeinator;

    textPrinter = std::make_shared<TextPrinter>(themeinator, gfx);

    gfx->begin();
    gfx->fillScreen(themeinator->GetBgColor());
}

void ScreenController::Tick(uint64_t millisDelta)
{
    textPrinter->SetPosition(20, 20);
    textPrinter->SetTextScale(3);
    textPrinter->DrawText("Hello!");
}
