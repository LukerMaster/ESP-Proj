#include "CarSimWebServer.h"

CarSimWebServer::CarSimWebServer(std::shared_ptr<CarInfo> carData, std::string ssid, std::string wifiPass) : server(80)
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

        server.on("/api/stats", HTTP_GET, [this](AsyncWebServerRequest* request)
        {
            request->send(
                200, "text/json", 
                (
                std::string(R"({"anus" : "yes"})").c_str()
                )
            );
        });


        server.begin();
    });
    connectionTask.start();
}

void CarSimWebServer::Tick()
{
}