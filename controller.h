#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "vue.h"


#ifndef CONTROLLER_H
#define CONTROLLER_H   

struct s_button{
    struct s_controller* ctrl_parent;
    couleur color;
    int id;
};
typedef struct s_button button;

struct s_controller{
    mastermind* modele;
    vue_mastermind vue;  
    button color_button[NB_COULEURS];
    int indice_case;
    int mode_player;   //0 if solo player, 1 if 2 players 
}; 
typedef struct s_controller controller_t;        
 
 /* Initiate the color of the button depending on it's id*/
void controller_init_button_color(button * btn);

/*Reset the color selection to initial state*/
void controller_reset_colors_picked(controller_t* ctrl);

/*Confirm the colors picked and if it is valid then display it in the essaie array*/
void controller_confirm_colors_picked(GtkButton* btn1, controller_t* ctrl);

/*Add the combinaison of colors to the essai array*/
void controller_add_essai(controller_t* ctrl);

/*Add the color picked to the combinaison in modele and and in the vue*/
void controller_set_combinaison(GtkButton* btn1, button* btn);

void print_msg(GtkButton* btn1, button* btn );

/*Initiate the controller, after the call the game can be started with controller_start()*/
void controller_init(controller_t * controller, mastermind* modele);

/*Start the controller*/
void controller_start();

/*Compare the combinaison set by the player to the secret combinaison, modify stat[] and display it */
void controller_cmp_combinaison(controller_t* ctrl);

/*Called when the player press play*/
void controller_play_game(GtkButton* btn, controller_t * ctrl);

/*Set the game mode to 1 player*/
void controller_game_mode_solo(GtkButton* btn, controller_t* ctrl);

/*Set the game mode to 2 players*/
void controller_game_mode_multi(GtkButton* btn, controller_t* ctrl);

/*change the vue depending on state of the game*/
void controlleur_etat_partie(controller_t* ctrl);

/*Called when the player wish to replay*/
void controller_new_game(controller_t *ctrl);

/*Called to display the rules*/
void controller_rule_button(GtkButton* btn, vue_mastermind *vue);
#endif
