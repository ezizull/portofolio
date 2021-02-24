#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define max 2000
#define merah  "\x1B[31m"
#define biru  "\x1B[36m"
#define kuning  "\x1B[33m"

// Menghubungkan ke Database
FILE *fold;
FILE *fcek;
FILE *fnew;

void tulis_kalender();
void tulis_agenda();
void hapus_agenda();

int tahun, int_tahun, cek_tahun = 0, int_bulan, hari, int_tggl, hari_bulan, txt_agenda = 0 ,agenda = 0, pekan = 0, hari_mulai, get_hari, cek_sama = 0;
int tggl_bulan[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *bulan[12]={"januari","februari","maret","april","mei","juni","juli","agustus","september","oktober","november","desember"};
char get_bulan[max], get_agenda[max];
char set_tahun[max][10], set_bulan[max][10], set_agenda[max][10], set_hari[max][10], char_hari[max], char_tahun[max];
char  del_bulan[max], del_agenda[max], comp_bulan[max], comp_agenda[max];
int del_tahun, del_tggl;

int mulai_dari(int tahun){
    int tggl;
    tggl = (((tahun - 1) * 365) + ((tahun - 1) / 4) - ((tahun - 1) / 100) + ((tahun) / 400) + 1) % 7;
    return tggl;
}
void clear_data(){
    fflush(stdin);
    memset(set_tahun, 0, max);
    memset(set_bulan, 0, max);
    memset(set_hari, 0, max);
    memset(set_agenda, 0, max);
    memset(del_bulan, 0, max);
    memset(del_agenda, 0, max);
    memset(char_tahun, 0, max);
    memset(char_hari, 0, max);

}
void tulis_agenda(){
    fold = fopen("database.txt","a+");
    
    if(fold == NULL){
        printf("\n\t| database maintenance");
        return;
    }

    data:
    printf("\n");
    printf("%sdi bulan   : ",biru);
    scanf("%s", get_bulan);
    printf("%sdi tanggal : ",biru);
    scanf("%d", &get_hari);
    printf("%sagenda apa : ",biru);
    scanf("%s", get_agenda);

    if((tahun%4==0 && tahun%100!=0) || tahun%400==0){
        tggl_bulan[1]=29;
    }

    int b, s, h;
    b = 0;
    while(b < 12){
        hari_mulai = tggl_bulan[b];
        h = 1;
        while(h <= hari_mulai){
            if(get_hari == h && strcmp(bulan[b], get_bulan) == 0){
                s = 0;
                break;
            }else if(get_hari != h && strcmp(bulan[b], get_bulan) != 0){
                s++;
            }
            h++;
        }
        if(s == 0){
            break;
        }
        b++;
    }
    if(s > 0){
        printf("\n\n\t| bulan atau tggl tidak tepat :I\n\n");
        s = 0;
        goto data;
    }
    
    fprintf(fold, "%d %s %d %s\n", tahun, get_bulan, get_hari, get_agenda);
    
    fclose(fold);
    agenda = 0;
}
void tulis_kalender(){
    int warna = 0, s = 1, u = 0;
    // s = scan keberapa 
    // u = urutan keberapa
    
    clear_data();

    if((tahun%4==0 && tahun%100!=0) || tahun%400==0){
        tggl_bulan[1]=29;
    }

    hari_mulai = mulai_dari(tahun);

    // masalah sort selesai
    if(cek_tahun != 0){
        fold = fopen("database.txt","r");    

        while(s > 0){
            s = fscanf(fold, "%s %s %s %s", set_tahun[u], set_bulan[u], set_hari[u], set_agenda[u]);
            u++;
        }
            
        s = u;

        int_bulan = 0;
        while (int_bulan<12){
            hari_bulan = tggl_bulan[int_bulan];
            
            printf("\n\n\t%s| %s\n",biru, bulan[int_bulan]);
            printf("\n  %sminggu  senin  selasa  rabu  kamis   jum'at  sabtu\n", biru);

            pekan=0;
            while(pekan<hari_mulai){
                printf("       ");
                pekan++;
            }
  
            hari=1;
            while(hari<=hari_bulan){
                sprintf(char_hari, "%d", hari);
                sprintf(char_tahun, "%d", tahun);

                u = 0;
                while(u < s - 1){
                    if(strcmp(char_hari, set_hari[u]) == 0 && strcmp(bulan[int_bulan], set_bulan[u]) == 0 && strcmp(char_tahun,set_tahun[u]) == 0){
                        cek_sama = 1;
                        break;
                    }
                    else{
                        cek_sama = 0;
                        u++;
                    }
                }

                if(cek_sama == 0){
                    if(warna == 0){
                        printf(" %s%6s",biru, char_hari);
                    }if(warna != 0){
                        printf(" %s%6s",merah, char_hari);
                        warna = 0;
                    }
                }
                else if(cek_sama == 1){
                    printf(" %s%6s",kuning, char_hari);
                    warna = 0;
                }

                if(++pekan>6){
                    printf("\n");
                    warna++;
                    pekan=0;
                }
                hari_mulai = pekan;
                hari++;
            
            }
            u = 0;
            while (u < s - 1){
                sprintf(char_tahun, "%d", tahun);
                if(strcmp(bulan[int_bulan], set_bulan[u]) == 0 && strcmp(char_tahun,set_tahun[u]) == 0){
                    if(txt_agenda == 0){
                        printf("\n\n");
                        printf("%sAgenda:",kuning);
                        printf("\n%s%s   | %s", kuning, set_hari[u], set_agenda[u]);
                        txt_agenda++;
                    }
                    else if(txt_agenda != 0){
                        printf("\n%s%s   | %s", kuning, set_hari[u], set_agenda[u]);
                    }
                }                  
                u++;
            }
            printf("\n");
            txt_agenda = 0;
            int_bulan++;
        }
        fclose(fold);
    }
    else if (cek_tahun == 0){
        int_bulan=0;
        while (int_bulan<12){
            hari_bulan = tggl_bulan[int_bulan];
    
            printf("\n\n\t%s| %s\n",biru, bulan[int_bulan]);
            printf("\n  %sminggu  senin  selasa  rabu  kamis   jum'at  sabtu\n", biru);

            pekan = 0;
            while(pekan<hari_mulai){
                printf("       ");
                pekan++;
            }
            hari=1;
            while(hari<=hari_bulan){
                if(warna == 0){
                printf(" %s%6d",biru, hari);
                }
                if(warna != 0){
                printf(" %s%6d",merah, hari);
                warna = 0;
                }
                if(++pekan>6){
                    printf("\n");
                    warna++;
                    pekan=0;
                }
                hari_mulai = pekan;
                hari++;
            }
            int_bulan++;
        }
        printf("\n");
    }
    cek_tahun = 0;
}
void menu_delete(){
    clear_data();
    printf("\n");
    printf("%sdi tahun   : ", biru);
    scanf("%d", &del_tahun);
    printf("%sdi bulan   : ", biru);
    scanf("%s", del_bulan);
    printf("%sdi tanggal : ", biru);
    scanf("%d", &del_tggl);
    printf("%sagenda apa : ", biru);
    scanf("%s", del_agenda);
}
void hapus_agenda(){
    int s, u, c;

    fold = fopen("database.txt","r");
    fcek = fopen("database.txt","r");
    fnew = fopen("database.tmp","w");

    if(fold == NULL || fnew == NULL){
        printf("\n\t| database maintenance");
        return;
    }

    menu_delete();

    s = 1 , u = 0, c = 0;

    while(s > 0){
        s = fscanf(fold, "%s %s %s %s", set_tahun[u], set_bulan[u], set_hari[u], set_agenda[u]);
        u++;
    }
    fclose(fold);
    
    s = u;
    
    u = 0;
    while(u < s - 1){
        sprintf(char_hari, "%d", del_tggl);
        sprintf(char_tahun, "%d", del_tahun);

        if(strcmp(set_tahun[u], char_tahun) == 0 && strcmp(set_bulan[u], del_bulan) == 0 && strcmp(set_hari[u], char_hari) == 0 && strcmp(set_agenda[u], del_agenda) == 0){
            c = 0;
            break;
        }else{
            c++;
        }
        u++;
    }

    if(c > 0){
        printf("\n\t| tahun, bulannya,\n\t| tanggal, agenda,\n\t| tidak ditemukan :{\n");
        menu_delete();
    }

    while(fscanf(fcek, "%d %s %d %s", &int_tahun, comp_bulan, &int_tggl, comp_agenda) != EOF){        
        if(int_tahun == del_tahun && strcmp(comp_bulan, del_bulan) == 0 && int_tggl == del_tggl && strcmp(comp_agenda, del_agenda) == 0){
            continue;
        }else{
            fprintf(fnew, "%d %s %d %s\n", int_tahun, comp_bulan, int_tggl, comp_agenda);
        }
    }

    fclose(fnew);
    fclose(fcek);
    remove("database.txt");
    rename("database.tmp","database.txt");
}

int main(int argc, char* argv[]){
    int menu;
    ulang:

    clear_data();
    // system("cls");
    system("color B");

    fold = fopen("database.txt","r");

    printf("\n");
    printf("masukan tahun: ");
    scanf("%d", &tahun);

    if(fold == NULL){
        printf("\n\t| agendan kosong");
    }else{
        while(fscanf(fold, "%d %s %s %s", &int_tahun, set_bulan, set_hari, set_agenda) != EOF){
            if (tahun == int_tahun){
                cek_tahun ++;
                break;
            }
        }
    }
    
    fclose(fold);
    
    
    tulis_kalender();

    menu:
    printf("\n\n\n%smenu :v ",biru);
    printf("\n%s1. tulis agenda",biru);
    printf("\n%s2. hapus agenda",biru);
    printf("\n%s3. keluar\n",biru);
    printf("\n%snomor | ",biru);
    scanf("%d", &menu);

    if(menu == 1){
        printf("\n");
        tulis_agenda();
        goto ulang;
    }if(menu == 2){
        printf("\n");
        hapus_agenda();
        goto ulang;
    }if(menu == 3){
        printf("\t| Anda Keluar \n");
        exit(0);
    }

    return 0;    
}
