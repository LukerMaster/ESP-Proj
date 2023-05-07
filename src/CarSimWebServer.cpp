#include "CarSimWebServer.h"

CarSimWebServer::CarSimWebServer(std::shared_ptr<CarSimulation> carData, std::string ssid, std::string wifiPass) : server(80)
{
    this->carData = carData;
    WiFi.begin(ssid.c_str(), wifiPass.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected!");
    Serial.println("IP Address:");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [this](AsyncWebServerRequest* request)
    {
        request->send(200, "text/plain", std::to_string(this->carData->GetSpeedKmh()).c_str());
    });
    server.begin();
}

void CarSimWebServer::Tick()
{
}