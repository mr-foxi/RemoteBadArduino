#include <wifi.h>
#include <WiFi.h>
#include <payloadsList.h>
/* !#!# DANGER !#!# DANGER !#!# DANGER !#!# */
#include <pass.h>
/* !#!# DANGER !#!# DANGER !#!# DANGER !#!# */

#ifdef OLED_h
#include <oled.h>
#endif
void oledPayloadMessage(String payload) {
    #ifdef OLED_h
    oled.printlnString("$PAYLOAD$");
    oled.printlnString(payload);
    #endif
}
void oledRogerRoger() {
    #ifdef OLED_h
    oled.printlnString("Roger Roger!");
    delay(3000);
    oled.foxClear();
    #endif
}
void oledConnectionFailed() {
    oled.printlnString("Connect Failed...");
    delay(3000);
    oled.foxClear();
}

WIFI::WIFI() {}

void WIFI::up() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    #ifdef OLED_h
    oled.printString("Connecting");
    #endif
while(WiFi.status() != WL_CONNECTED) { 
        int i = 0;    
        delay(1000);
        Serial.print(".");
        #ifdef OLED_h
        oled.printString(".");
        #endif
        i++;
        if (i > 60) {break;}
    }
    if (WL_CONNECTED) {
        Serial.print("Connected to WiFi network with IP Address: ");
        String ipAddr = WiFi.localIP().toString();
        Serial.println(WiFi.localIP());
        #ifdef OLED_h
        oled.clear();
        oled.printlnString("Connected to WiFi!");
        oled.printlnString("IP address: ");
        oled.printlnString(ipAddr);
        #endif
    } else {
        Serial.println("WiFi Connection Failed");
        #ifdef OLED_h
        oled.printlnString("WiFi Connection Failed");
        #endif
    }
}
void WIFI::RSSI() {
    int signal = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.println(signal);
    #ifdef OLED_h
    oled.printString("RSSI: ");
    oled.printlnInt(signal);
    #endif
}
void WIFI::httpRequest() {
    HTTPClient http;
    http.begin(HOST_NAME + PATH_NAME); //HTTP
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        #ifdef OLED_h
        oled.printString(payload);
        #endif
    } else {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        #ifdef OLED_h
        oled.printString("[HTTP] GET... code: ");
        oled.printlnInt(httpCode);
        #endif
    }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        #ifdef OLED_h
        oled.printString("[HTTP] GET... failed, error: ");
        oled.printlnInt(httpCode);
        #endif
    }
    http.end();
}

WiFiServer server(ESP_PORT); // USING TCP ON PORT 7408
void WIFI::apStart() {
    WiFi.softAPConfig(ESP_IP, ESP_IP, ESP_SUBNET);
    // Start Wi-Fi in AP mode
    WiFi.softAP(ESP_SSID, ESP_PASS);
    Serial.println("Access Point Started");
    Serial.println(WiFi.softAPIP()); // Should print ESP_IP from pass.h

    // Start TCP server
    server.begin();
    Serial.println("Server started");
}

String WIFI::apRecieve() {
    WiFiClient client = server.available();  // Wait for a client
    String msg;
    if (client) {
        Serial.println("Client connected");
        while (client.connected()) {
        if (client.available()) {
            msg = client.readStringUntil('\n');
            Serial.print("Received: ");
            Serial.println(msg);
        }
        }
        client.stop();
        Serial.println("Client disconnected");
    }
    return msg;
}
// void WIFI::apRecieve() {
//     WiFiClient client = server.available();  // Wait for a client
//     if (client) {
//         Serial.println("Client connected");
//         while (client.connected()) {
//         if (client.available()) {
//             String msg = client.readStringUntil('\n');
//             Serial.print("Received: ");
//             Serial.println(msg);
//         }
//         }
//         client.stop();
//         Serial.println("Client disconnected");
//     }
// }
void WIFI::sendMessage() {
    Serial.println("Connecting to AP...");
    WiFi.begin(ESP_SSID, ESP_PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    // Connect to server
    WiFiClient client;
    if (client.connect(ESP_IP, ESP_PORT)) {
        Serial.println("Connected to Pycom server.");
        Serial.println("Sending Test Payload.");
        client.println("$Test Payload$");
        client.stop();
        Serial.println("Message sent and connection closed.");
    } else {
        Serial.println("Failed to connect to Pycom server.");
    }
}
void WIFI::sdPayload() {
    oledPayloadMessage("$SD$");
    Serial.println("Connecting to AP...");
    WiFi.begin(ESP_SSID, ESP_PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    // Connect to server
    WiFiClient client;
    if (client.connect(ESP_IP, ESP_PORT)) {
        Serial.println("Connected to dummyPayload server.");
        Serial.println("Sending SD Payload Activion.");
        client.println(payloadsList.CONST_SDCARD);
        client.stop();
        Serial.println("Message sent and connection closed.");
        oledRogerRoger();
    } else {
        Serial.println("Failed to connect to dummyPayload server.");
        oledConnectionFailed();
    }
}
void WIFI::pullScript() {
    oledPayloadMessage("$PULLSCRIPT$");
    Serial.println("Connecting to AP...");
    WiFi.begin(ESP_SSID, ESP_PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    // Connect to server
    WiFiClient client;
    if (client.connect(ESP_IP, ESP_PORT)) {
        Serial.println("Connected to dummyPayload server.");
        Serial.println("Sending Pull Script Payload Activion.");
        client.println(payloadsList.CONST_PULLSCRIPT);
        client.stop();
        Serial.println("Message sent and connection closed.");
        oledRogerRoger();
    } else {
        Serial.println("Failed to connect to dummyPayload server.");
        oledConnectionFailed();
    }
}
void WIFI::pullScriptExit() {
    oledPayloadMessage("$PULLSCRIPTEXIT$");
    Serial.println("Connecting to AP...");
    WiFi.begin(ESP_SSID, ESP_PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    // Connect to server
    WiFiClient client;
    if (client.connect(ESP_IP, ESP_PORT)) {
        Serial.println("Connected to dummyPayload server.");
        Serial.println("Sending Pull Script Exit Payload Activion.");
        client.println(payloadsList.CONST_PULLSCRIPTEXIT);
        client.stop();
        Serial.println("Message sent and connection closed.");
        oledRogerRoger();
    } else {
        Serial.println("Failed to connect to dummyPayload server.");
        oledConnectionFailed();
    }
}
WIFI wifi = WIFI();
