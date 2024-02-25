#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#define S1 7
#define S2 6
#define S3 5
#define S4 4
#define S5 3
#define ledPin 2 // Pin for the LED

int vote1 = 0;
int vote2 = 0;
int vote3 = 0;
int vote4 = 0;
unsigned long lastVoteTime = 0;
const unsigned long voteDelay = 6000; // 3 seconds
bool electionRunning = true; // Variable to track election state (running or paused)

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output

  lcd.begin(16, 2);
  lcd.print(" Electronic ");
  lcd.setCursor(0, 1);
  lcd.print(" Voting Machine ");
  delay(1500);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, HIGH);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("A");
  lcd.setCursor(5, 0);
  lcd.print("B");
  lcd.setCursor(9, 0);
  lcd.print("C");
  lcd.setCursor(13, 0);
  lcd.print("D");
}

void loop() {
  lcd.setCursor(1, 0);
  lcd.print("A");
  lcd.setCursor(1, 1);
  lcd.print(vote1);
  lcd.setCursor(5, 0);
  lcd.print("B");
  lcd.setCursor(5, 1);
  lcd.print(vote2);
  lcd.setCursor(9, 0);
  lcd.print("C");
  lcd.setCursor(9, 1);
  lcd.print(vote3);
  lcd.setCursor(13, 0);
  lcd.print("D");
  lcd.setCursor(13, 1);
  lcd.print(vote4);

  // Check if the election is running before allowing votes to be cast
  if (electionRunning) {
    if (digitalRead(S1) == 0 && millis() - lastVoteTime >= voteDelay) {
      vote1++;
      lastVoteTime = millis();
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      lcd.clear();
      lcd.print("Thanks");
      delay(2000);
      lcd.clear();
    }
    if (digitalRead(S2) == 0 && millis() - lastVoteTime >= voteDelay) {
      vote2++;
      lastVoteTime = millis();
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      lcd.clear();
      lcd.print("Thanks");
      delay(2000);
      lcd.clear();
    }
    if (digitalRead(S3) == 0 && millis() - lastVoteTime >= voteDelay) {
      vote3++;
      lastVoteTime = millis();
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      lcd.clear();
      lcd.print("Thanks");
      delay(2000);
      lcd.clear();
    }
  }

  // Check the 4th pushbutton for pausing and continuing the election
  if (digitalRead(S4) == 0) {
    if (electionRunning) {
      electionRunning = false; // Pause the election
      lcd.clear();
      lcd.print("Election Paused");
      delay(2000);
      lcd.clear();
    } else {
      electionRunning = true; // Continue the election
      lcd.clear();
      lcd.print("Election Continued");
      delay(2000);
      lcd.clear();
    }
  }

  // Check the 5th pushbutton for declaring the winner
  if (digitalRead(S5) == 0) {
    if (electionRunning) {
      int totalVotes = vote1 + vote2 + vote3 + vote4;
      if (totalVotes) {
        // Determine the winner as before
        if (vote1 > vote2 && vote1 > vote3 && vote1 > vote4) {
          lcd.clear();
          lcd.print("A is Winner");
          delay(3000);
          lcd.clear();
        } else if (vote2 > vote1 && vote2 > vote3 && vote2 > vote4) {
          lcd.clear();
          lcd.print("B is Winner");
          delay(3000);
          lcd.clear();
        } else if (vote3 > vote1 && vote3 > vote2 && vote3 > vote4) {
          lcd.clear();
          lcd.print("C is Winner");
          delay(3000);
          lcd.clear();
        } else if (vote4 > vote1 && vote4 > vote2 && vote4 > vote3) {
          lcd.clear();
          lcd.print("D is Winner");
          delay(3000);
          lcd.clear();
        } else {
          lcd.clear();
          lcd.print("Tie Up Or");
          lcd.setCursor(0, 1);
          lcd.print("No Result");
          delay(3000);
          lcd.clear();
        }
      } else {
        lcd.clear();
        lcd.print("No Voting....");
        delay(3000);
        lcd.clear();
      }
      vote1 = 0;
      vote2 = 0;
      vote3 = 0;
      vote4 = 0;
      totalVotes = 0;
    } else {
      lcd.clear();
      lcd.print("Election Paused");
      delay(2000);
      lcd.clear();
    }
  }
}
