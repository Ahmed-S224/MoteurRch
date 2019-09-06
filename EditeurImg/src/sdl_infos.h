/*
 * sdl_infos.c
 *
 *  Created on: 23 mars 2019
 *      Author: yallaboy224
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h>
#include <dirent.h>

#define TAILLE_MAX 512
#define WIDTH 1000
#define HEIGTH 750

struct SDL_Window {
	const void *magic;
	Uint32 id;
	char *title;
	SDL_Surface *icon;
	int x, y;
	int w, h;
	SDL_Rect poswin;

	SDL_Window *prev;
	SDL_Window *next;
};

void read_cmd(int* argc,char*** argv);
void chemin();


int init_and_open_window(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
void clean_sdl(SDL_Window *window, SDL_Renderer *renderer);
int runForever(SDL_Window *window, SDL_Renderer *renderer, char path[]);
void selection(SDL_Window * pWindow, SDL_Surface * image, SDL_Rect fonte, SDL_Renderer * renderer);
void surfaceEnRenderer(SDL_Surface *surface, SDL_Renderer *pRenderer);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
SDL_Surface *loadImage2(const char path[], SDL_Renderer *renderer);
int max(int a, int b);
void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename);
void sauvegarde (SDL_Surface* surf,const char* name);
SDL_Surface *copieSurfaceEntiere (SDL_Surface *src);
SDL_Surface *copieSurfacePartielle(SDL_Rect rectsrc, SDL_Surface *src);
SDL_Surface* colleSurface(SDL_Surface *source, SDL_Surface *destination, SDL_Rect rectsource, SDL_Rect rectdestination);
void changePixel(SDL_Surface *src,int w,int h,int r, int g,int b,int a);
SDL_Surface *coupeSurfaceEntiere ();
SDL_Surface *coupeSurfacePartielle(SDL_Rect rectsrc, SDL_Surface *src);
void dessineRectSelection(SDL_Renderer* pRenderer,int posX, int posY, int width, int length);
void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);
SDL_Surface* Ajout_Sous(SDL_Surface *surface, int quantR, int quantB, int quantV);
int *luminosite(SDL_Window *win, SDL_Renderer *ren, SDL_Surface *s);
SDL_Surface *negatif(SDL_Surface *s);
SDL_Surface* niveauxDeGris(SDL_Surface* surface);
SDL_Surface *noir_blanc(SDL_Surface *s);
void ligneHorizontale(SDL_Renderer* renderer,int x, int y, int w);
void ligneVerticale(SDL_Renderer* renderer,int x, int y, int h);
void rectangle(SDL_Renderer* renderer,int x, int y, int w,int h);
void decoupage(SDL_Renderer* renderer, SDL_Texture* src,SDL_Rect rectsrc);