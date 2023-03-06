#ifndef VUE_H
#define VUE_H
#include "mastermind.h"



typedef struct{
    GtkWindow* fenetre;
    /*Game menu*/
    GtkBox* main_menu;
    GtkBox* game_name_menu;
    GtkButton* one_player_mode;
    GtkButton* multiplayer_mode;
    GtkBox* options;
    GtkButton* play_button;
    GtkButton* rules_button;

    GtkWidget* rule;

    /*Game Interface widget*/
    GtkBox* main_container;
    GtkBox* box_v[2];
    GtkBox* dialog_box;
    GtkLabel* dialog;
    GtkLabel* game_name;
    GtkBox* game_name_box;
    GtkBox* color_selection_box;
    GtkBox* colors_box;
    GtkWidget* image_color[8];
    GtkButton* color_button[8]; 
    GtkBox* first_line;
    GtkBox* second_line;
    GtkBox* selection_show_box;
    GtkBox* selection_box[4]; 
    GtkButton* delete_button;
    GtkButton* confirm_button;
    GtkWidget* image_essai[48];
    GtkWidget* image_frame[4]; 
    GtkBox* box_essai[12];
    GtkBox* box_essai_combinaison[12];
    GtkBox* box_essai_color[48];
    GtkBox* box_essai_indication[12];
    GtkBox* box_essai_indication_color[48];  
}vue_mastermind;


/*Build vue*/
void vue_init(vue_mastermind* vue);


void vue_destroy(vue_mastermind* vue);

/*Get the button corresponding to the id given*/
GtkButton* vue_get_button_with_id(vue_mastermind* vue, int i);

void vue_init_css();

void vue_show(vue_mastermind* vue);

/*Set the color of selection show box at the given indice and with color, 
and return the indice of the current case changed*/
void vue_combinaison_set_color(vue_mastermind* vue, int indice, couleur color);


/*Change the color of the box given in the parameter to the color given
Pre-condition : the indice of the color given must be > 0 && < NB_COULEURS + 1 */
void vue_init_box_color_to(GtkBox* box, couleur color);

/*Change the color of the box given in the parameter to the color given
Pre-condition : the box must be a box_essai_color
                the indice of the color given must be > 0 && < NB_COULEURS + 1 */
void vue_init_essai_box_color_to(GtkBox* box, couleur color);

/*Get the delete selection button*/
GtkButton* vue_get_delete_button(vue_mastermind* vue);

/*Get the confirm selection button*/
GtkButton* vue_get_confirm_button(vue_mastermind* vue);

/*Get the one player button*/
GtkButton* vue_get_one_player_mod_button(vue_mastermind* vue);

/*Get the 2 players button*/
GtkButton* vue_get_two_players_mod_button(vue_mastermind* vue);

/*Get start game button*/
GtkButton* vue_get_start_game_button(vue_mastermind* vue);

/*Set the indicators at the given essai with the given stat_essai*/
void vue_set_stats_at_essai(vue_mastermind* vue, int num, stat_essai stats);

/*Called when the player want to restart a game*/
void vue_play_game(vue_mastermind* vue);

/*Set the content of the in game dialog box to string*/
void vue_set_dialog_to(GtkLabel* label, char* string);

/*initiate the rule dialog box*/
void vue_rule_dialog(vue_mastermind* vue);
#endif