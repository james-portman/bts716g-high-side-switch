// d1 mini

int outputPin = D0;
int outputPin2 = D1;
int inputPin = A0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  analogWriteFreq(200);
  analogWriteRange(100);
  Serial.begin(9600);
  Serial.println("hi");
}

// the loop function runs over and over again forever
void loop() {
  int in;
  Serial.println("setting output high");
  digitalWrite(LED_BUILTIN, LOW); // led backwards on these
  for (int i=0; i<=100; i++) {
      analogWrite(outputPin, i);
      analogWrite(outputPin2, 100-i);
      delay(100);
//      in = analogRead(inputPin);
//      Serial.println(in);
  }

  Serial.println("setting output low");
  digitalWrite(LED_BUILTIN, HIGH); // led backwards on these
  analogWrite(outputPin, 0);
  analogWrite(outputPin2, 0);
//  delay(100);
//  in = analogRead(inputPin);
//  Serial.println(in);
  delay(2000);
//  in = analogRead(inputPin);
//  Serial.println(in);
}
