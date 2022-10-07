/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : gtk1
 * @created     : Joi Oct 06, 2022 18:53:18 EEST
 */

#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(window);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}
