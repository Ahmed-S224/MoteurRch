#include "sdl_infos.h"

SDL_Surface *copieSurfaceEntiere (SDL_Surface *src){
    SDL_Surface *dst=SDL_CreateRGBSurface(0,
        src->w, src->h,32,0,0,0,0);
    SDL_BlitSurface(src,NULL,dst,NULL);
    return dst;
}

SDL_Surface *copieSurfacePartielle(SDL_Rect rectsrc, SDL_Surface *src){
    SDL_Surface *dst=SDL_CreateRGBSurface(
        0,rectsrc.w,rectsrc.h,32,0,0,0,0);
    SDL_BlitSurface(src,&rectsrc,dst,NULL);
    sauvegarde(dst,"colle.bmp");
    return dst;
}


SDL_Surface* colleSurface(SDL_Surface *source, SDL_Surface *destination, SDL_Rect rectsource, SDL_Rect rectdestination)
{
   
    SDL_BlitSurface(source,&rectsource,destination,&rectdestination);
    //sauvegarde(destination,"colle.bmp");
    return destination;
}

void changePixel(SDL_Surface *src,
    int w,int h,int r, int g,int b,int a){
    Uint32 pixel;
    SDL_Color color;
    int i,j;
    SDL_LockSurface(src); 
    for (i = 0; i < src->w; i++){
        for (j = 0; j < src->h; j++){
            pixel=obtenirPixel(src,i,j);//on va recuperer le pixel
            SDL_GetRGBA(pixel, src->format, &color.r, &color.g, &color.b, &color.a);//on recupere les composantes du pixel
            pixel= SDL_MapRGBA(src->format, r, g, b, a);//on modifie le pixel
            definirPixel(src,i,j,pixel);//changer la valeur du pixel
        }
    }
    SDL_UnlockSurface(src);
}

SDL_Surface *coupeSurfaceEntiere (){
    SDL_Surface *src=SDL_LoadBMP("tiger_snow.bmp");
    SDL_Surface *dst=SDL_CreateRGBSurface(0,
        src->w, src->h,32,0,0,0,0);
    SDL_BlitSurface(src,NULL,dst,NULL);
    changePixel(src,src->w,src->h,125,125,125,125);
    sauvegarde(src,"test.bmp");
    return dst;
}

SDL_Surface *coupeSurfacePartielle(SDL_Rect rectsrc, SDL_Surface *src){
    SDL_Surface *dst=SDL_CreateRGBSurface(
        0,rectsrc.w,rectsrc.h,32,0,0,0,0);
    SDL_BlitSurface(src,&rectsrc,dst,NULL);
    changePixel(src,rectsrc.w,rectsrc.h,125,125,125,125);
    sauvegarde(src,"testcoupe.bmp");
    return dst;
}

void dessineRectSelection(SDL_Renderer* pRenderer,int posX, int posY, int width, int length)
{
   
    SDL_Rect ligneHaut;
    ligneHaut.x = posX-1;
    ligneHaut.y = posY-1;
    ligneHaut.w = length;
    ligneHaut.h = 1;
 
    SDL_RenderFillRect(pRenderer, &ligneHaut);
 
    SDL_Rect ligneDroite;
    ligneDroite.x = posX+length-1;
    ligneDroite.y = posY-1;
    ligneDroite.w = 1;
    ligneDroite.h = width;
 
    SDL_RenderFillRect(pRenderer, &ligneDroite);
 
    SDL_Rect ligneGauche;
    ligneGauche.x = posX-1;
    ligneGauche.y = posY-1;
    ligneGauche.w = 1;
    ligneGauche.h = width;
 
    SDL_RenderFillRect(pRenderer, &ligneGauche);
 
    SDL_Rect ligneBas;
    ligneBas.x = posX-1;
    ligneBas.y = posY+width-1;
    ligneBas.w = length;
    ligneBas.h = 1;
 
    SDL_RenderFillRect(pRenderer, &ligneBas);
//    SDL_RenderPresent(pRenderer);
}

void ligneHorizontale(SDL_Renderer* renderer,int x, int y, int w)
{
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(renderer);
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
  SDL_SetRenderDrawColor(renderer, 150, 120, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &r);
//  SDL_RenderPresent(renderer);
  
}
 
void ligneVerticale(SDL_Renderer* renderer,int x, int y, int h)
{
    
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = h;
  SDL_SetRenderDrawColor(renderer, 150, 120, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &r);
  
}

void rectangle(SDL_Renderer* renderer,int x, int y, int w,int h) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    ligneHorizontale(renderer,x, y, w);
    ligneHorizontale(renderer,x, y + h - 1, w);
    ligneVerticale(renderer,x, y + 1, h - 2);
    ligneVerticale(renderer,x + w - 1, y + 1, h - 2);
    SDL_RenderPresent(renderer);
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)//couleur de la pixel qu'on donne )//modifier la couleur d'un pixel donné
{
//Efficace avec tout les formats d'images
    int OctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * OctetsParPixel;
    switch(OctetsParPixel) {
        case 1:
            *p = pixel;//on remplace la couleur du pixel
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER != SDL_BIG_ENDIAN)
            {   p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
        }else{
        
        p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
          break;
    case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}


void surfaceEnRenderer(SDL_Surface *surface, SDL_Renderer *pRenderer){
    SDL_Texture *texture = NULL;
    if (surface==NULL){
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return ;
    }
    texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_RenderCopy(pRenderer, texture, NULL, NULL);
    SDL_FreeSurface(surface);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return ;
    }
}


Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)//va me retourner le pixel (x,y) de l'image
{
    int OctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * OctetsParPixel;//va me retourner l'adresse du pixel

    switch(OctetsParPixel)
    {
        case 1://si 1 octet par pixel
            return *p;

        case 2://si 2 octets par pixel
            return *(Uint16 *)p;//Le pixel sera en Uint16 

        case 3://si 3 octets par pixels
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER != SDL_BIG_ENDIAN)
        return p[0] | p[1] << 8 | p[2] << 16;
       else
         return p[0] << 16 | p[1] << 8 | p[2];

        case 4:
            return *(Uint32 *)p;

        default:
            return 0; 
    }
}

void decoupage(SDL_Renderer* renderer, SDL_Texture* src,SDL_Rect rectsrc){
	if(SDL_RenderCopy(renderer,src,&rectsrc,NULL)!=0)
		SDL_Log("SDL_RenderCopy() failed: %s", SDL_GetError());;
	SDL_RenderPresent(renderer);
}