#include "sdl_infos.h"

SDL_Surface* Ajout_Sous(SDL_Surface *surface, int quantR, int quantB, int quantV)//surface à modifier et quantité de couleur de pixel a ajouter
{
    int tmp,tmp2,tmp3;
    int i,j;
    Uint32 pixel;//stocker le code couleur d'un pixel
    Uint8 r,g,b,a;//les composantes d'un pixel
    Uint8 rbis,gbis,bbis;
    SDL_LockSurface(surface);//travailler sur la surface
    

    for (i=0;i<surface->w;i++)
    {
        for (j=0;j<surface->h;j++)
        {
            
            pixel=obtenirPixel(surface,i,j);
            SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);//recupere les composante

    //on ajoute la quantité
        tmp=r+quantR;
        if (tmp>255)
            tmp=255;
         else if (tmp<0)
            tmp=0;
    rbis=tmp;
        
        tmp2=g+quantV;
        if (tmp2>255)
            tmp2=255;
         else if (tmp2<0)
            tmp2=0;
        
    gbis=tmp2;

         tmp3=b+quantB;
        if (tmp3>255)
            tmp3=255;
         else if (tmp3<0)
            tmp3=0;
        
    bbis=tmp3;
 
            //On met toutes les composantes dans le meme et seul pixel
            pixel=SDL_MapRGBA(surface->format, rbis, gbis, bbis, a);
        
            //On le remet dans le bon pixel
        definirPixel(surface,i,j, pixel);
        }
    }
   
    SDL_UnlockSurface(surface);
return surface;
}


int *luminosite(SDL_Window *win, SDL_Renderer *ren, SDL_Surface *s)
{
   
    SDL_Texture *image2 = loadImage("noir.bmp", ren);
    SDL_Texture *img = NULL;

    SDL_Event event;
    int quit = 0;
    int a2 = 10;
    int rst;
    SDL_Rect pos_window;

    double angle = 0.0;

    int flip = SDL_FLIP_NONE;

    while (quit != 1) // Récupération des actions de l'utilisateur
    {

        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_KEYDOWN: // Relâchement d'une touche
             if (event.key.keysym.sym == SDLK_UP) {
                a2 +=1;
                Ajout_Sous(s,a2,a2,a2);
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                a2 -= 1;
                Ajout_Sous(s,a2,a2,a2);
            }if (event.key.keysym.sym == SDLK_q) {
                quit = 1;
            } 
            pos_window = win->poswin;
            SDL_RenderPresent(ren);
            SDL_RenderCopy(ren, image2, NULL, NULL);
            img = SDL_CreateTextureFromSurface(ren,s);
            rst = SDL_RenderCopyEx(ren, img, NULL, &pos_window, angle, NULL, flip);

            if (rst) {
                printf("%s", SDL_GetError());
            }

            break;
        }

    }
    //clean_sdl(win, ren);

    return 0;
}

SDL_Surface *negatif(SDL_Surface *s){//l'image qu'on aura charger prealablement){//ici à partire d'une texture donné la modifié pixel par pixel 
    Uint32 pixel;
    SDL_Color color;
    int i,j;
    if (s==NULL){
           return NULL;
    }
    SDL_LockSurface(s); 
    for (i = 0; i < s->w; i++){
        for (j = 0; j < s->h; j++){
            pixel=obtenirPixel(s,i,j);//on va recuperer le pixel
            SDL_GetRGBA(pixel, s->format, &color.r, &color.g, &color.b, &color.a);//on recupere les composantes du pixel
            pixel= SDL_MapRGBA(s->format, 255 - color.r, 255 - color.g, 255 - color.b, 255-color.a);//on modifie le pixel

            definirPixel(s,i,j,pixel);//changer la valeur du pixel
        }
    }
SDL_UnlockSurface(s);
//sauvegarde(s,"test.bmp");
return s;
}



SDL_Surface* niveauxDeGris(SDL_Surface* surface)
{

    Uint32 pixel;
    SDL_Color color;
    int i,j;
    if (surface==NULL){
           return NULL;
    }
    SDL_LockSurface(surface); 
    for (i = 0; i < surface->w; i++){
        for (j = 0; j < surface->h; j++){
            pixel=obtenirPixel(surface,i,j);//on va recuperer le pixel
            SDL_GetRGBA(pixel, surface->format, &color.r, &color.g, &color.b, &color.a);//on recupere les composantes du pixel
         Uint8 gris = (color.r + color.g + color.b) / 3;
            pixel= SDL_MapRGBA(surface->format, gris, gris, gris, gris);//on modifie le pixel

            definirPixel(surface,i,j,pixel);//changer la valeur du pixel
        }
    }
SDL_UnlockSurface(surface);
return surface;
}


SDL_Surface *noir_blanc(SDL_Surface *s){//l'image qu'on aura charger prealablement){//ici à partire d'une texture donné la modifié pixel par pixel 
    Uint32 pixel;
    SDL_Color color;
    int i,j;
    if (s==NULL){
           return NULL;
    }
    SDL_LockSurface(s); 
    for (i = 0; i < s->w; i++){
        for (j = 0; j < s->h; j++){
            pixel=obtenirPixel(s,i,j);
            SDL_GetRGBA(pixel, s->format, &color.r, &color.g, &color.b, &color.a);//on recupere les composantes du pixel
            

 if( ((color.r+color.g+color.b)/3)>=229){
        
        pixel= SDL_MapRGBA(s->format, 255,255, 255, 255);
            definirPixel(s,i,j,pixel);

}
else if( ((color.r+color.g+color.b)/3)<=55){
         pixel= SDL_MapRGBA(s->format, 0, 0, 0, 0);
        definirPixel(s,i,j,pixel);

}
else if( 55<((color.r+color.g+color.b)/3) && ((color.r+color.g+color.b)/3)<229){

        Uint8 gris = (color.r + color.g + color.b) / 3;
            pixel= SDL_MapRGBA(s->format, gris, gris, gris,gris);

            definirPixel(s,i,j,pixel);
}

    }
    }
SDL_UnlockSurface(s);
return s;
}