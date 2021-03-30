const int inputPin = A3; //establish pin 3 (pin 2 of the DIP) as the analog input
const int outputPin = 1; //establish pin 1 (pin 6 of the DIP) as the output
unsigned int sampleIn = 0; //Stores the sample from the ADC

void setup() {
  pinMode (inputPin, INPUT);
  pinMode (outputPin, OUTPUT);
}

void loop() {
  sampleIn = analogRead(inputPin); //sample the input
  if (sampleIn > 521)
      {
        digitalWrite(outputPin, HIGH);
      }
  if (sampleIn < 503)
      {
        digitalWrite(outputPin, LOW);
      }
}

