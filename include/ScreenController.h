#pragma once
#include <memory>
#include <Arduino_GFX_Library.h>
#include <Themeinator.h>
#include <Configuration.h>
#include <TextPrinter.h>

class ScreenController
{
    std::shared_ptr<Arduino_DataBus> bus;
    std::shared_ptr<Arduino_GFX> gfx;
    std::shared_ptr<Themeinator> themeinator;
    std::shared_ptr<TextPrinter> textPrinter;
public:
    ScreenController(std::shared_ptr<Configuration> cfg, std::shared_ptr<Themeinator> themeinator);
    void Tick(uint64_t millisDelta);
};