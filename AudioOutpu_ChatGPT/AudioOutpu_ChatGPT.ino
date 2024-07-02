0 
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <ArduinoJson.h>
#include "Audio.h"


const char* ssid = "admin";
const char* password = "admin12345";

const char* chatgpt_token = "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";
const char* temperature = "0";
const char* max_tokens = "45";
String Question = "";
String Answer = "";

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();


  while (!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
}

void loop()
{
  String ask = "Ask your Question : ";
  Serial.println(ask);
  while (!Serial.available())
  {
    audio.loop();
  }
  while (Serial.available())
  {
    char add = Serial.read();
    Question = Question + add;
    delay(1);
  }
  int len = Question.length();
  Question = Question.substring(0, (len - 1));
  Question = "\"" + Question + "\"";
  Serial.println(Question);

  HTTPClient https;

  //Serial.print("[HTTPS] begin...\n");
  if (WiFi.status() == WL_CONNECTED) {  // HTTPS
    HTTPClient https;
    https.setTimeout(15000);
    https.begin("https://api.openai.com/v1/chat/completions");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "Bearer " + String(chatgpt_token));
    
    String payload = String("{\"model\": \"gpt-3.5-turbo\",\"messages\": [{\"role\": \"user\", \"content\": ") + Question + String("}], \"temperature\": 0.1, \"max_tokens\": 35}");

    // start connection and send HTTP header
    int httpCode = https.POST(payload);

    // httpCode will be negative on error
    // file found at server
    if (httpCode > 0) {
      String payload = https.getString();

      DynamicJsonDocument doc(1024);


      deserializeJson(doc, payload);
      String Answe = doc["choices"][0]["message"]["content"];
      Answer = Answe.substring(0);
      Serial.print("Answer : "); Serial.println(Answer);
      audio.connecttospeech(Answer.c_str(), "en");

    }
    else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  
  Question = "";
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
