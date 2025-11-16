#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <time.h>


gboolean updateTime(gpointer user_data);
void screenAlarm();
void fetchTime();
struct currentTime {
    int hour;
    int minute;
}curTime;

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

    //Init of headerbarMain
    GtkWidget *headerbarMain = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(windowMain),headerbarMain);

    //Init of buttonAlarm
    GtkWidget *buttonAlarm = gtk_button_new_with_label("⏰");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbarMain),buttonAlarm);
    g_signal_connect(buttonAlarm,"clicked",G_CALLBACK(screenAlarm),NULL);

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
    gtk_grid_attach(GTK_GRID(gridParent),entryTime,0,4,15,4);
    gtk_editable_set_editable(GTK_EDITABLE(entryTime),FALSE);
    gtk_widget_add_css_class(entryTime,"entryTime");
    gtk_widget_set_size_request(entryTime,300,80);
    gtk_entry_set_alignment(GTK_ENTRY(entryTime),0.5);

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

void screenAlarm() {

    //Fetches the current time in the currentTime struct
    fetchTime();

    //Init of windowAlarm
    GtkWidget *windowAlarm = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowAlarm),"Set Alarm");
    //gtk_window_set_default_size(GTK_WINDOW(windowAlarm),600,400);
    gtk_window_present(GTK_WINDOW(windowAlarm));

    //Init of gridParent
    GtkWidget *gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowAlarm),gridParent);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_end(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_top(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(gridParent),10);

    //Init of buttonHourUp
    GtkWidget *buttonHourUp = gtk_button_new_with_label("🔺");
    gtk_grid_attach(GTK_GRID(gridParent),buttonHourUp,0,0,1,1);

    //Init of entryhours
    GtkWidget *entryHour = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryHour,0,1,1,1);
    gtk_editable_set_editable(GTK_EDITABLE(entryHour),FALSE);
    char temp[5];
    snprintf(temp,sizeof(temp),"%d",curTime.hour);
    gtk_editable_set_text(GTK_EDITABLE(entryHour),temp);

    gtk_widget_add_css_class(entryHour,"entryHour");
    gtk_entry_set_alignment(GTK_ENTRY(entryHour),0.5);
    gtk_widget_set_hexpand(GTK_WIDGET(entryHour), FALSE);


    //Init of buttonHourDown
    GtkWidget *buttonHourDown = gtk_button_new_with_label("🔻");
    gtk_grid_attach(GTK_GRID(gridParent),buttonHourDown,0,2,1,1);


    //Init of labelSemiColon
    GtkWidget *labelSemiColon = gtk_label_new(":");
    gtk_grid_attach(GTK_GRID(gridParent),labelSemiColon,1,1,1,1);
    gtk_widget_add_css_class(labelSemiColon,"labelSemiColon");

    //Init of buttonMinUp
    GtkWidget *buttonMinUp = gtk_button_new_with_label("🔺");
    gtk_grid_attach(GTK_GRID(gridParent),buttonMinUp,2,0,1,1);

    //Init of entryMinutes
    GtkWidget *entryMinute = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryMinute,2,1,1,1);
    gtk_editable_set_editable(GTK_EDITABLE(entryMinute),FALSE);
    snprintf(temp,sizeof(temp),"%d",curTime.minute);
    gtk_editable_set_text(GTK_EDITABLE(entryMinute),temp);

    gtk_widget_add_css_class(entryMinute,"entryMinutes");
    gtk_entry_set_alignment(GTK_ENTRY(entryMinute),0.5);
    gtk_widget_set_size_request(entryMinute,90,90);
    gtk_widget_set_hexpand(GTK_WIDGET(entryMinute), FALSE);

    //Init of buttonHourDown
    GtkWidget *buttonMinDown = gtk_button_new_with_label("🔻");
    gtk_grid_attach(GTK_GRID(gridParent),buttonMinDown,2,2,1,1);

    //Init of buttonSetAlarm
    GtkWidget *buttonSetAlarm = gtk_button_new_with_label("Set Alarm");
    gtk_grid_attach(GTK_GRID(gridParent),buttonSetAlarm,0,3,3,1);

    gtk_widget_set_margin_top(buttonSetAlarm,10);

}

//fetches the current time
 void fetchTime() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    curTime.hour = t->tm_hour;
    curTime.minute = t->tm_min;
    printf("hour=%d\t",curTime.hour);
    printf("min=%d\t",curTime.minute);
}

int main(int argc, char **argv){
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    return status;
}