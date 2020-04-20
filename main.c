#include <stdio.h>
#include <stdlib.h>
#define en 0
#define fr 1
#define de 2
#define pl 3
int main()
{
    //Wczytaj informacje o rozkładzie liter w językach
    FILE *f;
    char langs[4][15] = {
        "lang-en.txt",
        "lang-fr.txt",
        "lang-de.txt",
        "lang-pl.txt"
    };
    float lang_stats[4][26];
    for(int i=0; i<4; i++)
    {
        if ((f = fopen(langs[i], "r"))== NULL)
        {
            printf("Błąd otwierania danych.\n");
            return 1;
        }
        for (int j=0; j<26; j++)
        {
            char buff[20];
            fscanf(f, "%s", buff);
            fgets(buff, 20, f);
            lang_stats[i][j] = strtof(buff, NULL);
        }
    }

    //Oblicz rozkład liter w tekście
    float text_stats[26]= {0};
    if((f=fopen("text-pl","r")) == NULL)
    {
        printf("Błąd otwierania danych.\n");
        return 2;
    }
    char curr_char;
    int sum=0;
    while((curr_char=fgetc(f)) != EOF)
    {
        if(curr_char<91 && curr_char>64)
        {
            text_stats[(int)curr_char-65]+=1;
            sum++;
        }
        else if(curr_char>96 && curr_char<123)
        {
            text_stats[(int)curr_char-97]+=1;
            sum++;
        }
    }
    fclose(f);
    for(int i=0; i<26; i++)
    {
        text_stats[i]=100*text_stats[i]/(float)sum;
    }

    //oblicz odchylenia w poszczególnych językach
    float odchylenie[4]= {0,0,0,0};
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<26; j++)
        {
            if(lang_stats[i][j]>text_stats[j])
            {
                odchylenie[i]+=lang_stats[i][j]-text_stats[j];
            }
            else
            {
                odchylenie[i]-=lang_stats[i][j]-text_stats[j];
            }
        }
    }

    //Wybierz język z najmniejszym odchyleniem
    int min=0;
    for(int i=1; i<4; i++)
    {
        if(odchylenie[i]<odchylenie[min])
        {
            min=i;
        }
    }
    switch(min)
    {
    case en:
        printf("Tekst jest prawdopodobnie napisany w języku Angielskim\n");
        break;
    case de:
        printf("Tekst jest prawdopodobnie napisany w języku Niemieckim\n");
        break;
    case fr:
        printf("Tekst jest prawdopodobnie napisany w języku Francuskim\n");
        break;
    case pl:
        printf("Tekst jest prawdopodobnie napisany w języku Polskim\n");
        break;
    }
    return 0;
}
