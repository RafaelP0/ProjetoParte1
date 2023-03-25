#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <locale.h>
#include <limits>

using namespace std;
const int MAX = 80;

class TGrafo {
private:
  int n;     // quantidade de vértices
  int m;     // quantidade de arestas
  float **adj; // matriz de adjacência
public:
  TGrafo(int n);
  void insereA(int v, int w, float a);
  void removeA(int v, int w);
  void show();
  void gravar();
  void ler();
  void inserirV();
  void removeV(int v);
  ~TGrafo();
};

TGrafo::TGrafo(int n) {
  this->n = n;
  this->m = 0;

  float **adjac = new float *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new float[n];
  adj = adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = numeric_limits<float>::infinity();
}

TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * adj;
  cout << "espaço liberado";
}

void TGrafo::insereA(int v, int w, float a) {
  if (adj[v][w] == numeric_limits<float>::infinity()) {
    adj[v][w] = a;
    m++;
  }
  else
    cout << "Aresta já existente" <<endl;
}

void TGrafo::removeA(int v, int w) {
  if (adj[v][w] !=  numeric_limits<float>::infinity()) {
    adj[v][w] = numeric_limits<float>::infinity();
    m--;}
  cout << "Aresta não existente" <<endl;
  }


void TGrafo::show() {
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n";
    for (int w = 0; w < n; w++)
      if (adj[i][w] != numeric_limits<float>::infinity())
         cout << "(" << i << "," << w << ") = " << adj[i][w]<< " ";

  }
  cout << "ou alternativamente \n";
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n";
    for (int w = 0; w < n; w++)
      if (adj[i][w] != numeric_limits<float>::infinity())
        cout << "[" << i << "," << w << "]= " << adj[i][w]
             << " ";
      else
        cout << "[" << i << "," << w << "]= ∞ "
             << " ";
  }
  cout << "\nfim da impressao do grafo." << endl;
}

void TGrafo::gravar() {
  ofstream fout("grafo.txt");
  fout << n << endl;
  for (int i = 0; i < n; i++) 
    fout << i << endl;
  fout << m << endl;
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++)
      
      if (adj[i][w] != numeric_limits<float>::infinity())
        fout << i << " " << adj[i][w] << " " << w << " " << endl;
  }
}

void TGrafo::ler() {
  char buffer[MAX];
  ifstream fin("grafo.txt");
  while (!fin.eof()){
  fin.getline(buffer, MAX);
  cout << buffer << endl;
}
}

void TGrafo::inserirV(){
  n+=1;
  
  float **adjac = new float *[n];
  for (int i = 0; i <= n; i++)
    adjac[i] = new float[n];
  
  for (int i = 0; i < n-1; i++)
    for (int j = 0; j < n-1; j++) 
      adjac[i][j] = adj[i][j];
  adj = adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) 
      if (i==(n-1))
        adj[i][j] = numeric_limits<float>::infinity();
      else if (j == (n-1))
        adj[i][j] = numeric_limits<float>::infinity();
      else
        adj[i][j] = adjac[i][j];
  
  }

void TGrafo::removeV(int v){
  n-=1;
  
  float **adjac = new float *[n];
  for (int i = 0; i <= n; i++)
    adjac[i] = new float[n];

  for (int w = 0; w < n; w++){
    removeA(v, w);
    removeA(w, v);}
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){ 
        if (i<v){
          if (j<v)
            adjac[i][j] = adj[i][j];
          
          else
            adjac[i][j] = adj[i][j+1];
        }
        else
          if (j<v)
            adjac[i][j] = adj[i+1][j];
          
          else
            adjac[i][j] = adj[i+1][j+1];
        }
  adj = adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) 
        adj[i][j] = adjac[i][j];

    
}

int main() {
  TGrafo g(4);

  g.insereA(0, 1, 01);
  g.insereA(0, 2, 02);
  g.insereA(2, 1, 21);
  g.insereA(2, 3, 23);
  g.insereA(1, 3, 13);

  

char b;
int v1, v2;
float a;
while (b != 'i'){
  cout << "\nEscolha uma opção: \n"<< 
    " a) Ler dados do arquivo grafo.txt\n b) Gravar dados no arquivo grafo.txt\n c) Inserir vértice\n d) Inserir aresta;\n e) Remove vértice;\n f) Remove aresta;\n g) Mostrar conteúdo do arquivo;\n h) Mostrar grafo;\n i) Encerrar a aplicação.\n\n" << endl;
    cin >> b;
  switch(b) {

  case 'a':
    cout << "A" << endl;
    g.gravar();
    break;

    
  case 'b':
    cout << "B" << endl;
    g.ler();
    // code block
    break;

    
  case 'c':
    g.inserirV();
    break;

  case 'd':
      cout<<"\nInsira o primeiro vertice: ";
      cin >> v1;
      cout<<"\nInsira o segunto vertice: ";
      cin >> v2;
      cout<<"\nInsira a aresta: ";
      cin >> a;
      g.insereA(v1, v2, a);
      break;

    case 'e':
      cout<<"\nInsira o vertice que gostaria de apagar: ";
      cin >> v1;
      g.removeV(v1);
      break;
    case 'f':
      cout<<"\nInsira o primeiro vertice: ";
      cin >> v1;
      cout<<"\nInsira o segunto vertice: ";
      cin >> v2;

      g.removeA(v1, v2);
      break;
    
    case 'h':
      g.show();
    break;
    
  case 'i':
    cout<<"bye bye!!"<< endl;
    break;
    
  default:
    cout << "\nopção invalida, tente novamente" << endl;
    break;
    // code block

}}

  return 0;
}
