#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//The music
Mix_Music* FirstMusic = Mix_LoadMUS("Music/FirstMusic.wav");
Mix_Music* SecondMusic = NULL;
Mix_Music* Congratulations = NULL;

bool loadmediaMusic()
{  bool success = true;
    //Load music
    FirstMusic = Mix_LoadMUS("Music/FirstMusic.wav");
    if (FirstMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    SecondMusic = Mix_LoadMUS("Music/SecondMusic.wav");
    if (SecondMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    Congratulations = Mix_LoadMUS("Music/Congratulations.wav");
    if (Congratulations == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}