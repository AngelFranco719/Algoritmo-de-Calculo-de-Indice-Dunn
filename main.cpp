#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#define MAXN 200005
#define sl '\n'
#define sfcin() ios::sync_with_stdio(false); cin.tie(0);
#define console() {system("pause"); system("cls"); }

string op[3] = {"YES", "NO", "MAYBE"};

struct Objeto{
    ll index;
    string nombre;
    vector<ll>atributos;
    vector<double> distancias;
};

ll cO,cA,k; vector<Objeto>matrix; vector<vector<Objeto*>>grupos;

void getMatrix(){
    cout<<"Cantidad de Objetos: "; cin>>cO; cout<<sl;
    cout<<"Cantidad de Atributos: "; cin>>cA; cout<<sl;
    ll in=0;
    matrix.resize(cO);
    for(ll j=0; j<cO; j++){
        vector<ll>atributos(cA); in++; cout<<"Atributos de O"<<in<<": ";
        Objeto tupla; tupla.nombre="O"+to_string(in); tupla.index=j;
        for(ll i=0; i<cA; i++) cin>>atributos[i];
        tupla.atributos=atributos;
        matrix[j]=tupla;
    }
    return;
}

void setGrupos(){
    cout<<sl<<"Cantidad de Grupos: "; cin>>k;
    for(ll i=0; i<k; i++){
        ll car, num; cout<<"Cardinalidad: "; cin>>car;
        vector<Objeto*>g; cout<<"Objetos del Grupo "<<i+1<<": ";
        for(ll j=0; j<car; j++){cin>>num; g.push_back(&matrix[num-1]);}
        grupos.push_back(g);
    }
    return;
}

void coutGrupos(){
    for(ll i=0; i<k; i++){
        cout<<"En el grupo "<<i+1<<": ";
        for(Objeto* tupla: grupos[i]) cout<<tupla->nombre<<" ";
        cout<<sl;
    }
    return;
}

double distanciaEuclidiana(Objeto t1, Objeto t2){
    double distancia=0;
    for(ll i=0; i<(int)t1.atributos.size(); i++) distancia+=(pow(t1.atributos[i]-t2.atributos[i], 2));
    return sqrt(distancia);
}

void calcularDistancias(){
    for(Objeto& t1: matrix){
        vector<double>distancias;
        for (Objeto& t2: matrix)distancias.push_back(distanciaEuclidiana(t1,t2));
        t1.distancias=distancias;
    }
    return;
}

void getDistancias(Objeto t){
    for(double dis : t.distancias) cout<<dis<<" ";
    cout<<sl;
    return;
}

double distancia_Grupo(ll g1, ll g2){
     double minimoGlobal=LLONG_MAX;
    for(Objeto* t1: grupos[g1]){
        double minimo=LLONG_MAX;
        cout<<"A("<<t1->nombre<<"G"<<g2+1<<")= min { ";
        for(Objeto* t2: grupos[g2]){
            minimo=min(minimo, t1->distancias[t2->index]);
            minimoGlobal=min(minimoGlobal, minimo);
            cout<<t1->distancias[t2->index]<<", ";
        }
        cout<<" } = "<<minimo<<sl<<sl;
    }
    return minimoGlobal;
}

double diametro_Grupo(ll grupo){
    double maximo=LLONG_MIN;
    for(Objeto* x: grupos[grupo]){
        for(Objeto* y: grupos[grupo]){
            maximo=max(maximo, x->distancias[y->index]);
        }
    }
    cout<<"Delta(G"<<grupo+1<<")= "<<maximo<<sl;
    return maximo;
}

int main() {
    getMatrix(); setGrupos(); coutGrupos(); calcularDistancias(); console();
    vector<double> minDisK;
    for(ll i=0; i<k; i++) {
        for(ll j=i+1; j<k; j++) {
            double minimo=distancia_Grupo(i,j);
            cout<<sl<<"S(G"<<i+1<<",G"<<j+1<<")="<<minimo<<sl;
            minDisK.push_back(minimo);
        }
    }
    vector<double> diamK;
    for(int i=0; i<k; i++) diamK.push_back(diametro_Grupo(i));
    double dunn = *min_element(minDisK.begin(), minDisK.end()) / *max_element(diamK.begin(), diamK.end());
    cout<<sl<<"Dunn: "<<dunn<<sl;
    return 0;
}


/*
11
3
1 1 0
2 1 1
1 2 0
2 2 1
4 1 3
4 2 1
4 3 3
4 4 5
2 4 1
3 4 4
2 5 2
2
4
1 2 3 4
7
5 6 7 8 9 10 11
*/

/*
11
3
1 1 0
2 1 1
1 2 0
2 2 1
4 1 3
4 2 1
4 3 3
4 4 5
2 4 1
3 4 4
2 5 2
2
7
1 2 3 4 6 9 11
4
5 7 8 10
*/
