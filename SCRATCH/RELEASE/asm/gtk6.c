/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : gtk6
 * @created     : Miercuri Oct 19, 2022 10:10:02 EEST
 */

#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *layout;
  GtkWidget *image;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 290, 200);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  layout = gtk_layout_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(window), layout);
  gtk_widget_show(layout);

  image = gtk_image_new_from_file(
      "/Users/alex/dev/parcurs/SCRATCH/RELEASE/logo.png");
  gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

  button = gtk_button_new_with_label("Button");
  gtk_layout_put(GTK_LAYOUT(layout), button, 150, 50);
  gtk_widget_set_size_request(button, 80, 35);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
                           G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
