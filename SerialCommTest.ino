void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
}

char incoming = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    while(Serial.available()) {
      incoming = Serial.read();
    }
    Serial.print("ACK: ");
    Serial.println(incoming);
  }
    
}
