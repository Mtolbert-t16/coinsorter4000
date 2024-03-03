// orange:quarter red:penny yellow: nickel green: dime


#define TOP_SERVO 7
#define DOOR_SERVO 9
#define BOT_SERVO 6
#define P_BUTTON 13
#define Q_BUTTON 12
#define D_BUTTON 11
#define N_BUTTON 10
#define G_BUTTON 3
#define SCREEN 5 
#define POT_PIN A0
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

float savings = 0;
float goal = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include <Servo.h>


Servo servo;
Servo bservo;
Servo dservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(TOP_SERVO);
  servo.write(90);
  bservo.attach(BOT_SERVO);
  bservo.write(90);
  dservo.attach(DOOR_SERVO);
  dservo.write(30);
  pinMode(Q_BUTTON, INPUT_PULLUP);
  pinMode(P_BUTTON, INPUT_PULLUP);
  pinMode(D_BUTTON, INPUT_PULLUP);
  pinMode(N_BUTTON, INPUT_PULLUP);
  pinMode(G_BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
  

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.display();




}


void write_to_display(String message) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(message);
  display.display();
}


void sort_penny() {
  int p_button = digitalRead(P_BUTTON);

    if (p_button == 0)  { // Check if the button is pressed
    servo.write(45);  // Set the angle of the first servo to 90 degrees
    delay(1000);
    servo.write(90);
    delay(500);
    bservo.write(45);  // Set the angle of the second servo to 90 degrees
    delay(1000);  // Wait for 1 second
    bservo.write(90);

    savings += .01;

    delay(500);
  }
}

void sort_quarter() {
  int q_button = digitalRead(Q_BUTTON);

    if (q_button == 0)  { // Check if the button is pressed
    servo.write(45);  // Set the angle of the first servo to 90 degrees
    delay(1000);
    servo.write(90);
    delay(500);
    bservo.write(140);  // Set the angle of the second servo to 90 degrees
    delay(1000);  // Wait for 1 second
    bservo.write(90);

    savings += 0.25;

    delay(500);
  }
}


void sort_dime() {
  int d_button = digitalRead(D_BUTTON);

    if (d_button == 0)  { // Check if the button is pressed
    servo.write(140);  // Set the angle of the first servo to 90 degrees
    delay(1000);
    servo.write(90);
    delay(500);
    bservo.write(140);  // Set the angle of the second servo to 90 degrees
    delay(1000);  // Wait for 1 second
    bservo.write(90);

    savings += 0.1;

    delay(500);
  }
}


void sort_nickel() {
  int n_button = digitalRead(N_BUTTON);

    if (n_button == 0)  { // Check if the button is pressed
    servo.write(140);  // Set the angle of the first servo to 90 degrees
    delay(1000);
    servo.write(90);
    delay(500);
    bservo.write(45);  // Set the angle of the second servo to 90 degrees
    delay(1000);  // Wait for 1 second
    bservo.write(90);
    
    savings += 0.05;

    delay(500);
  }
}



void loop() {
  // put your main code here, to run repeatedly:

  

  sort_penny();
  sort_nickel();
  sort_quarter();
  sort_dime();
  

  float potValue = analogRead(POT_PIN);
  
  // Map the potentiometer value to the desired range for the goal
  goal = map(potValue, 0, 1023, 0, 5);

  Serial.println(goal);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Savings: $");
  display.println(savings);
  
  display.setCursor(0, 10);
  display.print("Goal: $");
  display.println(goal);

  display.display();

  if (savings > goal) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println("Goal Reached!");
    display.display();
    dservo.write(180);
    while(true); // Stop further execution if goal is reached
    delay(5000);
    dservo.write(150);
  }
  
  delay(100); // Delay for stability
}
