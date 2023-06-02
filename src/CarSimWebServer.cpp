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
                200, "application/json", 
                (
                    ("{ \"car-data\" : {" + 
                        Jsonify("speed", this->carData->GetSpeed()) +
                        Jsonify("fuel-left", this->carData->GetFuel()) +
                        Jsonify("fuel-tank-capacity", this->carData->GetTankCapacity()) +
                        Jsonify("rpm", this->carData->GetEngineRpm()) +
                        Jsonify("maxRpm", this->carData->GetMaxRpm()) +
                        Jsonify("odometer", this->carData->GetOdometerReading()) +
                        Jsonify("tripometer", this->carData->GetTripometerReading()) +
                        Jsonify("oil-temperature", this->carData->GetOilTempC()) +
                        Jsonify("current-gear", this->carData->GetCurrentGear()) +
                        Jsonify("num-of-forward-gears", this->carData->GetNumOfForwardGears())+
                        Jsonify("throttle-valve-open-percent", this->carData->GetThrottleInput()) + 
                        Jsonify("brake-pressure-applied", this->carData->GetBrakeInput()) + 
                        Jsonify("inside-temperature", this->carData->GetInsideTemperature(), true) +
                    "}\n}").c_str()
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