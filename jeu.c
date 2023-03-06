#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "controller.h"

int main () {

    mastermind modele;
    controller_t ctrl;
    controller_init(&ctrl, &modele);
    g_signal_connect(G_OBJECT(ctrl.vue.fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    controller_start();
	return EXIT_SUCCESS;
} 