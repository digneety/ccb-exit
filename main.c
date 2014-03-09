#include <gtk/gtk.h>
#include <stdlib.h>

/*
  Copyright (C) 2013-2014 Dennis Tusk
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

void
on_logout_button_clicked(GtkWidget *widget, gpointer data) {
  system("openbox --exit");
  gtk_main_quit();
}

void
on_suspend_button_clicked(GtkWidget *widget, gpointer data) {
  system("cb_lock");
  system("dbus-send --system --print-reply --dest=\"org.freedesktop.UPower\" /org/freedesktop/UPower org.freedesktop.UPower.Suspend");
  gtk_main_quit();
}

void 
on_restart_button_clicked(GtkWidget *widget, gpointer data) {
  system("sudo reboot");
}

void
on_power_off_button_clicked(GtkWidget *widget, gpointer data) {
  system("dbus-send --system --print-reply --dest=\"org.freedesktop.ConsoleKit\" /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Stop");
}

int main( int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *buttons[5];

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  gtk_window_set_title(GTK_WINDOW(window), "ccb-exit");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  vbox = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  buttons[0] = gtk_button_new_with_label("Cancel");
  buttons[1] = gtk_button_new_with_label("Logout");
  buttons[2] = gtk_button_new_with_label("Suspend");
  buttons[3] = gtk_button_new_with_label("Restart");
  buttons[4] = gtk_button_new_with_label("Shut down");

  gtk_box_pack_start(GTK_BOX(vbox), buttons[0], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttons[1], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttons[2], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttons[3], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), buttons[4], TRUE, TRUE, 0);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  g_signal_connect(G_OBJECT(buttons[0]), "clicked",
    G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(buttons[1]), "clicked",
    G_CALLBACK(on_logout_button_clicked), NULL);
  g_signal_connect(G_OBJECT(buttons[2]), "clicked",
    G_CALLBACK(on_suspend_button_clicked), NULL);
  g_signal_connect(G_OBJECT(buttons[3]), "clicked",
    G_CALLBACK(on_restart_button_clicked), NULL);
  g_signal_connect(G_OBJECT(buttons[4]), "clicked",
    G_CALLBACK(on_power_off_button_clicked), NULL);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
