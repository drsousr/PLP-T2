#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

GtkWidget *display;
char expression[256] = "";

void update_display() {
    gtk_label_set_text(GTK_LABEL(display), expression);
}

void append_to_expression(const char *text) {
    strcat(expression, text);
    update_display();
}

void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));

    if (strcmp(label, "C") == 0) {
        expression[0] = '\0';
    } else if (strcmp(label, "=") == 0) {
        double a, b;
        char op;
        if (sscanf(expression, "%lf %c %lf", &a, &op, &b) == 3) {
            double result = 0;
            switch (op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b != 0) result = a / b;
                    else {
                        strcpy(expression, "Erro: Div 0");
                        update_display();
                        return;
                    }
                    break;
                default:
                    strcpy(expression, "Erro");
                    update_display();
                    return;
            }
            snprintf(expression, sizeof(expression), "%.10g", result);
        } else {
            strcpy(expression, "Inválido");
        }
    } else {
        append_to_expression(label);
        return;
    }
    update_display();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora em C (GTK3)");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    display = gtk_label_new("");
    gtk_widget_set_hexpand(display, TRUE);
    gtk_widget_set_vexpand(display, TRUE);
    gtk_widget_set_halign(display, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(display, GTK_ALIGN_CENTER);
    gtk_label_set_xalign(GTK_LABEL(display), 0.5);
    gtk_label_set_yalign(GTK_LABEL(display), 0.5);
    gtk_box_pack_start(GTK_BOX(vbox), display, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 5);

    const char *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    for (int i = 0; i < 16; i++) {
        GtkWidget *btn = gtk_button_new_with_label(buttons[i]);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
        gtk_grid_attach(GTK_GRID(grid), btn, i % 4, i / 4, 1, 1);
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}