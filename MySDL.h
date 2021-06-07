#pragma once
#include <SDL.h>
#include <ctime>
#include "MyMaps.h"
#include "Music.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
using namespace std;

bool init();

bool loadMedia();

void close();

//������������ ���� �������
enum KeyPressSurfaces 
{
	G_TEXTURE_SURFACE_VOID,
	G_TEXTURE_SURFACE_BRICK,
	G_TEXTURE_SURFACE_HURT,
	G_TEXTURE_SURFACE_WALL,
	G_TEXTURE_SURFACE_SPIDERPUP,
	G_TEXTURE_SURFACE_PINKPINGUIN,
	G_TEXTURE_SURFACE_GREENPINGUIN,
	G_TEXTURE_SURFACE_TOTAL
};

//������������ ����������
enum PlayerOnMap
{
	PinkPinguin = 5,
	GreenPinguin = 6
};

SDL_Renderer* ren;

SDL_Surface* gTextureSurfaces[G_TEXTURE_SURFACE_TOTAL];

SDL_Surface* loadSurface(string path);
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gCurrentSurfacePinkPiguin = NULL;
SDL_Surface* gCurrentSurfaceGreenPiguin = NULL;
SDL_Surface* gSurfaceVoidForPinguin = NULL;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gTexShow = NULL;


//������� ������������� SDL
bool init()
{
	bool success = true;
	ren = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << SDL_GetError();
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Binary Land",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << SDL_GetError();
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
			loadmediaMusic();
			//SDL_Delay(2000);
		}
	}
	return success;
}

SDL_Surface* loadSurface(string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << SDL_GetError();
	}
	return loadedSurface;
}

//������� �������� ����������� �� ������
bool loadMedia()
{
	bool success = true;
	gTextureSurfaces[G_TEXTURE_SURFACE_VOID] = loadSurface("pics/Void_0.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_VOID] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_BRICK] = loadSurface("pics/Brick_1.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_BRICK] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_HURT] = loadSurface("pics/Hurt_2.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_HURT] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_WALL] = loadSurface("pics/Wall_3.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_WALL] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_SPIDERPUP] = loadSurface("pics/Spider_pup_4.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_SPIDERPUP] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_PINKPINGUIN] = loadSurface("pics/Pink_pinguin_5.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_PINKPINGUIN] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	gTextureSurfaces[G_TEXTURE_SURFACE_GREENPINGUIN] = loadSurface("pics/Green_pinguin_6.bmp");

	if (gTextureSurfaces[G_TEXTURE_SURFACE_GREENPINGUIN] == NULL)
	{
		cout << SDL_GetError();
		success = false;
	}
	return success;
}

int DrawMap()
{
	int DestX = (SCREEN_WIDTH / 2) - 272;
	int DestY = (SCREEN_HEIGHT / 2) - 256;

	SDL_Rect DestR{ DestX, DestY, 0, 0 };

	while (currentMap < CountMaps)
	{
		for (int i = currentMap; i < CountMaps;)
		{
			for (int x = 0; x < SizeHeight; x++)
			{
				for (int y = 0; y < SizeWidth; y++)
				{
					//������ �����
					if (MapsCounter[i][x][y] == 0)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� ������� �������
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_BRICK)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_BRICK];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� ������
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_HURT)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_HURT];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� ���������� ����
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_WALL)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_WALL];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� �������
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_SPIDERPUP)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_SPIDERPUP];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� ������� ��������
					if (MapsCounter[i][x][y] == PinkPinguin)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//�������� ������� ��������
					if (MapsCounter[i][x][y] == GreenPinguin)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
				}
				DestR.x = (SCREEN_WIDTH / 2) - 272;
				DestR.y += 32;
			}
			return currentMap;
		}
	}
}

int& pointerOnMap = currentMap;

void RandomMusic()//��������� ������ �� ���� ���������
{
	srand(time(0));
	int counter = rand() % 2;
	if (counter == 0)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//������ ���� ������
			Mix_PlayMusic(FirstMusic, -1);
		}
		else if (Mix_PlayingMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
	if (counter == 1)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//������ ���� ������
			Mix_PlayMusic(SecondMusic, -1);
		}
		else if (Mix_PlayingMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
	
}

//������������ ������ ����� ������ ������
void CongratulationsMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_PlayMusic(Congratulations, 0);
	}
	else if (Mix_PlayingMusic() == 0)
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

//�������� ���������� �� ������ ����� ������ �� ������� ��������(�� ��� �� �����������)
void TeleportLeftAfterTakingHeart(int& PinkY, int& PinkX, int& GreenY, int& GreenX, SDL_Rect& DstPinkPinguin, SDL_Rect& DstGreenPinguin)
{
	if (MapsCounter[pointerOnMap][PinkY][PinkX - 1] == 2 && MapsCounter[pointerOnMap][GreenY][GreenX + 1] == 2)
	{
		CongratulationsMusic();
		SDL_Delay(5000);
		pointerOnMap++;

		PinkX = 7;
		PinkY = 10;

		GreenX = 9;
		GreenY = 10;

		DstPinkPinguin.y += 288;
		DstGreenPinguin.y += 288;
	}
}

//�������� ���������� �� ������ ����� ������ �� �������� ��������
void TeleportRightAfterTakingHeart(int& PinkY, int& PinkX, int& GreenY, int& GreenX, SDL_Rect& DstPinkPinguin, SDL_Rect& DstGreenPinguin)
{
	if (MapsCounter[pointerOnMap][PinkY][PinkX + 1] == 2 && MapsCounter[pointerOnMap][GreenY][GreenX - 1] == 2)
	{
		CongratulationsMusic();
		SDL_Delay(5000);
		pointerOnMap++;

		PinkX = 7;
		PinkY = 10;

		GreenX = 9;
		GreenY = 10;

		DstPinkPinguin.y += 288;
		DstGreenPinguin.y += 288;
	}
}

//���������� ���������
//��������� ������ ������� � ���� ���, ����� ���� ��������� :-)
void CharacterMovement()
{
	//������� ���� �����
	bool quit = false;

	SDL_Event e;//���������� �������

	//���������� �������������� ��������� �������� ��������
	int dstPinkPinguinX = (SCREEN_WIDTH / 2) - 48;
	int dstPinkPinguinY = (SCREEN_HEIGHT / 2) + 64;
	SDL_Rect DstPinkPinguin{ dstPinkPinguinX, dstPinkPinguinY, 0, 0 };

	//���������� �������������� ��������� ������� ��������
	int dstGreenPinguinX = (SCREEN_WIDTH / 2) + 16;
	int dstGreenPinguinY = (SCREEN_HEIGHT / 2) + 64;
	SDL_Rect DstGreenPinguin{ dstGreenPinguinX, dstGreenPinguinY, 0, 0 };

	//���������� ��������������� ������� ���������� �������� ��������
	int dstVoidPinkPinguinX = dstPinkPinguinX;
	int dstVoidPinkPinguinY = dstPinkPinguinY;
	SDL_Rect DstVoidPinkPinguin{ dstVoidPinkPinguinX, dstVoidPinkPinguinY, 0, 0 };

	//���������� ��������������� ������� ���������� ������� ��������
	int dstVoidGreenPinguinX = dstGreenPinguinX;
	int dstVoidGreenPinguinY = dstGreenPinguinY;
	SDL_Rect DstVoidGreenPinguin{ dstVoidGreenPinguinX, dstVoidGreenPinguinY, 0, 0 };

	//���������� ������� ��������
	int PinkX = 7;
	int PinkY = 10;

	//���������� ������� ���������
	int GreenX = 9;
	int GreenY = 10;

	gCurrentSurfacePinkPiguin = gTextureSurfaces[G_TEXTURE_SURFACE_PINKPINGUIN];
	gCurrentSurfaceGreenPiguin = gTextureSurfaces[G_TEXTURE_SURFACE_GREENPINGUIN];
	gSurfaceVoidForPinguin = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];

	int& pointerOnMap = currentMap;

	//�������� ���� ����
	while (!quit)
	{
		RandomMusic();//������� ��������� ������ � ����
		TheOtherMapAfterTakingHeart();//������ ����� ����� ������ ������
		DrawMap();//��������� �����

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)//�������� �� ������� �������� � ������ ������� ����
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)//�������� �� ������� ������ �� ���������� 
			{
				switch (e.key.keysym.sym)
				{

				case SDLK_UP://�������� �� ������� ������� ����

					if (MapsCounter[pointerOnMap][PinkY - 1][PinkX] != 1 && MapsCounter[pointerOnMap][PinkY - 1][PinkX] != 3)// �������� �� ����� 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//������� ��� �������� �������� ���������� ���������
						MapsCounter[pointerOnMap][PinkY - 1][PinkX] = 5;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						PinkY -= 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.y -= 32;
					}
					if (MapsCounter[pointerOnMap][GreenY - 1][GreenX] != 1 && MapsCounter[pointerOnMap][GreenY - 1][GreenX] != 3)// �������� �� ����� 
					{
						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//������� ��� ������� �������� ���������� ���������
						MapsCounter[pointerOnMap][GreenY - 1][GreenX] = 6;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						GreenY -= 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.y -= 32;
					}
					break;

				case SDLK_LEFT://�������� �� ������� ������� ����

					if (MapsCounter[pointerOnMap][PinkY][PinkX - 1] != 1 && MapsCounter[pointerOnMap][PinkY][PinkX - 1] != 3)// �������� �� ����� 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//������� ��� �������� �������� ���������� ���������
						MapsCounter[pointerOnMap][PinkY][PinkX - 1] = 5;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						PinkX -= 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.x -= 32;
					}
					if (MapsCounter[pointerOnMap][GreenY][GreenX + 1] != 1 && MapsCounter[pointerOnMap][GreenY][GreenX + 1] != 3)// �������� �� ����� 
					{

						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;
						MapsCounter[pointerOnMap][GreenY][GreenX + 1] = 6;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						GreenX += 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.x += 32;
					}
					TeleportLeftAfterTakingHeart(PinkY, PinkX, GreenY, GreenX, DstPinkPinguin, DstGreenPinguin);
					break;

				case SDLK_RIGHT://�������� �� ������� ������� ����

					if (MapsCounter[pointerOnMap][PinkY][PinkX + 1] != 1 && MapsCounter[pointerOnMap][PinkY][PinkX + 1] != 3)// �������� �� ����� 
					{

						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//������� ��� �������� �������� ���������� ���������
						MapsCounter[pointerOnMap][PinkY][PinkX + 1] = 5;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						PinkX += 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.x += 32;
					}
					if (MapsCounter[pointerOnMap][GreenY][GreenX - 1] != 1 && MapsCounter[pointerOnMap][GreenY][GreenX - 1] != 3)// �������� �� ����� 
					{

						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//������� ��� �������� �������� ���������� ���������
						MapsCounter[pointerOnMap][GreenY][GreenX - 1] = 6;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						GreenX -= 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.x -= 32;
						
					}
					TeleportRightAfterTakingHeart(PinkY, PinkX, GreenY, GreenX, DstPinkPinguin, DstGreenPinguin);//�������� ���������� � ������
					break;

				case SDLK_DOWN://�������� �� ������� ������� ����
					if (MapsCounter[pointerOnMap][PinkY + 1][PinkX] != 1 && MapsCounter[pointerOnMap][PinkY + 1][PinkX] != 3)// �������� �� ����� 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//������� ��� �������� �������� ���������� ���������
						MapsCounter[pointerOnMap][PinkY + 1][PinkX] = 5;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						PinkY += 1;

						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.y += 32;
					}
					if (MapsCounter[pointerOnMap][GreenY + 1][GreenX] != 1 && MapsCounter[pointerOnMap][GreenY + 1][GreenX] != 3)// �������� �� ����� 
					{
						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						MapsCounter[pointerOnMap][GreenY + 1][GreenX] = 6;//�������� ��������� � ������� � ����������� ��������� �� ����� �����
						GreenY += 1;//�������� ��������� ��������� � �������
						
						//���������� ������ ������� ����������� ������� ��������� ���������
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.y += 32;
					}
					break;
				}
			}
		}
		
		SDL_BlitSurface(gSurfaceVoidForPinguin, NULL, gScreenSurface, &DstVoidPinkPinguin);//������������ �������� ���� ���������
		SDL_BlitSurface(gCurrentSurfacePinkPiguin, NULL, gScreenSurface, &DstPinkPinguin);//��������� ��������� �� ������

		SDL_BlitSurface(gSurfaceVoidForPinguin, NULL, gScreenSurface, &DstVoidGreenPinguin);//������������ �������� ���� ���������
		SDL_BlitSurface(gCurrentSurfaceGreenPiguin, NULL, gScreenSurface, &DstGreenPinguin);//��������� ��������� �� ������

		//���������� ������
		SDL_UpdateWindowSurface(gWindow);

		//�������� �� ��������
		//SDL_Delay(1300);
	}
}

void Game()//������� ������� ����
{
	if (init() != 1)
	{
		cout << SDL_GetError();
	}
	else
	{
		if (loadMedia() != 1)
		{
			cout << SDL_GetError();
		}
		else
		{
			CharacterMovement();
		}
	}
	close();
}

void close()//������� �������� ���� � ������ � ������ SDL
{
	//������� ���������
	SDL_FreeSurface(gTexShow);
	gTexShow = NULL;

	//������� ����
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	Mix_FreeMusic(FirstMusic);
	Mix_FreeMusic(SecondMusic);
	Mix_FreeMusic(Congratulations);

	//������� �� ���������� SDL
	Mix_Quit();
	SDL_Quit();

}
