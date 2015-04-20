

#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;





template<typename T>
class CorrePocoyo {


public:

	CorrePocoyo();  //TESTED

	CorrePocoyo(const CorrePocoyo<T>&);

	~CorrePocoyo(); //TESTED

	void nuevoCorredor(const T&); //TESTED

	void nuevoCorredor(const T&, const T&); //TESTED

	void seCansa(const T&); //TESTED

	void sobrepasar(const T&); //TESTED

	const T& corredorFilmado() const; //TESTED

	void filmarProxPerdedor(); //TESTED

	void filmarProxExitoso(); //TESTED

	const T& damePrimero() const; //TESTED

	int damePosicion(const T& ) const; //TESTED

	const T& dameCorredorEnPos(int) const; //TESTED

	bool esVacia() const; //TESTED

	int tamanio() const; //TESTED

	bool operator==(const CorrePocoyo<T>&) const; // UNTESTED

	ostream& mostrarCorrePocoyo(ostream& os) const; //TESTED




private:
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}


	struct Nodo {
		Nodo(T elem) : automovil(elem) {}
		T automovil;
		Nodo* adelante;
		Nodo* atras;
	};


	Nodo* primero;
	Nodo* camara;
	Nodo* ultimo;



};
template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}


template<typename T>
CorrePocoyo<T>::CorrePocoyo()
	: primero(NULL), camara(NULL), ultimo(NULL) {}

template<typename T>
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otra)
{
	this->primero = NULL;
	this->ultimo = NULL;
	this->camara = NULL;

	if(!(otra.esVacia()))
	{
			
		Nodo* buscadorOtra = otra.primero;
		Nodo* newPrimerAuto = new Nodo(buscadorOtra->automovil);
		this->primero = newPrimerAuto;
		
		buscadorOtra = buscadorOtra->atras;
		Nodo* buscadorThis = this->primero;
		Nodo* auxThis = NULL;

		while(buscadorOtra != NULL)
		{	
			 Nodo* newAuto = new Nodo(buscadorOtra->automovil);
			 buscadorThis->atras = newAuto;
			 auxThis = buscadorThis;
			 buscadorThis = buscadorThis->atras;
			 buscadorThis->adelante = auxThis;

			 buscadorOtra = buscadorOtra->atras;
		}

		this->ultimo = buscadorThis;

		if(!(otra.camara == NULL))
		{
			
			int intCam = otra.damePosicion((otra.camara)->automovil);
			Nodo* buscaCam = this->primero;
			this->camara = buscaCam;
			while(intCam != 1)
			{
				buscaCam = buscaCam->atras;
				this->camara = buscaCam;
				intCam--;
			}



		}
	}


}


 //    int i = 0;
	//  if (!(this->primero == NULL))
	// {
 //        Nodo* actual = this->primero;
 //        i = 1;
 //        while (actual->automovil != ultimo->automovil) {
 //            i++;
 //            actual = actual->atras;
 //            }
 //    }
	//  return i;


template<typename T>
CorrePocoyo<T>::~CorrePocoyo()
{

	if (!this->esVacia()) 
	{
		Nodo* todel = primero;
		Nodo* next = NULL;
		while (!(todel->automovil == ultimo->automovil))
		{
					
			next = todel;
			todel = todel->atras;
			delete  next;
		
		}

		delete ultimo;

	}

	// delete this;
}





template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& a)
{
	if (primero == NULL)
		// if(this.es)
	{
		Nodo* nuevo = new Nodo(a);
		nuevo->adelante = NULL;
		nuevo->atras = NULL;
		this->primero = nuevo;
		this->ultimo = nuevo;
		this->camara = nuevo;


	}
	else
	{
		Nodo* nuevo = new Nodo(a);

		nuevo->atras = NULL;
		nuevo->adelante = ultimo;

		ultimo->atras = nuevo;
		this->ultimo = nuevo;

	}
}

template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& a1 , const T& a2)
{

	// SI A2 ES PRIMERO
	if (primero->automovil == a2)
	{
		Nodo* nuevo = new Nodo(a1);
		nuevo->adelante = NULL;
		nuevo->atras = this->primero;
		primero->adelante = nuevo;
		this->primero = nuevo;

	} else
	{

		// SI A2 ES ULTIMO
		if (ultimo->automovil == a2)
		{
			Nodo* guardaN = this->ultimo;
			guardaN = ultimo->adelante;


			Nodo* nuevo = new Nodo(a1);

			nuevo->adelante = guardaN;
			nuevo->atras = this->ultimo;

			guardaN->atras = nuevo;
			ultimo->adelante = nuevo;

		} else
		{

			// A2 ESTA EN EL MEDIO
			Nodo* buscador = this->primero;

			// BUSCO A2
			while (!(buscador->automovil == a2))
			{
				buscador = buscador->atras;
			}

			// ENCONTRE A2
			// CREO NODO
			Nodo* nuevo = new Nodo(a1);
			Nodo* guardaN = buscador->adelante;

			nuevo->adelante = guardaN;
			nuevo->atras = buscador;

			buscador->adelante = nuevo;
			guardaN->atras = nuevo;
		}
	}


}

template<typename T>
void CorrePocoyo<T>::seCansa(const T& a )
{


	// SI a ES PRIMERO
	if (primero->automovil == a)
	{
		if(primero->atras == NULL)
		{
			delete primero;
			primero= NULL;
			ultimo = NULL;

		}else
		{
			Nodo* guardaN0 = primero;
			primero = primero->atras;
			delete guardaN0;
		}

	}else
	{
		if(ultimo->automovil == a)
		{

			Nodo* guardaN0 = ultimo;
			ultimo = ultimo->adelante; 
			ultimo->atras =	NULL;

			delete guardaN0;	


		

		}else
		{
				Nodo* buscador = this->primero;
				while (!(buscador->automovil == a))
				{
					buscador = buscador->atras;
				}
				// ENCONTRAMOS A a

				// GUARDAMOS EL adelante Y atras DE a

				Nodo* guardaNAd = buscador->adelante;
				Nodo* guardaNAt = buscador->atras;
				// LOS CONECTAMOS
				guardaNAt->adelante = guardaNAd;
				guardaNAd->atras = guardaNAt;
				// DEJAMOS AFUERA A a
				buscador->adelante=NULL;
				buscador->atras=NULL;
				// BORRAMOS A a
				delete buscador;
		}
	}







}

template<typename T>
void CorrePocoyo<T>::sobrepasar(const T& a )
{
	// BUSCO a EN LA LISTA
	Nodo* buscador = this->primero;

	while (!(buscador->automovil == a))
	{
		buscador = buscador->atras;
	}
	// ENCONTRE A a

	if (buscador->automovil == ultimo->automovil)
	{

		Nodo* guardaN0 = buscador->adelante;
		if (guardaN0->adelante == NULL)
		{
			buscador->adelante = NULL;
			buscador->atras = guardaN0;
			guardaN0->adelante = buscador;
			guardaN0->atras = NULL;
			this->primero = buscador;
			this->ultimo = guardaN0;

		} else
		{

			Nodo* guardaN1 = guardaN0->adelante;
			buscador->adelante = guardaN1;
			buscador->atras = guardaN0;

			guardaN0->adelante = buscador;
			guardaN0->atras = NULL;
			guardaN1->atras = buscador;
			ultimo = guardaN0;
		}


	} else
	{

		Nodo* guardaN0 = buscador->adelante;
		if (guardaN0->adelante == NULL)
		{

			Nodo* guardaN1 = buscador->atras;

			buscador->adelante = NULL;
			buscador->atras = guardaN0;

			guardaN0->adelante = buscador;
			guardaN0->atras = guardaN1;

			guardaN1->adelante = guardaN0;

			this->primero = buscador;


		} else
		{

		//"[10, 20, 22, 27]" ---> "[10, 22, 20, 27]"
		//buscador 22
		//guardaN0 20
		Nodo* guardaN1 = buscador->atras; //27
		Nodo* guardaN2 = guardaN0->adelante;//10

		buscador->adelante = guardaN2;
		buscador->atras = guardaN0;

		guardaN0->adelante = buscador;
		guardaN0->atras = guardaN1;

		guardaN1->adelante = guardaN0;
		guardaN2->atras = buscador;
		}
	}

}

template<typename T>
const T& CorrePocoyo<T>::corredorFilmado() const
{
	return camara->automovil;
}

template<typename T>
void CorrePocoyo<T>:: filmarProxPerdedor()
{
	camara = camara->atras;
}


template<typename T>
void CorrePocoyo<T>:: filmarProxExitoso()
{
	camara = camara->adelante;
}

template<typename T>//NO SE X NO FUNCIONA
const T& CorrePocoyo<T>:: damePrimero()const 
{
	return primero->automovil;
}

template<typename T>
int CorrePocoyo<T>:: damePosicion(const T& a) const
{
	int i = 1;
	Nodo* auxiliar = primero;
	while (!(auxiliar->automovil== a))
	{
		auxiliar = auxiliar->atras;
		i++;
	}
	return i--;
}

template<typename T>
const T& CorrePocoyo<T>:: dameCorredorEnPos(int a) const	
{
	int i = a;
	Nodo* auxiliar = primero;
	while ( i > 1)
	{
		i--;
		auxiliar = auxiliar->atras;
		
	}
	return auxiliar->automovil;
	
}

template<typename T>
bool CorrePocoyo<T>:: esVacia() const
{
	return (0 == this->tamanio());
}

template<typename T>
int CorrePocoyo<T>:: tamanio() const
{
    int i = 0;
	 if (!(this->primero == NULL))
	{
        Nodo* actual = this->primero;
        i = 1;
        while (actual->automovil != ultimo->automovil) {
            i++;
            actual = actual->atras;
            }

    }
	 return i;

}


template <typename T>
bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& elotro) const 
{

	if(esVacia() && elotro.esVacia())
	{
        return true;

	}else{
		
		if(tamanio() == elotro.tamanio())
		{
			Nodo* buscadorThis = this->primero;
	        Nodo* buscadorOtro = elotro.primero;

	        while(!(buscadorThis==NULL))
	        {
	        	if (!(buscadorThis->automovil == buscadorOtro->automovil))
	        	{
                	return false;
                	break;
                }
                
                buscadorThis = buscadorThis->atras;
	      		buscadorOtro = buscadorOtro->atras;
	        }

	        return true;
		}else
		{
			return false;
		}
	}

}

template<typename T>
ostream& CorrePocoyo<T>:: mostrarCorrePocoyo(ostream& out) const
{
	if (this->esVacia()) {
		out << "[]";
	}
	else {




		out << "[" << primero->automovil;

		Nodo* actual = primero->atras;

		while (!(actual == NULL)) {

			out << ", " << actual->automovil;

			actual = actual->atras;

		}
		out << "]";
	}
	return out;

}



#endif //CORREPOCOYO_H_