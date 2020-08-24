#include <iostream>
#include<queue>

using namespace std;

struct Nodo
{
	int elemento;
	Nodo *izq;
	Nodo *der;
};

class ArbolBinario
{
	protected:
		Nodo *raiz;
	public:
		ArbolBinario();
		Nodo *getRaiz();//ya
		void setRaiz(Nodo *);//ya
		//iterativo, retorna la nueva raiz
		Nodo *agregar(Nodo *,int);//ya, agregando a sub-arbol menos profundo
		int eliminar(Nodo *);
		//se le pasa el nodo por que el metodo es recursivo (Nodo *) 
		int profundidad(Nodo *);//ya    modo postorden creo
		Nodo *mostrarPreorden(Nodo *);//ya
		Nodo *mostrarInorden(Nodo *);//ya
		Nodo *mostrarPosorden(Nodo *);//ya
		void Inorden();//sirve de algo?
		void Postorden();//sirve de algo?
		void Niveles();//sirve de algo?; muestra los niveles XD
		int cantidadNodos();
		int cantidadHojas();
		Nodo *buscar(Nodo *,int);
		char menu();
		char menumostrar();
};

//constructor
ArbolBinario::ArbolBinario()
{
	//inicia el arbol vacio
	raiz=NULL;
}
Nodo *ArbolBinario::getRaiz()
{
	return raiz;
}
void ArbolBinario::setRaiz(Nodo *raiz)
{
	this->raiz=raiz;
}
Nodo *ArbolBinario::agregar(Nodo *raiz, int elemento)
{
	Nodo *p;
	//miramos que subarbol es menos profundo y agregamos por ahí
	if (raiz)
	{
		if (profundidad(raiz->izq)<profundidad(raiz->der)) raiz->izq=agregar(raiz->izq,elemento);
		else raiz->der=agregar(raiz->der,elemento);
	}
	else
	{
		p= new Nodo;
		raiz=p;
		raiz->elemento=elemento;
		raiz->izq=raiz->der=NULL;
	}
	return raiz;
}

//debe eliminar el elemento mas profundo del arbol creo
//averiguar bn que debe eliminar
//probar eliminando elementos a ver si los muestra, si no, un return eliminar(raiz->izq) a ver si sirve, lo mismo con eliminar(raiz->der)

int ArbolBinario::eliminar(Nodo *raiz)
{
	if(raiz)
	{
		if(raiz->izq||raiz->der)
		{
			if(profundidad(raiz->izq)>profundidad(raiz->der))eliminar(raiz->izq);
			else eliminar(raiz->der);
		}
		else
		{
			int a=raiz->elemento;
			delete(raiz);
			return a;
		}
	}
	else return 0;
}

//profundidad (recursivamente post-orden)
int ArbolBinario::profundidad(Nodo *raiz)
{
	int profizq,profder;
	if(raiz)
	{
		//si no esta vacio =! NULL
		profizq=profundidad(raiz->izq);
		profder=profundidad(raiz->der);
		//verificar cual de las dos es mayor
		if(profizq>profder) return profizq+1;
		else return profder+1;
	}
	else return 0;
}

Nodo *ArbolBinario::mostrarPreorden(Nodo *raiz)
{
	if(raiz)
	{
		cout<<raiz->elemento<<" ";
		mostrarPreorden(raiz->izq);
		mostrarPreorden(raiz->der);
	}
	else return NULL;
}
Nodo *ArbolBinario::mostrarInorden(Nodo *raiz)
{
	if(raiz)
	{
		
		mostrarInorden(raiz->izq);
		cout<<raiz->elemento<<" ";
		mostrarInorden(raiz->der);
	}
	else return NULL;
}
Nodo *ArbolBinario::mostrarPosorden(Nodo *raiz)
{
	if(raiz)
	{
		
		mostrarPosorden(raiz->izq);
		mostrarPosorden(raiz->der);
		cout<<raiz->elemento<<" ";
	}
	else return NULL;
}

Nodo *ArbolBinario::buscar(Nodo *raiz,int abuscar){
	if(raiz)
	{
		if(raiz->elemento==abuscar) return (raiz);
		else
		{
			buscar(raiz->izq, abuscar);
			buscar(raiz->der, abuscar);
		}
	}
	else return NULL;
}

void ArbolBinario::Niveles()
{
	if(raiz)
	{
		queue<Nodo *> q;
		q.push(raiz);
		while(!q.empty())
		{
			Nodo*nodo = q.front();
			cout<< nodo->elemento <<" ";
			q.pop();
			if (nodo->izq!=NULL) q.push(nodo->izq);
			if (nodo->der!=NULL) q.push(nodo->der);
		}
	}
}

char ArbolBinario::menu()
{
	char a;
	cout<<"-------------------------"<<endl;
	cout<<"------------MENU---------"<<endl;
	cout<<"(A)gregar"<<endl;
	cout<<"(E)liminar"<<endl;
	cout<<"(M)ostrar"<<endl;
	cout<<"(P)rofundidad"<<endl;
	cout<<"Contar (N)odos"<<endl;
	cout<<"Contar (H)ojas"<<endl;
	cout<<"(T)erminar"<<endl;
	cout<<"Ingrese una opcion: ";
	cin>>a;
	cout<<"-------------------------"<<endl;
	return a;
}

char ArbolBinario::menumostrar()
{
	char a;
	cout<<"-------------------------"<<endl;
	cout<<"-----Mostar Arbol--------"<<endl;
	cout<<"(P)re-Orden"<<endl;
	cout<<"(I)n-Orden"<<endl;
	cout<<"P(O)s-Orden"<<endl;
	cout<<"(N)iveles"<<endl;
	cout<<"Ingrese una opcion: ";
	cin>>a;
	cout<<"-------------------------"<<endl;
	return a;
}

//Arbol binario ordenado que hereda del binario normal

class ArbolBinarioOrdenado: public ArbolBinario
{
	public:
		ArbolBinarioOrdenado();
		//redefinimos los metodos agregar y buscar (esta forma es iterativa)
		Nodo *agregar(int);
		Nodo *buscar(int);
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado()
{
	//comienza vacio
	raiz=NULL;
}

Nodo *ArbolBinarioOrdenado::agregar(int elemento)
{
	//recursivo
	//R inicia en la raiz
	Nodo *R=raiz, *s;
	//declaracion de otro apuntador (s)
	while(R)
	{
		//asignamos "s" a "R"
		s=R;
		//Asumiendo que ele elemento a agregar NO ESTÄ, y es menor al elemento de la raiz, lo agregamos por la izquierda
		if(elemento<R->elemento) R=R->izq;
		//si no, lo agregaos por la derecha
		else R=R->der;
	}
	//creamos el nodo R:
	R=new Nodo;
	//guardamos el elemento que estabamos agregando
	R->elemento=elemento;
	//nos aseguramosde que siempre sea una hoja
	R->der=R->izq=NULL;
	//lo conectamos al padre para saber si la salida es por derecha o por izquierda
	if(raiz)
	{
		if(elemento < s->elemento) s->izq=R;
		else s->der=R;
		return raiz;
	}
	raiz=R;//asigna a la raiz el valor de r, y luego la retorna
}

class AVL: public ArbolBinarioOrdenado
{
	public:
		AVL();
		//redefinimos los metodos agregar y buscar (esta forma es iterativa)
		Nodo *agregar(int);
		Nodo *buscar(int);
};

AVL::AVL()
{
	this->raiz=NULL;
}

char menuprincipal()
{
	char a;
	cout<<"-------------------------"<<endl;
	cout<<"-----Menu Principal------"<<endl;
	cout<<"Arbol (B)inario"<<endl;
	cout<<"Arbol Binario (O)rdenado"<<endl;
	cout<<"(A)VL"<<endl;
	cout<<"(S)alir"<<endl;
	cout<<"Ingrese una opcion: ";
	cin>>a;
	cout<<"-------------------------"<<endl;
	return a;
}

int main()
{
	ArbolBinario *arbol;
	char dato=menuprincipal();
	while (dato != 'S' || dato != 's')
	{
		switch(dato)
		{
			case('b'):
			case('B'):
				{
					arbol=new ArbolBinario();
				}
			break;
			case('o'):
			case('O'):
				{
					arbol=new ArbolBinarioOrdenado();
				}
			break;
			case('a'):
			case('A'):
				{
					arbol=new AVL();
				}
			break;
		}
		char opcion=arbol->menu();
		while (opcion != 'T' || opcion != 't')
		{
			switch(opcion)
			{
				case('a'):
				case('A'):
					{
						int a;
						cout<<"-----------------"<<endl;
						cout<<"Ingrese el valor: ";
						cin >>a;
						cout<<"-----------------"<<endl;
						try
						{
							arbol->agregar(arbol->getRaiz(),a);
						}
						catch (int error)
						{
							arbol->agregar(a);
						}
					}
				break;
				case('e'):
				case('E'):
					{
						arbol=new ArbolBinario();
					}
				break;
				case('m'):
				case('M'):
					{
						char f=arbol->menumostrar();
						switch(f)
						{
							case('I'):
							case('i'):
									arbol->mostrarInorden(arbol->getRaiz());
							break;
							case('P'):
							case('p'):
									arbol->mostrarPreorden(arbol->getRaiz());
							break;
							case('O'):
							case('o'):
									arbol->mostrarPosorden(arbol->getRaiz());
							break;
							case('N'):
							case('n'):
									arbol->Niveles();
							break;
						}
					}
				break;
				case('p'):
				case('P'):
					{
						arbol=new ArbolBinario();
					}
				break;
				case('n'):
				case('N'):
					{
						arbol=new ArbolBinario();
					}
				break;
				case('H'):
				case('h'):
					{
						arbol=new ArbolBinario();
					}
				break;
			}
			opcion=arbol.menu();
		}
		dato=menuprincipal();
	}
	system("pause");
	return 0;
}
