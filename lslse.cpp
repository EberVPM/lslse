#include <iostream>

template<class T>
class LSLSE;

template<class T>
class node {
private:
    T data;
    node<T>* sig;
public:
    node() :sig(nullptr) {};
    friend class LSLSE<T>;
};

class SocioClub {
private:
    int NumeroSocio, ingreso;
    std::string NombreSocio, Domicilio;
public:
    SocioClub() {
        NumeroSocio = 0;
        NombreSocio = " ";
        Domicilio = " ";
        ingreso = 0;
    }
    SocioClub(int Numero, std::string nombre, std::string dom, int ing) {
        NumeroSocio = Numero;
        NombreSocio = nombre;
        Domicilio = dom;
        ingreso = ing;
    }

    int getNumero() {
        return NumeroSocio;
    }

    friend bool operator == (SocioClub& socio1, SocioClub& socio2) {
        return (
            socio1.NombreSocio == socio2.NombreSocio &&
            socio1.Domicilio == socio2.Domicilio
            );
    }

    friend bool operator != (SocioClub& s1, SocioClub& s2) {
        return !(s1 == s2);
    }

    friend SocioClub operator + (SocioClub& s1, SocioClub& s2) {
        return SocioClub(s1.NumeroSocio + s2.NumeroSocio, s1.NombreSocio + s2.NombreSocio,
            s1.Domicilio + s2.Domicilio, s1.ingreso + s2.ingreso);
    }

    friend bool operator > (SocioClub& s1, SocioClub& s2) {
        return s1.NumeroSocio > s2.NumeroSocio;
    }

    friend bool operator < (SocioClub& s1, SocioClub& s2) {
        return s1.NumeroSocio < s2.NumeroSocio;
    }

    friend std::istream& operator >> (std::istream& i, SocioClub& e) {
        std::cout << "Ingresa la Numero de socio: ";
        i >> e.NumeroSocio;

        std::cout << "Ingresa el nombre de socio: ";
        std::cin.ignore();
        i >> e.NombreSocio;

        std::cout << "Ingresa el domicilio del socio: ";
        std::cin.ignore();
        i >> e.Domicilio;

        std::cout << "Ingresa el ingreso del socio: ";
        i >> e.ingreso;

        return i;
    }

    friend std::ostream& operator << (std::ostream& o, SocioClub& e) {
        o << "Clave: " << e.NumeroSocio << std::endl;
        o << "NombreSocio: " << e.NombreSocio << std::endl;
        o << "Domicilio: " << e.Domicilio << std::endl;
        o << "ingreso: " << e.ingreso << std::endl;

        return o;
    }
};

template<class T>
class LSLSE {
private:
    node<T>* lista;
public:
    LSLSE() :lista(nullptr) {};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir()const;
    node<T>* busqueda(SocioClub socio, bool dom=false);
    void ordenar();
    int total();
};

template<class T>
void LSLSE<T>::imprimir()const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << aux->data << std::endl;
        aux = aux->sig;
        std::cout << "----------------------------------------" << std::endl;
    }
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
    }
    else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem) {
    node<T>* aux = new node<T>;
    aux->data = elem;

    if (pos == nullptr) {
        aux->sig = lista;
        lista = aux;
    }
    else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const {
    if (vacia()) {
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* LSLSE<T>::ultimo()const {
    if (vacia()) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template <class T>
node<T>* LSLSE<T>::busqueda(SocioClub socio, bool dom) {
    if (vacia()) {
        return nullptr;
    }

    if (!dom) {
        for (node<T>* s = lista; s != nullptr; s = s->sig) {
            if (s->data.getNumero() == socio.getNumero()) {
                return s;
            }
        }
    } else {
        for (node<T>* s = lista; s != nullptr; s = s->sig) {
            if (s->data == socio) {
                std::cout << s->data << std::endl;
                return s;
            }
        }
    }

    return nullptr;
}

template <class T>
int LSLSE<T>::total() {
    int contador = 0;

    if (vacia()) {
        return contador;
    }

    for (node<T>* s = lista; s != nullptr; s = s->sig) {
        contador++;
    }

    return contador;
}

template<class T>
void LSLSE<T>::ordenar() {
    node<T>* actual = lista;

    while (actual != nullptr) {
        node<T>* min = actual;
        node<T>* siguiente = actual->sig;
        SocioClub temp;

        while (siguiente != nullptr) {
            if (siguiente->data.getNumero() < min->data.getNumero()) {
                min = siguiente;
            }
            siguiente = siguiente->sig;
        }

        temp = actual->data;
        actual->data = min->data;
        min->data = temp;

        actual = actual->sig;
    }
}

template<class T>
bool LSLSE<T>::vacia()const {
    if (lista == nullptr)
        return true;
    return false;
}

int main()
{
    LSLSE<SocioClub> milista;
    int opcion, num;
    SocioClub socio;
    std::string nom, domi;

    do {
        std::cout << "---------------Menu---------------" << std::endl;
        std::cout << "1. Registrar un nuevo socio" << std::endl;
        std::cout << "2. Dar de baja un socio del club" << std::endl;
        std::cout << "3. Generar un reporte con los datos de todos los socios" << std::endl;
        std::cout << "4. Buscar por nombre y domicilio a un socio" << std::endl;
        std::cout << "5. Calcular e imprimir el total de socios registrados" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            std::cin >> socio;

            if (milista.busqueda(socio) != nullptr) {
                std::cout << "Numero de socio ya en uso, use otro" << std::endl;
            }
            else {
                milista.insertar(milista.ultimo(), socio);
                milista.ordenar();
            }
            break;
        case 2:
            if (milista.vacia()) {
                std::cout << "La lista se encuentra vacia" << std::endl;
            }
            else {
                std::cout << "Ingrese el numero de socio a dar de baja: ";
                std::cin >> num;

                SocioClub pepe(num, "", "", 0);

                if (milista.busqueda(pepe) != nullptr) {
                    milista.eliminar(milista.busqueda(pepe));
                    std::cout << "Socio eliminado" << std::endl;
                }
                else {
                    std::cout << "No existe el socio" << std::endl;
                }
            }
            break;
        case 3:
            if (milista.vacia()) {
                std::cout << "La lista se encuentra vacia" << std::endl;
            }
            else {
                std::cout << "Reporte: " << std::endl;
                milista.imprimir();
            }
            break;
        case 4:
            if (milista.vacia()) {
                std::cout << "La lista se encuentra vacia" << std::endl;
            }
            else {
                std::cout << "Ingrese el nombre del socio a buscar: ";
                std::cin >> nom;

                std::cout << "Ingrese el domicilio del socio a buscar: ";
                std::cin >> domi;

                SocioClub paco(0, nom, domi, 0);

                if (milista.busqueda(paco, true) == nullptr) {
                    std::cout << "Socio no encontrado" << std::endl;
                }

            }
            break;
        case 5:
            std::cout << "Numero total de socios: " << milista.total() << std::endl;
            break;
        case 6:
            std::cout << "Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opcion incorrecta :(" << std::endl;
            break;
        }
    } while (opcion != 6);

    return 0;
}
