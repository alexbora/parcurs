/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : gtk9
 * @created     : Sâmbătă Oct 22, 2022 08:24:57 EEST
 */

#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GtkWidget  *window;

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "/Users/alex/Desktop/tutorial.xml", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
  g_object_unref(G_OBJECT(builder));
  gtk_widget_show(window);
  gtk_main();

  return 0;
}
