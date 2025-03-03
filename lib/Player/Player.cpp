#include "Player.h"

Player::Player()
{
}

void Player::PlayDisam()
{
    int melody[] = {NOTE_C5, 4, NOTE_A4, 4, NOTE_A4, 4, REST, 4};
    playMusic(144, sizeof(melody), melody);
}

void Player::PlayArm()
{
    int melody[] = {NOTE_E5, 4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5, 8, NOTE_B4, 8};
    playMusic(144, sizeof(melody), melody);
}

void Player::playMusic(int tempo, int size, int melody[])
{
    Serial.print("Play Music");
    int notes = size / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;
    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
    {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0)
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0)
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(pin, melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(pin);
    }
    Serial.print(" END Music");
}