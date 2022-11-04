#include <iostream>

class Clienti{
protected:
        std :: string nume;
        std :: string prenume;
        std :: string telefon;
        std :: string adresa;
public:
    Clienti(std :: string = "", std :: string = "", std :: string = "",std :: string = "");
    virtual ~Clienti();
    Clienti(const Clienti &);
    virtual void afisare(std :: ostream &out);
    virtual void citire(std :: istream &in);

    friend std :: ostream& operator<<(std :: ostream& out, Clienti&);
    friend std :: istream& operator>>(std :: istream& in, Clienti&);
};

Clienti :: Clienti(std :: string nume, std :: string prenume , std :: string telefon, std :: string adresa){
    this->nume = nume;
    this->prenume = prenume;
    this->telefon = telefon;
    this->adresa = adresa;
}

Clienti :: ~Clienti(){
    nume = "";
    prenume = "";
    telefon = "";
    adresa ="";
}
Clienti :: Clienti(const Clienti& cl){
    nume = cl.nume;
    prenume = cl.prenume;
    telefon = cl.telefon;
    adresa = cl.adresa;
}

std :: istream& operator<<(std :: istream& in, Clienti& cl){
    cl.citire(in);
    return in;
}

void Clienti ::citire(std::istream &in) {
    std :: cout << "Introduceti datele dumneavoastra :" << "\n";
    std :: cout << "Nume :";
    in >> nume;
    std :: cout << "Prenume :";
    in >> prenume;
    std :: cout << "Numarul de telefon :";
    in >> telefon;
    std :: cout << "Adresa :";
    in.get();
    std :: string aux;
    std::getline(in,aux);
    adresa = aux;
}
std::ostream& operator<<(std :: ostream& out, Clienti& cl){
    cl.afisare(out);
    return out;
}

void Clienti ::afisare(std::ostream &out) {
    out << "Numele : "<< nume << "\n";
    out << "Prenumele :" << prenume << "\n";
    out << "Telefonul : "<< telefon << "\n";
    out << "Adresa :"<< adresa << "\n";
}

class Curieri{
    std :: string nume;
    std :: string telefon;
    std :: string adresa;
    int salariu;
public:
    Curieri(const std :: string& nume_, const std :: string& telefon_,  const std :: string& adresa_, int salariu_) : nume{nume_}, telefon{telefon_}, adresa{adresa_}, salariu{salariu_}{
        std :: cout << "intializare\n";
    }

    friend std :: ostream& operator<<(std::ostream& os, const Curieri& cr){
        os << "Informatii despre curier: " << "\n" << "Nume: "<< cr.nume << "\n" << "Numar de telefon: " << cr.telefon << "\n" << "Adresa: " << cr.adresa <<"\n" << "Salariu (in RON): " << cr.salariu << "\n";
        return os;
    }
    void Marire_salariu(){
        if(salariu < 3354)
            salariu = salariu + 0.1 * salariu;
    }
    ~Curieri() = default;
};

class Destinatari : public Clienti{
protected:
    int cod_primire;
public:
    Destinatari(std :: string ="", std :: string="", std :: string="",std :: string="", int=0);
    ~Destinatari();
    Destinatari(const Destinatari &);

    virtual void afisare(std::ostream &out);
    virtual void citire(std :: istream &in);

    friend std::ostream& operator<<(std :: ostream& out, Destinatari&);
    friend std::istream& operator>>(std :: istream& in, Destinatari&);

};

Destinatari :: Destinatari(std::string nume, std::string prenume, std::string telefon, std::string adresa, int cod_primire) : Clienti(nume,prenume,telefon,adresa) {
    this->cod_primire = cod_primire;
}

Destinatari :: ~Destinatari(){
    cod_primire = 0;
}

/*Destinatari ::Destinatari(const Destinatari &d){
    cod_primire = d.cod_primire;
}*/
int get_cod_primire() {
    int aux;
    aux = 1 + (std::rand() % (99999));
    if (aux <= 9999)
        get_cod_primire();
    else
        return aux;
    return -1;
}

void Destinatari ::citire(std::istream &in) {
    Clienti ::citire(in);
    std :: cout << "Codul dvs. de primire este : ";
    int aux = get_cod_primire();
    cod_primire = aux;
}
std::istream& operator>>(std::istream &in, Destinatari& d){
    d.citire(in);
    return in;
}

void Destinatari ::afisare(std::ostream &out) {
    Clienti :: afisare(out);
    out << "Codul de primire este : " << cod_primire << "\n";
}

std::ostream & operator<<(std::ostream& out, Destinatari& d){
    d.afisare(out);
    return out;
}

class Colete{
    int AWB;
    std :: string nume;
    float greutate;
    float distanta;
    std :: string detalii;
    friend class Expeditori;
public:
    Colete(int AWB_, const std :: string& nume_, float greutate_, float distanta_, const std :: string& detalii_) : AWB{AWB_}, nume{nume_}, greutate{greutate_}, distanta{distanta_}, detalii{detalii_}{};

    Colete(const Colete& other){
        AWB = other.AWB;
        nume = other.nume;
        greutate = other.greutate;
        distanta = other.distanta;
        detalii = other.detalii;
        std :: cout << "cc\n";

    }
    Colete& operator=(const Colete& other){
        AWB = other.AWB;
        nume = other.nume;
        greutate = other.greutate;
        distanta = other.distanta;
        detalii = other.detalii;
        std :: cout << "op egal\n";
        return *this;

    }
    ~Colete(){
        //std :: cout << "salut la revedere!\n";
    }

    friend std :: ostream& operator<<(std::ostream& os, const Colete& col) {
        os << "Informatii despre colet: " << "\n" << "Denumire: " << col.nume << "\n" << "AWB: " << col.AWB << "\n" << "Greutate (in kg): " << col.greutate << "\n" << "Distanta :" << col.distanta <<"\n";
        os << "Pret (in RON) :" << col.greutate * col.distanta <<"\n";
        return os;
    }

};

class Expeditori{
    std :: string nume;
    std :: string telefon;
    std :: string adresa;
    Colete colet_1;
    friend class Colete;

public:

    Expeditori(const std :: string& nume_, const std :: string& telefon_, const std :: string& adresa_, Colete colet_1_) : nume{nume_}, telefon{telefon_}, adresa{adresa_}, colet_1(colet_1_){}
    friend std :: ostream& operator<<(std::ostream& os, const Expeditori& ex){
        os << "Informatii despre expeditor: " << "\n" << "Nume: "<< ex.nume << "\n" << "Numar de telefon: " << ex.telefon << "\n" << "Adresa: " << ex.adresa <<"\n";
        return os;
    }
    void Depunere_Colet(Colete &m_colet_1){
        std :: cout << "Ce colet doriti sa depuneti ? "<< "\n";
        std :: cout << "Nume colet :" << "\n";
        std :: cin >> m_colet_1.nume;
        std :: cout << "Greutate colet :" << "\n";
        std :: cin >> m_colet_1.greutate;
        std :: cout << "Distanta (in km) :" << "\n";
        std :: cin >> m_colet_1.distanta;
        std :: cout << "Pretul (in RON) pentru colet este :" << (m_colet_1.distanta * m_colet_1.greutate);
    }
    ~Expeditori() = default;
};

int main() {
//    Colete colet_1{1, "Documente", 1, 50, "Important foarte tare"};
//    Colete colet_4 = colet_3;
//    colet_3 = colet_2;
//     Curieri curier_1{"Marcel Love", "0741273748", "Strada Principala", 3500};
//     Curieri curier_2{"Marcel Love", "0741273748", "Strada Principala", 3000};
//
//    Expeditori ex_1{"Petrica","074123748","Principala",colet_1};
//    ex_1.Depunere_Colet(colet_1);
//    curier_2.Marire_salariu();
//    std :: cout << curier_2;
    /*Clienti client_1{"Marcel", "Love", "0741273748", "Strada Principala"};
    client_1.citire(std :: cin);
    client_1.afisare(std :: cout);*/
    Destinatari dest_1{"Petrica", "Ion", "07412121221", "Strada Neagoe", 1};
    dest_1.citire(std :: cin);
    dest_1.afisare(std :: cout);



    return 0;
}
