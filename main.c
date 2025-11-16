#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <time.h>


gboolean updateTime(gpointer user_data);
void screenAlarms();
void declareAlarms();
void deleteAlarm(GtkButton *button,gpointer user_data);
void screenAddAlarm();
void fetchTime();
void setTimeHour();
void setTimeMinutes();
struct currentTime {
    int hour;
    int minute;
}curTime;
void alarmHourButton(GtkButton *button, gpointer user_data);
void alarmMinButton(GtkButton *button, gpointer user_data);
void setAlarm(); int alarmCount=0; //tracks how many alarms are there
struct alarms {
    int hour;
    int minute;
    GtkWidget *labelAlarmTime;
    GtkWidget *buttonDeleteAlarm;
    GtkWidget *boxAlarm;
}alarms[10];

//Globalised Variables
GtkWidget *gridParentAlarms;
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

    //Init of buttonAddAlarm
    GtkWidget *buttonAddAlarm = gtk_button_new_with_label("➕");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbarMain),buttonAddAlarm);
    g_signal_connect(buttonAddAlarm,"clicked",G_CALLBACK(screenAddAlarm),NULL);

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
    gtk_grid_attach(GTK_GRID(gridParent),entryTime,0,0,16,1);
    gtk_editable_set_editable(GTK_EDITABLE(entryTime),FALSE);
    gtk_widget_add_css_class(entryTime,"entryTime");
    gtk_widget_set_size_request(entryTime,300,80);
    gtk_entry_set_alignment(GTK_ENTRY(entryTime),0.5);

    //Calling and Polling the updateTime Function
    g_timeout_add_seconds(1, updateTime, entryTime);
    updateTime(entryTime);

    //init of gridParentAlarms
    gridParentAlarms = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(gridParent),gridParentAlarms,0,1,16,1);
    gtk_grid_set_column_spacing(GTK_GRID(gridParentAlarms),50);
    gtk_widget_set_halign(gridParentAlarms,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParentAlarms,GTK_ALIGN_CENTER);

    //Declare the alarm subgrids
    declareAlarms();

}


void declareAlarms() {
    for (int i=0;i<alarmCount;i++) {
        //Init of boxAlarm
        alarms[i].boxAlarm = gtk_center_box_new();
        gtk_orientable_set_orientation(GTK_ORIENTABLE(alarms[i].boxAlarm),GTK_ORIENTATION_HORIZONTAL);
        gtk_grid_attach(GTK_GRID(gridParentAlarms),alarms[i].boxAlarm,0,i+2,1,1);
        gtk_widget_add_css_class(alarms[i].boxAlarm,"boxAlarm");

        //Init of labelAlarm
        char alarmTime[15];
        snprintf(alarmTime,sizeof(alarmTime),"%d:%d",
            alarms[i].hour,
            alarms[i].minute);
        alarms[i].labelAlarmTime = gtk_label_new(alarmTime);
        gtk_center_box_set_start_widget(GTK_CENTER_BOX(alarms[i].boxAlarm),alarms[i].labelAlarmTime);
        gtk_widget_add_css_class(alarms[i].labelAlarmTime,"labelAlarmTime");
        gtk_widget_set_halign(alarms[i].labelAlarmTime,GTK_ALIGN_START);

        //Init of buttonDeleteAlarm
        alarms[i].buttonDeleteAlarm = gtk_button_new_with_label("❌");
        gtk_center_box_set_end_widget(GTK_CENTER_BOX(alarms[i].boxAlarm),alarms[i].buttonDeleteAlarm);
        g_signal_connect(alarms[i].buttonDeleteAlarm,"clicked",G_CALLBACK(deleteAlarm),GINT_TO_POINTER(i));
        gtk_widget_add_css_class(alarms[i].buttonDeleteAlarm,"buttonDeleteAlarm");
        gtk_widget_set_halign(alarms[i].buttonDeleteAlarm,GTK_ALIGN_END);


    }
}

void deleteAlarm(GtkButton *button, gpointer user_data) {
    printf("\n deleteAlarm is executed");
    int i = GPOINTER_TO_INT(user_data);
    for (int j = i; j!=alarmCount;j++) {
       alarms[j]=alarms[j+1];
        alarmCount--;
    }
    declareAlarms();
}

gboolean updateTime(gpointer user_data) {
    GtkEntry *entryTime = GTK_ENTRY(user_data);
    GDateTime *timeCurrent = g_date_time_new_now_local();
    gchar *time = g_date_time_format(timeCurrent, "%H:%M:%S");
    gtk_editable_set_text(GTK_EDITABLE(entryTime), time);
    return G_SOURCE_CONTINUE;
}
//GLoblised Variables
GtkWidget *windowAddAlarm;
GtkWidget *entryHour;
GtkWidget *entryMinute;
void screenAddAlarm() {

    //Fetches the current time in the currentTime struct
    fetchTime();

    //Init of windowAlarm
    windowAddAlarm = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowAddAlarm),"Set Alarm");
    //gtk_window_set_default_size(GTK_WINDOW(windowAlarm),600,400);
    gtk_window_present(GTK_WINDOW(windowAddAlarm));

    //Init of gridParent
    GtkWidget *gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowAddAlarm),gridParent);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_end(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_top(GTK_WIDGET(gridParent),10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(gridParent),10);

    //Init of buttonHourUp
    GtkWidget *buttonHourUp = gtk_button_new_with_label("🔺");
    gtk_grid_attach(GTK_GRID(gridParent),buttonHourUp,0,0,1,1);
    g_signal_connect(buttonHourUp,"clicked",G_CALLBACK(alarmHourButton),GINT_TO_POINTER(1));

    //Init of entryhours
    entryHour = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryHour,0,1,1,1);
    gtk_editable_set_editable(GTK_EDITABLE(entryHour),FALSE);
    setTimeHour(); //Sets the correctly formatted time in the entryHour
    gtk_widget_add_css_class(entryHour,"entryHour");
    gtk_entry_set_alignment(GTK_ENTRY(entryHour),0.5);
    gtk_widget_set_hexpand(GTK_WIDGET(entryHour), FALSE);


    //Init of buttonHourDown
    GtkWidget *buttonHourDown = gtk_button_new_with_label("🔻");
    gtk_grid_attach(GTK_GRID(gridParent),buttonHourDown,0,2,1,1);
    g_signal_connect(buttonHourDown,"clicked",G_CALLBACK(alarmHourButton),GINT_TO_POINTER(0));


    //Init of labelSemiColon
    GtkWidget *labelSemiColon = gtk_label_new(":");
    gtk_grid_attach(GTK_GRID(gridParent),labelSemiColon,1,1,1,1);
    gtk_widget_add_css_class(labelSemiColon,"labelSemiColon");

    //Init of buttonMinUp
    GtkWidget *buttonMinUp = gtk_button_new_with_label("🔺");
    gtk_grid_attach(GTK_GRID(gridParent),buttonMinUp,2,0,1,1);
    g_signal_connect(buttonMinUp,"clicked",G_CALLBACK(alarmMinButton),GINT_TO_POINTER(1));

    //Init of entryMinutes
    entryMinute = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryMinute,2,1,1,1);
    gtk_editable_set_editable(GTK_EDITABLE(entryMinute),FALSE);
    setTimeMinutes(); //Sets the correctly formatted time in the entryMinute
    gtk_widget_add_css_class(entryMinute,"entryMinutes");
    gtk_entry_set_alignment(GTK_ENTRY(entryMinute),0.5);
    gtk_widget_set_size_request(entryMinute,90,90);
    gtk_widget_set_hexpand(GTK_WIDGET(entryMinute), FALSE);

    //Sets the correct time in the respective entries

    //Init of buttonHourDown
    GtkWidget *buttonMinDown = gtk_button_new_with_label("🔻");
    gtk_grid_attach(GTK_GRID(gridParent),buttonMinDown,2,2,1,1);
    g_signal_connect(buttonMinDown,"clicked",G_CALLBACK(alarmMinButton),GINT_TO_POINTER(0));


    //Init of buttonSetAlarm
    GtkWidget *buttonSetAlarm = gtk_button_new_with_label("Set Alarm");
    gtk_grid_attach(GTK_GRID(gridParent),buttonSetAlarm,0,3,3,1);
    g_signal_connect(buttonSetAlarm,"clicked",G_CALLBACK(setAlarm),NULL);

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


void setTimeHour() {
    char temp[5];
    //Appends the time format for hours
    if (curTime.hour<10) {
        snprintf(temp,sizeof(temp),"0%d",curTime.hour);
    }else {
        snprintf(temp,sizeof(temp),"%d",curTime.hour);
    }
    gtk_editable_set_text(GTK_EDITABLE(entryHour),temp);

}

void setTimeMinutes() {
    char temp[5];
    //appends the time format for minutes
    if (curTime.minute<10) {
        snprintf(temp,sizeof(temp),"0%d",curTime.minute);
    }else {
        snprintf(temp,sizeof(temp),"%d",curTime.minute);
    }
    gtk_editable_set_text(GTK_EDITABLE(entryMinute),temp);
}


void alarmHourButton(GtkButton *button, gpointer user_data) {
    int a = GPOINTER_TO_INT(user_data);
    printf("\nalarmHourButton is executed");
    printf("\na=%d",a);
    switch (a) {
        case 0:
            if (curTime.hour==0) {
                curTime.hour = 24;
            }
            curTime.hour--;
            break;

        case 1:
            if (curTime.hour==23) {
                curTime.hour = -1;
            }
            curTime.hour++;
            break;
        default:
            printf("switch gets nuttin");
    }
    setTimeHour();
}
void alarmMinButton(GtkButton *button,gpointer user_data) {
    int a = GPOINTER_TO_INT(user_data);
    char tempk[5];
    char tempj[5];
    printf("\nalarmMinuteButton is executed");
    printf("\na=%d",a);
    switch (a) {
        case 0:
            if (curTime.minute==0) {
                curTime.minute = 59;
            }
            curTime.minute--;
            printf("\nChanged Minute=%d Minute is decreased\n",curTime.minute);
            snprintf(tempk,sizeof(tempk),"%d",curTime.minute);
            gtk_editable_set_text(GTK_EDITABLE(entryMinute),tempk);
            break;

        case 1:
            if (curTime.minute==59) {
                curTime.minute = -1;
            }
            curTime.minute++;
            printf("\nChanged Minute=%d Minute is increased\n",curTime.minute);
            snprintf(tempj,sizeof(tempj),"%d",curTime.minute);
            gtk_editable_set_text(GTK_EDITABLE(entryMinute),tempj);
            break;
        default:
            printf("switch gets nuttin");
    }
    setTimeMinutes();
}

void setAlarm() {
    alarms[alarmCount].hour = curTime.hour;
    alarms[alarmCount].minute = curTime.minute;
    printf("\n Alarm set for %d:%d",
        alarms[alarmCount].hour,
        alarms[alarmCount].minute);
    alarmCount++;
    declareAlarms();
}

int main(int argc, char **argv){
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    return status;
}