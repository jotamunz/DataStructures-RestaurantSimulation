#include <Cola.h>
#include <qDebug>



bool Cola::estaVacia(){
    return frente == nullptr;
}

Nodo * Cola::descolar(){
    Nodo * borrado = frente;
    if(!estaVacia()){
        frente = frente->siguiente;
        borrado->siguiente = nullptr;
    }
    return borrado;
}

void Cola::encolar(int dato){
    if(estaVacia())
        final = frente = new Nodo(dato);
    else{
        final->siguiente = new Nodo(dato);
        final = final->siguiente;
    }
}

void Cola::imprimir()
{
    if(estaVacia())
        qDebug() << "vacio";
    else
    {
        Nodo * temp = frente;

        while(temp != nullptr){
            qDebug() << temp ->dato;
            temp = temp->siguiente;
        }
    }

    qDebug() << "\n";

}
