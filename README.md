# IR Remote Button Tester (Remote_Signal_Logging)

This project is designed to test and display the IR remote button signals received by an Arduino. It helps identify the hex codes sent by the remote for different buttons, which can be useful for mapping and programming remote-controlled projects.

## Components Used

- Arduino Uno
- IR Receiver
- Jumper Wires
- Breadboard

## Pin Configuration

- **RECV_PIN**: connected to the IR receiver (Pin 11)

## Code Overview

The code continuously tests the IR remote buttons and displays their corresponding hex codes on the Serial Monitor. It uses an array of button names to label each signal received.

```cpp
#include <IRremote.h>

// Pin Definitions
const int RECV_PIN = 11;

// Global Vars
IRrecv irrecv(RECV_PIN);
decode_results results;

String buttons[] = { "Power", "Backward", "Forward", "Plus", "Minus", "0", "1", "2", "3", "4", "5", "6", "7" };

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
}

void loop() {
    for (int i = 0; i < sizeof(buttons) / sizeof(String); i++) {
        Serial.print("Signal for button ");
        Serial.print(buttons[i]);
        Serial.print(" : ");
        delay(1000);

        bool is_decode_success;

        do {
            is_decode_success = irrecv.decode(&results);
            if (is_decode_success) {
                irrecv.resume();
            }
        } while (!is_decode_success || results.value == 0xFFFFFFFF);

        Serial.println(results.value, HEX);
        delay(100);
    }

    while (true); // Stop execution after testing all buttons
}
```

## How to Use

1. Connect the IR receiver to the specified pin on the Arduino.
2. Upload the code to your Arduino.
3. Open the Serial Monitor in the Arduino IDE.
4. Point your IR remote at the IR receiver and press each button.
5. Observe the hex codes printed on the Serial Monitor for each button.

## Notes

- Ensure the IR receiver is properly connected to avoid any signal issues.
- The while (true); statement in the code halts further execution after the testing loop, so you will need to reset the Arduino to run the test again.
