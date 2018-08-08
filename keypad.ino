const int inputs=4,outputs=4; // this is for a 4x4 keypad

int inputPins[inputs] = {5,4,3,2} ; // most examples of keypad use will use these pins 
int outputPins[outputs] = {9,8,7,6}; 

void setup() {
  // put your setup code here, to run once:

  // set pins as outputs and inputs accordingly
  for(int inp=0; inp<inputs ; inp++) pinMode( inputPins[inp],INPUT_PULLUP);
  for(int outp=0; outp<outputs; outp++) pinMode( outputPins[outp], OUTPUT);    
  Serial.begin(9600);   
}

char hexaKeys[4][4] = { // maps row and col to key
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

int pressed=0; // used to wait for a key to be released

void loop() {
  // put your main code here, to run repeatedly:
    
  if(!pressed) { 
     for(int row=0; row<4; row++) digitalWrite(outputPins[row],HIGH); // set all rows to HIGH
     for(int row=0; row<4; row++) {
       digitalWrite(outputPins[row],LOW); // set to LOW the row we are going to check
       for(int col=0; col<4; col++) {
         if(digitalRead(inputPins[col])==LOW) { // a key was pressed
          Serial.println( hexaKeys[row][col]); // the key pressed is determined by the ROW and the COLUMN that are LOW
          pressed=1;           
          break;  // skip the for, since a key was detected       
       }
      }    
      if(pressed) break;   // skip the for, a key was detected
      digitalWrite(outputPins[row],HIGH); // set the ROW back to HIGH
     }
  } 
  else   { // check if the key was released
    for(int row=0; row<4; row++) digitalWrite(outputPins[row],LOW); // set all rows to LOW in the case 2 or more keys are pressed at the same time          
    pressed=0;
    for(int col=0; col<4; col++) // checks if one or more keys are pressed
      if(digitalRead(inputPins[col])==LOW) { // still holding the key
        pressed=1;
        break;
      }
  }      

  delay(100);
  
  

}
