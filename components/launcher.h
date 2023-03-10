using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include "component.h"
#include "../config.h"



class launcher : public component{
public:
    string icon,name,command;
    GtkWidget *button,*button_box;
    

    //launcher(char icon[NUM_CHARS_STR],char name[NUM_CHARS_STR],char command[NUM_CHARS_STR]){
    //    this->icon = icon;
    //    this->name = name;
    //    this->command = command;
    //}
    launcher(string icon,string name,string command){
        
        this->icon = icon;
        this->name = name;
        this->command = command + " &";
    }

    
    static void run_command (GtkWidget *widget,gpointer data)
    {
        system((char*)data);
    }
    void render(GtkWidget *container){
        
        GtkImage *image;

                                                        
        

        GtkSettings *default_settings = gtk_settings_get_default();
        g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
        

        //create button
        button = gtk_button_new_with_label("");
        g_signal_connect (button, "clicked", G_CALLBACK (launcher::run_command), (gpointer)(char*)command.c_str());

        //set image
        //GtkIconTheme *icon_theme = get_icon_theme ();
        //GtkIconTheme *icon_theme;
        
        GdkPixbuf *pb  = gtk_icon_theme_load_icon (icon_theme,icon.c_str(),48, GTK_ICON_LOOKUP_USE_BUILTIN,  NULL);
        GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pb,icon_res,icon_res,GDK_INTERP_BILINEAR);
        image = (GtkImage*)gtk_image_new_from_pixbuf(pxbscaled);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
        gtk_button_set_image (GTK_BUTTON(button),(GtkWidget *)image); 





 
        //add text
        gtk_widget_set_tooltip_text(button, (const char*)name.c_str());
        
        //put on the list
        gtk_box_pack_start(GTK_BOX(container), button, TRUE, TRUE, 0);
        
    }
};