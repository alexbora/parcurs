/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : gtk4
 * @created     : Vineri Oct 07, 2022 20:40:24 EEST
 */

#include <fcntl.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

gchar *data;
void   enter_button(GtkWidget *widget, gpointer data)
{

  (void)data;
  GdkColor col = {0, 27000, 30000, 35000};
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
  g_print("%s\n", data);
}

static void print_hello(GtkWidget *widget, gpointer data)
{
  g_print("Hello World\n");
}

static void insert(void)
{
  int fd = open("gtk4.txt", O_RDWR | O_CREAT);
  write(fd, "txt\n", 4);
  close(fd);
}

static void print_hello_2(GtkWidget *widget, gpointer data)
{
  g_print("Buna zius, Bogdan\n");
}
static void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "BOGDAN");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_default_size(window, 2000, 2000);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  /* gtk_widget_set_size_request(GTK_WIDGET(window), 1366, 768); */
  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new();

  /* Pack the container in the window */
  gtk_container_add(GTK_CONTAINER(window), grid);

  GdkColor color;

  gdk_color_parse("grey", &color);

  gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

  button = gtk_button_new_with_label("Generate");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label("Mail");
  /* g_signal_connect(button, "clicked", G_CALLBACK(print_hello_2), NULL); */
  g_signal_connect(button, "clicked", G_CALLBACK(enter_button), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy),
                           window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  /* gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1); */

  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

  GtkWidget *emailLabel, *entry;
  emailLabel = gtk_label_new("Email:");
  entry      = gtk_entry_new();
  /* gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Email"); */

  gtk_grid_attach(GTK_GRID(grid), entry, 20, 10, 20, 1);
  gtk_grid_attach(GTK_GRID(grid), emailLabel, 20, 20, 20, 1);
  data = gtk_entry_get_text(GTK_ENTRY(entry));

  gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int             status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
