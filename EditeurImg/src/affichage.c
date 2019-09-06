#include "sdl_infos.h"

int init_and_open_window(SDL_Window **window, SDL_Renderer **renderer, int w,
		int h) {
	if (0 != SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		return -1;
	}
	*window = SDL_CreateWindow("EDITEUR", 10, 20, WIDTH, HEIGTH, SDL_WINDOW_RESIZABLE);
	if (!window) {
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		return -1;
	}
	*renderer = SDL_CreateRenderer(*window, 0, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		return -1;
	}

	(*window)->poswin.x = 0;
	(*window)->poswin.y = 0;
	(*window)->poswin.w = WIDTH;
	(*window)->poswin.h = HEIGTH;

	if ((*window)->next == NULL)
	{
		(*window) ->next = *window;
	}if ((*window)->prev == NULL)
	{
		(*window) ->prev = *window;
	}

	return 0;
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer) {
	SDL_Surface *tmp = NULL;
	SDL_Texture *texture = NULL;
	tmp = SDL_LoadBMP(path);
	if (NULL == tmp) {
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		return NULL;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_FreeSurface(tmp);
	if (NULL == texture) {
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s",
				SDL_GetError());
		return NULL;
	}
	return texture;
}


SDL_Surface *loadImage2(const char path[], SDL_Renderer *renderer) {
	SDL_Surface *tmp = NULL;
	//SDL_Texture *texture = NULL;
	tmp = SDL_LoadBMP(path);
	if (NULL == tmp) {
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		return NULL;
	}
	
	return tmp;
}


void clean_sdl(SDL_Window *window, SDL_Renderer *renderer) {

  if (NULL != renderer)
    SDL_DestroyRenderer(renderer);
  if (NULL != window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

	

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename)
{
    SDL_Texture *ren_tex;
    SDL_Surface *surf;
    int st;
    int w;
    int h;
    int format;
    void *pixels;

    pixels  = NULL;
    surf    = NULL;
    ren_tex = NULL;
    format  = SDL_PIXELFORMAT_RGBA32;

    /* Get information about texture we want to save */
    st = SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    if (st != 0) {
        SDL_Log("Failed querying texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    ren_tex = SDL_CreateTexture(ren, format, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we 
     * can access
     */
    st = SDL_SetRenderTarget(ren, ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);

    st = SDL_RenderCopy(ren, tex, NULL, NULL);
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        goto cleanup;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        goto cleanup;
    }

    st = SDL_RenderReadPixels(ren, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        goto cleanup;
    }

    

    /* Save result to an image */
    st = SDL_SaveBMP(surf, filename);
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Log("Saved texture as BMP to \"%s\"\n", filename);

cleanup:
    SDL_FreeSurface(surf);
    free(pixels);
    SDL_DestroyTexture(ren_tex);
}


void sauvegarde (SDL_Surface* surf,const char* name){
    if(SDL_SaveBMP(surf,name)!=0)
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
}
