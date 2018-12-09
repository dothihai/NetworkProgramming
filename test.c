#include <gtk/gtk.h>
#include "transcript.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

int main( int   argc,
          char *argv[] )
{
	
	readFileTranscript("transcript.txt");
	readFileSubject("subject.txt");
    GtkWidget *window;
    GtkWidget *table;

   

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* Set the window title */
    gtk_window_set_title (GTK_WINDOW (window), "Bảng điểm học tập");

    /* Set a handler for delete_event that immediately
     * exits GTK. */
    g_signal_connect (window, "delete-event",
                      G_CALLBACK (delete_event), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Create a 2x2 table */
    table = gtk_table_new (10, 5, TRUE);

    /* Put the table in the main window */
    gtk_container_add (GTK_CONTAINER (window), table);

    GtkWidget *label[10][5];
    GtkWidget *idSubject,*nameSubject,*pointMid,*pointFinal,*point;
    idSubject = gtk_label_new ("Mã môn học");
    nameSubject = gtk_label_new ("Tên môn học");
    pointMid = gtk_label_new ("Điểm giữa kỳ");
    pointFinal = gtk_label_new ("Điểm cuối kỳ");
    point = gtk_label_new ("Điểm chữ");
    gtk_table_attach(GTK_TABLE (table), idSubject, 0,1,1,2,0,30,10,10);
    gtk_table_attach(GTK_TABLE (table), nameSubject, 1,2,1,2,30,30,30,30);
    gtk_table_attach(GTK_TABLE (table), pointMid, 2,3,1,2,30,30,30,30);
    gtk_table_attach(GTK_TABLE (table), pointFinal, 3,4,1,2,30,30,30,30);
    gtk_table_attach(GTK_TABLE (table), point, 3,5,1,2,30,30,30,30);
  gtk_widget_show (idSubject);
    gtk_widget_show (nameSubject);
     gtk_widget_show (pointMid);
    gtk_widget_show (pointFinal);
     gtk_widget_show (point);
    
    int i = 0;
    int j = 0;
    int count = 0;
    for(i = 0; i< 10 ;i++){
    		
	    		label[i][0] = gtk_label_new (transcript[i].id_subject);
	    		label[i][1] = gtk_label_new (getNameSubject(transcript[i].id_subject));
	    		char gk[10];
	    		sprintf(gk,"%.1f", transcript[i].giua_ki);
	    		label[i][2] = gtk_label_new (gk);
	    		char ck[10];
	    		sprintf(ck,"%.1f", transcript[i].cuoi_ki);
	    		label[i][3] = gtk_label_new (ck);
	    		label[i][4] = gtk_label_new (transcript[i].diem_chu);
    	
    }

   for (i = 0; i < 10; ++i){
    		gtk_table_attach (GTK_TABLE (table), label[i][0], 0,1,i+2,i+3,30,30,30,30);
    		gtk_table_attach (GTK_TABLE (table), label[i][1], 1,2,i+2,i+3,30,30,30,30);
    		gtk_table_attach (GTK_TABLE (table), label[i][2], 2,3,i+2,i+3,30,30,30,30);
    		gtk_table_attach (GTK_TABLE (table), label[i][3], 3,4,i+2,i+3,30,30,30,30);
    		gtk_table_attach (GTK_TABLE (table), label[i][4], 3,5,i+2,i+3,30,30,30,30);

   		 	gtk_widget_show (label[i][0]);
   		 	gtk_widget_show (label[i][1]);
   		 	gtk_widget_show (label[i][2]);
   		 	gtk_widget_show (label[i][3]);
   		 	gtk_widget_show (label[i][4]);
    
    }
    

    /* Create second button */


    /* Create "Quit" button */
    

    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;

}
