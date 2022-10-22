/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : gtk8
 * @created     : Sâmbătă Oct 22, 2022 08:10:20 EEST
 */

#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  GtkBuilder *builder;

  GObject *window;
  GObject *button;

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "/Users/alex/Desktop/untitled.ui", NULL);
  gtk_widget_show(window);
  gtk_main();

  return 0;
}
