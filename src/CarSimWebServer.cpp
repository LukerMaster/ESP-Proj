#include "CarSimWebServer.h"

CarSimWebServer::CarSimWebServer(std::shared_ptr<CarSimulation> carData, std::string ssid, std::string wifiPass) : server(80)
{
    this->carData = carData;
    connectionTask.setName("Connection to WiFi");
    connectionTask.setFn([this, ssid, wifiPass] () {
        Serial.printf("WiFi Data Server Starting. Network SSID: %s\n", ssid.c_str());
        WiFi.begin(ssid.c_str(), wifiPass.c_str());
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(4500);
            Serial.println("Connecting to WiFi...");
            if (wifiPass == "PASSWORD" || wifiPass == "")
                Serial.println("Password is either set to default or empty. It is very unlikely that connection succeeds.\nChange password in Configuration header file if neccessary.");
        }
        Serial.println("Connected!");
        Serial.println("IP Address:");
        Serial.println(WiFi.localIP());

        server.on("/", HTTP_GET, [this](AsyncWebServerRequest* request)
        {
            request->send(200, "text/plain", ("Car Data Statistics Server:\n" +
            StrFormat::string_format("%.2f", this->carData->GetSpeedKmh()) + "KM/H\n" +
            StrFormat::string_format("%.0f", this->carData->GetRpm()) + "RPM\n" +
            std::to_string(this->carData->GetGear()) + " gear\n" + 
            StrFormat::string_format("%.2f", this->carData->GetFuelLeft() * 100.f) + "%% fuel left.")
            .c_str());
        });

        server.on("/speed", HTTP_GET, [this](AsyncWebServerRequest* request)
        { 
            request->send(200, "application/json", std::to_string(this->carData->GetSpeedKmh()).c_str()); 
        });

        server.on("/rpm", HTTP_GET, [this](AsyncWebServerRequest* request)
        { 
            request->send(200, "application/json", std::to_string(this->carData->GetRpm()).c_str()); 
        });

        server.on("/gear", HTTP_GET, [this](AsyncWebServerRequest* request)
        { 
            request->send(200, "application/json", std::to_string(this->carData->GetGear()).c_str()); 
        });

        server.on("/fuel", HTTP_GET, [this](AsyncWebServerRequest* request)
        { 
            request->send(200, "application/json", std::to_string(this->carData->GetFuelLeft()).c_str()); 
        });

        server.begin();
    });
    connectionTask.start();
}

void CarSimWebServer::Tick()
{
}