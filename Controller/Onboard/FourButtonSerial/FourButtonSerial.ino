
// constants won't change. They're used here to set pin numbers:
const int button1 = 2;// the number of the pushbutton pin
const int button2 = 4;
const int button3 = 7;
const int button4 = 8;

unsigned long timingCounter = 0;

// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status
int button3State = 0;         // variable for reading the pushbutton status
int button4State = 0;         // variable for reading the pushbutton status

bool canSend = true;

void setup() {

  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  timingCounter = millis();
  
}

void loop() {

  // read the state of the pushbutton value:
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);

  //check time elapsed between each reading
  if(millis() - timingCounter >= 10)
  {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (button1State == HIGH && canSend == true) 
    {
      Serial.print("1\n");
      canSend = false;
    }
  if (button2State == HIGH && canSend == true) 
    {
      Serial.print("2\n");
      canSend = false;
    }
  if (button3State == HIGH && canSend == true) 
    {
      Serial.print("3\n");
      canSend = false;
    }
  if (button4State == HIGH && canSend == true) 
    {
      Serial.print("4\n");
      canSend = false;
    }

    //reset counter to current time
    timingCounter = millis();
    
  }
  canSend = true;
 
}
