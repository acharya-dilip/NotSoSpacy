#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <time.h>


gboolean updateTime(gpointer user_data);


static void activate(GtkApplication *app,gpointer user_data) {

    //Connecting the stylesheet
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "styles.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );;


    //Init of windowMain
    GtkWidget *windowMain = gtk_application_window_new(app);
    //gtk_window_set_default_size(GTK_WINDOW(windowMain),300,300);
    gtk_window_set_title(GTK_WINDOW(windowMain),"NotSoSpacy");
    gtk_window_present(GTK_WINDOW(windowMain));

    //Init of gridParent
    GtkWidget *gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMain),gridParent);
    //Margins & Paddings
    gtk_widget_set_halign(GTK_WIDGET(gridParent),GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(gridParent),GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_end(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_top(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(gridParent),10);

    //Init of entryTime
    GtkWidget *entryTime = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryTime,0,4,10,4);

    gtk_widget_set_size_request(entryTime,280,80);

    //Calling and Polling the updateTime Function
    g_timeout_add_seconds(1, updateTime, entryTime);
    updateTime(entryTime);

}

gboolean updateTime(gpointer user_data) {
    GtkEntry *entryTime = GTK_ENTRY(user_data);
    GDateTime *timeCurrent = g_date_time_new_now_local();
    gchar *time = g_date_time_format(timeCurrent, "%H:%M:%S");
    gtk_editable_set_text(GTK_EDITABLE(entryTime), time);
    return G_SOURCE_CONTINUE;
}




int main(int argc, char **argv){
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    return status;
}