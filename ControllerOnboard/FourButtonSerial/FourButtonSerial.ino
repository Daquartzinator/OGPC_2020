
// constants won't change. They're used here to set pin numbers:
const int button1 = 2;// the number of the pushbutton pin
const int button2 = 4;
const int button3 = 7;
const int button4 = 8;

// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status
int button3State = 0;         // variable for reading the pushbutton status
int button4State = 0;         // variable for reading the pushbutton status

void setup() {

  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  
}

void loop() {
  // read the state of the pushbutton value:
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (button1State == HIGH) 
    {
      Serial.print("1\n");
    }
  if (button2State == HIGH) 
    {
      Serial.print("2\n");
    }
  if (button3State == HIGH) 
    {
      Serial.print("3\n");
    }
  if (button4State == HIGH) 
    {
      Serial.print("4\n");
    }
}
