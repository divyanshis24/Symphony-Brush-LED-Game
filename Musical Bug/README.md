# Music Arena

## Introduction

The aim of the Music Arena project is to create an interactive platform for students to learn about musical notes. The project involves two participants sitting on opposite sides of the arena. One participant starts a musical note using a button, and the opponent must guess the starting note. This engaging method helps students recognize and understand musical notes in a fun and competitive environment.

## Construction

The Music Arena is built using the following components:

1. **Arduino Uno**: The core of our setup, the Arduino Uno microcontroller, is programmed to control the buzzer and read inputs from the infrared (IR) sensors.
2. **Buzzer**: The buzzer is responsible for playing the musical notes. It is connected to the Arduino Uno and produces sound when activated.
3. **IR Sensors**: Multiple IR sensors are placed in the arena, each corresponding to a specific musical note. When an IR sensor is activated, it signals the Arduino Uno to play the associated note through the buzzer.
4. **Buttons**: Each participant has a button that starts the game. When pressed, the button triggers the Arduino Uno to play a random note using the buzzer. The opponent then listens to the note and attempts to guess it.
5. **LEDs**: Each participant has three lives indicated by three LEDs. On a wrong guess, one LED turns off. The game continues until all LEDs are off for a participant.
6. **Bug Eyes**: These are additional features where one eye functions as a power-off button and the other as a trial tone button.

## Detailed Explanation

### Setup

The Music Arena consists of a circular arrangement where participants sit facing each other. The Arduino Uno and the buzzer are centrally located. The IR sensors are positioned around the participants, each one mapped to a different musical note.

### Operation

1. **Start the Game**: When the game begins, one participant presses their button, which sends a signal to the Arduino Uno.
2. **Play a Note**: The Arduino randomly activates one of the IR sensors. The active IR sensor determines the note to be played by the buzzer. The buzzer plays the note, and the opponent listens carefully.
3. **Guessing Mechanism**: The opponent listens to the note played by the buzzer and tries to identify it. They then press their own button and announce their guess.
4. **Lives Indicator**: Each participant starts with three lives, represented by three LEDs. If a participant guesses incorrectly, one of their LEDs turns off. The game continues until a participant loses all three lives.
5. **Bug Eyes**: The eyes of the bugs serve special functions. One eye can be pressed to power off the system, and the other can be used to play a trial tone for practice.

### Learning Outcome

This interactive setup helps students familiarize themselves with different musical notes through a hands-on and engaging method. The competitive aspect also adds an element of excitement, encouraging participants to learn more effectively.

## Conclusion

The Music Arena project successfully combines technology and education, providing a unique way for students to learn and enjoy music. We hope this platform will make learning musical notes a fun and interactive experience for everyone.
