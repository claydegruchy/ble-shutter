#include <Arduino.h>
/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the
 * words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */

#define TRIGGER_PIN 14
#define RECOIL_PIN 27
#define LASER_PIN 26
#define TOGGLE_1_PIN 25
#define TOGGLE_2_PIN 33

#include <BleKeyboard.h>

int trigger_state = 0;      // Variable to hold button state
int TOGGLE_1_state = false; // Variable to hold button state
int TOGGLE_2_state = false; // Variable to hold button state

BleKeyboard bleKeyboard("Exitus Rifle");

void setup()
{
  Serial.begin(115200);
  pinMode(TRIGGER_PIN,
          INPUT_PULLUP); // Set pin as input with internal pull-up resistor
  pinMode(RECOIL_PIN, OUTPUT);
  pinMode(LASER_PIN, OUTPUT);

  pinMode(TOGGLE_1_PIN,
          INPUT_PULLUP); // Set pin as input with internal pull-up resistor
  pinMode(TOGGLE_2_PIN,
          INPUT_PULLUP); // Set pin as input with internal pull-up resistor

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void send_keypress()
{

  if (bleKeyboard.isConnected())
  {

    Serial.println("Sending UP key...");
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  }
}

void activate_solenoid()
{
  Serial.println("RECOIL_PIN, HIGH");
  digitalWrite(RECOIL_PIN, HIGH);
  delay(25);
  Serial.println("RECOIL_PIN, LOW");
  digitalWrite(RECOIL_PIN, LOW);
}

void loop()
{

  trigger_state = digitalRead(TRIGGER_PIN); // Read the button state

  if (digitalRead(TOGGLE_1_PIN) == LOW)
  {
    TOGGLE_1_state = !TOGGLE_1_state;
    Serial.print("switched toggle 1 state:");
    Serial.println(TOGGLE_1_state);
    delay(400);
  }

  if (digitalRead(TOGGLE_2_PIN) == LOW)
  {
    // activation_time += 5;
    // if (activation_time > 100)
    //   activation_time = 10;
    TOGGLE_2_state = !TOGGLE_2_state;
    Serial.println("switched toggle 2 ");
    delay(400);
  }

  if (trigger_state == LOW)
  { // Button pressed (active LOW)
    Serial.println("Button Pressed");

    send_keypress();
    activate_solenoid();
    delay(1000);
  }

  if (TOGGLE_1_state == true)
  {
    digitalWrite(LASER_PIN, HIGH);
  }
  else
  {
    digitalWrite(LASER_PIN, LOW);
  }

  delay(100); // Small delay to debounce
}