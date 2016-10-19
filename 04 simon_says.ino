#define MAXSEQ 20
#define note_len 200000
#define play_c 3830
#define play_d 3400
#define play_e 3038

int rand_array[MAXSEQ];
int ledPin1 = 10;
int ledPin2 = 11;
int ledPin3 = 12;
int inPin1 = 7;
int inPin2 = 8;
int inPin3 = 9;
int score = 1;
int speakerOut = 13;

/* DISPLAY ORDER: a,b,c,d,e,f,g */
int segPin[7]={0,1,2,3,4,5,6};

bool segNum[10][7]={
 {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0},
 {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1},
 {0,1,1,0,0,1,1}, {1,0,1,1,0,1,1},
 {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0},
 {1,1,1,1,1,1,1}, {1,1,1,1,0,1,1},
 };
 
 void setup() {
   long val_rand = 0;
   pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
   pinMode(ledPin3, OUTPUT);
   pinMode(inPin1, INPUT);
   pinMode(inPin2, INPUT);
   pinMode(inPin3, INPUT);
   pinMode(speakerOut, OUTPUT);
   randomSeed(analogRead(0));
   for (int i=0; i<=MAXSEQ; i++){
     rand_array[i] = random (3);
   }
   for (int i=0; i<7; i++){
     pinMode(segPin[i], OUTPUT);
     digitalWrite(segPin[i], HIGH);
   }  
 }
 
 int readButtons()
 {
      int val1 = 0; int val2 = 0; int val3 = 0;
   do {
        val1 = digitalRead(inPin1); val2 = digitalRead(inPin2); val3 = digitalRead(inPin3);
      } while (val1 == HIGH && val2 == HIGH && val3 == HIGH);
if (val1==LOW){
  playTone(play_c);
  return 0;
} else if (val2==LOW) {
  playTone(play_d);
  return 1;
} else if (val3==LOW) {
  playTone(play_e);
  return 2;
}
 }
 
 void playSequence(int count)
 {
    for (int i=0; i<=count; i++){
      digitalWrite(ledPin1, LOW); digitalWrite(ledPin2, LOW); digitalWrite(ledPin3, LOW);
      delay (200);
switch (rand_array[i]) {
   case 0:
     digitalWrite(ledPin1, HIGH);
     playTone(play_c);
     break;
   case 1:
     digitalWrite(ledPin2, HIGH);
     playTone(play_d);
     break;
   case 2:
     digitalWrite(ledPin3, HIGH);
     playTone(play_e);
     break;
   }
    delay (200);
    }
    digitalWrite(ledPin1, LOW); digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
 }

int flashSuccess()
 {
/*   
  playTone(10000); 
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay (200);
  playTone(5000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay (200);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay (200);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);  
  delay (200);
*/
  delay(500);
 }

int flashFailure()
 {
  playTone(8000); 
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay (1000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay (1000);
 }

void playTone(int note) {
  long elapsed_time = 0;
  while (elapsed_time < note_len) {
     digitalWrite(speakerOut,HIGH);
     delayMicroseconds(note / 2);
     digitalWrite(speakerOut, LOW);
     delayMicroseconds(note / 2);
     elapsed_time += (note);
   }
}

void displayNum (int number) {
  if (number <= 9){
    for (int i=0; i<7; i++){
      if (segNum[number][i]){
        digitalWrite(segPin[i], LOW);
      } else {
        digitalWrite(segPin[i], HIGH);
      }
    }
  }
}
 
 void loop(){
   int input_key;
   int winning = true;
   int i=0;
   playSequence (score-1);
   
   while (winning && i<score){
     input_key = readButtons();
     if (input_key == rand_array[i]){
        i++;
        flashSuccess();        
      } else {
        winning = false;
        flashFailure();
      }
   }
   if (winning) {
   displayNum(score/3);  
   score++;
   }
 }
