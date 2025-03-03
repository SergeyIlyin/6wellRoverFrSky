#include "Player.h"

Player::Player()
{
}
void Player::LostSignal()
{
    Serial.print("\tPlay LostSignal");
    int melody[] = {NOTE_C6, 8, NOTE_C6, 8};
    playMusic(100, sizeof(melody), melody);
}

void Player::PowerOn()
{
    Serial.print("\tPlay PowerOn");
    int melody[] = {NOTE_C4, 4, NOTE_C5, 4};
    playMusic(120, sizeof(melody), melody);
}

void Player::PlayDisam()
{
    Serial.print("\tPlay Disarm");
    int melody[] = {NOTE_A4, 8, NOTE_E4, 8};
    playMusic(144, sizeof(melody), melody);
}

void Player::PlayArm()
{
    Serial.print("\tPlay Arm");
    int melody[] = {NOTE_E4, 8, NOTE_A4, 8};
    playMusic(144, sizeof(melody), melody);
}

void Player::playMusic(int tempo, int size, int melody[])
{
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
}