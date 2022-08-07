#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//ESP8266WebServer server(80);

// Replace with your network credentials
const char* ssid     = "Kubi";
const char* password = "Justkillit";

//Domain Name
const char* serverName = "unfamiliar-hunts.000webhostapp.com";

int potPin =A0;
float ph;
String sendphval;
 float Value=0;
 

//#define SEALEVELPRESSURE_HPA (1013.25)
void setup() {
 
Serial.begin(115200); 
Serial.println("Communication Started \n\n");  

pinMode(LED_BUILTIN, OUTPUT);
pinMode(potPin,INPUT);
delay(1000);
  
     // initialize built in led on the board
 


WiFi.mode(WIFI_STA);           
WiFi.begin(ssid, password);                                     //try to connect with wifi
Serial.print("Connecting to ");
Serial.print(ssid);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print(".");
    delay(500); }

Serial.println();
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP());    //print local IP address

//delay(30);
}

void loop() {
 // sendphval = String(phval);

 Value= analogRead(potPin);
    Serial.print(Value);
    Serial.print(" | ");
    float voltage=Value*(3.3/4095.0);
    ph=(3.3*voltage);
    sendphval=String(ph);
   Serial.println(sendphval);
 
  HTTPClient http; // http object of clas HTTPClient
  WiFiClient client;
  
  Serial.print("pH = ");
 Serial.println( sendphval);
  //Serial.println(ph(voltage));
  delay(3000);
 

      // Prepare your HTTP POST request data
   String httpRequestData = "&sendphval=" + sendphval;
    
    
    // Your Domain name with URL path or IP address with path
   http.begin(client,"http://unfamiliar-hunts.000webhostapp.com/post-sensor-data.php");
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    
    int httpCode = http.POST(httpRequestData);  // Send HTTP POST request
 Serial.print("HValues are, : ");
      Serial.println(httpRequestData);
      
 
// if connection eatablished then do this
if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
String webpage = http.getString();    // Get html webpage output and store it in a string
Serial.println(webpage + "\n"); 
}

   // if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }
  
 delay(3000); 
digitalWrite(LED_BUILTIN, LOW);
delay(3000);
digitalWrite(LED_BUILTIN, HIGH);

}
