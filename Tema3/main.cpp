#include <bits/stdc++.h>

using namespace std;
///                                                   INTERFATA
class Pret
{
public:
    virtual float calcularePretNrClienti (int NrClienti)=0;
};


///                                            CLASA ALIMENT(ABSTRACTA)
class Aliment:public Pret
{
protected:
    const int idAliment;
    string nume;
    float pret;
    bool contineGluten;
public:
    static int contorIDAliment;
    Aliment():idAliment(contorIDAliment++)
    {
        this -> nume = "Nedefinit";
        this -> pret = 0;
        this -> contineGluten = false;
    }
    Aliment(string nume, float pret, bool contineGluten):idAliment(contorIDAliment++)
    {
        this -> nume = nume;
        this -> pret = pret;
        this -> contineGluten = contineGluten;
    }
    Aliment(const string nume):idAliment(contorIDAliment++)
    {
        this -> nume = nume;
    }
    Aliment(const Aliment& a):idAliment(a.contorIDAliment)
    {
        this -> nume = a.nume;
        this -> pret = a.pret;
        this -> contineGluten = a.contineGluten;
    }
    Aliment& operator=(const Aliment& a)
    {
        if (this != &a)
        {
            this -> nume = a.nume;
            this -> pret = a.pret;
            this -> contineGluten = a.contineGluten;
        }
        return *this;
    }
    ~Aliment()
    {
        this -> pret = 0;
        this -> contineGluten = false;
    }

    virtual ostream& AfisareVirtuala(ostream& out)const
    {
        out<<"\nID aliment: "<<this -> idAliment;
        out<<"\nNume aliment: "<<this -> nume;
        out<<"\nPret produs: "<<this -> pret;
        out<<"\nAlimentul contine gluten(1 DA / 0 NU): "<<this -> contineGluten;
        return out;
    }
    virtual istream& CitireVirtuala (istream& in)
    {
        cout<<"\nNumele alimentului: ";
        in>>this-> nume;
        cout<<"Pret produs: ";
        in>>this -> pret;
        cout<<"Alimentul contine gluten(1 DA / 0 NU): ";
        in>>this -> contineGluten;
        return in;
    }
    friend istream& operator>>(istream& in, Aliment& a);
    friend ostream& operator<<(ostream& out,const Aliment& a);
    virtual string detalii_aliment()=0;
};
istream& operator>>(istream& in, Aliment& a)
{
    return a.CitireVirtuala(in);
}
ostream& operator<<(ostream& out, const Aliment& a)
{
    return a.AfisareVirtuala(out);
}

///                                                CLASA TORT

class Tort:public Aliment
{
protected:
    float cantitatePortie;
    int nrIngrediente;
    string* ingrediente;
public:
    Tort():Aliment()
    {
        this -> cantitatePortie = 0;
        this -> nrIngrediente = 0;
        this -> ingrediente = NULL;
    }
    Tort(string nume, float pret, bool contineGluten, float cantitatePortie, int nrIngrediente, string* ingrediente):Aliment(nume,pret,contineGluten)
    {
        this -> cantitatePortie = cantitatePortie;
        this -> nrIngrediente = nrIngrediente;
        this -> ingrediente = new string[this -> nrIngrediente];
        for (int i = 0; i < this -> nrIngrediente; i++)
            this -> ingrediente[i] = ingrediente[i];
    }
    Tort(const Tort& t):Aliment(t)
    {
        this -> cantitatePortie = t.cantitatePortie;
        this -> nrIngrediente = t.nrIngrediente;
        this -> ingrediente = new string[this -> nrIngrediente];
        for (int i = 0; i < this -> nrIngrediente; i++)
            this -> ingrediente[i] = t.ingrediente[i];
    }
    Tort& operator=(const Tort& t)
    {
        if (this != &t)
        {
            if (this -> ingrediente != NULL)
                delete[] this -> ingrediente;
            Aliment::operator=(t);
            this -> cantitatePortie = t.cantitatePortie;
            this -> nrIngrediente = t.nrIngrediente;
            this -> ingrediente = new string[this -> nrIngrediente];
            for (int i = 0; i < this -> nrIngrediente; i++)
                this -> ingrediente[i] = t.ingrediente[i];
        }
        return *this;
    }
    ~Tort()
    {
        if (this -> ingrediente != NULL)
            delete[] this -> ingrediente;
    }

    virtual istream& CitireVirtuala(istream& in)
    {
        Aliment::CitireVirtuala(in);
        cout<<"Cantitatea unei portii (grame): ";
        in>>this -> cantitatePortie;
        cout<<"Numar ingrediente tort: ";
        in>>this -> nrIngrediente;
        if (this -> ingrediente != NULL)
            delete[] this -> ingrediente;
        this -> ingrediente = new string[this -> nrIngrediente];
        cout<<"Numele ingredientelor ("<<this -> nrIngrediente<<" nume intre spatii): ";
        for (int i = 0; i < this -> nrIngrediente; i++)
            in>>this -> ingrediente[i];
        return in;
    }
    virtual ostream& AfisareVirtuala(ostream& out) const
    {
        Aliment::AfisareVirtuala(out);
        out<<"\nCantitatea unei portii (grame): "<<this -> cantitatePortie;
        out<<"\nNumar ingrediente tort: "<<this -> nrIngrediente;
        out<<"\nIngrediente: ";
        if (this -> nrIngrediente > 0)
        {
            for (int i = 0; i < this -> nrIngrediente - 1; i++)
                out<<this -> ingrediente[i]<<", ";
            out<<this -> ingrediente[this -> nrIngrediente - 1];

        }
        else
            out<<"fara";
        return out;
    }
    virtual float calcularePretNrClienti (int NrClienti)
    {
//        return this -> pret * NrClienti;

//        return this -> pret * (1000 / this -> cantitatePortie + 1) * NrClienti;
        return ((NrClienti * this -> cantitatePortie) / 1000 + 1) * this -> pret;
    }

    virtual string detalii_aliment()
    {
        string rez;
        rez = this -> nume;
        rez += "(contine ";
        if (this -> nrIngrediente > 0)
        {
            for (int i = 0; i < this -> nrIngrediente - 1; i++)
                rez += this ->ingrediente[i] + ", ";
            rez += this -> ingrediente[this -> nrIngrediente - 1] + ")";
        }
        else
            rez += "nimic)";
        return rez;
    }
};

///                                         CLASA APERITIV

class Aperitiv:public Aliment
{
protected:
    string ingredientPrincipal;
    int nrAperitivePerPersoana;
public:
    Aperitiv():Aliment()
    {
        this -> ingredientPrincipal = "Nedefinit";
        this -> nrAperitivePerPersoana = 0;
    }
    Aperitiv(string nume, float pret, bool contineGluten, string ingredientPrincipal, int nrAperitivePerPersoana):Aliment(nume,pret,contineGluten)
    {
        this -> ingredientPrincipal = ingredientPrincipal;
        this -> nrAperitivePerPersoana = nrAperitivePerPersoana;
    }
    Aperitiv(const Aperitiv& a):Aliment(a)
    {
        this -> ingredientPrincipal = a.ingredientPrincipal;
        this -> nrAperitivePerPersoana = a.nrAperitivePerPersoana;
    }
    ~Aperitiv()
    {
        this -> nrAperitivePerPersoana = 0;
    }

    Aperitiv& operator=(const Aperitiv& a)
    {
        if (this != &a)
        {
            Aliment::operator=(a);
            this -> ingredientPrincipal = a.ingredientPrincipal;
            this -> nrAperitivePerPersoana = a.nrAperitivePerPersoana;
        }
        return *this;
    }
    virtual istream& CitireVirtuala(istream& in)
    {
        Aliment::CitireVirtuala(in);
        cout<<"Ingredientul principal al aperitivului: ";
        in>>this -> ingredientPrincipal;
        cout<<"Numarul de aperitive servite unei persoane: ";
        in>>this -> nrAperitivePerPersoana;
        return in;
    }
    virtual ostream& AfisareVirtuala(ostream& out) const
    {
        Aliment::AfisareVirtuala(out);
        out<<"\nIngredientul principal al aperitivului: "<<this -> ingredientPrincipal;
        out<<"\nNumarul de aperitive servite unei persoane: "<<this -> nrAperitivePerPersoana;
        return out;
    }
    virtual float calcularePretNrClienti (int NrClienti)
    {
        return this -> pret * this -> nrAperitivePerPersoana * NrClienti;
    }
    virtual string detalii_aliment()
    {
        string rez = this -> nume;
        rez += "(contine " + this -> ingredientPrincipal + ")";
        return rez;
    }

};

///                                             CLASA SUC(ABSTRACTA)

class Suc
{
protected:
    const int idSuc;
    int volum;
    float pret;
    string nume;
public:
    static int contorIDSuc;
    Suc():idSuc(contorIDSuc++)
    {
        this -> volum = 0;
        this -> pret = 0;
        this -> nume = "Nedefinit";
    }
    Suc(int volum, float pret, string nume):idSuc(contorIDSuc++)
    {
        this -> volum = volum;
        this -> pret = pret;
        this -> nume = nume;
    }
    Suc(const int volum, string nume):idSuc(contorIDSuc++)
    {
        this -> volum = volum;
        this -> nume = nume;
    }
    Suc(const Suc& s):idSuc(contorIDSuc++)
    {
        this -> volum = s.volum;
        this -> pret = s.pret;
        this -> nume = s.nume;
    }
    ~Suc()
    {
        this -> volum = 0;
        this -> pret = 0;
    }
    Suc& operator=(const Suc& s)
    {
        if (this != &s)
        {
            this -> volum = s.volum;
            this -> pret = s.pret;
            this -> nume = s.nume;
        }
        return *this;
    }
    friend istream& operator>>(istream& in, Suc& s);
    friend ostream& operator<<(ostream& out,const Suc& s);
    virtual istream& CitireVirtuala(istream& in)
    {
        cout<<"\nNumele sucului: ";
        in>>this -> nume;
        cout<<"Volumul sucului(in mililitri): ";
        in>>this -> volum;
        cout<<"Pretul sucului: ";
        in>>this -> pret;
        return in;
    }
    virtual ostream& AfisareVirtuala(ostream& out)const
    {
        out<<"\nID suc: "<<this -> idSuc;
        out<<"\nNumele sucului: "<<this -> nume;
        out<<"\nVolumul sucului(in mililitri): "<<this -> volum;
        out<<"\nPretul sucului: "<<this -> pret;
        return out;
    }
    virtual float calcularePretSuc(int nrPer)=0;
    string getNume()
    {
        return this -> nume;
    }
};

istream& operator>>(istream& in, Suc& s)
{
    return s.CitireVirtuala(in);
}
ostream& operator<<(ostream& out,const Suc& s)
{
    return s.AfisareVirtuala(out);
}

///                                         CLASA SUCNATURAL

class SucNatural:public Suc
{
protected:
    int nrFructe;
    string* numeFructe;

public:
    SucNatural():Suc()
    {
        this -> nrFructe = 0;
        this -> numeFructe = NULL;
    }
    SucNatural(int volum, float pret, string nume, int nrFructe, string* numeFructe):Suc(volum,pret,nume)
    {
        this -> nrFructe = nrFructe;
        this -> numeFructe = new string[this -> nrFructe];
        for (int i = 0; i < this -> nrFructe; i++)
            this -> numeFructe[i] = numeFructe[i];
    }
    SucNatural(const SucNatural& s):Suc(s)
    {
        this -> nrFructe = s.nrFructe;
        this -> numeFructe = new string[this -> nrFructe];
        for (int i = 0; i < this -> nrFructe; i++)
            this -> numeFructe[i] = s.numeFructe[i];
    }
    ~SucNatural()
    {
        if (this -> numeFructe != NULL)
            delete[] this -> numeFructe;
    }
    Suc& operator=(const SucNatural& s)
    {
        if (this != &s)
        {
            Suc::operator=(s);
            if (this -> numeFructe != NULL)
                delete[] this -> numeFructe;
            this -> nrFructe = s.nrFructe;
            this -> numeFructe = new string[this -> nrFructe];
            for (int i = 0; i < this -> nrFructe; i++)
                this -> numeFructe[i] = s.numeFructe[i];
        }
        return *this;
    }
    virtual istream& CitireVirtuala(istream& in)
    {
        Suc::CitireVirtuala(in);
        cout<<"Numarul de fructe pe care le contine sucul: ";
        in>>this -> nrFructe;
        if (this -> numeFructe != NULL)
            delete[] this -> numeFructe;
        this -> numeFructe = new string[this -> nrFructe];
        cout<<"Numele fructelor pe care le contine("<<this -> nrFructe<<" intre spatii): ";
        for (int i = 0; i < this -> nrFructe; i++)
            in>>this -> numeFructe[i];
        return in;
    }
    virtual ostream& AfisareVirtuala(ostream& out)const
    {
        Suc::AfisareVirtuala(out);
        out<<"\nNumarul de fructe pe care le contine sucul: "<<this -> nrFructe;
        out<<"\nSucul contine fructele: ";
        if (this -> nrFructe > 0)
        {
            for (int i = 0; i < this -> nrFructe - 1; i++)
                out<<this -> numeFructe[i]<<", ";
            out<<this -> numeFructe[this -> nrFructe - 1];

        }
        return out;
    }
    virtual float calcularePretSuc(int nrPer)
    {
        return ((nrPer / ((this -> volum) / 500.0)) + 1) * this -> pret;
    }
};

///                                           CLASA SUCIMPORT

class SucImport:public Suc
{
protected:
    bool contineZahar;
    bool carbogazos;
public:
    SucImport():Suc()
    {
        this -> contineZahar = 0;
        this -> carbogazos = 0;
    }
    SucImport(int volum, float pret, string nume, bool contineZahar, bool carbogazos):Suc(volum, pret, nume)
    {
        this -> contineZahar = contineZahar;
        this -> carbogazos = carbogazos;
    }
    SucImport(const SucImport& s):Suc(s)
    {
        this -> contineZahar = s.contineZahar;
        this -> carbogazos = s.carbogazos;
    }
    ~SucImport()
    {
        this -> contineZahar = 0;
        this -> carbogazos = 0;
    }
    SucImport& operator=(const SucImport& s)
    {
        if (this != &s)
        {
            Suc::operator=(s);
            this -> contineZahar = s.contineZahar;
            this -> carbogazos = s.carbogazos;
        }
        return *this;
    }
    virtual istream& CitireVirtuala(istream& in)
    {
        Suc::CitireVirtuala(in);
        cout<<"Sucul contine zahar(1 DA / 0 NU): ";
        in>>this -> contineZahar;
        cout<<"Sucul este carbogazos(1 DA / 0 NU): ";
        in>>this -> carbogazos;
        return in;
    }
    virtual ostream& AfisareVirtuala(ostream& out)const
    {
        Suc::AfisareVirtuala(out);
        if (this -> contineZahar)
            out<<"\nSucul contine zahar";
        else
            out<<"\nSucul nu contine zahar";
        if (this -> carbogazos)
            out<<"\nSucul este carbogazos";
        else
            out<<"\nSucul nu este carbogazos";
        return out;
    }
    virtual float calcularePretSuc(int nrPer)
    {
        return ((nrPer / ((this -> volum) / 300.0)) + 1) * this -> pret;
    }

};


///                                         CLASA ACTIVITATE
class Activitate
{
private:
    const int idActivitate;
    string numeActivitate;
    int varstaRecomandata;
    float tarifSuplimentar;

public:
    static int contorIDActivitate;

    explicit operator float()              ///operatorul cast
    {
        return this -> tarifSuplimentar;
    }

//    float get_tarifSuplimentar()
//    {
//        return this -> tarifSuplimentar;
//    }
    string get_numeActivitate()
    {
        return this -> numeActivitate;
    }

    Activitate& operator=(const Activitate& a)///operator =
    {
        if(this != &a)
        {
            this -> numeActivitate = a.numeActivitate;
            this -> varstaRecomandata = a.varstaRecomandata;
            this -> tarifSuplimentar = a.tarifSuplimentar;
        }
        return *this;
    }
    friend istream& operator>>(istream& in, Activitate& a);
    friend ostream& operator<<(ostream& out, const Activitate& a);

    const Activitate& operator++()/// pre-incremenatre
    {
        this -> tarifSuplimentar += 5;  ///adauga 5 Ron
        return *this;
    }
    const Activitate operator++(int) ///post-incrementare
    {
        Activitate aux(*this);
        this -> tarifSuplimentar += 5;
        return aux;
    }
    bool operator>(const Activitate& a)
    {
        if(this -> tarifSuplimentar > a.tarifSuplimentar)
            return true;
        return false;
    }
    bool operator==(const Activitate& a)
    {
        if (this -> varstaRecomandata == a.varstaRecomandata && this -> tarifSuplimentar == a.tarifSuplimentar)
            return true;
        return false;
    }

    Activitate operator+(Activitate a)
    {
        a.numeActivitate = this -> numeActivitate + ", " + a.numeActivitate;
        a.varstaRecomandata = (this -> varstaRecomandata + a.varstaRecomandata) / 2;
        a.tarifSuplimentar += this -> tarifSuplimentar;
        return a;
    }

    Activitate():idActivitate(contorIDActivitate++)
    {
        this -> numeActivitate = "FaraNume";
        this -> varstaRecomandata = 0;
        this -> tarifSuplimentar = 0;
    }
    Activitate(string numeActivitate, const int varstaRecomandata, float tarifSuplimentar):idActivitate(contorIDActivitate++)
    {
        this -> numeActivitate = numeActivitate;
        this -> varstaRecomandata = varstaRecomandata;
        this -> tarifSuplimentar = tarifSuplimentar;
    }
    Activitate(const string numeActivitate):idActivitate(contorIDActivitate++)
    {
        this -> numeActivitate = numeActivitate;
    }
    Activitate(const Activitate& a):idActivitate(a.idActivitate)
    {
        this -> numeActivitate = a.numeActivitate;
        this -> varstaRecomandata = a.varstaRecomandata;
        this -> tarifSuplimentar = a.tarifSuplimentar;
    }

    ~Activitate()
    {

    }

    int get_idActivitate()
    {
        return this -> idActivitate;
    }

};

istream& operator>>(istream& in, Activitate& a)
{
    cout<<"Numele activitatii(Fara spatii): ";
    in>>a.numeActivitate;
    cout<<"Varsta recomandata pentru activitate(5-12 ani): ";
    in>>a.varstaRecomandata;
    while (a.varstaRecomandata < 5 || a.varstaRecomandata > 12)
    {
        cout<<"Varsta nevalida, introduceti varsta in intervalul 5-12: ";
        in>>a.varstaRecomandata;
    }
    cout<<"Tarif suplimentar pentru activitate: ";
    in>>a.tarifSuplimentar;
    return in;
}
ostream& operator<<(ostream& out, const Activitate& a)
{
    out<<"\nID activitate: "<<a.idActivitate;
    out<<"\nNume activitate:  "<<a.numeActivitate;
    out<<"\nVarsta recomandata pentru activitate: "<<a.varstaRecomandata;
    out<<"\nTarif suplimentar pentru activitate: "<<a.tarifSuplimentar;
    return out;
}





///                                             CLASA LOCATIE
class Locatie
{
private:
    const int idLocatie;

    string numeLoc;
    int capacitateMax;

    bool amenajareParinti;

    char initialaSupervizor;
    char* numeSupervizor;

    int* program;///ora de inceput si ora de final
    float tarifInchiriereOra;
    float* tarifInchiriereOreSuplimentare;///maxim 3 valori, pentru mai mult de 3 ore suplimentare se repeta al treilea tarif
    double tarifDj;

    int nrPersonalAux;
    string* numePersonalAux;

public:
    static int contorIDLocatie;

///Constructori/Destructor
    Locatie();
    Locatie(string numeLoc, const int capacitateMax, bool amenajareParinti, char initialaSupervizor, char* numeSupervizor, int* program, float tarifInchiriereOra, float* tarifInchiriereOreSuplimentare, double tarifDj, const int nrPersonalAux, string* numePersonalAux);
    Locatie(string numeLoc, int capacitateMax,const bool amenajareParinti);
    Locatie(const Locatie& loc);
    ~Locatie();

///Operatori
    string operator[](int index);
    Locatie& operator=(const Locatie& loc);
    friend istream& operator>>(istream& in, Locatie& loc);
    friend ostream& operator<<(ostream& out,const Locatie& loc);

/// Setters
    void set_numeLoc(string numeLoc);
    void set_capacitateMax(int capacitateMax);
    void set_amenajareParinti(bool amenajareParinti);
    void set_initialaSupervizor(char initialaSupervizor);
    void set_numeSupervizor(char* numeSupervizor);
    void set_program(int* program);
    void set_tarifInchiriereOra(float tarifInchiriereOra);
    void set_tarifInchiriereOreSuplimentare(float* tarifInchiriereOreSuplimentare);
    void set_tarifDj(double tarifDj);
    void set_nrPersonalAux(int nrPersonalAux);
    void set_numePersonalAux(string* numePersonalAux,const int nrPersonalAux);
/// Getters
    int get_idLocatie();
    string get_numeLoc();
    int get_capacitateMax();
    bool get_amenajareParinti();
    char get_initialaSupervizor();
    char* get_numeSupervizor();
    int* get_program();
    float get_tarifInchiriereOra();
    float* get_tarifInchiriereOreSuplimentare();
    double get_tarifDj();
    int get_nrPersonalAux();
    string* get_numePersonalAux();

};

Locatie::Locatie():idLocatie(contorIDLocatie++)
{
    this -> numeLoc = "FaraNume";
    this -> capacitateMax = 0;
    this -> amenajareParinti = false;
    this -> initialaSupervizor = 'a';
    this -> numeSupervizor = new char[strlen("Anonim")+1];
    strcpy(this -> numeSupervizor, "Anonim");
    this -> program = NULL;
    this -> tarifInchiriereOra = 0;
    this -> tarifInchiriereOreSuplimentare = NULL;
    this -> tarifDj = 0;
    this -> nrPersonalAux = 0;
    this -> numePersonalAux = NULL;
}

Locatie::Locatie(string numeLoc, const int capacitateMax, bool amenajareParinti, char initialaSupervizor, char* numeSupervizor, int* program, float tarifInchiriereOra, float* tarifInchiriereOreSuplimentare, double tarifDj, const int nrPersonalAux, string* numePersonalAux):idLocatie(contorIDLocatie++)
{
    this -> numeLoc = numeLoc;
    this -> capacitateMax = capacitateMax;
    this -> amenajareParinti = amenajareParinti;
    this -> initialaSupervizor = initialaSupervizor;
    this -> numeSupervizor = new char[strlen(numeSupervizor)+1];
    strcpy(this -> numeSupervizor, numeSupervizor);
    this -> program = new int[2];
    this -> program[0] = program[0]; this -> program[1] = program[1];
    this -> tarifInchiriereOra = tarifInchiriereOra;
    this -> tarifInchiriereOreSuplimentare = new float[3];
    this -> tarifInchiriereOreSuplimentare[0] = tarifInchiriereOreSuplimentare[0]; this -> tarifInchiriereOreSuplimentare[1] = tarifInchiriereOreSuplimentare[1]; this -> tarifInchiriereOreSuplimentare[2] = tarifInchiriereOreSuplimentare[2];
    this -> tarifDj = tarifDj;
    this -> nrPersonalAux = nrPersonalAux;
    this -> numePersonalAux = new string[this -> nrPersonalAux];
    for (int i = 0; i < this -> nrPersonalAux; i++)
        this -> numePersonalAux[i] = numePersonalAux[i];
}

Locatie::Locatie(string numeLoc, int capacitateMax,const bool amenajareParinti):idLocatie(contorIDLocatie++)
{
    this -> numeLoc = numeLoc;
    this -> capacitateMax = capacitateMax;
    this -> amenajareParinti = amenajareParinti;
}
Locatie::Locatie(const Locatie& loc):idLocatie(loc.idLocatie)
{
    this -> numeLoc = loc.numeLoc;
    this -> capacitateMax = loc.capacitateMax;
    this -> amenajareParinti = loc.amenajareParinti;
    this -> initialaSupervizor = loc.initialaSupervizor;
    this -> numeSupervizor = new char[strlen(loc.numeSupervizor)+1];
    strcpy(this -> numeSupervizor, loc.numeSupervizor);
    this -> program = new int[2];
    this -> program[0] = loc.program[0]; this -> program[1] = loc.program[1];
    this -> tarifInchiriereOra = loc.tarifInchiriereOra;
    this -> tarifInchiriereOreSuplimentare = new float[3];
    this -> tarifInchiriereOreSuplimentare[0] = loc.tarifInchiriereOreSuplimentare[0]; this -> tarifInchiriereOreSuplimentare[1] = loc.tarifInchiriereOreSuplimentare[1]; this -> tarifInchiriereOreSuplimentare[2] = loc.tarifInchiriereOreSuplimentare[2];
    this -> tarifDj = loc.tarifDj;
    this -> nrPersonalAux = loc.nrPersonalAux;
    this -> numePersonalAux = new string[this -> nrPersonalAux];
    for (int i = 0; i < this -> nrPersonalAux; i++)
        this -> numePersonalAux[i] = loc.numePersonalAux[i];
}


Locatie::~Locatie()
{
    if (this -> numeSupervizor != NULL)
        delete[] this -> numeSupervizor;
    if (this -> program != NULL)
        delete[] this -> program;
    if (this -> tarifInchiriereOreSuplimentare != NULL)
        delete[] this -> tarifInchiriereOreSuplimentare;
    if (this -> numePersonalAux != NULL)
        delete[] this -> numePersonalAux;
}

string Locatie::operator[](int index)
{
    if (0 <= index && index < this->nrPersonalAux)
        return this -> numePersonalAux[index];
    else
        cout<<"Indexul este gresit";
}
Locatie& Locatie::operator=(const Locatie& loc)
{
    if (this != &loc)
    {
        if (this -> numeSupervizor != NULL)
            delete[] this -> numeSupervizor;
        if (this -> program != NULL)
            delete[] this -> program;
        if (this -> tarifInchiriereOreSuplimentare != NULL)
            delete[] this -> tarifInchiriereOreSuplimentare;
        if (this -> numePersonalAux != NULL)
            delete[] this -> numePersonalAux;

        this -> numeLoc = loc.numeLoc;
        this -> capacitateMax = loc.capacitateMax;
        this -> amenajareParinti = loc.amenajareParinti;
        this -> initialaSupervizor = loc.initialaSupervizor;
        this -> numeSupervizor = new char[strlen(loc.numeSupervizor)+1];
        strcpy(this -> numeSupervizor, loc.numeSupervizor);
        this -> program = new int[2];
        this -> program[0] = loc.program[0]; this -> program[1] = loc.program[1];
        this -> tarifInchiriereOra = loc.tarifInchiriereOra;
        this -> tarifInchiriereOreSuplimentare = new float[3];
        this -> tarifInchiriereOreSuplimentare[0] = loc.tarifInchiriereOreSuplimentare[0]; this -> tarifInchiriereOreSuplimentare[1] = loc.tarifInchiriereOreSuplimentare[1]; this -> tarifInchiriereOreSuplimentare[2] = loc.tarifInchiriereOreSuplimentare[2];
        this -> tarifDj = loc.tarifDj;
        this -> nrPersonalAux = loc.nrPersonalAux;
        this -> numePersonalAux = new string[this -> nrPersonalAux];
        for (int i = 0; i < this -> nrPersonalAux; i++)
            this -> numePersonalAux[i] = loc.numePersonalAux[i];
    }
    return *this;
}
istream& operator>>(istream& in, Locatie& loc)
{
    cout<<"\nNumele locatiei(fara spatii): ";
    in>>loc.numeLoc;
    cout<<"Capacitate maxima: ";
    in>>loc.capacitateMax;
    cout<<"Locatia are spatiu destinat parintilor(1 Da/0 Nu): ";
    in>>loc.amenajareParinti;
    cout<<"Initiala supervizor: ";
    in>>loc.initialaSupervizor;
    if(loc.numeSupervizor != NULL)
        delete[] loc.numeSupervizor;
    char aux[100];
    cout<<"Numele supervizorului: ";
    in>>aux;
    loc.numeSupervizor = new char[strlen(aux)+1];
    strcpy(loc.numeSupervizor, aux);
    if (loc.program != NULL)
        delete[] loc.program;
    loc.program = new int[2];
    cout<<"Ora de deschidere/inchidere(separate prin spatiu in format 24h): ";
    in>>loc.program[0]>>loc.program[1];
    cout<<"Tarif inchiriere pret/ora: ";
    in>>loc.tarifInchiriereOra;
    if (loc.tarifInchiriereOreSuplimentare != NULL)
        delete[] loc.tarifInchiriereOreSuplimentare;
    loc.tarifInchiriereOreSuplimentare = new float[3];
    cout<<"Tarif ore suplimentare (3 valori separate prin spatiu): ";
    for (int i = 0; i < 3; i++)
        in>>loc.tarifInchiriereOreSuplimentare[i];
    cout<<"Tarif DJ: ";
    in>>loc.tarifDj;
    cout<<"Numar de angajati auxiliari: ";
    in>>loc.nrPersonalAux;
    if (loc.numePersonalAux != NULL)
        delete[] loc.numePersonalAux;
    loc.numePersonalAux = new string[loc.nrPersonalAux];
    cout<<"Numele angajatilor auxiliari("<<loc.nrPersonalAux<<" separate prin spatii): ";
    for (int i = 0; i < loc.nrPersonalAux; i++)
        in>>loc.numePersonalAux[i];
    return in;
}
ostream& operator<<(ostream& out,const Locatie& loc)
{
    out<<"\nID locatie: "<<loc.idLocatie;
    out<<"\nNume locatie: "<<loc.numeLoc;
    out<<"\nCapacitate maxima: "<<loc.capacitateMax;
    out<<"\nLocatia are spatiu destinat parintilor(1 Da/0 Nu): "<<loc.amenajareParinti;
    out<<"\nInitiala supervizor: "<<loc.initialaSupervizor;
    out<<"\nNume supervizor: "<<loc.numeSupervizor;
    if (loc.program != NULL)
        out<<"\nProgram locatie: "<<loc.program[0]<<'-'<<loc.program[1];
    out<<"\nTarif inchiriere pret/ora: "<<loc.tarifInchiriereOra;
    if (loc.tarifInchiriereOreSuplimentare != NULL)
        out<<"\nTarif ore suplimentare:\n\to ora suplimentara: "<<loc.tarifInchiriereOreSuplimentare[0]<<"\n\tdoua ore suplimentare: "<<loc.tarifInchiriereOreSuplimentare[1]<<"\n\ttrei ore sau mai mult: "<<loc.tarifInchiriereOreSuplimentare[2];
    out<<"\nTarif DJ: "<<loc.tarifDj;
    out<<"\nNumar angajati auxiliari: "<<loc.nrPersonalAux;

    if (loc.numePersonalAux != NULL)
    {
        out<<"\nNume angajati auxiliari: ";
        for (int i = 0; i < loc.nrPersonalAux-1; i++)
            out<<loc.numePersonalAux[i]<<", ";
        out<<loc.numePersonalAux[loc.nrPersonalAux-1];
    }
    return out;
}
void Locatie::set_numeLoc(string numeLoc)
{
    this -> numeLoc = numeLoc;
}
void Locatie::set_capacitateMax(int capacitateMax)
{
    this -> capacitateMax = capacitateMax;
}
void Locatie::set_amenajareParinti(bool amenajareParinti)
{
    this -> amenajareParinti = amenajareParinti;
}
void Locatie::set_initialaSupervizor(char initialaSupervizor)
{
    this -> initialaSupervizor = initialaSupervizor;
}
void Locatie::set_numeSupervizor(char* numeSupervizor)
{
    if (this -> numeSupervizor != NULL)
        delete[] this -> numeSupervizor;
    this -> numeSupervizor = new char[strlen(numeSupervizor)+1];
    strcpy(this -> numeSupervizor, numeSupervizor);
}
void Locatie::set_program(int* program)
{
    if(this -> program != NULL)
        delete[] program;
    this -> program = new int[2];
    this -> program[0] = program[0];
    this -> program[1] = program[1];
}
void Locatie::set_tarifInchiriereOra(float tarifInchiriereOra)
{
    this -> tarifInchiriereOra = tarifInchiriereOra;
}
void Locatie::set_tarifInchiriereOreSuplimentare(float* tarifInchiriereOreSuplimentare)
{
    if(this -> tarifInchiriereOreSuplimentare != NULL)
        delete[] tarifInchiriereOreSuplimentare;
    this -> tarifInchiriereOreSuplimentare = new float[3];
    for (int i = 0; i < 3; i++)
        this -> tarifInchiriereOreSuplimentare[i] = this ->tarifInchiriereOreSuplimentare[i];
}
void Locatie::set_tarifDj(double tarifDj)
{
    this -> tarifDj = tarifDj;
}
void Locatie::set_nrPersonalAux(int nrPersonalAux)
{
    this -> nrPersonalAux = nrPersonalAux;
}
void Locatie::set_numePersonalAux(string* numePersonalAux,const int nrPersonalAux)
{
    if( this-> numePersonalAux != NULL)
        delete[] this -> numePersonalAux;
    this -> numePersonalAux = new string[nrPersonalAux];
    for (int i = 0; i < nrPersonalAux; i++)
        this -> numePersonalAux[i] = numePersonalAux[i];
}

int Locatie::get_idLocatie()
{
    return this -> idLocatie;
}

string Locatie::get_numeLoc()
{
    return this -> numeLoc;
}
int Locatie::get_capacitateMax()
{
    return this -> capacitateMax;
}
bool Locatie::get_amenajareParinti()
{
    return amenajareParinti;
}
char Locatie::get_initialaSupervizor()
{
    return this -> initialaSupervizor;
}
char* Locatie::get_numeSupervizor()
{
    return this -> numeSupervizor;
}
int* Locatie::get_program()
{
    return this -> program;
}
float Locatie::get_tarifInchiriereOra()
{
    return this -> tarifInchiriereOra;
}
float* Locatie::get_tarifInchiriereOreSuplimentare()
{
    return this -> tarifInchiriereOreSuplimentare;
}
double Locatie::get_tarifDj()
{
    return this -> tarifDj;
}
int Locatie::get_nrPersonalAux()
{
    return this -> nrPersonalAux;
}
string* Locatie::get_numePersonalAux()
{
    return this -> numePersonalAux;
}



///                                                     CLASA ANIMATOR
class Animator
{
private:
    const int idAnimator;
    string nume;
    string prenume;
    int varsta;
    float salariu;
    char* specializare;
public:
    static int contorIdAnimator;
    Animator();
    Animator(string nume, string prenume, int varsta, const float salariu, char* specializare);
    Animator(string nume, string prenume, char* specializare);
    Animator(string nume, string prenume, const float salariu);
    Animator(const Animator& a);
    ~Animator();

    Animator& operator=(const Animator& a);
    friend istream& operator>>(istream& in, Animator& a);
    friend ostream& operator<<(ostream& out,const Animator& a);
    Animator operator+(int x);
    Animator operator+=(int x);
    Animator operator-(int x);

    int get_idAnimator()
    {
        return this -> idAnimator;
    }

    string get_nume();
    string get_prenume();
    char* get_specializare();
    float get_salariu();

    void set_varsta(const int varsta);
};

Animator::Animator():idAnimator(contorIdAnimator++)
{
    this -> nume = "Anonim";
    this -> prenume = "Anonimus";
    this -> varsta = 0;
    this -> salariu = 0;
    this -> specializare = NULL;
}
Animator::Animator(string nume, string prenume, int varsta, const float salariu, char* specializare):idAnimator(contorIdAnimator++)
{
    this -> nume = nume;
    this -> prenume = prenume;
    this -> salariu = salariu;
    this -> varsta = varsta;
    if (this -> specializare != NULL)
        delete[] this -> specializare;
    this -> specializare = new char[strlen(specializare)+1];
    strcpy(this -> specializare, specializare);
}
Animator::Animator(string nume, string prenume, char* specializare):idAnimator(contorIdAnimator++)
{
    this -> nume = nume;
    this -> prenume = prenume;
    if (this -> specializare != NULL)
        delete[] this -> specializare;
    this -> specializare = new char[strlen(specializare)+1];
    strcpy(this -> specializare, specializare);
}
Animator::Animator(string nume, string prenume, const float salariu):idAnimator(contorIdAnimator++)
{
    this -> nume = nume;
    this -> prenume = prenume;
    this -> salariu = salariu;
}
Animator::Animator(const Animator& a):idAnimator(a.idAnimator)
{
    this -> nume = a.nume;
    this -> prenume = a.prenume;
    this -> salariu = a.salariu;
    this -> varsta = a.varsta;
    this -> specializare = new char[strlen(a.specializare)+1];
    strcpy(this -> specializare, a.specializare);
}
Animator::~Animator()
{
    if (this -> specializare != NULL)
        delete[] this -> specializare;
}
Animator& Animator::operator=(const Animator& a)
{
    if (this != &a)
    {
        if (this -> specializare != NULL)
            delete[] this -> specializare;
        this -> nume = a.nume;
        this -> prenume = a.prenume;
        this -> salariu = a.salariu;
        this -> varsta = a.varsta;
        this -> specializare = new char[strlen(a.specializare)+1];
        strcpy(this -> specializare, a.specializare);
    }
    return *this;
}
istream& operator>>(istream& in, Animator& a)
{
    cout<<"\nNume animator: ";
    in>>a.nume;
    cout<<"Prenume animator: ";
    in>>a.prenume;
    cout<<"Varsta animator: ";
    in>>a.varsta;
    cout<<"Salariu animator: ";
    in>>a.salariu;
    cout<<"Specializare animator: ";
    if (a.specializare != NULL)
        delete[] a.specializare;
    char c[100];
    in>>c;
    a.specializare = new char[strlen(c)+1];
    strcpy(a.specializare, c);
    return in;
}
ostream& operator<<(ostream& out,const Animator& a)
{
    out<<"\nID animator: "<<a.idAnimator;
    out<<"\nNume animator: "<<a.nume;
    out<<"\nPrenume animator: "<<a.prenume;
    out<<"\nVarsta animator: "<<a.varsta;
    out<<"\nSalariu animator: "<<a.salariu;
    if (a.specializare != NULL)
        out<<"\nSpecializare animator: "<<a.specializare;
    return out;
}
Animator Animator::operator+(int x)
{
    Animator aux(*this);
    aux.salariu += x;

    return aux;
}
Animator Animator::operator+=(int x)
{
    this -> salariu += x;
    return *this;
}
Animator Animator::operator-(int x)
{
    Animator aux(*this);
    aux.salariu -= x;

    return aux;
}

string Animator::get_nume()
{
    return this -> nume;
}
string Animator::get_prenume()
{
    return this -> prenume;
}
float Animator::get_salariu()
{
    return this -> salariu;
}
char* Animator::get_specializare()
{
    return this -> specializare;
}
void Animator::set_varsta(const int varsta)
{
    this -> varsta = varsta;
}

///                                                 CLASA CLIENT
class Client
{
private:
    const int idClient;
    string nume;
    string prenume;
    char* telefon;
    string prenumeSarbatorit;
    int ziInchiriere;
    int lunaInchiriere;
    int oraInceput;
    int oraFinal;
    int varstaSarbatorit;
    int nrParticipanti;
    string numeLocatie;
    int nrActivitati;
    string* activitatiOnomastica;
    Aliment* tort;                      ///HAS a + virtualizare la citire
    vector<Suc*> listaSucuri;
    vector<Aperitiv*> listaAperitive;
public:
    static int contorIDClient;
    Client();
    Client(string nume, string prenume, char* telefon, string prenumeSarbatorit, int ziInchiriere, int lunaInchiriere, int oraInceput, int oraFinal, int varstaSarbatorit, int nrParticipanti, string numeLocatie, int nrActivitati, string* activitatiOnomastica, Aliment* tort, vector<Suc*> listaSucuri, vector<Aperitiv*> listaAperitive);
    Client(string nume, string prenume, char* telefon, int ziInchiriere, int lunaInchiriere);
    Client(const Client& c);
    ~Client();

    Client& operator=(const Client& c);
    friend istream& operator>>(istream& in, Client& c);
    friend ostream& operator<<(ostream& out,const Client& c);


    void restProgramare(string numeLocatie, int nrActivitati, string* activitatiOnomastica, Aliment* tort, vector<Suc*> listaSucuri, vector<Aperitiv*> listaAperitive)
    {

        this -> numeLocatie = numeLocatie;
        this -> nrActivitati = nrActivitati;
        if (this -> activitatiOnomastica != NULL)
            delete[] this -> activitatiOnomastica;

        this -> activitatiOnomastica = new string[nrActivitati];
        for (int i = 0; i < nrActivitati; i++)
            this -> activitatiOnomastica[i] = activitatiOnomastica[i];
        if (this -> tort != NULL)
            delete this -> tort;

        this -> tort = new Tort;
        static_cast<Tort&>(*(this -> tort)) = static_cast<Tort&>(*tort);

        this -> listaSucuri = listaSucuri;
        this -> listaAperitive = listaAperitive;
    }

    int get_ziInchiriere();
    int get_lunaInchiriere();
    int get_oraInceput();
    int get_oraFinal();
    int get_nrParticipanti()
    {
        return this -> nrParticipanti;
    }
    string get_numeLocatie()
    {
        return this -> numeLocatie;
    }
    void creareProgramare() ///pentru meniu(unde nu pot citi si produsele de la tastatura
    {
        cout<<"\nNume client: ";
        cin>>this -> nume;
        cout<<"Prenume client: ";
        cin>>this -> prenume;
        cout<<"Numarul de telefon al clientului: ";
        char tel[11];
        cin>>tel;
        if (this -> telefon != NULL)
            delete[] this -> telefon;
        this -> telefon = new char[11];
        strcpy(this -> telefon, tel);
        cout<<"Prenumele sarbatoritului: ";
        cin>>this -> prenumeSarbatorit;
        cout<<"Ziua de inchiriere: ";
        cin>>this -> ziInchiriere;
        cout<<"Luna inchiriere: ";
        cin>>this -> lunaInchiriere;
        cout<<"Ora de inceput a petrecerii: ";
        cin>>this -> oraInceput;
        cout<<"Ora de final a petrecerii: ";
        cin>>this -> oraFinal;
        cout<<"Varsta sarbatoritului: ";
        cin>>this -> varstaSarbatorit;
        cout<<"Numarul de participanti: ";
        cin>>this -> nrParticipanti;
    }
};
    Client::Client():idClient(contorIDClient++)
    {
        this -> nume = "Anonim";
        this -> prenume = "Anonimus";
        this -> telefon = NULL;
        this -> prenumeSarbatorit = "Anonim";
        this -> ziInchiriere = 0;
        this -> lunaInchiriere = 0;
        this -> oraInceput = 0;
        this -> oraFinal = 0;
        this -> varstaSarbatorit = 0;
        this -> nrParticipanti = 0;
        this -> numeLocatie = "Locatie_nedefinita";
        this -> nrActivitati = 0;
        this -> activitatiOnomastica = NULL;
        this -> tort = NULL;
    }
    Client::Client(string nume, string prenume, char* telefon, string prenumeSarbatorit, int ziInchiriere, int lunaInchiriere, int oraInceput, int oraFinal, int varstaSarbatorit, int nrParticipanti, string numeLocatie, int nrActivitati, string* activitatiOnomastica, Aliment* tort, vector<Suc*> listaSucuri, vector<Aperitiv*> listaAperitive):idClient(contorIDClient++)
    {
        this -> nume = nume;
        this -> prenume = prenume;
        this -> telefon = new char[strlen(telefon)+1];
        strcpy(this -> telefon, telefon);
        this -> prenumeSarbatorit = prenumeSarbatorit;
        this -> ziInchiriere = ziInchiriere;
        this -> lunaInchiriere = lunaInchiriere;
        this -> oraInceput = oraInceput;
        this -> oraFinal = oraFinal;
        this -> varstaSarbatorit = varstaSarbatorit;
        this -> nrParticipanti = nrParticipanti;
        this -> numeLocatie = numeLocatie;
        this -> nrActivitati = nrActivitati;
        this -> activitatiOnomastica = new string[this -> nrActivitati];
        for (int i = 0; i < this -> nrActivitati; i++)
            this -> activitatiOnomastica[i] = activitatiOnomastica[i];
        this -> tort = new Tort;
        static_cast<Tort&>(*(this -> tort)) = static_cast<Tort&>(*tort);
        for (int i = 0; i < listaSucuri.size(); i++)
        {
            this -> listaSucuri.push_back(listaSucuri[i]);
        }
        for (int i = 0; i < listaAperitive.size(); i++)
        {
            this -> listaAperitive.push_back(listaAperitive[i]);
        }

    }
    Client::Client(string nume, string prenume, char* telefon, int ziInchiriere, int lunaInchiriere):idClient(contorIDClient++)
    {
        this -> nume = nume;
        this -> prenume = prenume;
        this -> telefon = new char[strlen(telefon)+1];
        strcpy(this -> telefon, telefon);
        this -> prenumeSarbatorit = prenumeSarbatorit;
        this -> ziInchiriere = ziInchiriere;
        this -> lunaInchiriere = lunaInchiriere;
    }
    Client::Client(const Client& c):idClient(c.idClient)
    {
        this -> nume = c.nume;
        this -> prenume = c.prenume;
        this -> telefon = new char[strlen(c.telefon)+1];
        strcpy(this -> telefon, c.telefon);
        this -> prenumeSarbatorit = c.prenumeSarbatorit;
        this -> ziInchiriere = c.ziInchiriere;
        this -> lunaInchiriere = c.lunaInchiriere;
        this -> oraInceput = c.oraInceput;
        this -> oraFinal = c.oraFinal;
        this -> varstaSarbatorit = c.varstaSarbatorit;
        this -> nrParticipanti = c.nrParticipanti;
        this -> numeLocatie = c.numeLocatie;
        this -> nrActivitati = c.nrActivitati;
        this -> activitatiOnomastica = new string[this -> nrActivitati];
        for (int i = 0; i < this -> nrActivitati; i++)
            this -> activitatiOnomastica[i] = c.activitatiOnomastica[i];
        this -> tort = new Tort;
        static_cast<Tort&>(*(this -> tort)) = static_cast<Tort&>(*c.tort);
        for (int i = 0; i < c.listaSucuri.size(); i++)
        {
            this -> listaSucuri.push_back(c.listaSucuri[i]);
        }
        for (int i = 0; i < c.listaAperitive.size(); i++)
        {
            this -> listaAperitive.push_back(c.listaAperitive[i]);
        }
    }
    Client::~Client()
    {
        if ( this -> telefon != NULL)
            delete[] this -> telefon;
        if (this -> activitatiOnomastica != NULL)
            delete[] this -> activitatiOnomastica;
        if (this -> tort != NULL)
            delete this -> tort;
        if (!this -> listaSucuri.empty())
            this -> listaSucuri.clear();
        if (!this -> listaAperitive.empty())
            this -> listaAperitive.clear();
    }

    Client& Client::operator=(const Client& c)
    {
        if(this != &c)
        {
            if ( this -> telefon != NULL)
                delete[] this -> telefon;
            if (this -> activitatiOnomastica != NULL)
                delete[] this -> activitatiOnomastica;
            if (this -> tort != NULL)
                delete this -> tort;
            if (!this -> listaSucuri.empty())
                this -> listaSucuri.clear();
            if (!this -> listaAperitive.empty())
                this -> listaAperitive.clear();

            this -> nume = c.nume;
            this -> prenume = c.prenume;
            this -> telefon = new char[strlen(c.telefon)+1];
            strcpy(this -> telefon, c.telefon);
            this -> prenumeSarbatorit = c.prenumeSarbatorit;
            this -> ziInchiriere = c.ziInchiriere;
            this -> lunaInchiriere = c.lunaInchiriere;
            this -> oraInceput = c.oraInceput;
            this -> oraFinal = c.oraFinal;
            this -> varstaSarbatorit = c.varstaSarbatorit;
            this -> nrParticipanti = c.nrParticipanti;
            this -> numeLocatie = c.numeLocatie;
            this -> nrActivitati = c.nrActivitati;
            this -> activitatiOnomastica = new string[this -> nrActivitati];
            for (int i = 0; i < this -> nrActivitati; i++)
                this -> activitatiOnomastica[i] = c.activitatiOnomastica[i];
            this -> tort = new Tort;
            static_cast<Tort&>(*(this -> tort)) = static_cast<Tort&>(*c.tort);

            for (int i = 0; i < c.listaSucuri.size(); i++)
            {
                this -> listaSucuri.push_back(c.listaSucuri[i]);
            }
            for (int i = 0; i < c.listaAperitive.size(); i++)
            {
                this -> listaAperitive.push_back(c.listaAperitive[i]);
            }

        }
        return *this;
    }
    istream& operator>>(istream& in, Client& c)
    {
        cout<<"\nNume client: ";
        in>>c.nume;
        cout<<"Prenume client: ";
        in>>c.prenume;
        cout<<"Numarul de telefon al clientului: ";
        char tel[11];
        in>>tel;
        if (c.telefon != NULL)
            delete[] c.telefon;
        c.telefon = new char[11];
        strcpy(c.telefon, tel);
        cout<<"Prenumele sarbatoritului: ";
        in>>c.prenumeSarbatorit;
        cout<<"Ziua de inchiriere: ";
        in>>c.ziInchiriere;
        cout<<"Luna inchiriere: ";
        in>>c.lunaInchiriere;
        cout<<"Ora de inceput a petrecerii: ";
        in>>c.oraInceput;
        cout<<"Ora de final a petrecerii: ";
        in>>c.oraFinal;
        cout<<"Varsta sarbatoritului: ";
        in>>c.varstaSarbatorit;
        cout<<"Numarul de participanti: ";
        in>>c.nrParticipanti;
        cout<<"Nume locatie: ";
        in>>c.numeLocatie;
        cout<<"Numar de activitati alese: ";
        in>>c.nrActivitati;
        if (c.activitatiOnomastica != NULL)
            delete[] c.activitatiOnomastica;
        c.activitatiOnomastica = new string[c.nrActivitati];
        cout<<"Numele activitatilor alese("<<c.nrActivitati<<" separate prin spatii): ";
        for (int i = 0; i < c.nrActivitati; i++)
            in>>c.activitatiOnomastica[i];
        if (c.tort != NULL)
            delete c.tort;
        c.tort = new Tort;
        cout<<"Detalii legate de tort";
        in>>*c.tort;

        if (!c.listaSucuri.empty())
            c.listaSucuri.clear();
        int nrSucuri;
        cout<<"Numar sucuri: ";
        in>>nrSucuri;
        for (int i = 0; i < nrSucuri; i++)
        {
            int tip;
            cout<<"Tipul sucului(NATURAL 0/IMPORT 1): ";
            in>>tip;
            if (tip == 0)
            {
//                Suc *s = new SucNatural;
//                in>>*s;
//                c.listaSucuri.push_back(s);
                Suc *s;
                c.listaSucuri.push_back(s);
                c.listaSucuri[c.listaSucuri.size()-1] = new SucNatural;
                in>>*c.listaSucuri[c.listaSucuri.size()-1];
            }
            else
            {
//                Suc *s = new SucImport;
//                in>>*s;
//                c.listaSucuri.push_back(s);
                Suc *s;
                c.listaSucuri.push_back(s);
                c.listaSucuri[c.listaSucuri.size()-1] = new SucImport;
                in>>*c.listaSucuri[c.listaSucuri.size()-1];
            }
        }

        if (!c.listaAperitive.empty())
            c.listaAperitive.clear();
        int nrAperitive;
        cout<<"Numar aperitive: ";
        in>>nrAperitive;
        for (int i = 0; i < nrAperitive; i++)
        {
            Aperitiv *a = new Aperitiv;
            in>>*a;
            c.listaAperitive.push_back(a);
        }

        return in;

    }
    ostream& operator<<(ostream& out,const Client& c)
    {
        out<<"\nID client: "<<c.idClient;
        out<<"\nNume client: "<<c.nume;
        out<<"\nPrenume client: "<<c.prenume;
        if (c.telefon != NULL)
            out<<"\nNumarul de telefon al clientului: "<<c.telefon;
        out<<"\nPrenumele sarbatoritului: "<<c.prenumeSarbatorit;
        out<<"\nZiua de inchiriere: "<<c.ziInchiriere;
        out<<"\nLuna de inchiriere: "<<c.lunaInchiriere;
        out<<"\nOra de inceput a petrecerii: "<<c.oraInceput;
        out<<"\nOra de final a petrecerii: "<<c.oraFinal;
        out<<"\nVarsta sarbatoritului: "<<c.varstaSarbatorit;
        out<<"\nNumarul de participanti: "<<c.nrParticipanti;
        out<<"\nNumele locatiei alese: "<<c.numeLocatie;
        out<<"\nNumar de activitati alese: "<<c.nrActivitati;
        if (c.activitatiOnomastica != NULL)
        {
            out<<"\nNumele activitatilor alese: ";
            for (int i = 0; i < c.nrActivitati-1; i++)
                out<<c.activitatiOnomastica[i]<<", ";
            out<<c.activitatiOnomastica[c.nrActivitati-1];
        }
        if (c.tort != NULL)
        {
            out<<"\nDetalii tort: "<<c.tort->detalii_aliment();
        }

        if (!c.listaSucuri.empty())
        {
            out<<"\nSucuri: ";
            for (int i = 0; i < c.listaSucuri.size() - 1; i++)
                out<<c.listaSucuri[i]->getNume()<<", ";
            out<<c.listaSucuri[c.listaSucuri.size()-1]->getNume();
        }
        if (!c.listaAperitive.empty())
        {
            out<<"\nAperitive: ";
            for (int i = 0; i < c.listaAperitive.size()-1; i++)
                out<<c.listaAperitive[i]->detalii_aliment()<<", ";
            out<<c.listaAperitive[c.listaAperitive.size()-1]->detalii_aliment();
        }

        return out;

    }
    int Client::get_ziInchiriere()
    {
        return this -> ziInchiriere;
    }
    int Client::get_lunaInchiriere()
    {
        return this -> lunaInchiriere;
    }
    int Client::get_oraInceput()
    {
        return this -> oraInceput;
    }
    int Client::get_oraFinal()
    {
        return this -> oraFinal;
    }




int Locatie::contorIDLocatie=10;
int Animator::contorIdAnimator=1000;
int Activitate::contorIDActivitate=100;
int Client::contorIDClient=10000;
int Aliment::contorIDAliment=1000;
int Suc::contorIDSuc=1000;


int calcTarifActivit(Activitate* activitati, int nrActivitati)/// functionalitate Activitate (calculeaza tariful pentru mai multe activitati)
{
    float sum = 0;
    for (int i = 0; i < nrActivitati; i++)
        sum += (float)activitati[i];
    return sum;

}
int calcTarifIntervalLocatie(Locatie loc, int end, int start)///functionalitate Locatie (calculeaza tariful pentru inchirierea intre 2 ore)
{
        return (end - start) * loc.get_tarifInchiriereOra() + loc.get_tarifDj();
}
float calcSalariuAnimatori(Animator* ani, int nrAnimatori)///functionalitate Animator (calculeaza suma cu care trebuie platiti mai multi animatori);
{
    float sum = 0;
    for (int i = 0; i < nrAnimatori; i++)
        sum += ani[i].get_salariu();
        return sum;
}
bool verifZiDisponibila(map<string,Client*> clienti, string numeLocatie, int zi, int luna)///functionalitate Client(verifica daca o locatie este inchiriata intr-o zi pe baza programarilor deja facute)
{
//    for (int i = 0; i < clienti.size(); i++)
//        if (numeLocatie == clienti[i]->get_numeLocatie && luna == clienti[i]->get_lunaInchiriere() && zi == clienti[i]->get_ziInchiriere())
//            return false;
//    return true;
    for (auto i = clienti.begin(); i != clienti.end(); i++)
    {
        if (numeLocatie == i->second->get_numeLocatie() && luna == i->second->get_lunaInchiriere() && zi == i->second->get_ziInchiriere())
            return false;
    }
    return true;
}


class MeniuLog
{
private:
    static MeniuLog* m;
public:
    static MeniuLog* getInstance()
    {
        if (!m)
            m = new MeniuLog;
        return m;
    }

    void meniu()
    {
        ifstream dateAfacere("date.in");

        list<Locatie*> locatii;
        map<string,Client*> inchirieri; ///stringul e parola
        set<Animator*> animatori;
        vector<Activitate*> activitati;
        vector<Suc*> sucuri;
        vector<Aliment*> alimente;
        string UserAdmin = "admin";
        string ParolaAdmin = "admin";

        streambuf *old = cout.rdbuf(0);///ca sa nu ia in calcul cout-urile cand citeste din fisier

        int nrLocatii, nrInchirieri, nrAnimatori, nrActivitati, nrSucuri, nrAlimente;

        dateAfacere>>nrLocatii;
        for (int i = 0; i < nrLocatii; i++)
        {
            Locatie* l = new Locatie;
            dateAfacere>>*l;
            locatii.push_back(l);
        }
        dateAfacere>>nrInchirieri;
        for (int i = 0; i < nrInchirieri; i++)
        {
            Client *c = new Client;
            string parola;
            dateAfacere>>parola>>*c;
            inchirieri.insert(pair<string,Client*>(parola,c));
        }
        dateAfacere>>nrAnimatori;
        for (int i = 0; i < nrAnimatori; i++)
        {
            Animator* a = new Animator;
            dateAfacere>>*a;
            animatori.insert(a);
        }
        dateAfacere>>nrActivitati;
        for (int i = 0; i < nrActivitati; i++)
        {
            Activitate* a = new Activitate;
            dateAfacere>>*a;
            activitati.push_back(a);
        }
        dateAfacere>>nrSucuri;
        for (int i = 0; i < nrSucuri; i++)
        {
            int tipSuc; ///0 natural/1 import
            dateAfacere>>tipSuc;
            if (!tipSuc)
            {
                Suc* s = new SucNatural;
                dateAfacere>>*s;
                sucuri.push_back(s);
            }
            else
            {
                Suc* s = new SucImport;
                dateAfacere>>*s;
                sucuri.push_back(s);
            }
        }
        dateAfacere>>nrAlimente;
        for (int i = 0; i < nrAlimente; i++)
        {
            int tipAliment;
            dateAfacere>>tipAliment;///0 tort/ 1 aperitiv
            if (!tipAliment)
            {
                Aliment *a = new Tort;
                dateAfacere>>*a;
                alimente.push_back(a);
            }
            else
            {
                Aliment *a = new Aperitiv;
                dateAfacere>>*a;
                alimente.push_back(a);
            }
        }
        cout.rdbuf(old);
        int k = 1;

        while (k==1)
        {
            int optiuneConectare;
            cout<<"\n\nConectare ca: \n\t1.Administrator\n\t2.Client\n\t3.Inchidere aplicatie\n\nOptiune: ";
            cin>>optiuneConectare;

            switch(optiuneConectare)
            {
            case 1:
                {
                    string userIntrodus, parolaIntrodusa;
                    cout<<"\nUser: ";
                    cin>>userIntrodus;
                    cout<<"Parola: ";
                    cin>>parolaIntrodusa;

                    if (userIntrodus == UserAdmin && parolaIntrodusa == ParolaAdmin)
                        {
                            cout<<"\nConectat ca administrator\n-------------------------\n";

                            int k2=1;
                            while (k2==1)
                            {
                                int optiune2;
                                cout<<"\n\n\t1.Gestionare Locatii\n\t2.Gestionare animatori\n\t3.Afisare Programari\n\t4.Gestionare Produse\n\t5.Inapoi\n\nOptiune: ";
                                cin>>optiune2;

                                switch(optiune2)
                                {
                                case 1:
                                    {
                                        int k3 = 1;
                                        while (k3 == 1)
                                        {
                                            cout<<"\n\n\t1.Afisare Locatii(ID, Nume)\n\t2.Prelucrare Locatie Dupa ID\n\t3.Adaugare Locatie\n\t4.Inapoi\n\nOptiune: ";
                                            int optiuneLocatie;
                                            cin>>optiuneLocatie;

                                            switch(optiuneLocatie)
                                            {
                                                case 1:
                                                    {
                                                        cout<<"\nLocatiile curente sunt: ";
                                                        int contor = 1;
                                                        for (auto i = locatii.begin(); i != locatii.end(); i++)
                                                            cout<<"\n\t"<<contor++<<". "<<(*i)->get_idLocatie()<<", "<<(*i)->get_numeLoc();
                                                        cout<<'\n';
                                                        break;
                                                    }
                                                case 2:
                                                    {
                                                        cout<<"\nID locatie: ";
                                                        int idLocatie;
                                                        cin>>idLocatie;
                                                        bool locatieGasita = 0;

                                                        for (auto i = locatii.begin(); i != locatii.end(); i++)
                                                            if ((*i)->get_idLocatie() == idLocatie)
                                                                {
                                                                    locatieGasita = 1;
                                                                    cout<<"Locatie cu ID "<<idLocatie<<" selectata!";
                                                                    int k4 = 1;
                                                                    while (k4 == 1)
                                                                    {
                                                                        cout<<"\n\n\t1.Modificare capacitate maxima\n\t2.Modificare tarif inchiriere ora\n\t3.Stergere Locatie\n\t4.Afisare detalii locatie\n\t5.Inapoi\n\nOptiune: ";
                                                                        int optiunePrelucrareLocatie;
                                                                        cin>>optiunePrelucrareLocatie;

                                                                        switch(optiunePrelucrareLocatie)
                                                                        {
                                                                            case 1:
                                                                                {
                                                                                    cout<<"\nCapacitate maxima actuala: "<<(*i)->get_capacitateMax();
                                                                                    int capacitateNoua;
                                                                                    cout<<"\nIntroduceti capacitatea maxima noua: ";
                                                                                    cin>>capacitateNoua;
                                                                                    (*i)->set_capacitateMax(capacitateNoua);
                                                                                    break;
                                                                                }
                                                                            case 2:
                                                                                {
                                                                                   cout<<"\nTarif actual: "<<(*i)->get_tarifInchiriereOra();
                                                                                   cout<<"\nIntroduceti tariful nou: ";
                                                                                   float tarifNou;
                                                                                   cin>>tarifNou;
                                                                                   (*i)->set_tarifInchiriereOra(tarifNou);
                                                                                   break;
                                                                                }
                                                                            case 3:
                                                                                {
                                                                                    locatii.erase(i);
                                                                                    k4 = 0;
                                                                                    break;
                                                                                }
                                                                            case 4:
                                                                                {
                                                                                    cout<<"\nDetalii locatie\n---------------\n"<<**i;
                                                                                    break;
                                                                                }
                                                                            case 5:
                                                                                {
                                                                                    k4 = 0;
                                                                                    break;
                                                                                }
                                                                        }
                                                                    }

                                                                    break;
                                                                }

                                                        if (!locatieGasita)
                                                            cout<<"\n!!!Locatia nu a fost gasita!!!\n";
                                                        break;
                                                    }
                                                case 3:
                                                    {
                                                       cout<<"\nIntroduceti detaliile pentru locatia noua\n-----------------------------------------\n";
                                                       Locatie *l = new Locatie;
                                                       cin>>*l;
                                                       locatii.push_back(l);
                                                       break;
                                                    }
                                                case 4:
                                                    {
                                                        k3 = 0;
                                                        break;
                                                    }
                                            }
                                        }
                                        break;
                                    }
                                case 2:
                                    {
                                        int k3=1;
                                        while (k3==1)
                                        {
                                            cout<<"\n\n\t1.Afisare animatori\n\t2.Adaugare animator\n\t3.Eliminare animator\n\t4.Afisare salariu total animatori\n\t5.Inapoi\n\nOptiune: ";
                                            int optiuneAnimatori;
                                            cin>>optiuneAnimatori;

                                            switch(optiuneAnimatori)
                                            {
                                            case 1:
                                                {
                                                    cout<<"\nAnimatorii sunt: \n";
                                                    for (auto i = animatori.begin(); i != animatori.end(); i++)
                                                        cout<<**i<<endl;
                                                    cout<<'\n';
                                                    break;
                                                }
                                            case 2:
                                                {
                                                    cout<<"\nIntroduceti informatiile animatorului nou\n-----------------------------------------\n";
                                                    Animator* a = new Animator;
                                                    cin>>*a;
                                                    animatori.insert(a);
                                                    break;
                                                }
                                            case 3:
                                                {
                                                    cout<<"\nIntroduceti ID-ul animatorului: ";
                                                    int idStergere;
                                                    cin>>idStergere;
                                                    bool sters = 0;
                                                    for (auto i = animatori.begin(); i != animatori.end() && !sters; i++)
                                                    {
                                                        if ((*i)->get_idAnimator() == idStergere)
                                                            animatori.erase(i), sters = 1;
                                                    }
                                                    if (sters)
                                                    {
                                                        cout<<"\nAnimator eliminat!";
                                                    }
                                                    else
                                                        cout<<"\nAnimatorul cu ID-ul dat nu exista";
                                                    break;
                                                }
                                            case 4:
                                                {
                                                    cout<<"\nSuma cu care trebuie platiti toti animatorii este: ";
                                                    Animator *ani = new Animator[animatori.size()];
                                                    int contor = 0;
                                                    for (auto i = animatori.begin(); i != animatori.end(); i++)
                                                            ani[contor++] = **i;
                                                    cout<<calcSalariuAnimatori(ani,contor);
                                                    delete[] ani;
                                                    break;
                                                }
                                            case 5:
                                                {
                                                    k3 = 0;
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    case 3:
                                        {
                                            cout<<"\nProgramarile sunt: ";
                                            for (auto i = inchirieri.begin(); i != inchirieri.end(); i++)
                                                cout<<"\n"<<*(i->second);
                                            break;
                                        }
                                    case 4:
                                        {
                                            int k3 = 1;
                                            while (k3==1)
                                            {
                                                cout<<"\n\n\t1.Afisare Produse Disponibile\n\t2.Adaugare Produs\n\t3.Inapoi\n\nOptiune: ";
                                                int optiuneProdus;
                                                cin>>optiuneProdus;
                                                switch (optiuneProdus)
                                                {
                                                case 1:
                                                    {
                                                        cout<<"\nSucurile sunt: \n";
                                                        for (int i = 0; i < sucuri.size(); i++)
                                                            cout<<*sucuri[i]<<endl;
                                                        cout<<"\n\nAlimentele sunt: \n";
                                                        for (int i = 0; i < alimente.size(); i++)
                                                            cout<<*alimente[i]<<endl;
                                                        break;
                                                    }
                                                case 2:
                                                    {
                                                        cout<<"\nTipul de produs\n---------------\n\t1.Suc\n\t2.Aliment\n\nOptiune: ";
                                                        int optiuneAdaugareProdus;
                                                        cin>>optiuneAdaugareProdus;
                                                        switch(optiuneAdaugareProdus)
                                                        {
                                                        case 1:
                                                            {
                                                                cout<<"\nTipul sucului(0 NATURAL/1 IMPORT): ";
                                                                int tipSuc;
                                                                cin>>tipSuc;
                                                                switch(tipSuc)
                                                                {
                                                                case 0:
                                                                    {
                                                                        Suc *s = new SucNatural;
                                                                        cin>>*s;
                                                                        sucuri.push_back(s);
                                                                        break;
                                                                    }
                                                                case 1:
                                                                    {
                                                                        Suc *s = new SucImport;
                                                                        cin>>*s;
                                                                        sucuri.push_back(s);
                                                                        break;
                                                                    }
                                                                }
                                                                break;
                                                            }
                                                        case 2:
                                                           {
                                                               cout<<"\nTipul alimentului(0 TORT/1 APERITIV): ";
                                                               int tipAliment;
                                                               cin>>tipAliment;
                                                               switch(tipAliment)
                                                               {
                                                               case 0:
                                                                {
                                                                    Aliment *a = new Tort;
                                                                    cin>>*a;
                                                                    alimente.push_back(a);
                                                                    break;
                                                                }
                                                               case 1:
                                                                {
                                                                    Aliment *a = new Aperitiv;
                                                                    cin>>*a;
                                                                    alimente.push_back(a);
                                                                    break;
                                                                }
                                                               }
                                                               break;
                                                           }
                                                        }
                                                        break;
                                                    }
                                               case 3:
                                                {
                                                    k3 = 0;
                                                    break;
                                                }
                                                }
                                            }
                                            break;
                                        }
                                       case 5:
                                            {
                                                k2 = 0;
                                                break;
                                            }
                                }
                            }
                        }
                    else
                        cout<<"\n!!!Userul sau parola sunt gresite!!!\n";
                    break;
                    }
               case 2:
                   {
                       int k2 = 1;
                       cout<<"\nConectat ca client!\n------------------\n";
                       while (k2 == 1)
                       {
                            cout<<"\n\n\t1.Vizualizare Locatii\n\t2.Vizualizare activitati\n\t3.Creare programare\n\t4.Gestionare programare\n\t5.Inapoi\n\nOptiune: ";
                            int optiuneClient;
                            cin>>optiuneClient;

                            switch(optiuneClient)
                            {
                                case 1:
                                    {
                                        cout<<"\nLocatiile sunt: ";
                                        for (auto i = locatii.begin(); i != locatii.end(); i++)
                                            cout<<endl<<**i<<endl;
                                        break;
                                    }
                                case 2:
                                    {
                                        cout<<"\nActivitatile sunt: ";
                                        for (int i = 0; i < activitati.size(); i++)
                                            cout<<*activitati[i]<<endl;
                                            break;
                                    }
                                case 3:
                                    {
                                        int totalPlata = 0;
                                        Client *c = new Client;
                                        c->creareProgramare();

                                        string numeLocatie;
                                        cout<<"\nLocatia dorita: ";
                                        cin>>numeLocatie;
                                        bool locatieGasita = 0;
                                        for (auto i = locatii.begin(); i != locatii.end(); i++)
                                        {
                                            if ((*i)->get_numeLoc() == numeLocatie)
                                                {
                                                    locatieGasita = 1;
                                                    break;
                                                }
                                        }
                                        if (!locatieGasita)
                                        {
                                            cout<<"\n\n!!!Locatia dorita nu exista!!!\n";
                                            break;
                                        }

                                        bool locatieDisponibila = verifZiDisponibila(inchirieri,numeLocatie,c->get_ziInchiriere(),c->get_lunaInchiriere());

                                        if (!locatieDisponibila)
                                            cout<<"\nLocatia aleasa nu este disponibila in ziua si luna aleasa!";
                                        else
                                        {
                                            for (auto i = locatii.begin(); i != locatii.end(); i++)
                                            {
                                                if ((*i)->get_numeLoc() == c->get_numeLocatie());
                                                    {
                                                        totalPlata += calcTarifIntervalLocatie(**i,c->get_oraFinal(),c->get_oraInceput());
                                                        break;
                                                    }
                                            }
                                            cout<<"\nSelectati din activitatile noaste\n---------------------------------\n";
                                            int nrActivitati = 0;
                                            string *activitatiOnomastica = new string[activitati.size()];
                                            for (int i = 0; i < activitati.size(); i++)
                                            {
                                                cout<<*activitati[i]<<"\nAdaugati activitate(1 DA/0 NU): ";
                                                bool da;
                                                cin>>da;
                                                if (da)
                                                    {
                                                        totalPlata += calcTarifActivit(activitati[i],1);
                                                        activitatiOnomastica[nrActivitati++] = activitati[i]->get_numeActivitate();
                                                    }
                                            }

                                            cout<<"\nSelectati tortul: \n----------------\n";
                                            Aliment *tort = new Tort;
                                            for(int i = 0; i < alimente.size(); i++)
                                            {
                                                if (typeid(*alimente[i])==typeid(Tort))
                                                {
                                                    cout<<*alimente[i]<<endl;
                                                    bool da;
                                                    cout<<"\nAlegeti acest tort(1 DA/0 NU): ";
                                                    cin>>da;
                                                    if (da)
                                                    {
                                                        static_cast<Tort&>(*tort) = static_cast<Tort&>(*alimente[i]);
                                                        totalPlata += (int)tort->calcularePretNrClienti(c->get_nrParticipanti());
                                                        break;
                                                    }
                                                }
                                            }

                                            vector<Suc*> sucuriOnomastica;
                                            cout<<"\nSelectati sucurile: \n------------------\n";
                                            for (int i = 0; i < sucuri.size(); i++)
                                            {
                                                cout<<*sucuri[i];
                                                bool da;
                                                cout<<"\nAlegeti acest suc(1 DA/0 NU): ";
                                                cin>>da;
                                                if (da)
                                                {
                                                    sucuriOnomastica.push_back(sucuri[i]);
                                                    totalPlata += (int)sucuri[i]->calcularePretSuc(c->get_nrParticipanti());
                                                }
                                            }

                                            vector<Aperitiv*> aperitiveOnomastica;
                                            cout<<"\nSelectati aperitivele: \n---------------------\n";
                                            for (int i = 0; i < alimente.size(); i++)
                                            {
                                                if (typeid(*alimente[i]) == typeid(Aperitiv))
                                                {
                                                    cout<<*alimente[i];
                                                    bool da;
                                                    cout<<"\nAlegeti acest aperitiv(1 DA/0 NU): ";
                                                    cin>>da;
                                                    if (da)
                                                        {
                                                            Aperitiv *aperitiv = new Aperitiv;
                                                            *aperitiv = static_cast<Aperitiv&>(*alimente[i]);
                                                            aperitiveOnomastica.push_back(aperitiv);
//                                                            aperitiveOnomastica.push_back(&static_cast<Aperitiv&>(*alimente[i]));
//                                                            cout<<"\nMerge castu";
                                                            totalPlata += alimente[i]->calcularePretNrClienti(c->get_nrParticipanti());
//                                                            cout<<"\nMerge totalPlata";
                                                        }
                                                }
                                            }

                                            c->restProgramare(numeLocatie, nrActivitati, activitatiOnomastica, tort, sucuriOnomastica, aperitiveOnomastica);
                                            cout<<*c<<"\nTotal plata: "<<totalPlata<<"\nSalvati programarea(1 DA/0 NU): ";
                                            bool salvare;
                                            cin>>salvare;
                                            if (salvare)
                                            {
                                                cout<<"Introduceti o parola pentru a putea accesa sau sterge ulterior programarea: ";
                                                string parolaProgramare;
                                                cin>>parolaProgramare;
                                                inchirieri.insert(pair<string,Client*>(parolaProgramare,c));
                                                cout<<"\nSalvati detaliile intr-un format accesibil la iesirea din aplicatie(1 DA/0 NU): ";
                                                bool da;
                                                cin>>da;
                                                if (da)
                                                {
                                                    ofstream factura("date.out");
                                                    factura<<"***********************************************************************\n\n                            JoyClub S.R.L.\n\n***********************************************************************\n";
                                                    factura<<*c;
                                                    factura<<"\n\n\n\nTotal plata.......................................................";
                                                    factura<<totalPlata;
                                                }
                                            }

                                        }

                                        break;
                                    }
                                case 4:
                                    {
                                       cout<<"\nIntroduceti parola cu care ati salvat programarea: ";
                                       string parolaProgramare;
                                       cin>>parolaProgramare;
                                       if (inchirieri.find(parolaProgramare) == inchirieri.end())
                                            cout<<"\n!!!Parola introdusa nu corespunde niciunei programari!!!";
                                       else
                                       {
                                           Client* c = new Client;
                                           c = inchirieri.find(parolaProgramare)->second;

                                           int k3 = 1;
                                           while (k3 == 1)
                                           {
                                               cout<<"\n\n\t1.Afisare programare\n\t2.Stergere programare\n\t3.Inapoi\n\nOptiune: ";
                                               int optiuneProgramare;
                                               cin>>optiuneProgramare;

                                               switch(optiuneProgramare)
                                               {
                                                   case 1:
                                                    {
                                                        cout<<"Programarea: \n-----------\n";
                                                        cout<<*c;
                                                        break;
                                                    }
                                                   case 2:
                                                    {
                                                        inchirieri.erase(parolaProgramare);
                                                        cout<<"\n!!!Programare stearsa!!!";
                                                        k3 = 0;
                                                        break;
                                                    }
                                                   case 3:
                                                    {
                                                        k3 = 0;
                                                        break;
                                                    }
                                               }
                                           }
                                       }
                                       break;
                                    }
                                case 5:
                                    {
                                        k2 = 0;
                                        break;
                                    }
                            }
                       }
                       break;
                   }
               case 3:
                   {
                       k = 0;
                   }

                }
            }
        }
    };

MeniuLog* MeniuLog::m=0;
int main()
{

    MeniuLog *m = m ->getInstance();
    m->meniu();

}
