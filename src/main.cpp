#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MAX_MSG_LEN (128)

const char* ssid = "Searching...";
const char* password = "l0nbr1g@9@c@";

const char* mqttServer = "10.0.0.49";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
// const char *topic = "testTopic";
const char *topic = "sprinkler";


WiFiClient espClient;
PubSubClient client(espClient);
 
// Assigning relays to digital outputs 

// int Tx_Pin = GPIO1;
// int Rx_Pin = GPIO3;
int relay1Pin = D1;
int relay2Pin = D2;
int relay3Pin = D3;
int relay4Pin = D4;
int relay5Pin = D5;
int relay6Pin = D6;
int relay7Pin = D7;
int relay8Pin = D8;
 
void setRelay1State(boolean state){
  digitalWrite (relay1Pin, !state);
  if (state) {
    client.publish("sprinkler", "r1_is_on");
  } else {
    client.publish("sprinkler", "r1_is_off");  
  }
}

void setRelay2State(boolean state){
  digitalWrite (relay2Pin, !state);
  if (state) {
    client.publish("sprinkler", "r2_is_on");
  } else {
    client.publish("sprinkler", "r2_is_off");  
  }  
}

void setRelay3State(boolean state){
  digitalWrite (relay3Pin, !state);
  if (state) {
    client.publish("sprinkler", "r3_is_on");
  } else {
    client.publish("sprinkler", "r3_is_off");  
  }
}

void setRelay4State(boolean state){
  digitalWrite (relay4Pin, !state);
  if (state) {
    client.publish("sprinkler", "r4_is_on");
  } else {
    client.publish("sprinkler", "r4_is_off");  
  }
}

void setRelay5State(boolean state){
  digitalWrite (relay5Pin, !state);
  if (state) {
    client.publish("sprinkler", "r5_is_on");
  } else {
    client.publish("sprinkler", "r5_is_off");  
  }
}

void setRelay6State(boolean state){
  digitalWrite (relay6Pin, !state);
  if (state) {
    client.publish("sprinkler", "r6_is_on");
  } else {
    client.publish("sprinkler", "r6_is_off");  
  }
}

void setRelay7State(boolean state){
  digitalWrite (relay7Pin, !state);
  if (state) {
    client.publish("sprinkler", "r7_is_on");
  } else {
    client.publish("sprinkler", "r7_is_off");  
  }
}

void setRelay8State(boolean state){
  digitalWrite (relay8Pin, !state);
  if (state) {
    client.publish("sprinkler", "r8_is_on");
  } else {
    client.publish("sprinkler", "r8_is_off");  
  }
}

void callback(char *msgTopic, byte *msgPayload, unsigned int msgLength) {
  // copy payload to a static string
  static char message[MAX_MSG_LEN+1];
  if (msgLength > MAX_MSG_LEN) {
    msgLength = MAX_MSG_LEN;
  }
  strncpy(message, (char *)msgPayload, msgLength);
  message[msgLength] = '\0';
  
  Serial.printf("topic %s, message received: %s\n", msgTopic, message);

  // decode message
  if (strcmp(message, "r1_off") == 0) {
    setRelay1State(false);
  } else if (strcmp(message, "r1_on") == 0) {
    setRelay1State(true);
  }

  if (strcmp(message, "r2_off") == 0) {
    setRelay2State(false);
  } else if (strcmp(message, "r2_on") == 0) {
    setRelay2State(true);
  }

  if (strcmp(message, "r3_off") == 0) {
    setRelay3State(false);
  } else if (strcmp(message, "r3_on") == 0) {
    setRelay3State(true);
  }

  if (strcmp(message, "r4_off") == 0) {
    setRelay4State(false);
  } else if (strcmp(message, "r4_on") == 0) {
    setRelay4State(true);
  }

  if (strcmp(message, "r5_off") == 0) {
    setRelay5State(false);
  } else if (strcmp(message, "r5_on") == 0) {
    setRelay5State(true);
  }

  if (strcmp(message, "r6_off") == 0) {
    setRelay6State(false);
  } else if (strcmp(message, "r6_on") == 0) {
    setRelay6State(true);
  }

  if (strcmp(message, "r7_off") == 0) {
    setRelay7State(false);
  } else if (strcmp(message, "r7_on") == 0) {
    setRelay7State(true);
  }

  if (strcmp(message, "r8_off") == 0) {
    setRelay8State(false);
  } else if (strcmp(message, "r8_on") == 0) {
    setRelay8State(true);
  }

}

void connectMQTT() {
  // Wait until we're connected
  while (!client.connected()) {
    // Create a random client ID
    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);
    Serial.printf("MQTT connecting as client %s...\n", clientId.c_str());
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("MQTT connected");
      // Once connected, publish an announcement...
      client.publish(topic, "hello from ESP8266");
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      Serial.printf("MQTT failed, state %s, retrying...\n", client.state());
      // Wait before retrying
      delay(2500);
    }
  }
}

void setup() {
 
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  pinMode(relay5Pin, OUTPUT);
  pinMode(relay6Pin, OUTPUT);
  pinMode(relay7Pin, OUTPUT);
  pinMode(relay8Pin, OUTPUT);

  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);
  digitalWrite(relay4Pin, HIGH);
  digitalWrite(relay5Pin, HIGH);
  digitalWrite(relay6Pin, HIGH);
  digitalWrite(relay7Pin, HIGH);  
  digitalWrite(relay8Pin, HIGH);
 
  // Connect to WiFi network
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT..."); 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
  
      Serial.println("connected");  
  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
  client.publish("sprinkler", "Hello from ESP8266");
  client.subscribe("sprinkler");
}




 
void loop() {
  if (!client.connected()){
    connectMQTT();
  }
  client.loop();
  delay(500);
}