#include <IRremote.h>
 
// Pin Definitions
const int RECV_PIN = 11;
 
// Global Vars
IRrecv irrecv( RECV_PIN );
decode_results results;
 
String buttons[] = { "Power", "Backward", "Forward", "Plus", "Minus", "0", "1", "2", "3", "4", "5", "6", "7" };
 
void setup() {    
    Serial.begin( 9600 );
    irrecv.enableIRIn(); // Start the receiver
}
 
void loop() {
    
    for( int i = 0; i < sizeof(buttons) / sizeof(String); i++ ) {
        Serial.print( "Signal untuk tombol " );
        Serial.print( buttons[i] );
        Serial.print( " : " );
        delay( 1000 );
        
        bool is_decode_success;
 
        do {
            is_decode_success = irrecv.decode(&results);
            if( is_decode_success ) { 
                irrecv.resume();
            }
        } while( !is_decode_success || results.value == 0xFFFFFFFF );
        
        Serial.println( results.value, HEX );
        delay( 100 );
    }
 
    while( true );
}
