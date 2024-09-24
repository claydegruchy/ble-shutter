#include <Arduino.h>
/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the
 * words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */

#define TRIGGER_PIN 14

#include <BleKeyboard.h>

int buttonState = 0; // Variable to hold button state

BleKeyboard bleKeyboard("Exitus Rifle");

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN,
          INPUT_PULLUP); // Set pin as input with internal pull-up resistor

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void send_keypress() {
  Serial.println("Sending UP key...");
  bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}

void loop() {
  if (bleKeyboard.isConnected()) {

    buttonState = digitalRead(TRIGGER_PIN); // Read the button state

    if (buttonState == LOW) { // Button pressed (active LOW)
      Serial.println("Button Pressed");
      send_keypress();
      delay(400);
    } else {
      // Serial.println("Button Released");
    }

    delay(100); // Small delay to debounce

    return;
  }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}