// Name:  Kelly Rhodes
// Project:  RFID Cat Feeder

// *********************** Physical Setup **************** //
// (Stack:  Arduino, Ethernet Shield, Motor Shield)
// 1.  Connect 5V power source to Arudino
// 2.  Connect Motor (5V directly to 5V; Ground to middle leg of transistor).  Check that connections are secure.
// 3.  Connect RFID.  Gray to 5v.  Green to Ground.  Purple to pin 8.  Blue to pin 9.
// 4.  Connect to Ethernet
// 5.  Connect Pin 7 to resistor coming off transistor
// reference for motor circuit:  http://electronics.stackexchange.com/questions/102022/how-to-control-the-speed-of-a-12v-dc-motor-with-an-arduino
// reference for LCD:  https://www.arduino.cc/en/Tutorial/HelloWorld?from=Tutorial.LiquidCrystal

// *********************** Motor Initialization **************** //
unsigned long lastMotor = 0;

// *********************** RFID Initialization **************** //
// include the SoftwareSerial library so we can use it to talk to the RFID Reader
#include <SoftwareSerial.h>

#define enablePin  8   // Connects to the RFID's ENABLE pin
#define rxPin      9  // Serial input (connects to the RFID's SOUT pin)
#define txPin      11  // Serial output (unused)

#define BUFSIZE    11  // Size of receive buffer (in bytes) (10-byte unique ID + null character)

#define RFID_START  0x0A  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x0D

// set up a new serial port
SoftwareSerial rfidSerial =  SoftwareSerial(rxPin, txPin);

// assign cats RFID tags
String chewie = "18002B9459";
String cheeto = "170076D198";
String pepper = "1700768341";

// variable to detect if a match exists; initialize to False (0)
boolean rfidMatch = 0;

// *********************** Ethernet Initialization **************** //
#include <SPI.h>
#include <Ethernet.h>
unsigned long lastRan = 0;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0x78, 0x31, 0xc1, 0xb8, 0xc5, 0xca }; // 78:31:c1:b8:c4:ca
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "data.sparkfun.com";    // name address for Google (using DNS) -- change to data.sparkfun.com

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

String catid; // variable to hold the cat's id
String cat; // variable to hold cat name

// *********************** LCD Initialization **************** //
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// *********************** Setup **************** //
void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Welcome to the Kitty Kibble Dispenser!");

  pinMode(7, OUTPUT); // setting the motor pin

  // ************ RFID Setup ************ //
  // define pin modes
  pinMode(enablePin, OUTPUT);
  pinMode(rxPin, INPUT);

  digitalWrite(enablePin, HIGH);  // disable RFID Reader
  
  // set the baud rate for the SoftwareSerial port
  rfidSerial.begin(2400);

  Serial.flush();   // wait for all bytes to be transmitted to the Serial Monitor
  
  // ************ Ethernet Setup ************ //

  
  while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    while(1){}
  }
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  sparkfun("0","0"); // send zero's as variables initially
  

  // ************ LCD Setup ************ //
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

} // closes setup()


// *********************** Main Loop **************** //
void loop() {

  if(millis() > lastRan + 1000){

     
    /*When the RFID Reader is active and a valid RFID tag is placed with range of the reader,
    the tag's unique ID will be transmitted as a 12-byte printable ASCII string to the host
    (start byte + ID + stop byte)
    
    For example, for a tag with a valid ID of 0F0184F07A, the following bytes would be sent:
    0x0A, 0x30, 0x46, 0x30, 0x31, 0x38, 0x34, 0x46, 0x30, 0x37, 0x41, 0x0D
    
    We'll receive the ID and convert it to a null-terminated string with no start or stop byte. 
    */   
  
    digitalWrite(enablePin, LOW);   // enable the RFID Reader
    
    // Wait for a response from the RFID Reader
    // See Arduino readBytesUntil() as an alternative solution to read data from the reader
    char rfidData[BUFSIZE];  // Buffer for incoming data
    char offset = 0;         // Offset into buffer
    rfidData[0] = 0;         // Clear the buffer 
       
    while(1){

      // If there are any bytes available to read, then the RFID Reader has probably seen a valid tag
      if (rfidSerial.available() > 0) {

        // Get the byte and store it in our buffer
        rfidData[offset] = rfidSerial.read(); 

        // If we receive the start byte from the RFID Reader, then get ready to receive the tag's unique ID
        if (rfidData[offset] == RFID_START){
          // Clear offset (will be incremented back to 0 at the end of the loop)
          offset = -1;     
        }

        // If we receive the stop byte from the RFID Reader, then the tag's entire unique ID has been sent
        else if (rfidData[offset] == RFID_STOP){

          // Null terminate the string of bytes we just received
          rfidData[offset] = 0; 
          // Break out of the loop
          break;                
        } // end if / else if

        // Increment offset into array
        offset++; 

        // If the incoming data string is longer than our buffer, wrap around to avoid going out-of-bounds 
        if (offset >= BUFSIZE) offset = 0; 
        
      } // closes if (rfidSerial.available() > 0)
      
    } // closes while(1)
  
    Serial.println(rfidData);       // The rfidData string should now contain the tag's unique ID with a null termination, so display it on the Serial Monitor

    if (chewie == rfidData || pepper == rfidData || cheeto == rfidData){
      Serial.println("There was a match!");
      catid = rfidData;

        // set cat variable
        if(chewie == rfidData){
          cat = "chewie";
        } else if (cheeto == rfidData){
          cat = "cheeto";
        } else {
          cat = "pepper";
        }

        lcd.print("Hello, ");
        lcd.print(cat);
        delay(1000);
        lcd.clear();

      rfidMatch = 1; // set rfidMatch to True (1)
    } else {
      Serial.println("Cat not recognized");
      lcd.println("Cat not recognized");
      delay(1000);
      lcd.clear();
    }
    
    while(rfidMatch){
      motorRun(); // run the motor
      sparkfun(catid, cat);
      resetReader(); // reset the RFID reader
      rfidMatch = 0; // set rfidMatch to False (0)
    }

    rfidMatch = 0; // set rfidMatch to False (0)
    
    Serial.flush();                 // Wait for all bytes to be transmitted to the Serial Monitor
    lastRan = millis();             // Update lastRan
    
  } // closes if(millis() > lastRan + 10000)
  
  
  // if anything has been sent from server, read it
  // if there are incoming bytes available
  // from the server, read them and print them:
  
  while(client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {  
    client.stop();
  }

  

} // closes loop

// *********************** motorRun **************** //
// This function will turn the motor on & off
void motorRun(){

  if(millis() > lastMotor + 10000){

    Serial.println("motor running");
    digitalWrite(7, HIGH);
    delay(750);
    
    Serial.println("motor release");
    digitalWrite(7, LOW);      // stopped
  
    // Keep track of time.  Do not dispense for 30 seconds
    lastMotor = millis();
  } else {
    Serial.println("waiting to reset");
    lcd.println("Waiting to reset");
    delay(1000);
    lcd.clear();
  }

  
}

// *********************** sparkfun **************** //
// This function will connect to the sparkfun website & will send data to the site
void sparkfun(String catid, String cat){
  
   // if you get a connection, report back via serial:
  if (client.connect(server, 80)) { // port 80 is default for HTTP
    Serial.println("connected");
    // Make a HTTP request:
    
    //client.print("GET /input/EJxEj5J2ObILX36xXD9l?private_key=dqvMpeq7PyIanZoWn8P7&light1=");
    //client.print("19.80&light2=19.42");
    client.print("GET /input/0lxrKzMxG7IrmbKa1Q0Q?private_key=D6pdYn0pNzFnm12wNVDV&catid="); // Get this file path, what protocol to use...Take domain out from example!!!
    client.print(catid);
    client.print("&cat=");
    client.print(cat);
    client.println(" HTTP/1.1");
    client.println("Host: data.sparkfun.com"); // Need host header for the server to know which site to give you
    client.println("Connection: close"); // when you are done sending data, close the connection
    client.println(); // double return tells server done talking; signifies end of the request
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
}

// *********************** resetReader **************** //
void resetReader()
{
  digitalWrite(enablePin, LOW);
  digitalWrite(enablePin, HIGH);
  delay(20);
}
