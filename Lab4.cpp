#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif.
*/

#ifdef Zad_4_0
#include <cstdio>
#include <bitset>

struct Element
{
    bool p1;
    bool p2;
    bool p3;
    bool p4;
    short val;
};

void wypisz(Element &e){
    cout << "P1: "<<e.p1<< "\nP2: "<<e.p2 << "\nP3: "<<e.p3<<"\nP4: "<<e.p4<<"\nVALUE: "<<e.val<<endl;
}

void writeToFileText(Element* tab, short rozmiar, char const *nazwa){
    FILE* file = nullptr;

    file = fopen(nazwa,"w");

    if(file != nullptr){
        for(int i = 0; i < rozmiar; i++){
            Element e = tab[i];
            fprintf(file, "%d;%d;%d;%d;%d\n",e.p1,e.p2,e.p3,e.p4,e.val);
        }
    }else{
        throw -1;
    }

    fclose(file);
    file = nullptr;
}

Element readNElement(char const * nazwa, int n){
    FILE* file = nullptr;
    Element res; 
    file = fopen(nazwa,"r");

    if(file!=nullptr){
        int p1,p2,p3,p4,val;
        int index = 0;
        while (!feof(file) && index < n)
        {
            int read = 0;
            read = fscanf(file, "%d;%d;%d;%d;%d\n", &p1, &p2, &p3, &p4, &val);
            if(read != 5){
                throw -1;
            }
            res.p1 = (bool)p1;
            res.p2 = (bool)p2;
            res.p3 = (bool)p3;
            res.p4 = (bool)p4;
            res.val = (short)val;
            index++;
        }
        
    }

    fclose(file);
    file = nullptr;
    return res;
}

void writeToFileBinary(Element* tab, short rozmiar, char const *nazwa){
    FILE* file = nullptr;

    file = fopen(nazwa,"w+b");

    if(file != nullptr){
        fwrite(&rozmiar, sizeof(short),1,file);
        fwrite(tab, sizeof(Element),rozmiar,file);
    }else{
        throw -1;
    }

    fclose(file);
    file = nullptr;
}

void readfromFileBinary(char const *nazwa){
    FILE* file = nullptr;
    Element* tab = nullptr;
    short rozmiar = -1;
    file = fopen(nazwa,"r+b");

    if(file != nullptr){
        fread(&rozmiar, sizeof(short),1,file);
        if(rozmiar<0){
            throw -1;
        }
        tab = new Element[rozmiar];
        fread(tab, sizeof(Element), rozmiar, file);


        for(int i=0;i<rozmiar;i++){
            wypisz(tab[i]);
        }

        delete[] tab;
        tab = nullptr;
    }else{
        throw -1;
    }

    fclose(file);
    file = nullptr;
}

short compresElement(Element& e){
    short res = 0;
    
    res |= e.p1 << 0;
    res |= e.p2 << 1;
    res |= e.p3 << 2;
    res |= e.p4 << 3;
    res |= e.val << 6;
    return res;
}

Element decompresElement(short com){
    Element res;
    u_int16_t m1 = 0x0001;
    u_int16_t m2 = 0x0002;
    u_int16_t m3 = 0x0004;
    u_int16_t m4 = 0x0008;
    u_int16_t m5 = 0xFFC0;

    res.p1 = (com & m1);
    res.p2 = (com & m2);
    res.p3 = (com & m3);
    res.p4 = (com & m4);
    res.val = (com & m5) >>6;

    return res;
}

void writeToFileBinaryCompres(Element* tab, short rozmiar, char const *nazwa){
    FILE* file = nullptr;

    file = fopen(nazwa,"w+b");

    if(file != nullptr){
        short* tabC = new short[rozmiar];
        for(int i =0; i< rozmiar;i++){
            tabC[i] = compresElement(tab[i]);
        }

        fwrite(&rozmiar, sizeof(short),1,file);
        fwrite(tabC, sizeof(short),rozmiar,file);
        delete[] tabC;
        tabC = nullptr;
    }else{
        throw -1;
    }

    fclose(file);
    file = nullptr;
}

void readfromFileBinaryCompres(char const *nazwa){
    FILE* file = nullptr;
    Element* tab = nullptr;
    short rozmiar = -1;
    file = fopen(nazwa,"r+b");

    if(file != nullptr){
        fread(&rozmiar, sizeof(short),1,file);
        if(rozmiar<0){
            throw -1;
        }
        tab = new Element[rozmiar];
        short *tabC = new short[rozmiar];

        fread(tabC, sizeof(short), rozmiar, file);

        for(int i=0;i<rozmiar;i++){
            tab[i] = decompresElement(tabC[i]);
            wypisz(tab[i]);
        }

        delete[] tab;
        delete[] tabC;
        tab = nullptr;
        tabC = nullptr;
    }else{
        throw -1;
    }

    fclose(file);
    file = nullptr;
}


int main()
{
    Element e1 = {true,true,true,true,512};
    int romziar = 5;
    Element *tab = new Element[romziar]{
        {true,false,true,false,1},
        {false,false,true,false,2},
        {true,false,true,false,3},
        {true,false,true,false,4},
        {true,false,true,false,65}
    };
    
    wypisz(e1);
    writeToFileText(tab, romziar, "T1.txt");
    Element e2 = readNElement("T1.txt",1);
    wypisz(e2);

    writeToFileBinary(tab,romziar,"B1.txt");
    readfromFileBinary("B1.txt");

    writeToFileBinaryCompres(tab, 5, "C1.txt");
    readfromFileBinaryCompres("C1.txt");

    delete[] tab;
    tab = nullptr;

}

#endif

#ifdef Zad_4_1

int main()
{

}

#endif

#ifdef Zad_4_2

int main()
{

}

#endif

#ifdef Zad_4_3

int main()
{

}

#endif
