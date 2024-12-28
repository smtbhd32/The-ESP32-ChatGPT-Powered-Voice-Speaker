# The ESP32 ChatGPT-Powered Voice Speaker

This project demonstrates the integration of the **ESP32** microcontroller with **ChatGPT** to create a voice-powered speaker system. The system uses **text-to-speech (TTS)** and **speech recognition** to allow users to interact with the **ChatGPT** model, enabling conversational AI features with voice commands. It showcases the power of the ESP32 combined with cloud-based AI capabilities.

## Features

- **Voice Interaction**: Allows users to interact with ChatGPT using voice input.
- **Text-to-Speech**: Converts ChatGPT's text responses into speech using TTS.
- **ESP32 Powered**: Utilizes the ESP32 microcontroller for low-cost and efficient operation.
- **Cloud AI**: Leverages ChatGPT API to provide intelligent responses.
- **Speech Recognition**: Converts voice commands into text for processing by ChatGPT.

## Components Required

- **ESP32 Microcontroller** (e.g., ESP32 Dev Board)
- **Microphone Module** (e.g., I2S MEMS microphone)
- **Speaker** (with an amplifier if needed)
- **Jumper wires and Breadboard**
- **Wi-Fi connection** for internet access

## Software Dependencies

- **ESP-IDF** or **Arduino IDE** for programming the ESP32.
- **Arduino Libraries**:
  - `WiFi` - To connect to Wi-Fi.
  - `WiFiClientSecure` - For secure HTTPS requests.
  - `Audio` - For handling audio output (TTS).
  - `SpeechRecognition` (optional, for local processing).
- **ChatGPT API** - For processing user input and generating responses.
- **Text-to-Speech API** - For converting text to speech (e.g., Google TTS, eSpeak, etc.).

## Setup Instructions

### 1. Install the ESP32 Arduino Core

Follow the instructions on the [ESP32 Arduino Core GitHub](https://github.com/espressif/arduino-esp32) to install the ESP32 core in your Arduino IDE.

### 2. Setup Wi-Fi

Modify the following section of the code with your Wi-Fi credentials:

```cpp
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
```

### 3. ChatGPT API Key

To interact with ChatGPT, you will need an API key. Create an OpenAI account and retrieve the API key. Then, add the API key to the code:

```cpp
const char* openai_api_key = "your_openai_api_key";
```

### 4. Microphone Setup

Ensure the microphone module is connected to the ESP32 according to its specifications. You can use an I2S microphone like the **INMP441** or **SPH0645**.

### 5. Speaker Setup

Connect the speaker to the ESP32. You may need an amplifier if your speaker requires higher power to produce sound.

### 6. Upload the Code

Upload the provided Arduino code to the ESP32. This code will handle the Wi-Fi connection, speech recognition, communication with the ChatGPT API, and text-to-speech functionality.

### 7. Run the Project

Once the code is uploaded, open the Serial Monitor to monitor the connection status. The system should connect to Wi-Fi and await voice commands. Speak into the microphone to interact with ChatGPT, and listen to the voice responses through the speaker.

## Example Usage

- **User**: "What's the weather like today?"
- **ESP32**: Responds with a spoken weather report, using ChatGPT for the response.

## Troubleshooting

- **No response from the speaker**: Ensure the speaker is connected and powered correctly. Check the speaker volume.
- **Voice input not recognized**: Make sure the microphone is connected and functioning. Adjust the gain if needed.

## Contributing

If you would like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request. Any improvements or new features are welcome!

## License

This project is licensed under the MIT License.

---
