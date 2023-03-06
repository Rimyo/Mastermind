#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "controller.h"

void controller_init(controller_t * controller, mastermind* modele){
    gtk_init(NULL, NULL); 
    vue_init(&controller->vue); 
    controller->modele = modele;
    mastermind_initialiser(controller->modele);
    controller->indice_case = 0;
    gtk_toggle_button_set_active((GtkToggleButton *)controller->vue.one_player_mode, TRUE);
    gtk_toggle_button_set_active((GtkToggleButton *)controller->vue.multiplayer_mode, FALSE);

    g_signal_connect(G_OBJECT(controller->vue.rules_button),"clicked", G_CALLBACK(controller_rule_button),&(controller->vue));
    
    g_signal_connect(G_OBJECT(vue_get_one_player_mod_button(&controller->vue)), "clicked", G_CALLBACK(controller_game_mode_solo),(controller));
    g_signal_connect(G_OBJECT(vue_get_two_players_mod_button(&controller->vue)), "clicked", G_CALLBACK(controller_game_mode_multi),(controller));
    g_signal_connect(G_OBJECT(vue_get_start_game_button(&controller->vue)), "clicked", G_CALLBACK(controller_play_game),controller);
    
    /*Initialisation of the game interface*/
    GtkButton* widget;
     
    for(int i =0 ; i < NB_COULEURS; i++ ){
        controller->color_button[i].id = i;
        controller->color_button[i].ctrl_parent = controller;
        controller_init_button_color(&controller->color_button[i]);
    } 

    for(int i =0 ; i < NB_COULEURS; i++ ){      
        widget = vue_get_button_with_id(&controller->vue, i);
        g_signal_connect(G_OBJECT(widget), "clicked", G_CALLBACK(print_msg),&(controller->color_button[i]));
        g_signal_connect(G_OBJECT(widget), "clicked", G_CALLBACK(controller_set_combinaison),&(controller->color_button[i]));
        
    }
    widget = vue_get_delete_button(&controller->vue);
    g_signal_connect_swapped(G_OBJECT(widget),"clicked", G_CALLBACK(controller_reset_colors_picked), controller);

    widget = vue_get_confirm_button(&controller->vue);
    g_signal_connect(G_OBJECT(widget),"clicked", G_CALLBACK(controller_confirm_colors_picked), controller);
    vue_show(&controller->vue);
} 

void controller_game_mode_solo(GtkButton* btn, controller_t* ctrl){
    if((gtk_toggle_button_get_active((GtkToggleButton *)ctrl->vue.one_player_mode) == TRUE)&&
    (gtk_toggle_button_get_active((GtkToggleButton *)ctrl->vue.multiplayer_mode) == TRUE)){ 
        gtk_toggle_button_set_active((GtkToggleButton *)ctrl->vue.multiplayer_mode, FALSE);
        ctrl->mode_player = 0;
    }else {
        gtk_toggle_button_set_active((GtkToggleButton *)ctrl->vue.multiplayer_mode, TRUE);
    } 
} 

void controller_game_mode_multi(GtkButton* btn, controller_t* ctrl){
    if((gtk_toggle_button_get_active((GtkToggleButton *)ctrl->vue.multiplayer_mode) == TRUE)&&
    (gtk_toggle_button_get_active((GtkToggleButton *)ctrl->vue.one_player_mode) == TRUE)){ 
        gtk_toggle_button_set_active((GtkToggleButton *)ctrl->vue.one_player_mode, FALSE);
        ctrl->mode_player = 1;
    }else{
        gtk_toggle_button_set_active((GtkToggleButton *)ctrl->vue.one_player_mode, TRUE);
    } 
} 

void controller_play_game(GtkButton* btn, controller_t* ctrl){ 
    vue_play_game(&ctrl->vue);
    if(ctrl->mode_player == 0){
        mastermind_initialiser_avec_secret(ctrl->modele);
    }else{
        mastermind_initialiser(ctrl->modele);  
        
    } 
    controlleur_etat_partie(ctrl); 
    vue_show(&ctrl->vue);
} 

void controller_new_game(controller_t *ctrl){
    gtk_widget_destroy((GtkWidget*)ctrl->vue.fenetre);
    controller_init(ctrl, ctrl->modele);
    g_signal_connect(G_OBJECT(ctrl->vue.fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    controller_start();
    controlleur_etat_partie(ctrl); 
} 

void print_msg(GtkButton* btn1, button* btn ){
    printf("button clicked %d\n", btn->id); 
} 

void controller_set_combinaison(GtkButton* btn1, button* btn){
    mastermind* mm = btn->ctrl_parent->modele;
    vue_mastermind* vue = &btn->ctrl_parent->vue;
    int i = btn->ctrl_parent->indice_case;
    if(i > 3){
        btn->ctrl_parent->indice_case = 0;
        i = 0;
    }  
    printf("1.. etatgame = %d\n", mm->etat);
    printf("2.. plateau = %d\n", mm->num_essai_encours);
    if(mm->etat == ETAT_MM_SECRET) 
        mastermind_set_secret(mm, i+1, btn->color);
    mastermind_set_essai_encours(mm, i+1, btn->color);
    vue_combinaison_set_color(vue,i,btn->color);
    btn->ctrl_parent->indice_case = btn->ctrl_parent->indice_case +1;
} 

void controller_start(){
    gtk_main();
} 

void controller_init_button_color(button * btn){
    switch(btn->id){
        case 0:
            btn->color = COULEUR_ROUGE;
            break;
        case 1:
            btn->color = COULEUR_VERT;
            break;
        case 2:
            btn->color = COULEUR_BLEU;
            break;
        case 3:
            btn->color = COULEUR_MAUVE;
            break;
        case 4:
            btn->color = COULEUR_ORANGE;
            break;
        case 5:
            btn->color = COULEUR_JAUNE;
            break;
        case 6:
            btn->color = COULEUR_BLANC;
            break;
        case 7:
            btn->color = COULEUR_NOIR;
            break;
        default: 
            printf("controller_init_button_color: unknow case");
    } 
}

void controller_reset_colors_picked(controller_t* ctrl){
    ctrl->indice_case = 0;
    for(int i = 0; i < TAILLE_COMBI; i++)
    vue_combinaison_set_color(&ctrl->vue, i, COULEUR_INDETERMINEE);

    if(ctrl->modele->etat == ETAT_MM_SECRET){
        combinaison_initialiser(ctrl->modele->plateau[NB_ESSAIS]);
        return;
    } 
    if(ctrl->modele->etat == ETAT_MM_ENCOURS){
        combinaison_initialiser(ctrl->modele->plateau[ctrl->modele->num_essai_encours]);   
        return;
    } 
     
} 

void controller_confirm_colors_picked(GtkButton* btn1, controller_t* ctrl){
    if((ctrl->modele->etat == ETAT_MM_GAGNE)|| (ctrl->modele->etat == ETAT_MM_PERDU)){
        controller_new_game(ctrl);
        return;
    } 
    printf("etatgame = %d\n", ctrl->modele->etat);
    printf("plateau = %d\n", ctrl->modele->num_essai_encours);
    if(mastermind_est_secret_valide(ctrl->modele) == 0){
        printf("Combinaison non valide!!\n");
    }else{
        mastermind_valider_secret(ctrl->modele);     
    }
    printf("etatgame = %d\n", ctrl->modele->etat);
    printf("plateau = %d\n", ctrl->modele->num_essai_encours);
    if(mastermind_est_essai_encours_valide(ctrl->modele) == 0){
        printf("Combinaison non valide!!!\n");
    }else{
        controller_add_essai(ctrl); 
        controller_cmp_combinaison(ctrl);
        mastermind_valider_essai_encours(ctrl->modele);
    } 
    controller_reset_colors_picked(ctrl);
    controlleur_etat_partie(ctrl);
    
    
        
}  

void controller_add_essai(controller_t* ctrl){
    int num = ctrl->modele->num_essai_encours;
    for(int i = 0; i < TAILLE_COMBI; i++){
        vue_init_essai_box_color_to( ctrl->vue.box_essai_color[TAILLE_COMBI * (num-1) + i], ctrl->modele->plateau[num-1][i]);
    } 
} 

void controller_cmp_combinaison(controller_t* ctrl){
    int num = ctrl->modele->num_essai_encours;
    ctrl->modele->stat[num-1].ordo = combinaison_cmp_ordonnee(ctrl->modele->plateau[num-1] , ctrl->modele->plateau[NB_ESSAIS]);
    ctrl->modele->stat[num-1].non_ordo = combinaison_cmp_ensembliste(ctrl->modele->plateau[num-1] , ctrl->modele->plateau[NB_ESSAIS]);
    vue_set_stats_at_essai(&ctrl->vue, num-1, ctrl->modele->stat[num-1]);
} 

void controlleur_etat_partie(controller_t* ctrl){
    switch(ctrl->modele->etat){
        case ETAT_MM_SECRET:
            vue_set_dialog_to(ctrl->vue.dialog, "Player 1 : Set your secret combinaison!");
            break;
        case ETAT_MM_ENCOURS:
            vue_set_dialog_to(ctrl->vue.dialog, "Still trying to find the combinaison..");
            break;
        case ETAT_MM_GAGNE:
            vue_set_dialog_to(ctrl->vue.dialog, "Congratulation! You won!");
            break;
        case ETAT_MM_PERDU:
            vue_set_dialog_to(ctrl->vue.dialog, "Maybe a next time..");
            break;
        default:
            printf("controlleur_etat_partie : unknown case");
    } 
} 

void controller_rule_button(GtkButton* btn, vue_mastermind *vue){
    vue_rule_dialog(vue);
} 
