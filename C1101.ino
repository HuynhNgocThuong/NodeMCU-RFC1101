/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

//const char* ssid     = "PIONEER CLUB";
//const char* password = "c119bkdn";

char ssid[] = "Thuong";
char pass[] = "33334444";
char server[] = "www.vmig2016.16mb.com";

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers



int i;
char c;
char c1[30]={};

//const char* streamId   = "....................";
//const char* privateKey = "....................";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

    // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("\n Starting connetion to sever..");
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  printWifiStatus();
}
void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
    while(client.available()) {
    char c = client.read();  
   if( c=='0' || c== '1' || c=='2' || c == '3' || c =='4' || c=='5' || c=='6' || c =='7' || c=='8' || c=='9'){
          c1[i] = c;
          i++; 
    }
  }
    Serial.write(c1[30]);
      i=0;
      c1[30]={};
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
    httpRequest();
    delay(100);
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    // send the HTTP PUT request:
    client.println("GET /data.txt HTTP/1.1");
    client.println("Host: www.vmig2016.16mb.com");
    client.println("Connection: close");
    client.println();
    // note the time that the connection was made:
  }
  else {
    // if you couldn't make a connection:
    Serial.println("Connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


