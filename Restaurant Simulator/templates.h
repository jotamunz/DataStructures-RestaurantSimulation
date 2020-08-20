#ifndef MENU_H
#define MENU_H
#include <qdebug.h>

template <typename T> struct Node
{
    Node<T> *next, *previous;
    T data;

    Node<T>(T _data)
    {
        this->next = this->previous = nullptr;
        this->data = _data;
    }
};

template <typename T> struct Queue
{
    Node<T> *first, *last;

    Queue<T>()
    {
        this->first = this->last = nullptr;
    }

    bool isEmpty() { return this->first == nullptr; }

    T peek()
    {
        if (first != nullptr)
            return first->data;
        else
            return 0;
    }

    void queue(T data)
    {
        if (this->isEmpty()) this->last = this->first = new Node<T>(data);
        else
        {
            this->last->next = new Node<T>(data);
            this->last = this->last->next;
        }
    }

    void priorityQueue(T data)
    {
        if (this->isEmpty()) this->last = this->first = new Node<T>(data);
        else
        {
            Node<T> * temp = new Node<T>(data);
            temp->next = this->first;
            this->first = temp;
        }
    }

    T dequeue()
    {
        Node<T> * borrado = first;
        if(!isEmpty()){
            first = first->next;
            borrado->next = nullptr;
        }
        return borrado->data;
    }

    void print()
    {
        if(isEmpty())
            qDebug() << "vacio";
        else
        {
            QString str = "";
            Node<T> * temp = this->first;

            while(temp != nullptr)
            {
                str += QString::number(temp->data) + " ";
                temp = temp->next;
            }
            qDebug().noquote() << "\t" << "Cola:" << str;
        }
    }

    QString toString()
    {
        QString str = "Lista de Espera: \n";
        if(!isEmpty())
        {
            Node<T> * temp = this->first;

            while(temp != nullptr)
            {
                str += "\t" + QString::number(temp->data) + " clientes \n";
                temp = temp->next;
            }
        }
        return str;
    }
};

template <typename T> struct DoubleList
{
    Node<T> *first, *last;

    DoubleList<T>()
    {
        this->first = this->last = nullptr;
    }

    bool isEmpty() { return this->first == nullptr; }

    void insert(T data)
    {
        if (this->isEmpty()) this->last = this->first = new Node<T>(data);
        else
        {
            this->last->next = new Node<T>(data);
            this->last->next->previous = this->last;
            this->last = this->last->next;
        }
    }

    int size()
    {
        Node<T> * temp = this->first;
        int count = 0;

        while(temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T getPosition(int position)
    {
       Node<T> * temp = this->first;

       if (position < this->size())
       {
           for (int i = 0; i < position; i++)
               temp = temp->next;
       }
       return temp->data;
    }
};

template <typename T> struct SimpleList
{
    Node<T> *first, *last;

    SimpleList<T>()
    {
        this->first = this->last = nullptr;
    }

    bool isEmpty() { return this->first == nullptr; }

    void insert(T data)
    {
        if (this->isEmpty()) this->last = this->first = new Node<T>(data);
        else
        {
            this->last->next = new Node<T>(data);
            this->last = this->last->next;
        }
    }

    int size()
    {
        Node<T> * temp = this->first;
        int count = 0;

        while(temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T getPosition(int position)
    {
       Node<T> * temp = this->first;

       if (position < this->size())
       {
           for (int i = 0; i < position; i++)
               temp = temp->next;
       }
       return temp->data;
    }
};

template <typename T> struct QueueStack
{
    Node<T> *first, *last;
    bool stack = false;

    QueueStack<T>()
    {
        this->first = this->last = nullptr;
    }

    bool isEmpty() { return this->first == nullptr; }

    void queueORpush(T data)
    {
        if (this->isEmpty()) this->last = this->first = new Node<T>(data);
        else
        {
            this->last->next = new Node<T>(data);
            this->last = this->last->next;
        }
    }

    T dequeue()
    {
        Node<T> * borrado = first;
        if(!isEmpty()){
            first = first->next;
            borrado->next = nullptr;
        }
        return borrado->data;
    }

    T pop()
    {
        Node<T> * borrado = first;
        if(!isEmpty()){
            if (first == last){
                first = last = nullptr;
            }
            else{
                while (borrado->next != last)
                    borrado = borrado->next;
                last = borrado;
                borrado = borrado->next;
                last->next = nullptr;
            }
        }
        return borrado->data;
    }

    void switchMode()
    {
        this->stack = !stack;
        qDebug() << "Set mode stack to:" << this->stack;
    }
};

#endif // MENU_H
