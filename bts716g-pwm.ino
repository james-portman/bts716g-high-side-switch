// d1 mini

// todo: diagnostic
// normal status is high on diag pin
//
// "open load" detection in off state - will know if disconnected or dead wire
//   - with channel turned off, open load/disconnected should cause low on diag/status
//   - with channel turned on we won't be able to tell - it will probably look OK - need to do diag on startup before turning channels on
//   - DO connect ground to arduino, and only use analog reads - digital never sees high
//   - in practice this swaps from 0-3 (open circuit) to more with something connected (30/40+), prob needs an amp
//


//
// thermal shutdown in on state
//   - with channel turned on it will go low
//   - with channel turned off it can't tell

int outputPin1 = D0; // chip 3 (chan 1)
int outputPin2 = D2; // chip 5 (chan 2)
int inputPin1 = A0; // chip 4 (diag 1&2)

int highThreshold = 5;

int turnOnTestMs = 100;
int turnOnTestDC = 1;

void checkOpenDrain() {
  int in;
  
  // check for broken wires/disconnected - could refuse to turn it on and wait for a reset from user?
  digitalWrite(outputPin1, LOW);
  digitalWrite(outputPin2, LOW);
  delay(500);

  in = analogRead(inputPin1);
  Serial.println(in);
  if (in >= highThreshold) {
    Serial.println("1 & 2 are connected");
    return;
  }

  // decide between the 2 pins
  bool pin1 = false;
  bool pin2 = false;


  analogWrite(outputPin1, turnOnTestDC);
  digitalWrite(outputPin2, LOW);
  delay(turnOnTestMs);
  in = analogRead(inputPin1);
  digitalWrite(outputPin1, LOW);
  if (in >= highThreshold) {
    Serial.println("pin 2 must be connected");
    pin2 = true;
  }

  digitalWrite(outputPin1, LOW);
  analogWrite(outputPin2, turnOnTestDC);
  delay(turnOnTestMs);
  in = analogRead(inputPin1);
  digitalWrite(outputPin2, LOW);
  if (in >= highThreshold) {
    Serial.println("pin 1 must be connected");
    pin1 = false;
  }


}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outputPin1, OUTPUT);
  digitalWrite(outputPin1, LOW);
  pinMode(outputPin2, OUTPUT);
  digitalWrite(outputPin2, LOW);
  pinMode(inputPin1, INPUT);

  analogWriteFreq(200);
  analogWriteRange(100);
  Serial.begin(9600);
  Serial.println("hi");
  
}

void rollPwm() {
  
  int in;
  Serial.println("setting output high");
  digitalWrite(LED_BUILTIN, LOW); // led backwards on these
  for (int i=0; i<=100; i++) {
      analogWrite(outputPin1, i);
      analogWrite(outputPin2, 100-i);
      delay(100);
      in = analogRead(inputPin1);
      Serial.println(in);
  }

  Serial.println("setting output low");
  digitalWrite(LED_BUILTIN, HIGH); // led backwards on these
  analogWrite(outputPin1, 0);
  analogWrite(outputPin2, 0);
  delay(100);
  in = analogRead(inputPin1);
  Serial.println(in);
  delay(1000);
  in = analogRead(inputPin1);
  Serial.println(in);
}

// the loop function runs over and over again forever
void loop() {
  checkOpenDrain();
  // rollPwm();
  delay(1000);

}
