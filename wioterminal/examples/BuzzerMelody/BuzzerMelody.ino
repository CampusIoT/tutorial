#define BUZZER_PIN WIO_BUZZER //Define buzzer pin 
 
int length = 15; //number of notes 
char notes[] = "ccggaagffeeddc "; //notes to play
int beats[] = { 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 2, 4 }; //time delays when notes are played
int tempo = 300; //tempo of the melody 
 
void setup() {
    pinMode(BUZZER_PIN, OUTPUT); //set buzzer pin as output
}
 
void loop() {
    for(int i = 0; i < length; i++) {
        if(notes[i] == ' ') {
            delay(beats[i] * tempo); //beats with no notes  
        } else {
            playNote(notes[i], beats[i] * tempo); //play the melody 
        }
        delay(tempo / 2); //delay between notes 
    }
 
}
 
//Play buzzer tone 
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(BUZZER_PIN, HIGH); //set buzzer pin to HIGH
        delayMicroseconds(tone); //first half of the time period
        digitalWrite(BUZZER_PIN, LOW); //set buzzer pin to HIGH
        delayMicroseconds(tone); //second half of the time period
    }
}

//Play the notes 
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; //note names 
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; //note frequencies 
 
    //play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}
