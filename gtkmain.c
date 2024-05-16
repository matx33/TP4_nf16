#include "tp4.h"
#include <stdio.h>
#include <gtk/gtk.h>

// Déclaration des widgets globaux
GtkWidget *text_view_elements;
GtkWidget *text_view_sommets;

// Fonction pour initialiser l'arbre et afficher ses éléments
void initialize_tree() {
    T_Arbre abr = NULL;

    // Insertion des éléments dans l'arbre
    abr = insererElement(abr, 5);
    abr = insererElement(abr, 2);
    abr = insererElement(abr, 7);
    abr = insererElement(abr, 1);
    abr = insererElement(abr, 3);
    abr = insererElement(abr, 6);
    abr = insererElement(abr, 8);

    // Affichage des éléments de l'arbre
    gchar *elements_text = g_strdup_printf("Affichage des elements de l'arbre :\n");
    gchar *sommets_text = g_strdup_printf("Affichage des sommets de l'arbre :\n");

    afficher_elements(abr, elements_text);
    afficher_sommets(abr, sommets_text);

    // Libération de la mémoire
    g_free(elements_text);
    g_free(sommets_text);
}

// Fonction pour afficher les éléments de l'arbre
void afficher_elements(T_Arbre abr, gchar *text) {
    if (abr == NULL) {
        return;
    }

    afficher_elements(abr->filsGauche, text);
    gchar *element_text;
    if (abr->borneInf != abr->borneSup) {
        element_text = g_strdup_printf("%d-%d ", abr->borneInf, abr->borneSup);
    } else {
        element_text = g_strdup_printf("%d ", abr->borneInf);
    }
    g_strconcat(text, element_text);
    g_free(element_text);
    afficher_elements(abr->filsDroit, text);
}

// Fonction pour afficher les sommets de l'arbre
void afficher_sommets(T_Arbre abr, gchar *text) {
    if (abr == NULL) {
        return;
    }

    afficher_sommets(abr->filsGauche, text);
    gchar *sommet_text = g_strdup_printf("[%d; %d]\n", abr->borneInf, abr->borneSup);
    g_strconcat(text, sommet_text);
    g_free(sommet_text);
    afficher_sommets(abr->filsDroit, text);
}

// Fonction pour créer la fenêtre GTK
void create_window() {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label_elements;
    GtkWidget *label_sommets;

    // Initialisation de GTK
    gtk_init(NULL, NULL);

    // Création de la fenêtre
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Arbre binaire de recherche");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Création de la boîte verticale
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Création des labels pour afficher les éléments et les sommets
    label_elements = gtk_label_new("Elements de l'arbre :");
    gtk_box_pack_start(GTK_BOX(vbox), label_elements, FALSE, FALSE, 0);

    text_view_elements = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view_elements), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view_elements), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view_elements), GTK_WRAP_WORD);
    gtk_box_pack_start(GTK_BOX(vbox), text_view_elements, TRUE, TRUE, 0);

    label_sommets = gtk_label_new("Sommets de l'arbre :");
    gtk_box_pack_start(GTK_BOX(vbox), label_sommets, FALSE, FALSE, 0);

    text_view_sommets = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view_sommets), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view_sommets), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view_sommets), GTK_WRAP_WORD);
    gtk_box_pack_start(GTK_BOX(vbox), text_view_sommets, TRUE, TRUE, 0);

    // Afficher la fenêtre
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    // Initialiser l'arbre et afficher ses éléments
    initialize_tree();

    // Créer la fenêtre GTK
    create_window();

    // Exécuter la boucle principale de GTK
    gtk_main();

    return 0;
}
