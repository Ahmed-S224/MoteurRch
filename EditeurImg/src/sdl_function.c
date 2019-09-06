/*
 * sdl_function.c
 *
 *  Created on: 23 mars 2019
 *      Author: yallaboy224
 */

# include "sdl_infos.h"



void selection(SDL_Window * pWindow, SDL_Surface * image, SDL_Rect fonte, SDL_Renderer * renderer)
{
    SDL_Event event;
    SDL_Texture *img;
    int clic=0;
    SDL_Surface * temp;
    SDL_Rect posClic, posDeplacement, posRect;
    
    int fullscreen =0;
    int quit = 0;
    int dec = 0;
    int copier = 0;
    int coller =0;
    while (quit!=1) // Récupération des actions de l'utilisateur
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_KEYUP: // Relâchement d'une touche
            if ( event.key.keysym.sym == SDLK_f ) // Touche f
            {
                // Alterne du mode plein écran au mode fenêtré
                if ( fullscreen == 0 )
                {
                    fullscreen = 1;
                    SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN);
                }
                else if ( fullscreen == 1 )
                {
                    fullscreen = 0;
                    SDL_SetWindowFullscreen(pWindow,0);
                }
            }
            if ( event.key.keysym.sym == SDLK_q ) 
            {
                quit=1;
            }
            if ( event.key.keysym.sym == SDLK_s ) 
            {
                sauvegarde(temp,"tmp.bmp");
            }
            if ( event.key.keysym.sym == SDLK_d ) 
            {
                dec=1;
            }
            if ( event.key.keysym.sym == SDLK_c ) 
            {
                copier=1;
            }
            if ( event.key.keysym.sym == SDLK_p ) 
            {
                coller=1;
            }
            break;

        case SDL_MOUSEBUTTONDOWN: // quand le clic est enfonce
//            printf("%d %d\n", fonte.x, fonte.y);
            if (event.button.button==SDL_BUTTON_LEFT){
                posClic.x=event.button.x;
                posClic.y=event.button.y;
                clic = 1;
                //rectangle(renderer,posClic.x,posClic.y,0,0);
            }
            if (event.button.button==SDL_BUTTON_RIGHT && dec == 1){
                
                decoupage(renderer, img,posRect);
                dec = 0;
            }
            

            break;

        case SDL_MOUSEMOTION: // quand la souris se deplace
            if(clic==1){
                
                posDeplacement.x=event.motion.x;
                posDeplacement.y=event.motion.y;
                posRect.w=abs(posDeplacement.x - posClic.x);
                posRect.h=abs(posDeplacement.y - posClic.y);
                if (posDeplacement.x<posClic.x){
                    posRect.x=posDeplacement.x;
                }
                else
                    posRect.x=posClic.x;
                if (posDeplacement.y<posClic.y)
                    posRect.y=posDeplacement.y;
                else
                    posRect.y=posClic.y;
            }

        break;

        case SDL_MOUSEBUTTONUP: // quand le clic est relache
            if (event.button.button==SDL_BUTTON_LEFT){
                clic=0;
                dessineRectSelection(renderer,posRect.x,posRect.y,posRect.w,posRect.h);
                if (copier == 1)
                {
                    copier =0;
                    temp = copieSurfacePartielle(posRect, image);
                }
                if (coller== 1)
                {   coller = 0;
                    image = colleSurface(image, temp, posClic, posRect);
                }
                
            }

        break;
    }
    SDL_RenderPresent(renderer);
    //img = SDL_CreateTextureFromSurface(renderer,image);
    //SDL_RenderCopy(renderer, img, &fonte,NULL);
}
}


int runForever(SDL_Window *window, SDL_Renderer *renderer, char path[]) {
	SDL_Texture *image2 = loadImage("noir.bmp", renderer);
	SDL_Surface *image = loadImage2(path, renderer);
    SDL_Surface *imgTmp = image;
	SDL_RenderPresent(renderer);
	SDL_Texture *img;
	int fullscreen = 0;

	SDL_Rect pos_window;

	double angle = 0.0;

	int flip = SDL_FLIP_NONE;

	char tabCmd[100];

	if (NULL == image) {
		return 1;
	}
	
	SDL_RenderPresent(renderer);
	SDL_RenderCopy(renderer, image2, NULL, NULL);
	img = SDL_CreateTextureFromSurface(renderer,image);
	int rst = SDL_RenderCopyEx(renderer, img, NULL, &pos_window, angle, NULL, flip);

	while (!strcmp(tabCmd, "exit")==0) // Récupération des actions de l'utilisateur
	{
		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, image2, NULL, NULL);
		rst = SDL_RenderCopyEx(renderer, img, NULL, &pos_window, angle, NULL, flip);
		fgets(tabCmd,100,stdin);
		tabCmd[strlen(tabCmd)-1] = '\0';
			if (strcmp(tabCmd, "full")==0){
				// Alterne du mode plein écran au mode fenêtré
				if (fullscreen == 0) {
					fullscreen = 1;
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
				} else if (fullscreen == 1) {
					fullscreen = 0;
					SDL_SetWindowFullscreen(window, 0);
				}
			} else if (strcmp(tabCmd, "haut")==0) {
				(window)->poswin.y -= 50;
			} else if (strcmp(tabCmd, "bas")==0) {
				(window)->poswin.y += 50;
			} else if (strcmp(tabCmd, "gauche")==0) {
				(window)->poswin.x -= 50;
			} else if (strcmp(tabCmd, "droite")==0) {
				(window)->poswin.x += 50;
			} else if ( strcmp(tabCmd, "dezoomer")==0) {
				(window)->poswin.w -= 20;
				(window)->poswin.h -= 20;
			} else if (strcmp(tabCmd, "zoomer")==0) {
				(window)->poswin.w += 20;
				(window)->poswin.h += 20;
			} else if (strcmp(tabCmd, "rotation")==0) {
				angle += 90;
			} else if (strcmp(tabCmd, "symetriev")==0) {
				flip = SDL_FLIP_VERTICAL;
			} else if (strcmp(tabCmd, "symetrieh")==0) {
				flip = SDL_FLIP_HORIZONTAL;
			}else if (strcmp(tabCmd, "negative")==0)
			{
				image=negatif(image);
                //surfaceEnRenderer(image,renderer);
			}else if (strcmp(tabCmd, "ndg")==0)
            {
                image = niveauxDeGris(image);
                
            }else if (strcmp(tabCmd, "noirblanc")==0)
            {
                image = noir_blanc(image);
            }
            else if (strcmp(tabCmd, "lumin")==0)
            {
                luminosite(window, renderer, image);

            }else if (strcmp(tabCmd, "select")==0)
            {
                printf("On est dedans\n");
                selection(window, image, (window)->poswin, renderer);
                printf("On est dehors\n");
            } else if (strcmp(tabCmd, "save")==0)
			{
				printf("Entrer nom de fichier pour sauvegarder l'image:\n");
				char save[10];
				fgets(save,10,stdin);
				save[strlen(save)-1] = '\0';

				save_texture(renderer,img,save);

			}
			else if (strcmp(tabCmd, "open")==0)
			{
				printf("Entrer le nom de votre fichier:\n");
				char op[10];

				fgets(op,10,stdin);
				op[strlen(op)-1] = '\0';
				SDL_Window *newwin;
				SDL_Renderer *newRender;
				init_and_open_window(&newwin,&newRender,WIDTH,HEIGTH);
				runForever(newwin,newRender, op);

			}
			else{
				printf("Veuillez saisir les modifications correctes:\n");
				printf("haut, bas, gauche, droite, select, zoomer, dezoomer, lumin, noirblanc, ndg, negative, symetrieh, symetriev, rotation, open\n");
			}
			pos_window = window->poswin;
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, image2, NULL, NULL);
			img = SDL_CreateTextureFromSurface(renderer,image);
			rst = SDL_RenderCopyEx(renderer, img, NULL, &pos_window, angle, NULL, flip);

			if (rst) {
				printf("%s", SDL_GetError());
			}

		

	}
	clean_sdl(window,renderer);

	return 0;

}

