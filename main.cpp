#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include "evaluator.h"

///pt celelalte ferestre
#define width 1400
#define height 900
#define widthNoi 852
#define heightNoi 480
#define color COLOR(102, 204, 255)
#define colorUmplut COLOR(106,47,131)

///pt evaluare
#include <stdio.h>

using namespace std;
ifstream fin("upload.txt");
ofstream codOut("generareaCodului.txt");
ofstream saveOut("save.txt");
struct bloc
{
    int x,y;
    char tip;
    char var;
    char expresie[200]="";
    bloc *urm, *urmT,*urmF,*ant,*antLoop;
    int nrviz=1;
    char instr[200]="";
    double valo;
};

bloc *Schema[100];
int nrBlocuri=0;

double memo[100];
bool exista[100];

struct
{
    double colorLine,colorBk,colorLineBk,colorFill;
} paleta;

///inceput declarari pt scris in fereastra grafica
#define MAX_INPUT_LEN 80
char inputbuf[MAX_INPUT_LEN];
int input_pos = 0;
///sfarsit declarari pt scris in fereastra grafica

///declarari pt evaluator
char litere[]="QWERTYUIOPASDFGHJKLZXCVBNM";
///final declarari eval


///inceput functii eval
double evaluare(bloc *B);
///final declarari functii eval

///functii grafice
void butonClear();
void ClearDreapta();
void deleteDesenInOut(int x,int y);
void deleteDesenStartStop(int x,int y);
void desenStart(int x,int y);
void butonStart(int &x, int &y);
void desenStop(int x,int y);
void butonStop(int &x, int &y);
void desenInput(int x,int y,char sir[]);
void butonInput(int &x, int &y);
void desenOutput(int x,int y,char sir[]);
void butonOutput(int &x,int &y);
void deleteDesenDec(int x,int y);
void desenDec(int x,int y,char sir[]);
void butonDec(int &x,int &y);
void deleteDesenCalcul(int x,int y);
void desenCalcul(int x,int y,char sir[]);
void butonCalcul(int &x,int &y);
void desenClear();
void desenRun();
void butonRun(int x,int y);
void desenGenerateCode();
void butonGenerateCode(int x, int y);
void desenUploadSiSave();
void casutaUploadSiSave();
void butonUpload(int &contorUpload);
void deleteButonUploadSiSave();
void afisareDinSchema();
char cautaTipul(int x,int y,int &idBloc);

void changecolorPrimavara();
void changecolorVara();
void changecolorToamna();
void changecolorIarna();
void changecolorPaste();
void changecolorHalloween();
void changecolorCraciun();
void initializareEcranCuCuloareaCeruta();
void desenTeme();
void butonTeme(int x, int y);
void desenMeniuTeme(int x, int y);
void butoaneMeniuTeme(int x,int y);
void traseazaLegaturi(int x1, int y1);
void desenMiniMeniu(int x,int y);
void deleteMiniMeniu();
void citireDinGrafica(int x,int y);
bool verificarePixelBloc(int x,int y);
void mentineLegaturi(int idbloc1,int idbloc2);
void mentineLegaturiDecizie(int idbloc1,int idbloc2,int idbloc3);
void stergeLegaturi(int idbloc1,int idbloc2);
void stergeLegaturiDecizie(int idbloc1,int idbloc2,int idbloc3);
///final functii grafice

///inceput functii grafice pt ferestre multiple
void fereastraInterschem();
void desenBackInInterschem();
void coordonateDupaDragAndDropBlocActual(int &x,int &y);
void determinaMouseClick(int &x,int &y);
void determinaMouseClickDreapta(int &x,int &y);
void clearMouseClick();
void creareMainMenu();
void creareButonInterschem();
void creareButonReguli();
void creareButonDespreNoi();
void fereastraReguliInterschem();
void fereastraDespreNoi();
void menu();
///sfarsit functii grafice pt ferestre multiple

void adaugaLaGraf(bloc *B)
{
    switch(B->tip)
    {
    case 's':
    {
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->ant=NULL;
        break;
    }
    case 'f':
    {
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->ant=NULL;
        break;
    }
    case 'i':
    {
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->ant=NULL;
        break;
    }
    case 'o':
    {
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->ant=NULL;
        break;
    }
    case 'c':
    {
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->ant=NULL;
        break;
    }
    case 'd':
    {
        ///evaluarea expresiei
        Schema[nrBlocuri]=B;
        Schema[nrBlocuri]->urm=NULL;
        Schema[nrBlocuri]->urmT=NULL;
        Schema[nrBlocuri]->urmF=NULL;
        Schema[nrBlocuri]->ant=NULL;
        Schema[nrBlocuri]->antLoop=NULL;
        break;
    }
    }
    nrBlocuri++;
}

int gata;
int nrTaburi=0;
int ct;

void afisareCod(bloc *B)
{
    setcolor(paleta.colorLine);
    if(B->tip=='s')
    {
        bgiout<<"#include <bits/stdc++.h>\nusing namespace std;\nint main()\n{\n";

        outstreamxy(1010,130);

        codOut<<"#include <bits/stdc++.h>\nusing namespace std;\nint main()\n{\n";
        nrTaburi+=3;

        for (int i='A'; i<='Z'; i++)
            if (exista[i]!=0)
                ct++;               //numarul de variabile

        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        if (ct!=0)
        {
            bgiout<<"double ";
            outstream();
            codOut<<"double ";
        }

        for (int i='A'; i<='Z'&&ct!=0; i++)
            if (exista[i]!=0)
            {
                if (ct>1)
                {
                    bgiout<<char(i)<<", ";      //daca avem mai multe variabile, le initializam cu virgula intre ele
                    codOut<<char(i)<<", ";      //daca avem mai multe variabile, le initializam cu virgula intre ele
                    outstream();
                    ct--;
                }
                else
                {
                    bgiout<<char(i)<<";\n";
                    codOut<<char(i)<<";\n";
                    gata=1;       //dupa ultima variabila punem ;
                    outstream();
                    ct--;
                }
            }
        afisareCod(B->urm);
    }
    else if(B->tip=='f')
    {
        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        bgiout<<"return 0;\n";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        codOut<<"return 0;\n";
        nrTaburi-=3;
        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        bgiout<<"}\n";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        codOut<<"}\n";
        outstream();
    }

    else if(B->tip=='i')
    {
        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        bgiout<<"cin>>"<<B->var<<";\n";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        codOut<<"cin>>"<<B->var<<";\n";
        if(gata==1)
            outstreamxy(1010,230);
        else
            outstream();
        gata=0;
        afisareDinSchema();
        afisareCod(B->urm);
    }
    else if(B->tip=='o')
    {
        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        bgiout<<"cout<<";
        for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') bgiout<<"!=";
                else if (B->instr[i]=='s') bgiout<<"sin";
                else if (B->instr[i]=='c') bgiout<<"cos";
                else if (B->instr[i]=='l') bgiout<<"log";
                else if (B->instr[i]=='e') bgiout<<"exp";
                else if (B->instr[i]=='a') bgiout<<"abs";
                else if (B->instr[i]=='r') bgiout<<"sqrt";
                else bgiout<<B->instr[i];
        bgiout<<";\n";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        codOut<<"cout<<"<<B->expresie<<";\n";
        if(gata==1)
            outstreamxy(1010,230);
        else
            outstream();
        gata=0;
        afisareCod(B->urm);
    }
    else if(B->tip=='c')
    {
        for (int t=0; t<nrTaburi; t++)
            bgiout<<" ";
        for (int t=0; t<nrTaburi; t++)
            codOut<<" ";
        for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') codOut<<"!=";
                else if (B->instr[i]=='s') codOut<<"sin";
                else if (B->instr[i]=='c') codOut<<"cos";
                else if (B->instr[i]=='l') codOut<<"log";
                else if (B->instr[i]=='e') codOut<<"exp";
                else if (B->instr[i]=='a') codOut<<"abs";
                else if (B->instr[i]=='r') codOut<<"sqrt";
                else codOut<<B->instr[i];
        codOut<<";\n";
        for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') bgiout<<"!=";
                else if (B->instr[i]=='s') bgiout<<"sin";
                else if (B->instr[i]=='c') bgiout<<"cos";
                else if (B->instr[i]=='l') bgiout<<"log";
                else if (B->instr[i]=='e') bgiout<<"exp";
                else if (B->instr[i]=='a') bgiout<<"abs";
                else if (B->instr[i]=='r') bgiout<<"sqrt";
                else bgiout<<B->instr[i];
        bgiout<<";\n";
        if(gata==1)
            outstreamxy(1010,230);
        else
            outstream();
        gata=0;
        afisareCod(B->urm);
    }

    else if (B->tip=='d')
    {
        if (B->antLoop==NULL)
        {
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"if (";
            for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') bgiout<<"!=";
                else if (B->instr[i]=='=') bgiout<<"==";
                else if (B->instr[i]=='s') bgiout<<"sin";
                else if (B->instr[i]=='c') bgiout<<"cos";
                else if (B->instr[i]=='l') bgiout<<"log";
                else if (B->instr[i]=='e') bgiout<<"exp";
                else if (B->instr[i]=='a') bgiout<<"abs";
                else if (B->instr[i]=='r') bgiout<<"sqrt";
                else bgiout<<B->instr[i];
            bgiout<<")\n";
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"{\n";
            nrTaburi+=3;
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"if ("<<B->instr<<")\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"{\n";
            outstream();
            B->nrviz--;
            afisareCod(B->urmT);
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"else\n";
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"{\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"else\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"{\n";
            nrTaburi+=3;
            outstream();
            afisareCod(B->urmF);
            nrTaburi-=3;
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"}\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"}\n";
            outstream();
        }
        else if (B->antLoop!=NULL)
        {
            if (B->nrviz==0) return;
            B->nrviz--;
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"while (";
            for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') bgiout<<"!=";
                else if (B->instr[i]=='=') bgiout<<"==";
                else if (B->instr[i]=='s') bgiout<<"sin";
                else if (B->instr[i]=='c') bgiout<<"cos";
                else if (B->instr[i]=='l') bgiout<<"log";
                else if (B->instr[i]=='e') bgiout<<"exp";
                else if (B->instr[i]=='a') bgiout<<"abs";
                else if (B->instr[i]=='r') bgiout<<"sqrt";
                else bgiout<<B->instr[i];
            bgiout<<")\n";
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"{\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"while (";
            for (int i=0;i<strlen(B->instr);i++)
                if (B->instr[i]=='#') codOut<<"!=";
                else if (B->instr[i]=='=') codOut<<"==";
                else if (B->instr[i]=='s') codOut<<"sin";
                else if (B->instr[i]=='c') codOut<<"cos";
                else if (B->instr[i]=='l') codOut<<"log";
                else if (B->instr[i]=='e') codOut<<"exp";
                else if (B->instr[i]=='a') codOut<<"abs";
                else if (B->instr[i]=='r') codOut<<"sqrt";
                else codOut<<B->instr[i];
            codOut<<")\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"{\n";
            outstream();
            nrTaburi+=3;
            afisareCod(B->urmT);
            nrTaburi-=3;
            for (int t=0; t<nrTaburi; t++)
                bgiout<<" ";
            bgiout<<"}\n";
            for (int t=0; t<nrTaburi; t++)
                codOut<<" ";
            codOut<<"}\n";
            B->valo=evaluare(B);
            afisareCod(B->urmF);
            outstream();
        }
    }
}

void afisareSchemaActuala()
{
    int idUrmT,idUrmF,idUrm,idLoop;
    for (int i=0; i<nrBlocuri; i++)
        if (Schema[i]->tip=='s')
        {
            desenStart(Schema[i]->x,Schema[i]->y );
        }
        else if (Schema[i]->tip=='f')
        {
            desenStop(Schema[i]->x,Schema[i]->y );
        }
        else if (Schema[i]->tip=='i')
        {
            desenInput(Schema[i]->x,Schema[i]->y,Schema[i]->instr);
        }
        else if (Schema[i]->tip=='o')
        {
            desenOutput(Schema[i]->x,Schema[i]->y,Schema[i]->instr );
        }
        else if (Schema[i]->tip=='c')
        {
            desenCalcul(Schema[i]->x,Schema[i]->y,Schema[i]->instr );
        }
        else if (Schema[i]->tip=='d')
        {
            desenDec(Schema[i]->x,Schema[i]->y,Schema[i]->instr );
        }
    for (int i=0; i<nrBlocuri; i++)
    {
        if (Schema[i]->tip=='d')
        {
            if (Schema[i]->urmT!=NULL)
            {
                cautaTipul(Schema[i]->urmT->x,Schema[i]->urmT->y,idUrmT);
                mentineLegaturi(i,idUrmT);
            }
            if (Schema[i]->urmF!=NULL)
            {
                cautaTipul(Schema[i]->urmF->x,Schema[i]->urmF->y,idUrmF);
                mentineLegaturi(i,idUrmF);
            }
        }
        else
        {
            if (Schema[i]->urm!=NULL)
            {
                cautaTipul(Schema[i]->urm->x,Schema[i]->urm->y,idUrm);
                mentineLegaturi(i,idUrm);
            }
        }
    }
}

void afisareDinSchema()
{
    cout<<"Schema curenta este: \n";
    for (int i=0; i<nrBlocuri; i++)
    {
        cout<<Schema[i]->tip<<" "<<Schema[i]->x<<" "<<Schema[i]->y<<" "<<Schema[i]->instr<<'\n';
    }
    cout<<"Schema curenta finish! \n";
}

void citireDinUpload()
{
    int m,n;
    int idbloc1,idbloc2,idbloc3,idblocLoop;
    fin>>n>>m;
    for (int i=0; i<n; i++)
    {
        bloc *B=new bloc;
        fin>>B->tip>>B->x>>B->y;
        adaugaLaGraf(B);
        if (Schema[i]->tip=='i')
        {
            fin>>Schema[i]->instr;
            Schema[i]->var=Schema[i]->instr[0];
            exista[Schema[i]->var]=1;
        }
        else if (Schema[i]->tip=='c')
        {
            fin>>Schema[i]->instr;
            strcpy(Schema[i]->expresie,Schema[i]->instr+2);
            exista[Schema[i]->instr[0]]=1;
        }
        else if (Schema[i]->tip=='o')
        {
            fin>>Schema[i]->instr;
            strcpy(Schema[i]->expresie,Schema[i]->instr);
        }
        else if (Schema[i]->tip=='d')
        {
            fin>>Schema[i]->instr;
            strcpy(Schema[i]->expresie,Schema[i]->instr);
        }
    }
    for (int i=0; i<m; i++) ///m-ul conteaza de ce ai in fisier!! daca ai un if, una in minus si la fel pt loop
    {
        fin>>idbloc1>>idbloc2;///mai trebuie facute niste verif pt decizie, sunt altfel acolo mentine legaturile
        if (idbloc1==-1&&idbloc2==-1)
        {
            fin>>idbloc1>>idbloc2;
            Schema[idbloc1]->urm=Schema[idbloc2];
            Schema[idbloc2]->antLoop=Schema[idbloc1];
            mentineLegaturi(idbloc1,idbloc2);
        }
        else
        {
            if (Schema[idbloc1]->tip=='d')
            {
                Schema[idbloc1]->urmT=Schema[idbloc2];
                Schema[idbloc2]->ant=Schema[idbloc1];
                fin>>idbloc1>>idbloc3;
                Schema[idbloc1]->urmF=Schema[idbloc3];
                Schema[idbloc3]->ant=Schema[idbloc1];
                mentineLegaturi(idbloc1,idbloc2);
                mentineLegaturi(idbloc1,idbloc3);
            }
            else
            {
                Schema[idbloc1]->urm=Schema[idbloc2];
                Schema[idbloc2]->ant=Schema[idbloc1];
                mentineLegaturi(idbloc1,idbloc2);
            }
        }
    }
    fin.close();
}

int main()
{
    menu();
    return 0;
}

void coordonateDupaDragAndDropBlocActual(int &x,int &y)
{
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        x=mousex();
        y=mousey();
    }
}

void desenBackInInterschem()
{
    int poly[10]= {900,10,950,10,950,50,900,50,900,10};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << "back";
    outstreamxy(905,20);
}

bool verificarePixelBloc(int x,int y)
{
    if (getpixel(x,y)==paleta.colorFill||getpixel(x,y)==paleta.colorLine) return 1;
    return 0;
}

void deleteMiniMeniu()
{
    setcolor(paleta.colorBk);
    for (int i=0; i<=106; i++)
        line(0,i,56,i);
    setcolor(paleta.colorLineBk);
    for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
        line(0,i,1000,i);
}

void desenMiniMeniu(int x,int y)
{
    int poly[10]= {x,y,x+50,y,x+50,y+100,x,y+100,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << "delete" << endl;
    outstreamxy(x+1,y+1);
    bgiout <<"content" << endl;
    outstreamxy(x+1,y+21);
    bgiout << "binding" << endl;
    outstreamxy(x+1,y+41);
    bgiout << "back" << endl;
    outstreamxy(x+1,y+61);
    bgiout << "move" << endl;
    outstreamxy(x+1,y+81);
    line(x,y+20,x+50,y+20);
    line(x,y+40,x+50,y+40);
    line(x,y+60,x+50,y+60);
    line(x,y+80,x+50,y+80);
}

void citireDinGrafica(int x,int y)
{
    int the_end = 0;
    char c;
    setcolor(paleta.colorLine);
    do
    {
        outtextxy (x,y, inputbuf);
        c = getch();
        switch (c)
        {
        case 8: /* backspace */
            if (input_pos)
            {
                input_pos--;
                inputbuf[input_pos] = 0;
            }
            break;
        case 13: /* return */
            the_end = 1;
            break;
        case 27: /* Escape = Abort */
            inputbuf[0] = 0;
            the_end = 1;
            break;
        default:
            if (input_pos < MAX_INPUT_LEN-1 && c >= ' ' && c <= '~')
            {
                inputbuf[input_pos] = c;
                input_pos++;
                inputbuf[input_pos] = 0;
            }
        }
    }
    while (!the_end);
}

char cautaTipul(int x,int y,int &idBloc)
{
    idBloc=0;
    for (int i=0; i<nrBlocuri; i++)
    {
        idBloc=i;
        if (Schema[i]->tip=='f' && x>=Schema[i]->x && x<=Schema[i]->x+60 && y>=Schema[i]->y && y<=Schema[i]->y+60) return 102;
        else if (Schema[i]->tip=='s' && x>=Schema[i]->x && x<=(60+(Schema[i]->x)) && y>=Schema[i]->y && y<=(60+(Schema[i]->y))) return 115;
        else if (Schema[i]->tip=='i' && x>=Schema[i]->x && x<=Schema[i]->x+90 && y>=Schema[i]->y && y<=Schema[i]->y+60) return 105;
        else if (Schema[i]->tip=='o' && x>=Schema[i]->x && x<=Schema[i]->x+90 && y>=Schema[i]->y && y<=Schema[i]->y+60) return 111;
        else if (Schema[i]->tip=='d' && x>=Schema[i]->x-60 && x<=Schema[i]->x+60 && y>=Schema[i]->y && y<=Schema[i]->y+60) return 100;
        else if (Schema[i]->tip=='c' && x>=Schema[i]->x && x<=Schema[i]->x+90 && y>=Schema[i]->y && y<=Schema[i]->y+60) return 99;
    }
    //return -1;
}

void deleteBloc(int x,int y)
{
    afisareDinSchema();
    ClearDreapta();
    char tip;
    int idBloc,idAntLoop,idUrmT,idUrmF,idAnt,idUrm;
    tip=cautaTipul(x,y,idBloc);
    if (idBloc==0)
    {
        showerrorbox("Error! Not possible!");
        return;
    }
    if (tip=='d')
    {
        deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
        if(Schema[idBloc]->antLoop!=NULL)
        {
            cautaTipul(Schema[idBloc]->antLoop->x,Schema[idBloc]->antLoop->y,idAntLoop);
            Schema[idBloc]->antLoop->urm=NULL;
            stergeLegaturi(idAntLoop,idBloc);
        }
        if(Schema[idBloc]->urmT!=NULL)
        {
            cautaTipul(Schema[idBloc]->urmT->x,Schema[idBloc]->urmT->y,idUrmT);
            Schema[idBloc]->urmT->ant=NULL;
            stergeLegaturi(idBloc,idUrmT);
        }
        if(Schema[idBloc]->urmF!=NULL)
        {
            cautaTipul(Schema[idBloc]->urmF->x,Schema[idBloc]->urmF->y,idUrmF);
            Schema[idBloc]->urmF->ant=NULL;
            stergeLegaturi(idBloc,idUrmF);
        }
        if(Schema[idBloc]->ant!=NULL)
        {
            cautaTipul(Schema[idBloc]->ant->x,Schema[idBloc]->ant->y,idAnt);
            Schema[idBloc]->ant->urm=NULL;
            stergeLegaturi(idAnt,idBloc);
        }
        delete Schema[idBloc];
        for(int i=idBloc ; i<nrBlocuri-1 ; i++)
            Schema[i]=Schema[i+1];
        nrBlocuri--;
        afisareDinSchema();
    }
    else
    {
        switch (tip)
        {
        case 'f':
        {
            deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
            break;
        }
        case 'i':
        {
            deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
            break;
        }
        case 'o':
        {
            deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
            break;
        }
        case 'c':
        {
            deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
            break;
        }
        }
        if(Schema[idBloc]->ant!=NULL)
        {
            cautaTipul(Schema[idBloc]->ant->x,Schema[idBloc]->ant->y,idAnt);
            if (Schema[idAnt]->tip=='d')
            {
                if (Schema[idAnt]->urmT==Schema[idBloc])
                    Schema[idBloc]->ant->urmT=NULL;
                else Schema[idBloc]->ant->urmF=NULL;
            }
            else Schema[idBloc]->ant->urm=NULL;
            stergeLegaturi(idAnt,idBloc);
        }
        if(Schema[idBloc]->urm!=NULL)
        {
            cautaTipul(Schema[idBloc]->urm->x,Schema[idBloc]->urm->y,idUrm);
            if (Schema[idUrm]->tip=='d')
            {
                if (Schema[idUrm]->antLoop==Schema[idBloc])
                    Schema[idUrm]->antLoop=NULL;
                else Schema[idUrm]->ant=NULL;
            }
            else Schema[idBloc]->urm->ant=NULL;
            stergeLegaturi(idBloc,idUrm);
        }

        delete Schema[idBloc];
        for(int i=idBloc ; i<nrBlocuri-1 ; i++)
            Schema[i]=Schema[i+1];
        nrBlocuri--;
        afisareDinSchema();
    }
}

void introduVariabila(int x,int y)
{
    setcolor(paleta.colorLine);
    ClearDreapta();
    char tip;
    int idBloc=-1;
    tip=(cautaTipul(x,y,idBloc));
    switch(tip)
    {
    case 's':
    {

        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"De ce introduci aici?\nMai incearca alte blocuri!\n";
        outstreamxy(1100,130);
        break;
    }
    case 'f':
    {
        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"Nici aici nu poti!\nMai incearca alte blocuri!\n";
        outstreamxy(1100,130);
        break;
    }
    case 'i':
    {
        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);

        input_pos = 0;
        strcpy(inputbuf,"");
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"Give variable: ";
        outstreamxy(1100,130);

        setbkcolor(paleta.colorFill);
        setcolor(paleta.colorFill);
        setbkcolor(paleta.colorBk);
        citireDinGrafica(1100,150);
        desenInput(Schema[idBloc]->x,Schema[idBloc]->y,inputbuf);

        Schema[idBloc]->var=inputbuf[0];
        strcpy(Schema[idBloc]->instr,inputbuf);
        exista[Schema[idBloc]->var]=1;
        break;
    }
    case 'o':
    {

        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);
        input_pos = 0;
        strcpy(inputbuf,"");
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"What to print?";
        outstreamxy(1100,130);
        setbkcolor(paleta.colorBk);
        setbkcolor(paleta.colorBk);
        citireDinGrafica(1100,150);
        desenOutput(Schema[idBloc]->x,Schema[idBloc]->y,inputbuf);

        strcpy(Schema[idBloc]->expresie,inputbuf);
        strcpy(Schema[idBloc]->instr,inputbuf);
        break;
    }
    case 'c':
    {
        int eroare=0;
        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);

        input_pos = 0;
        strcpy(inputbuf,"");
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"What to assign?";
        outstreamxy(1100,130);
        setbkcolor(paleta.colorBk);

        citireDinGrafica(1100,150);
        desenCalcul(Schema[idBloc]->x,Schema[idBloc]->y,inputbuf);
        strcpy(Schema[idBloc]->instr,inputbuf);
        strcpy(Schema[idBloc]->expresie,inputbuf+2);
        exista[Schema[idBloc]->instr[0]]=1;

        break;
    }
    case 'd':
    {
        setcolor(paleta.colorBk);
        for (int i=130; i<=200; i++)
            line(1100,i,1500,i);
        input_pos = 0;
        strcpy(inputbuf,"");
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        settextstyle(10,HORIZ_DIR,2);
        bgiout<<"Wheel of Fortune";
        outstreamxy(1100,130);
        setbkcolor(paleta.colorBk);
        citireDinGrafica(1100,150);
        desenDec(Schema[idBloc]->x,Schema[idBloc]->y,inputbuf);
        strcpy(Schema[idBloc]->instr,inputbuf);
        strcpy(Schema[idBloc]->expresie,inputbuf);
        break;
    }
    }
}

void moveBloc(int &x,int &y,int mutare)
{
    char tip;
    bloc *urma=new bloc;
    bloc *urmaT=new bloc;
    bloc *urmaF=new bloc;
    bloc *ante=new bloc;
    bloc *anteLoop= new bloc;
    int x1,x2,y1,y2;
    int idBloc,idBlocDest,idBlocAnt,idBlocAnte, idBlocDest1,idBlocDest2;
    tip=cautaTipul(x,y,idBloc);
    if (mutare==0)
    {
        switch(tip)
        {
        case 's':
        {
            if (x>Schema[idBloc]->x && x<(60+(Schema[idBloc]->x)) && y>Schema[idBloc]->y && y<(60+(Schema[idBloc]->y)))
            {
                if(Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else
                {
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }

            }
            break;
        }
        case 'f':
        {
            if (x>Schema[idBloc]->x && x<(60+(Schema[idBloc]->x)) && y>Schema[idBloc]->y && y<(60+(Schema[idBloc]->y)))
            {
                if(Schema[idBloc]->ant!=NULL)
                {
                    ante=Schema[idBloc]->ant;
                    //cout<<ante->tip<<'\n';
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else
                {
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }

            }
            break;
        }
        case 'i':
        {
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {

                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else
                {
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
            }
            break;
        }
        case 'o':
        {
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;

                    cautaTipul(urma->x,urma->y,idBlocDest);

                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm==NULL)
                {
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
            }
            break;
        }
        case 'c':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urm==NULL)
                {

                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                }

            }
            break;
        }
        case 'd':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x-60 && x<Schema[idBloc]->x+60 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    ante=Schema[idBloc]->ant;
                    anteLoop=Schema[idBloc]->antLoop;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnt,idBloc);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnt,idBloc);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    ante=Schema[idBloc]->ant;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnt,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    anteLoop=Schema[idBloc]->antLoop;

                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturi(idBlocAnt,idBloc);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturi(idBlocAnt,idBloc);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF==NULL)
                {
                    ante=Schema[idBloc]->ant;

                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF==NULL)
                {
                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    anteLoop=Schema[idBloc]->antLoop;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    x=x+1;
                    y=y+1;
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
            }
            break;
        }
        }
    }
    else
    {
        switch(tip)
        {
        case 's':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<(60+(Schema[idBloc]->x)) && y>Schema[idBloc]->y && y<(60+(Schema[idBloc]->y)))
            {
                if(Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonStart(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else
                {
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonStart(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }

            }
            break;
        }
        case 'f':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<(60+(Schema[idBloc]->x)) && y>Schema[idBloc]->y && y<(60+(Schema[idBloc]->y)))
            {
                if(Schema[idBloc]->ant!=NULL)
                {
                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonStop(x,y );
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else
                {
                    deleteDesenStartStop(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonStop(x,y );
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }

            }
            break;
        }
        case 'i':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonInput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {

                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonInput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonInput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else
                {
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonInput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
            }
            break;
        }
        case 'o':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonOutput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;

                    cautaTipul(urma->x,urma->y,idBlocDest);

                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonOutput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonOutput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm==NULL)
                {
                    deleteDesenInOut(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonOutput(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
            }
            break;
        }
        case 'c':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x && x<Schema[idBloc]->x+90 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    ante=Schema[idBloc]->ant;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    stergeLegaturi(idBlocAnt,idBloc);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonCalcul(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if(Schema[idBloc]->ant==NULL && Schema[idBloc]->urm!=NULL)
                {
                    urma=Schema[idBloc]->urm;
                    cautaTipul(urma->x,urma->y,idBlocDest);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonCalcul(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urm==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBloc,idBlocDest);
                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonCalcul(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                    mentineLegaturi(idBloc,idBlocDest);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urm==NULL)
                {

                    deleteDesenCalcul(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonCalcul(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                }

            }
            break;
        }
        case 'd':
        {
            determinaMouseClick(x,y);
            if (x>Schema[idBloc]->x-60 && x<Schema[idBloc]->x+60 && y>Schema[idBloc]->y && y<Schema[idBloc]->y+60)
            {
                if(Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    ante=Schema[idBloc]->ant;
                    anteLoop=Schema[idBloc]->antLoop;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnt,idBloc);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnt,idBloc);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    ante=Schema[idBloc]->ant;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnt,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF==NULL)
                {
                    ante=Schema[idBloc]->ant;
                    anteLoop=Schema[idBloc]->antLoop;

                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturi(idBlocAnt,idBloc);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturi(idBlocAnt,idBloc);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
                else if (Schema[idBloc]->ant!=NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF==NULL)
                {
                    ante=Schema[idBloc]->ant;

                    cautaTipul(ante->x,ante->y,idBlocAnt);
                    stergeLegaturi(idBlocAnt,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturi(idBlocAnt,idBloc);
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT==NULL && Schema[idBloc]->antLoop==NULL && Schema[idBloc]->urmF==NULL)
                {
                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;
                }
                else if (Schema[idBloc]->ant==NULL && Schema[idBloc]->urmT!=NULL && Schema[idBloc]->antLoop!=NULL && Schema[idBloc]->urmF!=NULL)
                {
                    urmaT=Schema[idBloc]->urmT;
                    urmaF=Schema[idBloc]->urmF;
                    anteLoop=Schema[idBloc]->antLoop;

                    x1=urmaT->x;
                    y1=urmaT->y;
                    x2=urmaF->x;
                    y2=urmaF->y;

                    cautaTipul(x1,y1,idBlocDest1);
                    cautaTipul(x2,y2,idBlocDest2);
                    cautaTipul(anteLoop->x,anteLoop->y,idBlocAnte);
                    stergeLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    stergeLegaturi(idBlocAnte,idBloc);

                    deleteDesenDec(Schema[idBloc]->x,Schema[idBloc]->y);
                    butonDec(x,y);
                    Schema[idBloc]->x=x;
                    Schema[idBloc]->y=y;

                    mentineLegaturiDecizie(idBloc,idBlocDest1,idBlocDest2);
                    mentineLegaturi(idBlocAnte,idBloc);
                }
            }
            break;
        }
        }
    }
}

void butonUpload(int &contorUpload)
{
    if (contorUpload==1)
    {
        ClearDreapta();
        citireDinUpload();
        afisareDinSchema();
        afisareSchemaActuala();
        deleteButonUploadSiSave();
        settextstyle(10,HORIZ_DIR,3);
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        bgiout<<"Scheme uploaded succesfully!";
        outstreamxy(1050,130);
        contorUpload=0;
    }

}

void butonSave(int &contorUpload)
{
    int nrLegaturi=0;
    int idUrmT,idUrmF,idUrm,idLoop;
    if (contorUpload==1)
    {
        ClearDreapta();
        deleteButonUploadSiSave();
        if (nrBlocuri==0)
        {
            settextstyle(10,HORIZ_DIR,3);
            setcolor(paleta.colorLine);
            setbkcolor(paleta.colorBk);
            bgiout<<"Error! There is no scheme\nto save!";
            outstreamxy(1050,130);
        }
        else
        {
            settextstyle(10,HORIZ_DIR,3);
            setcolor(paleta.colorLine);
            setbkcolor(paleta.colorBk);
            bgiout<<"Scheme saved succesfully!";
            outstreamxy(1050,130);
            saveOut<<nrBlocuri<<' ';
            ///aici e numai pt numararea legaturilor
            for (int i=0; i<nrBlocuri; i++)
            {
                if (Schema[i]->tip=='d')
                {
                    if (Schema[i]->urmT!=NULL)
                    {
                        nrLegaturi++;
                    }
                    if (Schema[i]->urmF!=NULL)
                    {
                        nrLegaturi++;
                    }
                    if (Schema[i]->urmT!=NULL&&Schema[i]->urmF!=NULL) nrLegaturi--;
                }
                else
                {
                    if (Schema[i]->urm!=NULL)
                    {
                        if (Schema[i]->urm->tip=='d'&&Schema[i]->urm->antLoop==Schema[i])
                        {
                            nrLegaturi++;
                        }
                        else
                        {
                            nrLegaturi++;
                        }

                    }
                }
            }
            saveOut<<nrLegaturi<<'\n';
            for (int i=0; i<nrBlocuri; i++)
            {
                saveOut<<Schema[i]->tip<<" "<<Schema[i]->x<<" "<<Schema[i]->y<<" ";
                if (Schema[i]->tip=='i')
                {
                    saveOut<<Schema[i]->instr;
                }
                else if (Schema[i]->tip=='c')
                {
                    saveOut<<Schema[i]->instr;
                }
                else if (Schema[i]->tip=='o')
                {
                    saveOut<<Schema[i]->instr;
                }
                else if (Schema[i]->tip=='d')
                {
                    saveOut<<Schema[i]->instr;
                }
                saveOut<<'\n';
            }
            ///si pt afisarea efectiva a leg:
            for (int i=0; i<nrBlocuri; i++)
            {
                if (Schema[i]->tip=='d')
                {
                    if (Schema[i]->urmT!=NULL)
                    {
                        cautaTipul(Schema[i]->urmT->x,Schema[i]->urmT->y,idUrmT);
                        saveOut<<i<<" "<<idUrmT<<'\n';
                    }
                    if (Schema[i]->urmF!=NULL)
                    {
                        cautaTipul(Schema[i]->urmF->x,Schema[i]->urmF->y,idUrmF);
                        saveOut<<i<<" "<<idUrmF<<'\n';
                    }
                }
                else
                {
                    if (Schema[i]->urm!=NULL)
                    {
                        if (Schema[i]->urm->tip=='d'&&Schema[i]->urm->antLoop==Schema[i])
                        {
                            cautaTipul(Schema[i]->urm->x,Schema[i]->urm->y,idUrm);
                            saveOut<<-1<<" "<<-1<<'\n';
                            saveOut<<i<<" "<<idUrm<<'\n';
                        }
                        else
                        {
                            cautaTipul(Schema[i]->urm->x,Schema[i]->urm->y,idUrm);
                            saveOut<<i<<" "<<idUrm<<'\n';
                        }

                    }
                }
            }
            contorUpload=0;
        }
    }
}

void deleteButonUploadSiSave()
{
    setcolor(paleta.colorBk);
    for (int i=1048; i<=1252; i++)
        line(i,138,i,262);
}

void fereastraInterschem()
{
    int x,y,existaStart=0;
    int idbloc;
    int contorTeme=0,contorUpload=0;
    bool backButton=0,miniMeniu=0;
    int coordx,coordy;
    bool pressYes=0,pressRun=0;
    int xBlocActual,yBlocActual;

    initwindow(1500,750,"InterSchem");
    paleta.colorBk=COLOR(9,9,78);//fundalul basic
    paleta.colorLineBk=COLOR(255,69,0); //dungile de pe ecran
    setcolor(paleta.colorBk);
    paleta.colorFill=COLOR(150, 75, 132);
    paleta.colorLine=COLOR(204, 196, 202);
    initializareEcranCuCuloareaCeruta();

    for(long long i=0 ; i<9223372036854775807 && backButton==0; i++)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            line(0,0,0,1);
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(x>80 && x<140 && y>10 && y<70 && existaStart==0)
        {
            butonStart(x,y);
            existaStart++;
            xBlocActual=x;
            yBlocActual=y;
            bloc *B=new bloc;
            B->x=x;
            B->y=y;
            B->tip='s';
            adaugaLaGraf(B);
            afisareSchemaActuala();
        }

        else if (x>200 && x<260 && y>10 && y<70 && existaStart!=0)
        {
            xBlocActual=x;
            yBlocActual=y;
            butonStop(x,y);
            bloc *B=new bloc;
            B->x=x;
            B->y=y;
            B->tip='f';
            adaugaLaGraf(B);
            afisareSchemaActuala();
        }

        else if((x>1000 && x<1250) && (y>40 && y<80))
        {
            int nuexistalegatura=0;
            ClearDreapta();
            if (nrBlocuri==0||pressRun==0) showerrorbox("Schema nu exista, nu este completa\nsau nu a fost mai intai rulata!");
            else
            {
                bloc *p= new bloc;
                p=Schema[0];
                while(p!=NULL && p->tip!='f')
                {
                    if(p->urm==NULL)
                    {
                        showerrorbox("Schema nu exista\nsau nu este completa!");
                        nuexistalegatura=1;
                    }
                    p=p->urm;

                }
                if(nuexistalegatura==0)
                {
                    afisareSchemaActuala();
                    butonGenerateCode(x,y);
                    pressRun=0;
                }
            }
        }
        else if (x>1250 && x<1500 && y>40 && y<80&&contorUpload==0)
        {
            ClearDreapta();
            afisareDinSchema();
            casutaUploadSiSave();
            contorUpload=1;
        }
        else if (x>1250 && x<1500 && y>40 && y<80&&contorUpload==1)
        {
            deleteButonUploadSiSave();
            contorUpload=0;
        }
        else if (x>1050 && x<1250 && y>140 && y<200&&contorUpload==1)
        {
            if (nrBlocuri!=0)
            {
                showerrorbox("Aveti deja alta schema pusa aici!");
            }
            else
            {
                butonUpload(contorUpload);
                existaStart=1;
            }
        }

        else if (x>1050 && x<1250 && y>200 && y<260)
        {
            butonSave(contorUpload);
        }

        else if((x>320 && x<420) && (y>10 && y<70) && existaStart!=0)
        {
            xBlocActual=x;
            yBlocActual=y;
            bloc *B=new bloc;
            B->x=x;
            B->y=y;
            B->tip='i';
            strcpy(B->instr,"Input");
            adaugaLaGraf(B);
            butonInput(x,y);
            afisareSchemaActuala();
        }

        else if((x>450 && x<550) && (y>10 && y<70) && existaStart!=0)
        {
            xBlocActual=x;
            yBlocActual=y;
            bloc *B=new bloc;
            ///B->instr= este ceea ce se introduce de la tastatura
            B->x=x;
            B->y=y;
            B->tip='o';
            strcpy(B->instr,"Output");
            adaugaLaGraf(B);
            butonOutput(x,y);
            afisareSchemaActuala();
        }

        else if((x>620 && x<740) && (y>10 && y<70) && existaStart!=0)
        {
            xBlocActual=x;
            yBlocActual=y;
            bloc *B=new bloc;
            B->x=x;
            B->y=y;
            B->tip='d';
            strcpy(B->instr,"Dec");
            adaugaLaGraf(B);
            butonDec(x,y);
            afisareSchemaActuala();
        }

        else if((x>750 && x<840) && (y>10 && y<70) && existaStart!=0)
        {
            xBlocActual=x;
            yBlocActual=y;
            bloc *B=new bloc;
            B->x=x;
            B->y=y;
            B->tip='c';
            strcpy(B->instr,"Calcul");
            adaugaLaGraf(B);
            butonCalcul(x,y);
            afisareSchemaActuala();
        }

        else if((x>1250 && x<1500) && (y>0 && y<40))
        {
            butonRun(x,y);
            delay(3000);
            afisareSchemaActuala();
            pressRun=1;
        }

        else if((x>1000 && x<1500) && (y>80 && y<120) && contorTeme==0)
        {
            ClearDreapta();
            butonTeme(x,y);
            contorTeme=1;
        }

        else if((x>1000 && x<1500) && (y>80 && y<120) && contorTeme==1)
        {
            ClearDreapta();
            contorTeme=0;
        }
        else if(x>1100 && x<1300 && y>200 && y<550 && contorTeme==1)
        {
            butoaneMeniuTeme(x,y);
            if (nrBlocuri!=0) afisareSchemaActuala();
            ClearDreapta();
            contorTeme=0;
        }

        else if((x>1000 && x<1250) && (y>0 && y<40))
        {
            butonClear();
            existaStart=0;
        }

        else if (x>900&&x<950&&y>10&&y<50) backButton=1;

        else if (x>5&&x<55&&y>5&&y<105)
        {
            if (x>5&&x<55&&y>=5&&y<=25)
            {
                ClearDreapta();
                setbkcolor(paleta.colorBk);
                setcolor(paleta.colorLine);
                settextstyle(10,HORIZ_DIR,2);
                bgiout<<"Delete. Press yes.\n";
                outstreamxy(1100,130);
                bgiout<<"YES";
                outstreamxy(1100,150);
                cautaTipul(xBlocActual,yBlocActual,idbloc);
                if (Schema[idbloc]->urm!=NULL) moveBloc(Schema[idbloc]->urm->x,Schema[idbloc]->urm->y,0);
                pressYes=1;
            }
            else if (x>5&&x<55&&y>25&&y<=45) introduVariabila(coordx,coordy);
            else if (x>5&&x<55&&y>46&&y<=65) traseazaLegaturi(coordx,coordy);
            else if (x>5&&x<55&&y>66&&y<=85)
            {
                deleteMiniMeniu();
                miniMeniu=0;
            }
            else if (x>5&&x<55&&y>86&&y<=105)
            {
                moveBloc(coordx,coordy,1);
                afisareSchemaActuala();
            }
        }

        else if (y>85&&x<1000)
        {
            coordx=x;
            coordy=y;
            if (y>80&&x<1000&&verificarePixelBloc(x,y)==1&&miniMeniu==0)
            {
                desenMiniMeniu(0,0);
                miniMeniu=1;
            }
        }
        else if (y>85&&x>1000&&x<1500&&pressYes==1)
        {
            deleteBloc(coordx,coordy);
            pressYes=0;
        }
    }
    if (backButton==1)
    {
        butonClear();
        closegraph(CURRENT_WINDOW);
    }
    cout<<"click terminat linia 1981";
}

void determinaMouseClick(int &x,int &y)
{
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        line(0,0,0,1);
    }
    getmouseclick(WM_LBUTTONDOWN,x,y);
}

void clearMouseClick()
{
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        line(0,0,0,1);
    }
    clearmouseclick(WM_LBUTTONDOWN);

    while (!ismouseclick(WM_RBUTTONDOWN))
    {
        line(0,0,0,1);
    }
    clearmouseclick(WM_RBUTTONDOWN);
}

void creareMainMenu()
{
    int w,h;
    int x,y;
    x=480,y=150;
    w=400;
    h=75;
    setcolor(color);
    setlinestyle(SOLID_LINE, THICK_WIDTH, 4);
    setfillstyle(SOLID_FILL, colorUmplut);
    bar3d(x,y,x+w,y+h,20,1);
}

void creareButonInterschem()
{
    int w,h;
    int x,y;
    x=480,y=300;
    w=400;
    h=75;
    setcolor(color);
    setlinestyle(SOLID_LINE, THICK_WIDTH, 4);
    setfillstyle(SOLID_FILL, colorUmplut);
    bar3d(x,y,x+w,y+h,20,1);
}

void creareButonReguli()
{
    int w,h;
    int x,y;
    x=180,y=500;
    w=300;
    h=100;
    setcolor(color);
    setlinestyle(SOLID_LINE, THICK_WIDTH, 4);
    setfillstyle(SOLID_FILL, colorUmplut);
    bar3d(x,y,x+w,y+h,20,1);
}

void creareButonDespreNoi()
{
    int w,h;
    int x,y;
    x=800,y=500;
    w=300;
    h=100;
    setcolor(color);
    setlinestyle(SOLID_LINE, THICK_WIDTH, 4);
    setfillstyle(SOLID_FILL, colorUmplut);
    bar3d(x,y,x+w,y+h,20,1);
}

void fereastraReguliInterschem()
{
    int x,y;
    initwindow(widthNoi,heightNoi,"ReguliInterSchem");

    void* test_image = new char[imagesize(0, 0,widthNoi,heightNoi )];
    readimagefile("fundalReguli.jpg",0,0, widthNoi,heightNoi);
    getimage(0,0,width,height,test_image);

    setcolor(WHITE);
    setbkcolor(COLOR(31,5,16));
    settextstyle(10,HORIZ_DIR, 5);
    bgiout<<"Reguli InterSchem\n";
    outstreamxy(200,15);
    settextstyle(10,HORIZ_DIR,1);
    bgiout<<"1. Blocul de start trebuie pus intotdeauna primul si \npoate fi pus o singura data.\n";
    bgiout<<"2. Butonul de Run trebuie apasat inainte de Generate Code.\n";
    bgiout<<"3. Trebuie completata schema inainte de a rula/genera codul \n(obligatoriu un stop la final pt a nu se termina programul).\n";
    bgiout<<"4. Pentru salvarea unei scheme, este necesar macar un bloc.\n";
    bgiout<<"5. Variabilele trebuie sa fie mereu litere mari si trebuie puse\nin blocuri individuale de Input.\n";
    bgiout<<"6. Nu poti sterge blocul de Start, astfel el ramane mereu pe ecran.\n";
    bgiout<<"7. Cand se fac legaturile la Decizie, pentru a selecta ramura\ndorita, \"true\" si \"false\" se vor scrie\ndoar cu litere mari sau doar cu litere mici.\n";
    bgiout<<"8. Cand se introduce informatia de la tastatura, trebuie mereu\ndat un enter pt a continua schema.\n";
    bgiout<<"9. Atunci cand se introduc in schema/se muta blocurile, pentru a\nle lasa la locul lor trebuie dat un click stanga.\n";
    bgiout<<"10. Click-urile dreapta nu au nicio utilizare in acest program.\n";
    bgiout<<"11. Upload-ul functioneaza in momentul in care schema curenta\neste inexistenta.\n";
    bgiout<<"12. Stergerea unui bloc trebuie apasata prin apasarea butonului YES\ncare apare in partea dreapta a ferestrei.\n";
    bgiout<<"13. Valorile variabilelor se vor asigna dupa apasarea butonului de Run,\ncand acestea sunt cerute in partea dreapta a ferestrei.\n";
    outstreamxy(15,50);
    settextstyle(8,HORIZ_DIR,1);
    bgiout<<"back";
    outstreamxy(805,410);
    setcolor(WHITE);
    rectangle(800,400,850,440);

    determinaMouseClick(x,y);
    if (x>800&&x<840&&y>400&&y<440)
        closegraph(CURRENT_WINDOW);
}

void fereastraDespreNoi()
{
    int x,y;
    initwindow(widthNoi,heightNoi,"DespreNoi");

    void* test_image = new char[imagesize(0, 0,widthNoi,heightNoi )];
    readimagefile("fundalDespreNoi.jpg",0,0, widthNoi,heightNoi);
    getimage(0,0,widthNoi,heightNoi,test_image);


    setcolor(WHITE);
    setbkcolor(COLOR(27,2,31));
    settextstyle(10,HORIZ_DIR, 5);
    bgiout<<"Despre Noi";
    outstreamxy(190,200);

    settextstyle(10,HORIZ_DIR, 2);
    bgiout<<"Suntem Diana si Smaranda si avem proiectul numarul 18, InterSchem.\n";
    bgiout<<"Suntem doua studente in anul I la Facultatea de Informatica Iasi.";
    outstreamxy(30,250);

    settextstyle(8,HORIZ_DIR,1);
    bgiout<<"back";
    outstreamxy(805,410);
    setcolor(WHITE);
    rectangle(800,400,850,440);

    determinaMouseClick(x,y);
    if (x>800&&x<850&&y>400&&y<440)
        closegraph(CURRENT_WINDOW);
}

void menu()
{
    int menu;
    menu=initwindow(width,height,"main menu");
    void* test_image = new char[imagesize(0, 0,width,height )];
    readimagefile("fundal1.jpg",0,0, width,height);
    getimage(0,0, width,height,test_image);

    creareMainMenu();
    creareButonInterschem();
    creareButonReguli();
    creareButonDespreNoi();

    settextstyle(10,HORIZ_DIR, 7);
    setbkcolor(colorUmplut);
    setcolor(WHITE);
    bgiout<<"Main Menu";
    outstreamxy(500,155);

    settextstyle(10,HORIZ_DIR, 6);
    bgiout<<"InterSchem";
    outstreamxy(510,315);


    settextstyle(10,HORIZ_DIR, 5);
    bgiout<<"Reguli\n";
    bgiout<<"InterSchem";
    outstreamxy(200,510);

    bgiout<<"Despre noi";
    outstreamxy(823,525);

    int x,y;
    for (int i=0; i<20; i++)
    {
        determinaMouseClick(x,y);
        if (x>200&&x<380&&y>510&&1010)
            fereastraReguliInterschem();
        else if (x>823&&x< 1623&&y>525&&y<1025)
            fereastraDespreNoi();
        else if (x>510&&x<990 &&y>315&&y<615)
            fereastraInterschem();
        setcurrentwindow(menu);
    }

    getch();
    closegraph();
}
///sfarsit functii ferestre multiple

///inceput functii grafice
void desenStart(int x, int y)
{
    int poly[10]= {x,y,x+60,y,x+60,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1,2,1,2);
    setbkcolor(paleta.colorFill);
    bgiout << "Start" << endl;
    outstreamxy(x+10,y+17);

}

void desenStartDupaRun(int x, int y)
{
    int poly[10]= {x,y,x+60,y,x+60,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1,2,1,2);
    setbkcolor(paleta.colorLineBk);
    bgiout << "Start" << endl;
    outstreamxy(x+10,y+17);

}

void deleteDesenStartStop(int x,int y)
{
    setcolor(paleta.colorBk);
    for (int i=x; i<=x+60; i++)
        line(i,y,i,y+60);
}

void butonStart(int &x, int &y)
{
    int contor=0;
    setcolor(BLACK);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {
            desenStart(x,y);
            deleteDesenStartStop(x,y);
            x=mousex();
            y=mousey();
        }
        desenStart(x,y);
        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
    desenStart(80,10);
        desenStop(200,10);
        desenInput(320,10,"Input");
        desenOutput(450,10,"Output");
        desenCalcul(750,10,"Calcul");
        desenDec(620,10,"Dec");
}

void desenStopDupaRun(int x,int y)
{
    int poly[10]= {x,y,x+60,y,x+60,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorLineBk);
    bgiout << "Stop" << endl;
    outstreamxy(x+10,y+17);
}

void desenStop(int x,int y)
{
    int poly[10]= {x,y,x+60,y,x+60,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << "Stop" << endl;
    outstreamxy(x+10,y+17);
}

void butonClear()
{
    int i;
    setcolor(paleta.colorBk);
    for(i=0 ; i<=995 ; i++)
    {
        line(i,83,i,750);
    }
    for (int i=1005; i<=1500; i++)
    {
        line(i,125,i,750);
    }
    for(int j=0 ; j<nrBlocuri ; j++)
    {
        delete Schema[j];

    }
    nrBlocuri=0;
}

void butonStop(int &x, int &y)
{
    int a,b,contor=0;
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {
            desenStop(x,y);
            deleteDesenStartStop(x,y);
            x=mousex();
            y=mousey();
        }
        desenStop(x,y);

        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
    desenStart(80,10);
        desenStop(200,10);
        desenInput(320,10,"Input");
        desenOutput(450,10,"Output");
        desenCalcul(750,10,"Calcul");
        desenDec(620,10,"Dec");
}

void deleteDesenInOut(int x,int y )
{
    setcolor(paleta.colorBk);
    for (int i=x-10; i<=x+90; i++)
        line(i,y,i,y+60);
}

void desenInputDupaRun(int x,int y,char sir[])
{
    int poly[10]= {x-10,y,x+90,y,x+60,y+60,x+20,y+60,x-10,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorLineBk);
    if (strcmp(sir,"Input")==0) bgiout<<"Input"<<'\n';
    else bgiout << sir[0] << endl;
    outstreamxy(x+13,y+17);
}

void desenInput(int x,int y,char sir[])
{
    int poly[10]= {x-10,y,x+90,y,x+60,y+60,x+20,y+60,x-10,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    if (strcmp(sir,"Input")==0) bgiout<<"Input"<<'\n';
    else bgiout << sir[0] << endl;
    outstreamxy(x+13,y+17);
}

void butonInput(int &x, int &y )
{
    int contor=0;
    int idBloc;
    cautaTipul(x,y,idBloc);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {
            desenInput(x,y,"Input");
            deleteDesenInOut(x,y);
            x=mousex();
            y=mousey();
        }
        desenInput(x,y,Schema[idBloc]->instr);

        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
    desenStart(80,10);
        desenStop(200,10);
        desenInput(320,10,"Input");
        desenOutput(450,10,"Output");
        desenCalcul(750,10,"Calcul");
        desenDec(620,10,"Dec");
    Schema[idBloc]->x=x;
    Schema[idBloc]->y=y;
    cautaTipul(x,y,idBloc);
    desenInput(x,y,Schema[idBloc]->instr);
}

void desenOutputDupaRun(int x,int y,char sir[])
{
    int poly[10]= {x+20,y,x+60,y,x+90,y+60,x-10,y+60,x+20,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorLineBk);
    bgiout << sir << endl;
    outstreamxy(x+10,y+23);
}

void desenOutput(int x,int y,char sir[])
{
    int poly[10]= {x+20,y,x+60,y,x+90,y+60,x-10,y+60,x+20,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << sir << endl;
    outstreamxy(x+10,y+23);
}

void butonOutput(int &x, int &y)
{
    int contor=0;
    int idBloc;
    cautaTipul(x,y,idBloc);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {
            desenOutput(x,y,"Output");
            deleteDesenInOut(x,y);
            x=mousex();
            y=mousey();
        }
        desenOutput(x,y,Schema[idBloc]->instr);
        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
    desenStart(80,10);
    desenStop(200,10);
    desenInput(320,10,"Input");
    desenOutput(450,10,"Output");
    desenCalcul(750,10,"Calcul");
    desenDec(620,10,"Dec");
    Schema[idBloc]->x=x;
    Schema[idBloc]->y=y;
    cautaTipul(x,y,idBloc);
    desenOutput(x,y,Schema[idBloc]->instr);
}


void deleteDesenDec(int x,int y)
{
    setcolor(paleta.colorBk);
    for (int i=x-60; i<=x+70; i++)
        line(i,y,i,y+60);
}

void desenDecDupaRun(int x,int y,char sir[])
{
    int poly[8]= {x,y,x+60,y+60,x-60,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(4,poly);
    setcolor(paleta.colorLine);
    drawpoly(4,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorBk);
    bgiout<<"T";
    outstreamxy(x-60,y+35);
    bgiout<<"F";
    outstreamxy(x+60,y+35);
    setbkcolor(paleta.colorLineBk);
    bgiout << sir << endl;
    outstreamxy(x-10,y+30);
}

void desenDec(int x,int y,char sir[])
{
    int poly[8]= {x,y,x+60,y+60,x-60,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(4,poly);
    setcolor(paleta.colorLine);
    drawpoly(4,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorBk);
    bgiout<<"T";
    outstreamxy(x-60,y+35);
    bgiout<<"F";
    outstreamxy(x+60,y+35);
    setbkcolor(paleta.colorFill);
    bgiout << sir << endl;
    outstreamxy(x-10,y+30);
}

void butonDec(int &x, int &y)
{
    int contor=0;
    int idBloc;
    cautaTipul(x,y,idBloc);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {

            desenDec(x,y,"Dec" );
            deleteDesenDec(x,y);

            x=mousex();
            y=mousey();
        }
        desenDec(x,y,Schema[idBloc]->instr);
        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
        desenStart(80,10);
        desenStop(200,10);
        desenInput(320,10,"Input");
        desenOutput(450,10,"Output");
        desenCalcul(750,10,"Calcul");
        desenDec(620,10,"Dec");
    Schema[idBloc]->x=x;
    Schema[idBloc]->y=y;
    cautaTipul(x,y,idBloc);
    desenDec(x,y,Schema[idBloc]->instr);
}

void deleteDesenCalcul(int x,int y)
{
    setcolor(paleta.colorBk);
    for (int i=x; i<=x+90; i++)
        line(i,y,i,y+60);
}

void desenCalculDupaRun(int x,int y,char sir[])
{
    int poly[10]= {x,y,x+90,y,x+90,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorLineBk);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorLineBk);
    bgiout << sir << endl;
    outstreamxy(x+15,y+17);
}

void desenCalcul(int x,int y,char sir[])
{
    int poly[10]= {x,y,x+90,y,x+90,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << sir << endl;
    outstreamxy(x+15,y+17);
}

void butonCalcul(int &x, int &y)
{
    int contor=0;
    int idBloc;
    cautaTipul(x,y,idBloc);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {
        contor++;
        if(contor%30==0)
        {
            desenCalcul(x,y,"Calcul" );
            deleteDesenCalcul(x,y);
            x=mousex();
            y=mousey();
        }
        desenCalcul(x,y,Schema[idBloc]->instr);
        setcolor(paleta.colorLineBk);
        for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
            line(0,i,1000,i);
    }
    desenStart(80,10);
        desenStop(200,10);
        desenInput(320,10,"Input");
        desenOutput(450,10,"Output");
        desenCalcul(750,10,"Calcul");
        desenDec(620,10,"Dec");
    Schema[idBloc]->x=x;
    Schema[idBloc]->y=y;
    cautaTipul(x,y,idBloc);
    desenCalcul(x,y,Schema[idBloc]->instr);
}

void desenClear()
{
    setcolor(paleta.colorLineBk);
    rectangle(1000,0,1250,40);
    setcolor(paleta.colorLineBk);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setbkcolor(paleta.colorBk);
    bgiout << "Clear" << endl;
    outstreamxy(1120,15);
}

void desenRun()
{
    setcolor(paleta.colorLineBk);
    rectangle(1250,0,1500,40);
    setcolor(paleta.colorLineBk);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setbkcolor(paleta.colorBk);
    bgiout << "Run" << endl;
    outstreamxy(1350,15);
}

int afisOutput=170;

void butonRun(int x, int y)
{
    int eroare=0;
    if((x>1250 && x<1500) && (y>0 && y<40))
    {
        ClearDreapta();
        setcolor(paleta.colorLineBk);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setbkcolor(paleta.colorBk);
        bloc *p=new bloc;
        p=Schema[0];
        desenStartDupaRun(p->x,p->y);
        while (p!=NULL)
        {
            if (p->tip=='o')
            {
                setcolor(paleta.colorLine);
                settextstyle(10,HORIZ_DIR,1);
                setbkcolor(paleta.colorBk);

                for(int j='A' ; j<='Z' ; j++)
                if(strchr(p->instr,j) && exista[j]==0)
                {
                     showerrorbox("Eroare! Una din variabilele expresiei\n nu a fost declarata!");
                     eroare=1;

                }
                if(eroare==0)
                {
                    bgiout << "Your output value is:\n";
                    outstreamxy(1050,afisOutput);
                    afisOutput+=40;
                    p->valo=evaluare(p);
                    delay(100);
                    bgiout<<p->valo<<'\n';
                    outstream();
                    delay(1000);
                    desenOutputDupaRun(p->x,p->y,p->instr);
                }
            }
            else if (p->tip=='c')
            {
                for(int j='A' ; j<='Z' ; j++)
                if(strchr(p->instr,j) && exista[j]==0)
                {
                     showerrorbox("Eroare! Una din variabilele expresiei\n nu a fost declarata!");
                     eroare=1;

                }
                if(eroare==0)
                {
                    memo[int(p->instr[0])]=evaluare(p);
                    desenCalculDupaRun(p->x,p->y,p->instr);
                }
            }
            else if (p->tip=='i')
            {
                settextstyle(10,HORIZ_DIR,1);
                ClearDreapta();
                setcolor(paleta.colorLine);
                setbkcolor(paleta.colorBk);
                bgiout<<"Dati valoare lui "<<p->var<<'\n';
                outstreamxy(1050,130);
                input_pos=0;
                strcpy(inputbuf,"");
                citireDinGrafica(1050,150);
                bgiout<<'\n';
                outstream();
                memo[int(p->var)]=atof(inputbuf);
                desenInputDupaRun(p->x,p->y,p->instr);
            }
            else if (p->tip=='d')
            {
                for(int j='A' ; j<='Z' ; j++)
                if(strchr(p->instr,j) && exista[j]==0)
                {
                     showerrorbox("Eroare! Una din variabilele expresiei\n nu a fost declarata!");
                     eroare=1;

                }
                if(eroare==0)
                {
                     p->valo=evaluare(p);
                    if (p->valo!=0)
                        p->urm=p->urmT;
                    else p->urm=p->urmF;
                    desenDecDupaRun(p->x,p->y,p->instr);
                }
            }
            else if (p->tip=='f')
            {
                desenStopDupaRun(p->x,p->y);
            }
            p=p->urm;
        }
    }
}

void desenGenerateCode()
{
    setcolor(paleta.colorLineBk);
    rectangle(1000,40,1250,80);
    setcolor(paleta.colorLineBk);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setbkcolor(paleta.colorBk);
    bgiout << "Generate Code" << endl;
    outstreamxy(1085,55);

}

void butonGenerateCode(int x, int y)
{
    if((x>1000 && x<1250) && (y>40 && y<80))
    {
        setcolor(paleta.colorLineBk);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setbkcolor(paleta.colorBk);
        afisareCod(Schema[0]);
    }
}

void desenUploadSiSave()
{
    setcolor(paleta.colorLineBk);
    rectangle(1250,40,1500,80);
    setcolor(paleta.colorLineBk);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    setbkcolor(paleta.colorBk);
    bgiout << "Upload/Save" << endl;
    outstreamxy(1320,55);
}

void casutaUploadSiSave()
{
    int x=1050,y=140;
    int poly[10]= {x,y,x+200,y,x+200,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    settextstyle(10, HORIZ_DIR, 2);
    setbkcolor(paleta.colorFill);
    bgiout << "UPLOAD SCHEME" << endl;
    outstreamxy(x+22,y+23);

    x=1050,y=200;
    int polynome[10]= {x,y,x+200,y,x+200,y+60,x,y+60,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,polynome);
    setcolor(paleta.colorLine);
    drawpoly(5,polynome);
    settextstyle(10, HORIZ_DIR, 2);
    //setusercharsize(2, 1, 2, 1);
    setbkcolor(paleta.colorFill);
    bgiout << "SAVE SCHEME" << endl;
    outstreamxy(x+35,y+23);

}

void initializareEcranCuCuloareaCeruta()
{
    setcolor(paleta.colorBk);

    for (int i=0; i<79; i++)    //acopera fundalul din spatele butoanelor pentru blocuri
    {
        line(0,i,1000,i);
    }

    for (int i=0; i<=995; i++)  //acopera fundalul din partea pentru schema a ferestrei
    {
        line(i,83,i,750);
    }

    //paleta.colorLineBk=COLOR(255,69,0); ///dungile de pe ecran
    setcolor(paleta.colorLineBk);
    for (int i=996; i<=1004; i++)   //dunga care delimiteaza ferastra pentru schema de cea pentru cod
    {
        line(i,0,i,750);
    }

    setcolor(paleta.colorBk);
    for (int i=1005; i<=1500; i++)  //acopera fundalul din partea pentru cod a ferestrei si fundalul de la run, clear si generate code
    {
        line(i,0,i,750);
    }

    desenStart(80,10);
    desenStop(200,10);
    desenInput(320,10,"Input");
    desenOutput(450,10,"Output");
    desenDec(620,10,"Dec" );
    desenCalcul(750,10,"Calcul");
    desenTeme();
    desenRun();
    desenClear();
    desenGenerateCode();
    desenUploadSiSave();
    desenBackInInterschem();
    desenMiniMeniu(0,0);

    setcolor(paleta.colorLineBk);
    for (int i=78; i<=82; i++)     //dunga care separa butoanele de partea pentru schema
        line(0,i,1000,i);

    for (int i=120; i<=124; i++)     //dunga care separa butoanele de partile pentru cod si pentru schema
        line(1000,i,1500,i);
}

void desenTeme()
{
    setcolor(paleta.colorLineBk);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1,2,1,2);
    setbkcolor(paleta.colorBk);
    bgiout << "Tema" << endl;
    outstreamxy(1200,95);
}

void butonTeme(int x, int y)
{
    if((x>1000 && x<1500) && (y>80 && y<120))
    {

        desenMeniuTeme(1100,200);
    }
}

void desenMeniuTeme(int x, int y)
{
    int poly[10]= {x,y,x+200,y,x+200,y+350,x,y+350,x,y};
    setfillstyle(SOLID_FILL,paleta.colorFill);
    fillpoly(5,poly);
    setcolor(paleta.colorLine);
    drawpoly(5,poly);
    setcolor(paleta.colorLine);
    line(x,y+50,x+200,y+50);
    line(x,y+100,x+200,y+100);
    line(x,y+150,x+200,y+150);
    line(x,y+200,x+200,y+200);
    line(x,y+250,x+200,y+250);
    line(x,y+300,x+200,y+300);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 0);
    setusercharsize(1, 2, 1, 2);
    setbkcolor(paleta.colorFill);
    bgiout << "Primavara" << endl;
    outstreamxy(x+70,y+25);
    bgiout << "Vara" << endl;
    outstreamxy(x+70,y+75);
    bgiout << "Toamna" << endl;
    outstreamxy(x+70,y+125);
    bgiout << "Iarna" << endl;
    outstreamxy(x+70,y+175);
    bgiout << "Paste" << endl;
    outstreamxy(x+70,y+225);
    bgiout << "Halloween" << endl;
    outstreamxy(x+70,y+275);
    bgiout << "Craciun" << endl;
    outstreamxy(x+70,y+325);
}

void butoaneMeniuTeme(int x,int y)
{
    if(y>200 && y<250)
    {
        changecolorPrimavara();
        initializareEcranCuCuloareaCeruta();

    }
    else  if(y>250 && y<300)
    {
        changecolorVara();
        initializareEcranCuCuloareaCeruta( );

    }
    else if(y>300 && y<350)
    {
        changecolorToamna();
        initializareEcranCuCuloareaCeruta( );

    }
    else if(y>350 && y<400)
    {
        changecolorIarna();
        initializareEcranCuCuloareaCeruta( );

    }
    else if(y>400 && y<450)
    {
        changecolorPaste();
        initializareEcranCuCuloareaCeruta( );

    }
    else if(y>450 && y<500)
    {
        changecolorHalloween();
        initializareEcranCuCuloareaCeruta( );

    }
    else if(y>500 && y<550)
    {
        changecolorCraciun();
        initializareEcranCuCuloareaCeruta( );

    }
}

void changecolorPrimavara()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(6, 70, 53);
    paleta.colorFill=COLOR(244, 238, 169);
    paleta.colorBk=COLOR(81, 146, 89);
    paleta.colorLineBk=COLOR(240, 187, 98);

}

void changecolorVara()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(190, 0, 0);
    paleta.colorFill=COLOR(247, 234, 0);
    paleta.colorBk=COLOR(118, 150, 39);
    paleta.colorLineBk=COLOR(228, 137, 0);

}

void changecolorToamna()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(92, 61, 46);
    paleta.colorFill=COLOR(244, 238, 169);
    paleta.colorBk=COLOR(184, 92, 56);
    paleta.colorLineBk=COLOR(45, 36, 36);

}

void changecolorIarna()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(152, 214, 237);
    paleta.colorFill=COLOR(23, 105, 135);
    paleta.colorBk=COLOR(84, 95, 99);
    paleta.colorLineBk=COLOR(196, 202, 204);
}

void changecolorPaste()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(186, 240, 165);
    paleta.colorFill=COLOR(169, 157, 242);
    paleta.colorBk=COLOR(86, 166, 154);
    paleta.colorLineBk=COLOR(240, 235, 141);

}

void changecolorHalloween()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(231, 158, 79);
    paleta.colorFill=COLOR(160, 83, 68);
    paleta.colorBk=COLOR(115, 64, 70);
    paleta.colorLineBk=COLOR(50, 31, 40);
}

void changecolorCraciun()
{
    ///linie, blocuri, fundal, delimitare
    paleta.colorLine=COLOR(238, 235, 221);
    paleta.colorFill=COLOR(129, 0, 0);
    paleta.colorBk=COLOR(43, 84, 42);
    paleta.colorLineBk=COLOR(99, 0, 0);

}

void ClearDreapta()
{
    setcolor(paleta.colorBk);
    for(int i=1005 ; i<=1500 ; i++)
        line(i,125,i,750);
}

void traseazaLegaturi(int x1, int y1)
{
    int x2,y2,ym;
    int xdec,ydec;
    int nr,blocSt,blocDest;
    char tip;
    int blocDest1,blocDest2;
    tip=cautaTipul(x1,y1,nr);
    x1=Schema[nr]->x;
    y1=Schema[nr]->y;
    xdec=x1,ydec=y1;
    blocSt=nr;
    if (Schema[blocSt]->tip!='d')
    {
        if (Schema[blocSt]->urm!=NULL) showerrorbox("Binding already done!");
        else
        {
            if (tip=='s'||tip=='f') x1=x1+30,y1=y1+60;
            else if (tip=='i'||tip=='o') x1=x1+45,y1=y1+60;
            else if (tip=='c') x1+=45,y1+=60;
            while (!ismouseclick(WM_LBUTTONDOWN))
            {
                line(0,0,0,1);
            }
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            tip=cautaTipul(x2,y2,nr);
            x2=Schema[nr]->x;
            y2=Schema[nr]->y;
            blocDest=nr;

            if (tip=='s'||tip=='f') x2=x2+30;
            else if (tip=='i'||tip=='o') x2=x2+45;
            else if (tip=='c') x2+=45;
            setcolor(paleta.colorLine);
            ym=(y1+y2)/2;
            if(verificarePixelBloc(x2,y2))
            {
                if(y1>y2)
                {
                    line(x1,y1,x1,y1+7);
                    if(x1>x2)
                    {
                        line(x1,y1+7,x1+60,y1+7);
                        line(x1+60,y1+7,x1+60,y2-7);
                        line(x1+60,y2-7,x2,y2-7);
                        line(x2,y2-7,x2,y2);
                    }

                    else
                    {
                        line(x1,y1+7,x1-60,y1+7);
                        line(x1-60,y1+7,x1-60,y2-7);
                        line(x1-60,y2-7,x2,y2-7);
                        line(x2,y2-7,x2,y2);
                    }
                }
                else
                {
                    line (x1,y1,x1,ym);
                    line (x1,ym,x2,ym);
                    line (x2,ym,x2,y2);
                }


                line(x2,y2,x2-5,y2-5);
                line(x2,y2,x2+5,y2-5);

            }
            else
                showerrorbox("Eroare! Nu ati apasat un bloc!");
        }
    }
    else
    {
        ClearDreapta();
        settextstyle(10,HORIZ_DIR,2);
        setcolor(paleta.colorLine);
        setbkcolor(paleta.colorBk);
        bgiout<<"Do you want to bind TRUE or FALSE?";
        outstreamxy(1025,130);
        input_pos=0;
        strcpy(inputbuf,"");
        citireDinGrafica(1025,150);
        if (strcmp(inputbuf,"TRUE")==0||strcmp(inputbuf,"true")==0)
        {
            cout<<"butonul de true a fost apasat\n";
            ///facem legatura numai pt true; se si poate verifica daca nu este deja facuta
            if (Schema[blocSt]->urmT!=NULL) showerrorbox("Error! Binding already done!");
            else
            {
                clearmouseclick(WM_LBUTTONDOWN);
                while (!ismouseclick(WM_LBUTTONDOWN))
                {
                    line(0,0,0,1);
                }
                getmouseclick(WM_LBUTTONDOWN,x2,y2);
                tip=cautaTipul(x2,y2,nr);
                x2=Schema[nr]->x;
                y2=Schema[nr]->y;
                blocDest1=nr;

                if (tip=='s'||tip=='f') x2=x2+30;
                else if (tip=='i'||tip=='o') x2=x2+45;
                else if (tip=='c') x2+=45;
                setcolor(paleta.colorLine);
                ym=(y1+60+y2)/2;
                if(verificarePixelBloc(x2,y2))
                {
                    x1=xdec-60;
                    y1=ydec+60;
                    if(y1>y2)
                    {
                        line(x1,y1,x1,y1+7);
                        if(x1>x2)
                        {
                            line(x1,y1+7,x1+130,y1+7);
                            line(x1+130,y1+7,x1+130,y2-7);
                            line(x1+130,y2-7,x2,y2-7);
                            line(x2,y2-7,x2,y2);
                        }

                        else
                        {
                            line(x1,y1+7,x1-130,y1+7);
                            line(x1-130,y1+7,x1-130,y2-7);
                            line(x1-130,y2-7,x2,y2-7);
                            line(x2,y2-7,x2,y2);
                        }
                    }
                    else
                    {
                        line (x1,y1,x1,ym);
                        line (x1,ym,x2,ym);
                        line (x2,ym,x2,y2);
                    }

                    line(x2,y2,x2-5,y2-5);
                    line(x2,y2,x2+5,y2-5);
                    Schema[blocSt]->urmT=Schema[blocDest1];
                    Schema[blocDest1]->ant=Schema[blocSt];
                }
                else
                    showerrorbox("Eroare! Nu ati apasat un bloc!");

            }

        }
        else if (strcmp(inputbuf,"FALSE")==0||strcmp(inputbuf,"false")==0)
        {
            cout<<"butonul de false a fost apasat\n";
            ///facem legatura numai pt false; se si poate verifica daca nu este deja facuta
            if (Schema[blocSt]->urmF!=NULL) showerrorbox("Error! Binding already done!");
            else
            {
                clearmouseclick(WM_LBUTTONDOWN);
                while (!ismouseclick(WM_LBUTTONDOWN))
                {
                    line(0,0,0,1);
                }
                getmouseclick(WM_LBUTTONDOWN,x2,y2);
                tip=cautaTipul(x2,y2,nr);
                x2=Schema[nr]->x;
                y2=Schema[nr]->y;
                blocDest2=nr;

                if (tip=='s'||tip=='f') x2=x2+30;
                else if (tip=='i'||tip=='o') x2=x2+45;
                else if (tip=='c') x2+=45;

                ym=(ydec+60+y2)/2;
                if(verificarePixelBloc(x2,y2))
                {
                    x1=xdec+60;
                    y1=ydec+60;
                    if(y1>y2)
                    {
                        line(x1,y1,x1,y1+7);
                        if(x1>x2)
                        {
                            line(x1,y1+7,x1+130,y1+7);
                            line(x1+130,y1+7,x1+130,y2-7);
                            line(x1+130,y2-7,x2,y2-7);
                            line(x2,y2-7,x2,y2);
                        }

                        else
                        {
                            line(x1,y1+7,x1-130,y1+7);
                            line(x1-130,y1+7,x1-130,y2-7);
                            line(x1-130,y2-7,x2,y2-7);
                            line(x2,y2-7,x2,y2);
                        }
                    }
                    else
                    {
                        line (x1,y1,x1,ym);
                        line (x1,ym,x2,ym);
                        line (x2,ym,x2,y2);
                    }

                    line(x2,y2,x2-5,y2-5);
                    line(x2,y2,x2+5,y2-5);
                    Schema[blocSt]->urmF=Schema[blocDest2];
                    Schema[blocDest2]->ant=Schema[blocSt];
                }
                else
                    showerrorbox("Eroare! Nu ati apasat un bloc!");
            }
        }
        else
        {
            bgiout<<"Error! Try to be more carefull with\nthe syntax!\nFor example, some correct key words\nare \"TRUE\" or \"false\", not \"False\"!\n";
            outstreamxy(1025,170);
        }
    }
    if (Schema[blocSt]->tip!='d')
    {
        if(Schema[blocDest]->tip!='d')
        {
            Schema[blocSt]->urm=Schema[blocDest];
            Schema[blocDest]->ant=Schema[blocSt];
        }
        else
        {
            if(Schema[blocDest]->ant==NULL)             //daca ducem leg catre un bloc de decizie care nu are anterior inca(practic, construim un if)
            {
                Schema[blocSt]->urm=Schema[blocDest];
                Schema[blocDest]->ant=Schema[blocSt];
            }

            else if(Schema[blocDest]->ant!=NULL)        //daca ducem leg la un bloc dec care are deja un anterior(practic, construim un while)
            {
                Schema[blocSt]->urm=Schema[blocDest];
                Schema[blocDest]->antLoop=Schema[blocSt];
            }
        }
    }
}

void mentineLegaturi(int idbloc1,int idbloc2)
{
    char tip1,tip2;
    int x1,y1,x2,y2,ym;
    x1=Schema[idbloc1]->x;
    y1=Schema[idbloc1]->y;

    tip1=Schema[idbloc1]->tip;
    if (tip1=='s'||tip1=='f') x1=x1+30,y1=y1+60;
    else if (tip1=='i'||tip1=='o') x1=x1+45,y1=y1+60;
    else if (tip1=='c') x1+=45,y1+=60;
    else if (tip1=='d') y1+=60;

    x2=Schema[idbloc2]->x;
    y2=Schema[idbloc2]->y;

    tip2=Schema[idbloc2]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;

    if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmT==Schema[idbloc2]) x1-=60;
    else if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2]) x1+=60;

    setcolor(paleta.colorLine);
    ym=(y1+y2)/2;
    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmT==Schema[idbloc2])
            {
                line(x1,y1+7,x1+130,y1+7);
                line(x1+130,y1+7,x1+130,y2-7);
                line(x1+130,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2])
            {
                line(x1,y1+7,x1+10,y1+7);
                line(x1+10,y1+7,x1+10,y2-7);
                line(x1+10,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else
            {
                line(x1,y1+7,x1+60,y1+7);
                line(x1+60,y1+7,x1+60,y2-7);
                line(x1+60,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }

        }

        else
        {
            if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2])
            {
                line(x1,y1+7,x1-130,y1+7);
                line(x1-130,y1+7,x1-130,y2-7);
                line(x1-130,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else
            {
                line(x1,y1+7,x1-60,y1+7);
                line(x1-60,y1+7,x1-60,y2-7);
                line(x1-60,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }

        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }
    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);
}

void mentineLegaturiDecizie(int idbloc1,int idbloc2,int idbloc3)
{
    int x2,y2,ym,x1,y1;
    char tip2,tip1;
    int xdec,ydec;
    x1=Schema[idbloc1]->x;
    y1=Schema[idbloc1]->y;
    xdec=x1;
    ydec=y1;
    tip1=Schema[idbloc1]->tip;
    if (tip1=='s'||tip1=='f') x1=x1+30,y1=y1+60;
    else if (tip1=='i'||tip1=='o') x1=x1+45,y1=y1+60;
    else if (tip1=='c') x1+=45,y1+=60;

    x2=Schema[idbloc2]->x;
    y2=Schema[idbloc2]->y;

    tip2=Schema[idbloc2]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;

    setcolor(paleta.colorLine);
    ym=(ydec+60+y2)/2;
    x1=xdec-60;
    y1=ydec+60;
    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            line(x1,y1+7,x1+130,y1+7);
            line(x1+130,y1+7,x1+130,y2-7);
            line(x1+130,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }

        else
        {
            line(x1,y1+7,x1-10,y1+7);
            line(x1-10,y1+7,x1-10,y2-7);
            line(x1-10,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }


    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);

    x2=Schema[idbloc3]->x;
    y2=Schema[idbloc3]->y;
    tip2=Schema[idbloc3]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;
    ym=(ydec+60+y2)/2;
    x1=xdec+60;

    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            line(x1,y1+7,x1+130,y1+7);
            line(x1+130,y1+7,x1+130,y2-7);
            line(x1+130,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }

        else
        {
            line(x1,y1+7,x1-130,y1+7);
            line(x1-130,y1+7,x1-130,y2-7);
            line(x1-130,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }

    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);
}

void stergeLegaturi(int idbloc1, int idbloc2)
{
    char tip1,tip2;
    int x1,y1,x2,y2,ym;
    x1=Schema[idbloc1]->x;
    y1=Schema[idbloc1]->y;

    tip1=Schema[idbloc1]->tip;
    if (tip1=='s'||tip1=='f') x1=x1+30,y1=y1+60;
    else if (tip1=='i'||tip1=='o') x1=x1+45,y1=y1+60;
    else if (tip1=='c') x1+=45,y1+=60;
    else if (tip1=='d') y1+=60;

    x2=Schema[idbloc2]->x;
    y2=Schema[idbloc2]->y;

    tip2=Schema[idbloc2]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;

    if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmT==Schema[idbloc2]) x1-=60;
    else if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2]) x1+=60;

    setcolor(paleta.colorBk);
    ym=(y1+y2)/2;
    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmT==Schema[idbloc2])
            {
                line(x1,y1+7,x1+130,y1+7);
                line(x1+130,y1+7,x1+130,y2-7);
                line(x1+130,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2])
            {
                line(x1,y1+7,x1+10,y1+7);
                line(x1+10,y1+7,x1+10,y2-7);
                line(x1+10,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else
            {
                line(x1,y1+7,x1+60,y1+7);
                line(x1+60,y1+7,x1+60,y2-7);
                line(x1+60,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }

        }
        else
        {
            if (Schema[idbloc1]->tip=='d'&&Schema[idbloc1]->urmF==Schema[idbloc2])
            {
                line(x1,y1+7,x1-130,y1+7);
                line(x1-130,y1+7,x1-130,y2-7);
                line(x1-130,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }
            else
            {
                line(x1,y1+7,x1-60,y1+7);
                line(x1-60,y1+7,x1-60,y2-7);
                line(x1-60,y2-7,x2,y2-7);
                line(x2,y2-7,x2,y2);
            }

        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }
    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);
}

void stergeLegaturiDecizie(int idbloc1,int idbloc2,int idbloc3)
{
    int x2,y2,ym,x1,y1;
    int xdec,ydec;
    char tip2,tip1;
    x1=Schema[idbloc1]->x;
    y1=Schema[idbloc1]->y;
    xdec=x1;
    ydec=y1;
    tip1=Schema[idbloc1]->tip;
    if (tip1=='s'||tip1=='f') x1=x1+30,y1=y1+60;
    else if (tip1=='i'||tip1=='o') x1=x1+45,y1=y1+60;
    else if (tip1=='c') x1+=45,y1+=60;

    x2=Schema[idbloc2]->x;
    y2=Schema[idbloc2]->y;

    tip2=Schema[idbloc2]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;

    setcolor(paleta.colorBk);
    ym=(ydec+60+y2)/2;
    x1=xdec-60;
    y1=ydec+60;
    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            line(x1,y1+7,x1+130,y1+7);
            line(x1+130,y1+7,x1+130,y2-7);
            line(x1+130,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }

        else
        {
            line(x1,y1+7,x1-10,y1+7);
            line(x1-10,y1+7,x1-10,y2-7);
            line(x1-10,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }


    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);

    x2=Schema[idbloc3]->x;
    y2=Schema[idbloc3]->y;
    tip2=Schema[idbloc3]->tip;
    if (tip2=='s'||tip2=='f') x2=x2+30;
    else if (tip2=='i'||tip2=='o') x2=x2+45;
    else if (tip2=='c') x2+=45;
    ym=(ydec+60+y2)/2;
    x1=xdec+60;
    y1=ydec+60;
    setcolor(paleta.colorBk);

    if(y1>y2)
    {
        line(x1,y1,x1,y1+7);
        if(x1>x2)
        {
            line(x1,y1+7,x1+10,y1+7);
            line(x1+10,y1+7,x1+10,y2-7);
            line(x1+10,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }

        else
        {
            line(x1,y1+7,x1-130,y1+7);
            line(x1-130,y1+7,x1-130,y2-7);
            line(x1-130,y2-7,x2,y2-7);
            line(x2,y2-7,x2,y2);
        }
    }
    else
    {
        line (x1,y1,x1,ym);
        line (x1,ym,x2,ym);
        line (x2,ym,x2,y2);
    }


    line(x2,y2,x2-5,y2-5);
    line(x2,y2,x2+5,y2-5);
}

///inceput functii eval
void inverseaza(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // daca cere mai multe cifre, pui zerouri la inceput

    while (i < d)
        str[i++] = '0';

    inverseaza(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char res[], int afterpoint)
{
    // ia partea intreaga
    strcpy(res,"");
    int ipart = (int)n;

    // partea fractionara
    float fpart = n - (float)ipart;

    // converteste partea intreaga la char
    int i = intToStr(ipart, res, 0);

    if (afterpoint != 0)
    {
        res[i] = '.';

        // si acum partea fractionara
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

double evaluare(bloc *B)
{
    functie F;
    char doubleToChar[202]="";
    strcpy(F.expresie,B->expresie);

    strcat(F.expresie,")");

    PrelucrareExpresie(F);

    for (int i=0; i<F.lung; i++)
        if (strchr(litere,F.vect[i][0])!=NULL)
        {
            ftoa(memo[F.vect[i][0]], doubleToChar, 5);
            strcpy(F.vect[i],doubleToChar);
            F.vect[i][strlen(F.vect[i])]=NULL;
        }

    for (int i=0; i<F.lung; i++)
        cout<<F.vect[i];
    cout<<'\n';


    F.lung=strlen(F.expresie);
    double a=ValoareFunctie(F,3);
    cout<<"Functia valoreaza: "<<a<<'\n';
    return a;
}

///final functii eval
