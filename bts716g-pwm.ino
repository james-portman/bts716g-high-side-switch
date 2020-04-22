// d1 mini

// todo: diagnostic
// normal status is high on diag pin
//
// "open load" detection in off state - will know if disconnected or dead wire
//   - with channel turned off, open load/disconnected should cause low on diag/status
//   - with channel turned on we won't be able to tell - it will probably look OK - need to do diag on startup before turning channels on
//
// thermal shutdown in on state
//   - with channel turned on it will go low
//   - with channel turned off it can't tell

int outputPin1 = D0;
int inputPin1 = D1;
int outputPin2 = D2;
int inputPin2 = D3;

void checkOpenDrain() {
  // check for broken wires/disconnected - could refuse to turn it on and wait for a reset from user?
  digitalWrite(outputPin1, LOW);
  digitalWrite(outputPin2, LOW);
  delay(500);
  in = digitalRead(inputPin1);
  if (in == LOW) {
    Serial.println("open drain (circuit?) on either 1 or 2");
  } else {
    Serial.println("Looks like 1 & 2 are connected");
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  analogWriteFreq(200);
  analogWriteRange(100);
  Serial.begin(9600);
  Serial.println("hi");

  checkOpenDrain();
  
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
