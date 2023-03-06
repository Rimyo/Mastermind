#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "vue.h" 

void vue_init(vue_mastermind* vue) { 

    /* Init CSS */
    vue_init_css();

    /* Init Window */
    vue->fenetre = (GtkWindow*) gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_resizable(vue->fenetre, FALSE);
    gtk_widget_set_name(GTK_WIDGET(vue->fenetre), "window");

    /* ------------------------Init Menu---------------------------------------- */
    vue->main_menu = (GtkBox *) gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(vue->fenetre), GTK_WIDGET(vue->main_menu));
    gtk_widget_set_name(GTK_WIDGET(vue->main_menu), "menu");

    vue->game_name_menu = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(vue->main_menu, GTK_WIDGET(vue->game_name_menu) , TRUE, TRUE, 0 );
    gtk_widget_set_name(GTK_WIDGET(vue->game_name_menu), "menu_name");

    vue->one_player_mode = (GtkButton*)gtk_toggle_button_new_with_label("1 PLAYER");
    vue->multiplayer_mode = (GtkButton*)gtk_toggle_button_new_with_label("2 PLAYERS");
    gtk_box_pack_start(vue->main_menu, GTK_WIDGET(vue->one_player_mode) , FALSE, TRUE, 0 );
    gtk_box_pack_start(vue->main_menu, GTK_WIDGET(vue->multiplayer_mode) , FALSE, TRUE, 0 );
    gtk_widget_set_name(GTK_WIDGET(vue->one_player_mode), "button_one_player");
    gtk_widget_set_name(GTK_WIDGET(vue->multiplayer_mode), "button_multiplayer");

    vue->options = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(vue->main_menu, GTK_WIDGET(vue->options) , TRUE, TRUE, 0 );
    gtk_widget_set_name(GTK_WIDGET(vue->options), "options");

    vue->play_button = (GtkButton*) gtk_button_new_with_label("PLAY");
    vue->rules_button = (GtkButton*) gtk_button_new();
    gtk_container_add(GTK_CONTAINER(vue->options), GTK_WIDGET(vue->rules_button));
    gtk_container_add(GTK_CONTAINER(vue->options), GTK_WIDGET(vue->play_button));
    gtk_widget_set_name(GTK_WIDGET(vue->play_button), "play_button");
    gtk_widget_set_name(GTK_WIDGET(vue->rules_button), "rules_button");
    gtk_widget_set_size_request(GTK_WIDGET(vue->play_button), 200, 50);
    gtk_widget_set_size_request(GTK_WIDGET(vue->rules_button), 70, 50);

    /* ------------------------Init main container--------------------------- */ 
    vue->main_container = (GtkBox *) gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0); 
    gtk_widget_set_name(GTK_WIDGET(vue->main_container), "container");

    /*--------------------------Init child box------------------------------- */ 
    vue->box_v[0] = (GtkBox *) gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    vue->box_v[1] = (GtkBox *) gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    gtk_box_pack_start(vue->main_container, GTK_WIDGET(vue->box_v[0]), FALSE, TRUE , 30); 
    gtk_box_pack_start(vue->main_container, GTK_WIDGET(vue->box_v[1]), FALSE, TRUE , 30); 
    vue->color_selection_box = (GtkBox *) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    vue->selection_show_box = (GtkBox *) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gtk_widget_set_name(GTK_WIDGET(vue->box_v[0]), "left_box");
    gtk_widget_set_name(GTK_WIDGET(vue->box_v[1]), "right_box");
    gtk_widget_set_name(GTK_WIDGET(vue->color_selection_box), "color_selection_box");
    gtk_widget_set_name(GTK_WIDGET(vue->selection_show_box), "selection_show_box");

    for(int i = 0; i<4; i++){
        vue->selection_box[i] = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        gtk_container_add(GTK_CONTAINER(vue->selection_show_box), GTK_WIDGET(vue->selection_box[i]));
        gtk_widget_set_name(GTK_WIDGET(vue->selection_box[i]), "selection_box");
    } 


    /* -------------------------Init label game name ------------------------*/ 
    vue->game_name_box = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    vue->game_name = (GtkLabel*) gtk_label_new("");
    gtk_box_pack_start(vue->game_name_box,GTK_WIDGET( vue->game_name) , FALSE, TRUE, 0 );  
    gtk_widget_set_name(GTK_WIDGET(vue->game_name), "title");
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET( vue->game_name_box ) , FALSE, TRUE, 0 );
    gtk_widget_set_name(GTK_WIDGET(vue->game_name_box), "title_box");

    /*-----------------------Init label dialog-------------------------------*/
    vue->dialog_box = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(vue->dialog_box), "dialog_box");
    vue->dialog = (GtkLabel*) gtk_label_new("DIALOG");
    gtk_widget_set_name(GTK_WIDGET(vue->dialog), "dialog");
    gtk_box_pack_start(vue->dialog_box,GTK_WIDGET(vue->dialog) , TRUE, TRUE, 0 );
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET(vue->dialog_box) , FALSE, TRUE, 0 );


  /*---------------------Init Color selection--------------------------------*/
    vue->first_line = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    vue->second_line = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    for(int i =0; i< 8; i++){
        vue->color_button[i] = (GtkButton*) gtk_button_new();
        gtk_widget_set_size_request(GTK_WIDGET(vue->color_button[i]), 70, 60);
        if(i <= 3) {
            gtk_container_add(GTK_CONTAINER(vue->first_line), GTK_WIDGET(vue->color_button[i]));
        }else{ 
            gtk_container_add(GTK_CONTAINER(vue->second_line), GTK_WIDGET(vue->color_button[i]));
        } 
    }
    gtk_widget_set_name(GTK_WIDGET(vue->first_line), "first_line_color");
    gtk_widget_set_name(GTK_WIDGET(vue->second_line), "second_line_color");

    gtk_widget_set_name(GTK_WIDGET(vue->color_button[0]), "rouge");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[1]), "orange");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[2]), "jaune");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[3]), "vert");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[4]), "bleu");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[5]), "violet");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[6]), "blanc");
    gtk_widget_set_name(GTK_WIDGET(vue->color_button[7]), "gris");

    vue->colors_box = (GtkBox*) gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_container_add(GTK_CONTAINER(vue->colors_box), GTK_WIDGET(vue->first_line));
    gtk_container_add(GTK_CONTAINER(vue->colors_box), GTK_WIDGET(vue->second_line));
    gtk_box_pack_start(vue->color_selection_box, GTK_WIDGET(vue->colors_box), FALSE, TRUE, 0);
    gtk_widget_set_name(GTK_WIDGET(vue->colors_box), "colors_box");
    
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET( vue->color_selection_box ) , FALSE, TRUE, 0 ); 
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET( vue->selection_show_box ) , FALSE, TRUE, 0 );  

    /*---------Adding delete color selection and confirm buttons -----------*/
    vue->delete_button = (GtkButton*) gtk_button_new_with_label("Delete");    
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET( vue->delete_button ) , FALSE, TRUE, 0 );
    gtk_widget_set_size_request(GTK_WIDGET(vue->delete_button), 20, 10);
    gtk_widget_set_name(GTK_WIDGET(vue->delete_button), "delete_button");

    vue->confirm_button = (GtkButton*) gtk_button_new_with_label("Confirm");    
    gtk_box_pack_start(vue->box_v[1],GTK_WIDGET( vue->confirm_button ) , FALSE, TRUE, 0 ); 
    gtk_widget_set_name(GTK_WIDGET(vue->confirm_button), "confirm_button"); 

    for (int i = 0; i < 48; i ++) { 
        vue->box_essai_color[i] =  (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(vue->box_essai_color[i]), "color_essai_box");

        vue->box_essai_indication_color[i] =  (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        gtk_widget_set_name(GTK_WIDGET(vue->box_essai_indication_color[i]), "color_indication_box");
    }

    /*Init essai boxes*/
    gtk_widget_set_size_request(GTK_WIDGET(vue->box_v[0]), 340, 600);
    int num =0;
    for(int i =0; i<12; i++){
        vue->box_essai[i] = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);
        vue->box_essai_combinaison[i] = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);      
        vue->box_essai_indication[i] = (GtkBox*) gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2); 

        gtk_widget_set_name(GTK_WIDGET(vue->box_essai[i]), "essai_box");
        gtk_widget_set_name(GTK_WIDGET(vue->box_essai_combinaison[i]), "combinaison_box");
        gtk_widget_set_name(GTK_WIDGET(vue->box_essai_indication[i]), "indication_box");
        
        for(int j =0; j<4; j++){
            gtk_container_add(GTK_CONTAINER(vue->box_essai_combinaison[i]), GTK_WIDGET(vue->box_essai_color[num]));
            gtk_container_add(GTK_CONTAINER(vue->box_essai_indication[i]), GTK_WIDGET(vue->box_essai_indication_color[num]));
            num++;
        }
        gtk_container_add(GTK_CONTAINER(vue->box_essai[i]), GTK_WIDGET(vue->box_essai_combinaison[i]));
        gtk_container_add(GTK_CONTAINER(vue->box_essai[i]), GTK_WIDGET(vue->box_essai_indication[i]));
        gtk_box_pack_start(vue->box_v[0], GTK_WIDGET(vue->box_essai[i]), TRUE, TRUE, 2);

    
    }

} 


void vue_destroy(vue_mastermind* vue) {

    /* Destroy window and child */ 
    gtk_widget_destroy( GTK_WIDGET(vue->fenetre));

}

void vue_init_css() {
    GtkCssProvider* provider;
    GdkDisplay* display;
    GdkScreen* screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GError* error = 0;

    gboolean pb = gtk_css_provider_load_from_path(provider, "./main.css", &error);

    if(!pb) {
        perror("Css file failed to read");
        exit(0);
    }

   g_object_unref(provider);
}

GtkButton* vue_get_button_with_id(vue_mastermind* vue, int i){
    return (GtkButton*)vue->color_button[i];
} 

void vue_show(vue_mastermind* vue){
    gtk_widget_show_all(GTK_WIDGET(vue->fenetre));
} 

void vue_combinaison_set_color(vue_mastermind* vue, int indice, couleur color){
    vue_init_box_color_to(vue->selection_box[indice],color);
} 

void vue_init_box_color_to(GtkBox* box, couleur color){
    switch(color){
        case COULEUR_INDETERMINEE:
            gtk_widget_set_name(GTK_WIDGET(box), "selection_box");
            break;
        case COULEUR_ROUGE:
            gtk_widget_set_name(GTK_WIDGET(box), "rouge_selection");
            break;
        case COULEUR_VERT:
            gtk_widget_set_name(GTK_WIDGET(box), "orange_selection");
            break;
        case COULEUR_MAUVE:
            gtk_widget_set_name(GTK_WIDGET(box), "vert_selection");
            break;
        case COULEUR_BLEU:
            gtk_widget_set_name(GTK_WIDGET(box), "jaune_selection");
            break;
        case COULEUR_ORANGE:
            gtk_widget_set_name(GTK_WIDGET(box), "bleu_selection");
            break;
        case COULEUR_JAUNE:
            gtk_widget_set_name(GTK_WIDGET(box), "violet_selection");
            break;
        case COULEUR_NOIR:
            gtk_widget_set_name(GTK_WIDGET(box), "gris_selection");
            break;
        case COULEUR_BLANC:
            gtk_widget_set_name(GTK_WIDGET(box), "blanc_selection");
            break;
        default:
			printf("vue_init_box_color_to : unknow case\n");
    } 
} 

void vue_init_essai_box_color_to(GtkBox* box, couleur color){
    switch(color){
        case COULEUR_INDETERMINEE:
            gtk_widget_set_name(GTK_WIDGET(box), "color_essai_box");
            break;
        case COULEUR_ROUGE:
            gtk_widget_set_name(GTK_WIDGET(box), "rouge_essai");
            break;
        case COULEUR_VERT:
            gtk_widget_set_name(GTK_WIDGET(box), "orange_essai");
            break;
        case COULEUR_MAUVE:
            gtk_widget_set_name(GTK_WIDGET(box), "vert_essai");
            break;
        case COULEUR_BLEU:
            gtk_widget_set_name(GTK_WIDGET(box), "jaune_essai");
            break;
        case COULEUR_ORANGE:
            gtk_widget_set_name(GTK_WIDGET(box), "bleu_essai");
            break;
        case COULEUR_JAUNE:
            gtk_widget_set_name(GTK_WIDGET(box), "violet_essai");
            break;
        case COULEUR_NOIR:
            gtk_widget_set_name(GTK_WIDGET(box), "gris_essai");
            break;
        case COULEUR_BLANC:
            gtk_widget_set_name(GTK_WIDGET(box), "blanc_essai");
            break;
        default:
			printf("vue_init_box_color_to : unknow case\n");
    } 
} 


GtkButton* vue_get_delete_button(vue_mastermind * vue){
    return (GtkButton*) vue->delete_button;
} 

GtkButton* vue_get_confirm_button(vue_mastermind* vue){
    return (GtkButton*) vue->confirm_button;
}  

void vue_set_stats_at_essai(vue_mastermind* vue, int num, stat_essai stats){
    stats.non_ordo = stats.non_ordo - stats.ordo;
    for(int i = 0; i < TAILLE_COMBI; i++){
        if(stats.ordo > 0){
            stats.ordo = stats.ordo - 1;
            gtk_widget_set_name(GTK_WIDGET(vue->box_essai_indication_color[TAILLE_COMBI * num + i] ), 
            "color_indication_ordo"); 
        }else if(stats.non_ordo > 0){
            stats.non_ordo = stats.non_ordo - 1 ;
            gtk_widget_set_name(GTK_WIDGET(vue->box_essai_indication_color[TAILLE_COMBI * num + i] ), 
            "color_indication_non_ordo"); 
        } 
        
    }  
} 

void vue_play_game(vue_mastermind* vue){
    gtk_container_remove(GTK_CONTAINER(vue->fenetre), GTK_WIDGET(vue->main_menu));
    gtk_container_add(GTK_CONTAINER(vue->fenetre), GTK_WIDGET(vue->main_container));
} 

GtkButton* vue_get_one_player_mod_button(vue_mastermind* vue){
    return (GtkButton*) vue->one_player_mode;
} 

GtkButton* vue_get_two_players_mod_button(vue_mastermind* vue){
    return (GtkButton*) vue->multiplayer_mode;
} 


GtkButton* vue_get_start_game_button(vue_mastermind* vue){
    return (GtkButton*) vue->play_button;
} 

void vue_set_dialog_to(GtkLabel* label, char* string){
    gtk_label_set_label(label, string);
} 

void vue_rule_dialog(vue_mastermind* vue){ 
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Rules",vue->fenetre,flags,("_OK"),GTK_RESPONSE_NONE,NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new ("Le but du jeu de Mastermind est de trouver la combinaison secrète en un minimum de manche, le jeu peut être joué tout seul ou à deux: \n     => Le mode '1 player' permet de lancer une partie dont la combinaison secrète est générée aléatoirement\n   => Le mode '2 players' permet au premier joueur d'initialiser la combinaison secrète.\nLorsque la partie débute, le joueur doit entrer sa combinaison à l'aide du pannel de boutons de couleurs,\nil peut ensuite:\n    -effacer sa combinaison avec le bouton 'delete'\n    -confirmer sa combinaison avec le bouton 'confirm'\nUne fois la combinaison confirmée, 4 indicateurs apparaitront:\n  -Rouge:couleur correcte et bien placée\n    -Blanc:couleur correcte mais mal placée\n   -inchangée:couleur incorrecte\nMaintenant que vous savez comment y jouer, Bon jeu! ");

    // Ensure that the dialog box is destroyed when the user responds

    g_signal_connect_swapped (dialog,"response", G_CALLBACK (gtk_widget_destroy),dialog);

    // Add the label, and show everything we’ve added

    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all (dialog);
} 