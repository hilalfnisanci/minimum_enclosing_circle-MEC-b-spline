#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#define DOSYA_YOLU "points.txt"

float b_splinex(int n,float noktax[n],float t)
{
    int p0,p1,p2,p3;
    p1=(int)t+1;
    p2=p1+1;
    p3=p2+1;
    p0=p1-1;

    float N[4];
    t = t - (int)t;

    N[0] = (-t*(t*t - 2*t + 1))/2;
    N[1] = (t*t*(3*t - 5))/2 + 1;
    N[2] = (t*(-3*t*t + 4*t + 1))/2;
    N[3] = (t*t*(t - 1))/2;

    float px;
    px = noktax[p0]*N[0] + noktax[p1]*N[1] + noktax[p2]*N[2] + noktax[p3]*N[3];

    return px;
}
float b_spliney(int n,float noktay[n],float t)
{
    int p0,p1,p2,p3;
    p1=(int)t+1;
    p2=p1+1;
    p3=p2+1;
    p0=p1-1;

    float N[4];
    t = t - (int)t;

    N[0] = (-t*(t*t - 2*t + 1))/2;
    N[1] = (t*t*(3*t - 5))/2 + 1;
    N[2] = (t*(-3*t*t + 4*t + 1))/2;
    N[3] = (t*t*(t - 1))/2;

    float py;
    py = noktay[p0]*N[0] + noktay[p1]*N[1] + noktay[p2]*N[2] + noktay[p3]*N[3];

    return py;
}

void koordinat_sistemi()
{
    al_init_primitives_addon();
    ALLEGRO_COLOR blue=al_map_rgb(0,133,202);
    ALLEGRO_COLOR gray = al_map_rgb(158,151,142);

    int weight=800;
    int height=800;

    //koordinat sistemi
    al_draw_line(0.0,(height/2.0),(weight),(height/2.0),blue,1.0);
    al_draw_line((weight/2.0),0.0,(weight/2.0),(height),blue,1.0);

    //koordinat sayılarının yazılması
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font = al_load_font("arial.ttf",10,0);

    int num=1;
    for(int i=420; i<800; i+=20)
    {
        al_draw_textf(font,gray,i,400,0,"%d",num);
        al_draw_textf(font,gray,400,i,0,"%d",-1*num);
        num++;
    }
    num=1;
    for(int i=380; i>0; i-=20)
    {
        al_draw_textf(font,gray,400,i,0,"%d",num);
        al_draw_textf(font,gray,i,400,0,"%d",-1*num);
        num++;
    }

}

float uzaklik(float x1, float y1, float x2, float y2)
{
    float mesafe;
    mesafe = pow((x2-x1),2) + pow((y2-y1),2);
    mesafe = sqrt(mesafe);

    return mesafe;
}

float yaricap_hesapla(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float yaricap;
    float a,b,c,u,alan;

    a=uzaklik(x1,y1,x2,y2);
    b=uzaklik(x1,y1,x3,y3);
    c=uzaklik(x2,y2,x3,y3);

    u = (a+b+c)/2;
    alan=u*(u-a)*(u-b)*(u-c);
    alan=sqrt(alan);
    yaricap = (a*b*c)/(4*alan);

    return yaricap;
}

float karteyzen_merkezx(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float merkezx;
    float D;

    D = 2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
    merkezx = ((y1*y1+x1*x1)*(y2-y3)+(y2*y2+x2*x2)*(y3-y1)+(y3*y3+x3*x3)*(y1-y2))/D;

    return merkezx;
}

float kartezyen_merkezy(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float merkezy;
    float D;

    D = 2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
    merkezy = ((y1*y1+x1*x1)*(x3-x2)+(y2*y2+x2*x2)*(x1-x3)+(y3*y3+x3*x3)*(x2-x1))/D;

    return merkezy;
}
float cizim_koordinatx(float x)
{
    int w=800;
    x = w/2 + x*20;

    return x;
}
float cizim_koordinaty(float y)
{
    int h=800;
    y = h/2 - y*20;

    return y;
}

int main()
{
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"Allegro 5 baslatilamadi",NULL,NULL);
        return -1;
    }

    int weight=800;
    int height=800;
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY *display = al_create_display(weight,height);
    al_set_window_position(display,100,0);
    al_set_window_title(display,"Minimum Cevreleyen Cember");

    if(!display)
    {
        al_show_native_message_box(display,"Sample Title","Display Settings","Display ekrani olusturulamadi",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_init_primitives_addon();
    ALLEGRO_COLOR purple=al_map_rgb(187,41,187);
    ALLEGRO_COLOR green=al_map_rgb(0,171,132);
    ALLEGRO_COLOR red=al_map_rgb(249,66,58);
    ALLEGRO_COLOR white=al_map_rgb(255,255,255);
    ALLEGRO_COLOR orange=al_map_rgb(254,80,0);

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font = al_load_font("arial.ttf",10,0);

    koordinat_sistemi();

    //dosya islem
    FILE * dosya;

    char c;
    int n=1; //satir sayisi yani aslinda nokta sayisi

    // dosyayi ac
    if ((dosya=fopen(DOSYA_YOLU, "r")) == NULL)
    {
        printf("dosya acilamadi!\n");
        exit(1);
    }

    // dosya sonuna gelene kadar dongu calissin

    while ((c = fgetc(dosya)) != EOF)
    {
        printf("%c", c);
        if(c=='\n') //nokta sayisini satiri kontrol ederek buluyoruz
            n++;

    }
    //printf("\n%d",n); //kontrol için

    float noktalar[n][2];
    int i,j;

    //printf("\nDizi:\n");
    dosya=fopen(DOSYA_YOLU,"r");
    for(i=0; i<n; i++)
    {
        for(j=0; j<2; j++)
        {
            fscanf(dosya, "%f",&noktalar[i][j]);
            //printf("%f ",noktalar[i][j]); kontrol için
        }
        //printf("\n");
    }
    // dosyayi kapat
    fclose(dosya);

    float x;
    float y;
    for(i=0; i<n; i++)
    {
        x=noktalar[i][0];
        y=noktalar[i][1];

        if(n!=1)
            al_draw_filled_circle(cizim_koordinatx(x),cizim_koordinaty(y),2.5,purple); //dosyadaki noktalarin koordinat sisteminde gösterilmesi


        al_draw_textf(font,white,cizim_koordinatx(x),cizim_koordinaty(y),0.0,"(%.0f,%.0f)",x,y);

    }


    //burda cemberin yaricap ve merkez bilgilerini buluyoruz
    float noktax[n]; //noktalarin x bilgileri
    float noktay[n]; //noktalarin y bilgileri

    for(i=0; i<n; i++)
    {
        noktax[i]=noktalar[i][0];
        noktay[i]=noktalar[i][1];
    }

    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT *font2 = al_load_font("arial.ttf",17,0);
    ALLEGRO_COLOR gray = al_map_rgb(158,151,142);


    float merkezx, merkezy, yaricap;

    //max-x, min-x ve max-y, min-y olan noktalari buluyoruz
    float xmax[2],ymax[2],xmin[2],ymin[2];

    xmax[0]=noktax[0];
    ymax[1]=noktay[0];

    for(i=1; i<n; i++)
    {
        if(noktax[i]>xmax[0])
        {
            xmax[0]=noktax[i];
            xmax[1]=noktay[i];
        }

        if(noktay[i]>ymax[1])
        {
            ymax[1]=noktay[i];
            ymax[0]=noktax[i];
        }
    }

    xmin[0]=noktax[0];
    ymin[1]=noktay[0];

    for(i=1; i<n; i++)
    {
        if(noktax[i]<xmin[0])
        {
            xmin[0]=noktax[i];
            xmin[1]=noktay[i];
        }

        if(noktay[i]<ymin[1])
        {
            ymin[1]=noktay[i];
            ymin[0]=noktax[i];
        }
    }

    //dortgen mantıgının yukseklik ve genisligi
    float w = xmax[0]-xmin[0];
    float h = ymax[1]-ymin[1];

    //printf("\n\n%f %f %f %f",xmax[0],ymax[1],xmin[0],ymin[1]); //kontrol için

    //cember üstünde 2 nokta olma durumu
    if((ymax[0]==xmax[0] || ymin[0]==xmin[0]) && (ymax[0]==xmin[0] || ymin[0] || xmax[0]))
    {
        yaricap = uzaklik(ymin[0],ymin[1],ymax[0],ymax[1]);
        yaricap=yaricap/2;
        merkezx = w/2+xmin[0];
        merkezy = h/2+ymin[1];
    }

    float t[n];
    for(i=0; i<n; i++)
    {
        t[i] = uzaklik(w/2+xmin[0], h/2+ymin[0], noktax[i],noktay[i]); //tum noktaların dortgen merkezine olan uzaklıgı
    }

    float gecici;

    //uzaklıklar sıralanır ve noktaların yeri de uzaklıklarının indeksine göre degistirilir
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(t[i]>t[j])
            {
                gecici = t[i];
                t[i] = t[j];
                t[j] = gecici;

                gecici = noktax[i];
                noktax[i] = noktax[j];
                noktax[j] = gecici;

                gecici = noktay[i];
                noktay[i] = noktay[j];
                noktay[j] = gecici;
            }
        }
    }

    //uzaklıgı en buyuk olan 3 nokta ve bunların birbirlerine olan uzaklıkları
    float m1,m2,m3;
    m1=uzaklik(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2]);
    m2=uzaklik(noktax[n-1],noktay[n-1],noktax[n-3],noktay[n-3]);
    m3=uzaklik(noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);

    if(n==1)
    {
        merkezx = noktax[0];
        merkezy = noktay[0];
        al_draw_filled_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),3.0,green);

        al_draw_textf(font2,white,0.0,0.0,0,"Çemberin yaricapi = %f",yaricap);
        al_draw_textf(font2,white,0.0,18,0,"Çemberin merkezi = (%f , %f)",merkezx,merkezy);
        al_draw_textf(font,red,cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),0.0,"(%.1f,%.1f)",merkezx,merkezy);
    }

    if(n==2)
    {
        merkezx = (noktax[0]+noktax[1])/2;
        merkezy = (noktay[0]+noktay[1])/2;
        yaricap = uzaklik(noktax[0],noktay[0],noktax[1],noktay[1])/2;

        al_draw_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),yaricap*20,green,1.0); //çember çizen hazır fonksiyon
        al_draw_filled_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),2.5,red);

        al_draw_textf(font2,white,0.0,0.0,0,"Çemberin yaricapi = %f",yaricap);
        al_draw_textf(font2,white,0.0,18,0,"Çemberin merkezi = (%f , %f)",merkezx,merkezy);
        al_draw_textf(font,red,cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),0.0,"(%.1f,%.1f)",merkezx,merkezy);

    }

    float d,gecicix,geciciy;

    if(n==3)
    {
        if(m1>m2 || m1>m3)
        {
            gecicix = (noktax[2]+noktax[1])/2;
            geciciy = (noktay[2]+noktay[1])/2;
            d = uzaklik(noktax[0],noktay[0],gecicix,geciciy); //dısta kalan nokta ile en buyuk uzaklıgın ortasına olan mesafe

            if( d <= m1/2)
            {
                yaricap = m1/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                merkezy = kartezyen_merkezy(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                yaricap = yaricap_hesapla(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
            }
        }
        else if(m2>m1 || m2>m3)
        {
            gecicix = (noktax[2]+noktax[0])/2;
            geciciy = (noktay[2]+noktay[0])/2;
            d = uzaklik(noktax[1],noktay[1],gecicix,geciciy); //dısta kalan nokta ile en buyuk uzaklıgın ortasına olan mesafe

            if(d <= m2/2)
            {
                yaricap = m2/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                merkezy = kartezyen_merkezy(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                yaricap = yaricap_hesapla(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
            }
        }
        else
        {
            gecicix = (noktax[1]+noktax[0])/2;
            geciciy = (noktay[1]+noktay[0])/2;
            d = uzaklik(noktax[2],noktay[2],gecicix,geciciy);

            if(d <= m3/2)
            {
                yaricap = m3/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                merkezy = kartezyen_merkezy(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
                yaricap = yaricap_hesapla(noktax[0],noktay[0],noktax[1],noktay[1],noktax[2],noktay[2]);
            }
        }

        al_draw_textf(font2,white,0.0,0.0,0,"Çemberin yaricapi = %f",yaricap);
        al_draw_textf(font2,white,0.0,18,0,"Çemberin merkezi = (%f , %f)",merkezx,merkezy);
        al_draw_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),yaricap*20,green,1.0); //çember çizen hazır fonksiyon
        al_draw_filled_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),2.5,red);
        al_draw_textf(font,red,cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),0.0,"(%.1f,%.1f)",merkezx,merkezy);
    }

    else if(n>3)
    {
        if(m1>m2 || m1>m3)
        {
            gecicix = (noktax[n-1]+noktax[n-2])/2;
            geciciy = (noktay[n-1]+noktay[n-2])/2;
            d = uzaklik(noktax[n-3],noktay[n-3],gecicix,geciciy); //dısta kalan nokta ile en buyuk uzaklıgın ortasına olan mesafe

            if( d <= m1/2)
            {
                yaricap = m1/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                merkezy = kartezyen_merkezy(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                yaricap = yaricap_hesapla(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
            }

        }
        else if(m2>m1 || m2>m3)
        {
            gecicix = (noktax[n-1]+noktax[n-3])/2;
            geciciy = (noktay[n-1]+noktay[n-3])/2;
            d = uzaklik(noktax[n-2],noktay[n-2],gecicix,geciciy); //dısta kalan nokta ile en buyuk uzaklıgın ortasına olan mesafe

            if( d <= m2/2)
            {
                yaricap = m2/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                merkezy = kartezyen_merkezy(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                yaricap = yaricap_hesapla(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
            }
        }
        else
        {
            gecicix = (noktax[n-2]+noktax[n-3])/2;
            geciciy = (noktay[n-2]+noktay[n-3])/2;
            d = uzaklik(noktax[n-1],noktay[n-1],gecicix,geciciy); //dısta kalan nokta ile en buyuk uzaklıgın ortasına olan mesafe

            if( d <= m3/2)
            {
                yaricap = m3/2;
                merkezx = gecicix;
                merkezy = geciciy;
            }
            else
            {
                merkezx = karteyzen_merkezx(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                merkezy = kartezyen_merkezy(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
                yaricap = yaricap_hesapla(noktax[n-1],noktay[n-1],noktax[n-2],noktay[n-2],noktax[n-3],noktay[n-3]);
            }
        }
        al_draw_textf(font2,white,0.0,0.0,0,"Çemberin yaricapi = %f",yaricap);
        al_draw_textf(font2,white,0.0,18,0,"Çemberin merkezi = (%f , %f)",merkezx,merkezy);
        al_draw_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),yaricap*20,green,1.0); //çember çizen hazır fonksiyon
        al_draw_filled_circle(cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),2.5,red);
        al_draw_textf(font,red,cizim_koordinatx(merkezx),cizim_koordinaty(merkezy),0.0,"(%.1f,%.1f)",merkezx,merkezy);
    }

    //x degerlerine göre noktalari sıralama
    float temp;
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(noktax[i]>noktax[j])
            {
                temp = noktax[i];
                noktax[i] = noktax[j];
                noktax[j] = temp;

                temp=noktay[i];
                noktay[i] = noktay[j];
                noktay[j] = temp;
            }
        }
    }

    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(noktax[i] == noktax[j] || noktay[i]>noktay[j])
            {
                temp = noktay[i];
                noktay[i] = noktay[j];
                noktay[j] = temp;
            }
        }
    }

    for(float t=0; t <=n; t += 0.0005)
    {
        if(n>2)
        {
            float px = b_splinex(n,noktax,t);
            float py = b_spliney(n,noktay,t);
            al_draw_filled_circle(cizim_koordinatx(px),cizim_koordinaty(py),0.45,orange);
        }
        //al_put_blended_pixel(px,py,red);
        //al_draw_line(px-t,py,px,py,red,0.1);
    }
    if(n==2)
        al_draw_line(cizim_koordinatx(noktax[0]),cizim_koordinaty(noktay[0]),cizim_koordinatx(noktax[1]),cizim_koordinaty(noktay[1]),orange,1.0);

    printf("\n");
    al_flip_display();
    system("pause");
    //al_rest(10.0); //pencere açik kalma süresi
    al_destroy_display(display);

    return 0;
}
