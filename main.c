#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "transcript.c"
#define SEND_USER_ACTION 'u'
#define SEND_PASSWORD_ACTION 'p'
#define LOGIN_RESPONSE_ACTION 'r'

#define SUCCESS "success"
#define FAILED "failed"
#define OK "OK"
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 40000 /*port*/ 


GtkWidget *id_student_input;
GtkWidget *password_input;
GtkBuilder *builder; 
GtkWidget  *window;
GtkWidget  *viewTranscript;      
GtkWidget * loginButton;
GtkWidget * logoutButton;
GtkWidget *infoUser;
GtkWidget *box2;
int sockfd, responseLength;
struct sockaddr_in servaddr;
char sendline[MAXLINE], recvline[MAXLINE];
char * response;
void clear(char * s){
  memset(s, 0, strlen(s));
}

void on_window_destroy (GtkWidget *object, gpointer user_data)
{
    gtk_main_quit ();
}
void showMessage(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) {
    GtkWidget *mdialog;
    mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     type,
                                     GTK_BUTTONS_OK,
                                     "%s", mms);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
    gtk_dialog_run(GTK_DIALOG(mdialog));
    gtk_widget_destroy(mdialog);
}
void getIdAndPassword(GtkWidget *widget, gpointer *gp){
    
      
    char * student_id = gtk_entry_get_text(GTK_ENTRY(id_student_input));
    
    clear(sendline);
    sprintf(sendline, "%c_%s", SEND_USER_ACTION, student_id);
    send(sockfd, sendline, strlen(sendline), 0); 
    clear(recvline);
    recv(sockfd, recvline, MAXLINE,0);
    response =  recvline + 2;
    
    if(strcmp(OK, response) == 0){
        char *password = gtk_entry_get_text(GTK_ENTRY(password_input));
        clear(sendline);
        sprintf(sendline, "%c_%s", SEND_PASSWORD_ACTION, password);
        send(sockfd, sendline, strlen(sendline), 0); 
        recv(sockfd, recvline, MAXLINE,0);
        response =  recvline + 2;
        puts(response); 
        if(strcmp(SUCCESS, response) == 0){
            gtk_widget_hide(window);
            showTranscript();
        }
        else {
             showMessage(window, GTK_MESSAGE_ERROR, "Đăng nhập thất bại", "Sai tên đăng nhập hoặc mật khẩu");
        }
    }

    clear(recvline);

}

void logout(GtkWidget *widget, gpointer *gp){
     gtk_widget_hide(viewTranscript);
     gtk_entry_set_text(password_input,"");
     showFormLogin();
}

void initWidget(){
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "form-login.glade", NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    gtk_builder_add_from_file (builder, "transcript.glade", NULL);
    viewTranscript = GTK_WIDGET (gtk_builder_get_object (builder, "transcript"));
    id_student_input = GTK_WIDGET (gtk_builder_get_object (builder, "id_student"));
    password_input = GTK_WIDGET (gtk_builder_get_object (builder, "password"));
    loginButton = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
    g_signal_connect(loginButton, "clicked", G_CALLBACK(getIdAndPassword),NULL);
    logoutButton = GTK_WIDGET (gtk_builder_get_object (builder, "button_logout"));
    g_signal_connect(logoutButton, "clicked", G_CALLBACK(logout),NULL);
    infoUser = GTK_WIDGET (gtk_builder_get_object (builder, "info_user"));
    box2 = GTK_WIDGET (gtk_builder_get_object (builder, "box2"));
    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));

}

void showFormLogin(){
    

    gtk_widget_show (window);                

    
}

void showTranscript(){
   char *info;
    GtkWidget *table;
   readFileTranscript("transcript.txt");
    readFileSubject("subject.txt");
    table = gtk_table_new (10, 5, TRUE);

    gtk_container_add (GTK_CONTAINER (box2), table);

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
    gtk_table_attach(GTK_TABLE (table), point, 4,5,1,2,30,30,30,30);
    gtk_widget_show (idSubject);
    gtk_widget_show (nameSubject);
    gtk_widget_show (pointMid);
    gtk_widget_show (pointFinal);
    gtk_widget_show (point);
    
    int i = 0;
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
            gtk_table_attach (GTK_TABLE (table), label[i][4], 4,5,i+2,i+3,30,30,30,30);
            gtk_widget_show (label[i][0]);
            gtk_widget_show (label[i][1]);
            gtk_widget_show (label[i][2]);
            gtk_widget_show (label[i][3]);
            gtk_widget_show (label[i][4]);
    
    }

    gtk_widget_show (table);
    gtk_widget_show (box2);

    /*char *showInfo;
    strcpy(showInfo,accountLogin.name);
    strcat(showInfo," - ");
    strcat(showInfo,accountLogin.mssv);
    if(showInfo == NULL)
        printf("xxx\n");
    else {
        printf("%s\n",showInfo );
    
        gtk_label_set_text (infoUser,showInfo);
    }*/
    gtk_widget_show (viewTranscript);                

}





void createClient() 
{

    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        perror("Problem in creating the socket");
        exit(2);
    }
    
 //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr("127.0.0.1");
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
    
 //Connection of the client to the socket 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
        perror("Problem in connecting to the server");
        exit(3);
    }

 
}
 


int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    initWidget();
    createClient();
    showFormLogin();
    gtk_main ();
    return (0);
}