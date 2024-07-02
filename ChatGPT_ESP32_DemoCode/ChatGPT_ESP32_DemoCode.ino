

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Airtel_Happy Home :)";
const char* password = "Hno15467E";


// Replace with your OpenAI API key
const char* apiKey = "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";
String res = "";
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();


  while (!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Serial.print("Ask your Question : ");
  while (!Serial.available());
  while (Serial.available())
  {
    char add = Serial.read();
    res = res + add;
    delay(1);
  }
  int len = res.length();
  res = res.substring(0, (len - 1));
  res = "\"" + res + "\"";
  Serial.println(res);

  //Serial.print("[HTTPS] begin...\n");
  if (WiFi.status() == WL_CONNECTED) {  // HTTPS
    HTTPClient https;
    https.setTimeout(15000);
    https.begin("https://api.openai.com/v1/chat/completions");
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "Bearer " + String(apiKey));
    
    String payload = String("{\"model\": \"gpt-3.5-turbo\",\"messages\": [{\"role\": \"user\", \"content\": ") + res + String("}], \"temperature\": 0.1, \"max_tokens\": 100}");

    // start connection and send HTTP header
    int httpCode = https.POST(payload);

    // httpCode will be negative on error
    // file found at server
    if (httpCode > 0) {
      String payload = https.getString();

      DynamicJsonDocument doc(1024);


      deserializeJson(doc, payload);
      String Answer = doc["choices"][0]["message"]["content"];
      Answer = Answer.substring(0);
      Serial.print("Answer : "); Serial.println(Answer);

    }
    else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  Serial.println("Wait 10s before next round...");
  res = "";
  delay(10000);
}
