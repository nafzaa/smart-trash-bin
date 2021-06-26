#define BLYNK_PRINT Serial
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo servo;

String statuss = "";

int trigPin = D0;    
int echoPin = D1; 
long duration;
int distance;

int trigPin1 = D6;    
int echoPin1 = D7; 
long duration1;
int distance1;

int servoPin = D2;

int buzzer = D4;
int ledPin = D5;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "tnos-qTwOUUxtSj5Ueih_5qf1_ueoEFk";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DESKTOP-HP";
char pass[] = "nafza9494";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;

  Serial.print("sensor 1 = ");
  Serial.print(distance);
  Serial.print(" sensor 2 = ");
  Serial.println(distance1);

  if (distance1 <= 5){
    tone(buzzer, 1000, 300);
    digitalWrite(ledPin, HIGH);
    statuss = "Full";
    }
  else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
   statuss = "No Full";
  }

  if (distance <= 50){
    Serial.println("servo bukak");
    servo.write(150);    
    delay(3000);
    servo.write(0);
    Serial.println("servo tutup");    
    }
  
  Blynk.virtualWrite(V5, distance1);
  Blynk.virtualWrite(V6, statuss);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 
  pinMode(trigPin1, OUTPUT);  
  pinMode(echoPin1, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT); 
  servo.attach(servoPin);
  servo.write(0);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
