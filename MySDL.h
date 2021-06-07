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

//перечисление всех текстур
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

//перечислеине персонажей
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


//функция инициализации SDL
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

//функция загрузки изображения из файлов
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
					//пустые блоки
					if (MapsCounter[i][x][y] == 0)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка внешние кирпичи
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_BRICK)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_BRICK];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка сердца
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_HURT)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_HURT];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка внутренней стен
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_WALL)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_WALL];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка паутины
					if (MapsCounter[i][x][y] == G_TEXTURE_SURFACE_SPIDERPUP)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_SPIDERPUP];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка розовго пингвина
					if (MapsCounter[i][x][y] == PinkPinguin)
					{
						gCurrentSurface = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];
						SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &DestR);
						DestR.x += 32;
					}
					//картинка зелёного пингвина
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

void RandomMusic()//случайная музыка из двух возможных
{
	srand(time(0));
	int counter = rand() % 2;
	if (counter == 0)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//начало игры музыки
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
			//начало игры музыки
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

//проигрывание музыки после взятия сердца
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

//телепорт персонажей на начало когда игпаем за зелёного пингвина(но это не реализовано)
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

//телепорт персонажей на начало когда игпаем за розового пингвина
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

//управление персонажа
//добавлены другие функции в этот код, чтобы было нормально :-)
void CharacterMovement()
{
	//главный флаг цикла
	bool quit = false;

	SDL_Event e;//переменная событий

	//коондинаты первоначальной отрисовки розового пингвина
	int dstPinkPinguinX = (SCREEN_WIDTH / 2) - 48;
	int dstPinkPinguinY = (SCREEN_HEIGHT / 2) + 64;
	SDL_Rect DstPinkPinguin{ dstPinkPinguinX, dstPinkPinguinY, 0, 0 };

	//коондинаты первоначальной отрисовки зелёного пингвина
	int dstGreenPinguinX = (SCREEN_WIDTH / 2) + 16;
	int dstGreenPinguinY = (SCREEN_HEIGHT / 2) + 64;
	SDL_Rect DstGreenPinguin{ dstGreenPinguinX, dstGreenPinguinY, 0, 0 };

	//коондинаты первоначального чёрного квадратика розового пингвина
	int dstVoidPinkPinguinX = dstPinkPinguinX;
	int dstVoidPinkPinguinY = dstPinkPinguinY;
	SDL_Rect DstVoidPinkPinguin{ dstVoidPinkPinguinX, dstVoidPinkPinguinY, 0, 0 };

	//коондинаты первоначального чёрного квадратика зелёного пингвина
	int dstVoidGreenPinguinX = dstGreenPinguinX;
	int dstVoidGreenPinguinY = dstGreenPinguinY;
	SDL_Rect DstVoidGreenPinguin{ dstVoidGreenPinguinX, dstVoidGreenPinguinY, 0, 0 };

	//координаты розовго пингвина
	int PinkX = 7;
	int PinkY = 10;

	//координаты зелёного пингивина
	int GreenX = 9;
	int GreenY = 10;

	gCurrentSurfacePinkPiguin = gTextureSurfaces[G_TEXTURE_SURFACE_PINKPINGUIN];
	gCurrentSurfaceGreenPiguin = gTextureSurfaces[G_TEXTURE_SURFACE_GREENPINGUIN];
	gSurfaceVoidForPinguin = gTextureSurfaces[G_TEXTURE_SURFACE_VOID];

	int& pointerOnMap = currentMap;

	//основной цикл игры
	while (!quit)
	{
		RandomMusic();//функция рандомной музыки в игре
		TheOtherMapAfterTakingHeart();//ссмена карты после взятия сердца
		DrawMap();//отрисовка карты

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)//проверка на нажатия крестика в правом верхнем углу
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)//вроверка на нажатие клавиш на клавиатуре 
			{
				switch (e.key.keysym.sym)
				{

				case SDLK_UP://проверка на нажатие клавиши вниз

					if (MapsCounter[pointerOnMap][PinkY - 1][PinkX] != 1 && MapsCounter[pointerOnMap][PinkY - 1][PinkX] != 3)// проверка на стены 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//прошлый ход розового пингвина становится коридором
						MapsCounter[pointerOnMap][PinkY - 1][PinkX] = 5;//смещение персонажа в массиве и записывание персонажа на новом месте
						PinkY -= 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.y -= 32;
					}
					if (MapsCounter[pointerOnMap][GreenY - 1][GreenX] != 1 && MapsCounter[pointerOnMap][GreenY - 1][GreenX] != 3)// проверка на стены 
					{
						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//прошлый ход зелёного пингвина становится коридором
						MapsCounter[pointerOnMap][GreenY - 1][GreenX] = 6;//смещение персонажа в массиве и записывание персонажа на новом месте
						GreenY -= 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.y -= 32;
					}
					break;

				case SDLK_LEFT://проверка на нажатие клавиши вниз

					if (MapsCounter[pointerOnMap][PinkY][PinkX - 1] != 1 && MapsCounter[pointerOnMap][PinkY][PinkX - 1] != 3)// проверка на стены 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//прошлый ход розового пингвина становится коридором
						MapsCounter[pointerOnMap][PinkY][PinkX - 1] = 5;//смещение персонажа в массиве и записывание персонажа на новом месте
						PinkX -= 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.x -= 32;
					}
					if (MapsCounter[pointerOnMap][GreenY][GreenX + 1] != 1 && MapsCounter[pointerOnMap][GreenY][GreenX + 1] != 3)// проверка на стены 
					{

						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;
						MapsCounter[pointerOnMap][GreenY][GreenX + 1] = 6;//смещение персонажа в массиве и записывание персонажа на новом месте
						GreenX += 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.x += 32;
					}
					TeleportLeftAfterTakingHeart(PinkY, PinkX, GreenY, GreenX, DstPinkPinguin, DstGreenPinguin);
					break;

				case SDLK_RIGHT://проверка на нажатие клавиши вниз

					if (MapsCounter[pointerOnMap][PinkY][PinkX + 1] != 1 && MapsCounter[pointerOnMap][PinkY][PinkX + 1] != 3)// проверка на стены 
					{

						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//прошлый ход розового пингвина становится коридором
						MapsCounter[pointerOnMap][PinkY][PinkX + 1] = 5;//смещение персонажа в массиве и записывание персонажа на новом месте
						PinkX += 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.x += 32;
					}
					if (MapsCounter[pointerOnMap][GreenY][GreenX - 1] != 1 && MapsCounter[pointerOnMap][GreenY][GreenX - 1] != 3)// проверка на стены 
					{

						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//прошлый ход розового пингвина становится коридором
						MapsCounter[pointerOnMap][GreenY][GreenX - 1] = 6;//смещение персонажа в массиве и записывание персонажа на новом месте
						GreenX -= 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.x -= 32;
						
					}
					TeleportRightAfterTakingHeart(PinkY, PinkX, GreenY, GreenX, DstPinkPinguin, DstGreenPinguin);//телефорт персонажей в начало
					break;

				case SDLK_DOWN://проверка на нажатие клавиши вниз
					if (MapsCounter[pointerOnMap][PinkY + 1][PinkX] != 1 && MapsCounter[pointerOnMap][PinkY + 1][PinkX] != 3)// проверка на стены 
					{
						MapsCounter[pointerOnMap][PinkY][PinkX] = 0;//прошлый ход розового пингвина становится коридором
						MapsCounter[pointerOnMap][PinkY + 1][PinkX] = 5;//смещение персонажа в массиве и записывание персонажа на новом месте
						PinkY += 1;

						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidPinkPinguin.x = DstPinkPinguin.x;
						DstVoidPinkPinguin.y = DstPinkPinguin.y;
						DstPinkPinguin.y += 32;
					}
					if (MapsCounter[pointerOnMap][GreenY + 1][GreenX] != 1 && MapsCounter[pointerOnMap][GreenY + 1][GreenX] != 3)// проверка на стены 
					{
						MapsCounter[pointerOnMap][GreenY][GreenX] = 0;//смещение персонажа в массиве и записывание персонажа на новом месте
						MapsCounter[pointerOnMap][GreenY + 1][GreenX] = 6;//смещение персонажа в массиве и записывание персонажа на новом месте
						GreenY += 1;//смещение координат персонажа в массиве
						
						//координаты кубика который закрышивает прошлое положеине персонажа
						DstVoidGreenPinguin.x = DstGreenPinguin.x;
						DstVoidGreenPinguin.y = DstGreenPinguin.y;
						DstGreenPinguin.y += 32;
					}
					break;
				}
			}
		}
		
		SDL_BlitSurface(gSurfaceVoidForPinguin, NULL, gScreenSurface, &DstVoidPinkPinguin);//закрышивание прошлого ходя персонажа
		SDL_BlitSurface(gCurrentSurfacePinkPiguin, NULL, gScreenSurface, &DstPinkPinguin);//рендеринг персонажа на экране

		SDL_BlitSurface(gSurfaceVoidForPinguin, NULL, gScreenSurface, &DstVoidGreenPinguin);//закрышивание прошлого ходя персонажа
		SDL_BlitSurface(gCurrentSurfaceGreenPiguin, NULL, gScreenSurface, &DstGreenPinguin);//рендеринг персонажа на экране

		//обновление экрана
		SDL_UpdateWindowSurface(gWindow);

		//задержка до закрытия
		//SDL_Delay(1300);
	}
}

void Game()//функция запуска игры
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

void close()//функция закрытия окна и музыки и самого SDL
{
	//снимает указатель
	SDL_FreeSurface(gTexShow);
	gTexShow = NULL;

	//Удаляет окно
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	Mix_FreeMusic(FirstMusic);
	Mix_FreeMusic(SecondMusic);
	Mix_FreeMusic(Congratulations);

	//выходит из подсистемы SDL
	Mix_Quit();
	SDL_Quit();

}
