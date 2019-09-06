
#include <check.h>
#include "sdl_infos.h"

START_TEST(open_test){
int a;
SDL_Window **window=NULL;
SDL_Renderer **renderer=NULL;
a=init_and_open_window(window,renderer, 1000,750);
ck_assert_int_eq(a,1);
}END_TEST


START_TEST(negatif_test){
SDL_Surface *s=SDL_LoadBMP("tiger_snow.bmp");
SDL_Surface *temp=NULL;
temp=negatif(s);
ck_assert_msg(temp==NULL,"Erreur");
}END_TEST


START_TEST(load){
SDL_Texture *image= NULL;
SDL_Renderer *renderer = NULL;
image = loadImage("tiger_snow.bmp", renderer); 
ck_assert_msg(image==NULL,"Erreur");
}END_TEST


START_TEST(test_noir_blanc){
SDL_Surface *s=SDL_LoadBMP("tiger_snow.bmp");
SDL_Surface *temp=NULL;
temp=noir_blanc(s);
ck_assert_msg(temp==NULL,"Erreur");
}END_TEST


START_TEST(gris_test){
SDL_Surface *s=SDL_LoadBMP("tiger_snow.bmp");
SDL_Surface *temp=NULL;
temp=niveauxDeGris(s);
ck_assert_msg(temp=NULL,"Erreur");
}END_TEST

START_TEST(test_copie){
SDL_Rect posRect;
SDL_Surface *temp=NULL;
posRect.x=0;
posRect.y=0;
posRect.w=0;
posRect.h=0;
temp=copieSurfacePartielle(posRect,NULL);
ck_assert_msg(temp==NULL,"Erreur");
}END_TEST


START_TEST(luminosite_test){
SDL_Window *win= NULL;
SDL_Renderer *ren = NULL;
SDL_Surface *s=SDL_LoadBMP("tiger_snow.bmp");
int *a=luminosite(win, ren, s);
ck_assert_int_eq(*a,1);
}END_TEST
/*
START_TEST(select){
SDL_Surface *s=SDL_LoadBMP("tiger_snow.bmp");
SDL_Window *win= NULL;
SDL_Rect fonte = {0,0,1000,750};
SDL_Renderer *renderer = NULL;
ck_assert_ptr_(selection(&win,&s,fonte,&renderer));
}END_TEST
*/




Suite * test_suite()

{

   Suite *s = suite_create("Tests_unitaires");
   TCase *tc_tests = tcase_create("Tests");
   tcase_add_test (tc_tests, open_test);
   tcase_add_test (tc_tests, luminosite_test);
   tcase_add_test (tc_tests, load);
   tcase_add_test (tc_tests, negatif_test);
   tcase_add_test (tc_tests, test_noir_blanc);
   tcase_add_test (tc_tests, test_copie);
   tcase_add_test (tc_tests, gris_test);

   suite_add_tcase (s, tc_tests);

   return s;

}

int main()

{

   int erreurs = 0;
   Suite *s = test_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   erreurs = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (erreurs == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}
