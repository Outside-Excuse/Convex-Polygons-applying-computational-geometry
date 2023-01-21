/*
   Alejandro Hidalgo Badillo 
	Convex Polygons applying computational geometry
	fecha de inicio: 3 de noviembre del 2022
	fecha de ultima modificacion: 4 de noviembre del 2022
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
//inicio de funciones 
class Punto    {
public:
		string pos;
    int x, y;

 	
		//se realiza una comparacion primero en la coordenada y y luego en la coordenada x
    bool operator < (Punto b) {
        if (y != b.y){return y < b.y;}
        return x < b.x;
    }
};


Punto referencia; //creamos el punto que vamos a utilizar como referencia 


int ccw(Punto a, Punto b, Punto c) {
		//tiene una complejidad O(n)
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0){ return -1;}  
    else if (area < 0){return 1;}
        
    return 0;
}

// distancia euclidiana
int sqrDist(Punto a, Punto b)  {
	//tiene una complejidad O(n)
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// mi sort
bool POLAR_ORDER(Punto a, Punto b)  {
	//tiene una complejidad O(n)
    int order = ccw(referencia, a, b);
    if (order == 0){
			return sqrDist(referencia, a) < sqrDist(referencia, b);
		}
    
    return (order == -1);
}

stack<Punto> grahamScan(Punto *points, int N)    {
	/*
Primero buscamos el punto que tenga un menor valor en "Y".
Si dos puntos tienen el mismo valor, tiene prioridad el punto que tenga el menor valor en "X" .
*/
    stack<Punto> result; //stack se utiliza para almacenar valores de manera de plato

    if (N < 3){return result;}
    int leastY = 0;
    for (int i = 1; i < N; i++){
			if (points[i] < points[leastY]){leastY = i;}
		}
        
            


    Punto temp = points[0];
    points[0] = points[leastY];
    points[leastY] = temp;

   //ordenar el punto seleccionado de acuerdo con el orden polar conforme nuestra referencia declarada.
    referencia = points[0];
    sort(points + 1, points + N, POLAR_ORDER);
		//se agregan los valores a nuestro resultado
    result.push(points[0]);
    result.push(points[1]);
    result.push(points[2]);
		//tiene una complejidad O(n*n) debido a que tiene dos ciclos anidados 
    for (int i = 3; i < N; i++) {
        Punto top = result.top();
        result.pop();
        while (ccw(result.top(), top, points[i]) != -1)   {
            top = result.top();
            result.pop();
        }
        result.push(top);
        result.push(points[i]);
    }
    return result; //regresamos el resultado
}

//fin de funciones
int main() {

	int n;
	cin>>n;

	vector<vector<string>> puntos;
	string line;
	int cont = 0;
	//contq es el contador de lineas de entrada existentes
	int largo;
	getline(cin, line);
	 while (getline(cin, line)) {
		stringstream ss(line);
		puntos.push_back(vector<string>());
		while (ss.good()) {
        string substr;
        getline(ss, substr,' ');
        puntos[cont].push_back(substr);
    }
		 cont++;
  }//guardar matriz

/*
	cout<<"valores guardados: \n";
	for(int i=0; i<cont;i++){
		for(int l=0;l<puntos[i].size();l++){
			cout<<puntos[i][l]<<" ";
		}
		cout<<endl;
	}
	*/

	Punto points[n];
	
	for(int i=0; i<cont;i++){
		points[i].pos = puntos[i][0];
		points[i].x = stoi(puntos[i][1]);
		points[i].y = stoi(puntos[i][2]);	
		//cout<<points[i].x<<" "<<points[i].y<<"\n";
	}
		string sorted[n];
		cont=0;
	 stack<Punto> result = grahamScan(points, n);
    while (!result.empty())   {
        Punto p = result.top();
        result.pop();
			cont++;
     // cout<<p.pos<<" ";
			sorted[cont]=p.pos;
			
    }
		int t=cont;
		//cout<<"\n Resultado ordenado \n";
		for(int i = 0;i<t;i++)
		{
			
			cout<<sorted[cont]<<" ";
			cont--;
			}
	//el main tiene una complejidad de O(n*n) debido a que tiene dos ciclos anidados en su parte de almacenamiento
	//la complejidad que gobierna este programa es O(n*n)
}