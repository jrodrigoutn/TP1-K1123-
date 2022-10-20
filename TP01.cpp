#include <iostream>
#include <fstream>
using namespace std;

int buscarmayor (float vectorkmrecorridos[],int dimp)
{
int mayor {0};
for (int i = 1; i < dimp; i++)
{
    if (vectorkmrecorridos[mayor]<vectorkmrecorridos[i])
    {
        mayor=i;
    }
    
}
    return mayor;
}

void funcionordenamiento_ascendente (float vectorconcoordenadas[],float vectorkmrecorridos[],int dimp)
{   
    float temp;
    int temp2;
    for (int i = 0; i < dimp; i++)
    {
        for(int j=i+1;j<dimp;j++)
        {
            if (vectorkmrecorridos[i]>vectorkmrecorridos[j])
            {
                temp=vectorkmrecorridos[j];
                vectorkmrecorridos[j]=vectorkmrecorridos[i];
                vectorkmrecorridos[i]=temp;

                temp2=vectorconcoordenadas[j];
                vectorconcoordenadas[j]=vectorconcoordenadas[i];
                vectorconcoordenadas[i]=temp2;
            }  
        }
    };
};

int buscarmayorcantidad (float matrizkg[][5],int dimc)
{const int dimp {5};
    int mayor {0};
    int mayorcantidad;
    for (int i = 0; i < dimc; i++)
    {   int sum {0};
        for (int j=0;j<dimp;j++)
        {
           if (matrizkg[i][j] > 13000)
           {
            sum++;
            if (sum>mayor)
            {
                mayor=sum;
                mayorcantidad = i;
            }
    
           };
        }; 
    };
    return mayorcantidad;
};

void mostrarmatrizkg(float matrizkg[][5],int dimc)
{   
    const int dimp {5};
    for (int i = 0; i < dimc; i++)
    {
        for (int j = 0; j < dimp; j++)
        {
            cout<<"matrizkg  ["<<i<<"] ["<<j<<"] = "<<matrizkg [i][j]<<" kg"<<"\t";
        };
        cout<<endl;
    };
};

void mostrarmatrizkm(float matrizkm[][5],int dimc)
{   
    const int dimp {5};
    for (int i = 0; i < dimc; i++)
    {
        for (int j = 0; j < dimp; j++)
        {
            cout<<"matrizkm  ["<<i<<"] ["<<j<<"] = "<<matrizkm [i][j]<<"km"<<"\t";
        };
        cout<<endl;
    };
};
void mostrarclientes (string vclientes[],int dimc)
{
    for (int i = 0; i < dimc; i++)
    {
        cout<<"vclientes ["<<i<<"] =  "<< vclientes[i] <<endl;
    }
}

void mostrarproductos (string vproductos[],int dimp)
{
    for (int i = 0; i < dimp; i++)
    {
        cout<<"vproductos ["<<i<<"] =  "<< vproductos[i] <<endl;
    }
}

int main(){

    bool debug {false};
    const int dimc {8};
    string vclientes [dimc];

    const int dimp {5};
    string vproductos [dimp];

    ifstream archinombres;
    archinombres.open("nombres(TP01).txt");

    if (!archinombres)
    {
        cout<<"hubo un error a la hora de abrir el archivo de nombres"<<endl;
        return 1;
    };

    for (int i = 0; i < dimc; i++)
    {
        archinombres>>vclientes[i];
    };
    
    for (int i = 0; i < dimp; i++)
    {
        archinombres>>vproductos[i];
    };

    archinombres.close();
    
    if (debug)
    {
        mostrarclientes (vclientes,dimc);
        mostrarproductos (vproductos,dimp);
    }
    
    float matrizkg [dimc][dimp]{};
    float matrizkm [dimc][dimp]{};

    ifstream archidatos;
    archidatos.open("datos(TP01).txt");

    if (!archidatos)
    {
        cout<<"hubo un error a la hora de abrir el archovo de datos"<<endl;
        return 2;
    };

    int clientes,productos;
    float kg;
    float km;

    while(archidatos>>clientes>>productos>>kg>>km)
    {
        matrizkg[clientes][productos]+=kg;
        matrizkm[clientes][productos]+=km;
    };
    
    archidatos.close();

    if (debug)
    {
        mostrarmatrizkg(matrizkg,dimc);
        mostrarmatrizkm(matrizkm,dimc);
    }

    cout<<"====================================================================================="<<endl;
    
//PUNTO 1

    cout<<"Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: "<<endl;

    for (int i = 0; i < dimc; i++)
    {   int separador {0};
        for (int j = 0; j < dimp; j++)
        {   
            if (matrizkg[i][j] >= 13000 && separador == 0) //el "separador" lo utilizo para que cuando aparezca el  "vcliente[i] " en la lista 
            {                                               // y no aparezca mal escrita la lista de productos y clientes del primer ejercicio.
                cout<<vclientes[i]<<" : "<<vproductos[j];    
                separador++;
            }
            else    if (matrizkg[i][j] >= 13000 && separador > 0)
                    {
                        cout<<" , "<<vproductos[j];
                    }
        };
        cout<<"."<<endl;
    };

    cout<<"====================================================================================="<<endl;
    
//PUNTO 2
    int mayorcantidad = buscarmayorcantidad (matrizkg,dimc);

    if (debug)
    {
        cout<<"vector cliente : "<<vclientes[mayorcantidad]<<endl;
    }
    
    float vectorkmrecorridos [dimp];

    for (int i = 0; i < dimp; i++)
    {
        vectorkmrecorridos[i]=matrizkm[mayorcantidad][i];
    };

    float vectorconcoordenadas[dimp];
    
    for (int i = 0; i < dimp; i++)
    {
        vectorconcoordenadas[i]=i;
    };

    funcionordenamiento_ascendente (vectorconcoordenadas,vectorkmrecorridos,dimp);

    cout<<"Listado de Km recorridos por tipo de producto (ascendente): "<<endl;
    
    for (int i = 0; i < dimp; i++)
    {   
        int f=vectorconcoordenadas[i];
        cout<<vproductos[f]<<" : "<<vectorkmrecorridos[i]<<" km"<<endl;
    }

    cout<<"====================================================================================="<<endl;

//PUNTO 3
    int mayor=buscarmayor (vectorkmrecorridos,dimp);
    int producto = vectorconcoordenadas[mayor];

    archidatos.open("datos(TP01).txt");

    if (!archidatos)
    {
        cout<<"hubo un error a la hora de abrir el archovo de datos"<<endl;
        return 3;
    };

    int cont {0};
    int productos2;

    do
    {
        if (producto == productos2 )
        {
            cont++;
        }
    } 
    while (archidatos>>clientes>>productos2>>kg>>km);

    archidatos.close();

    cout<<"Cantidad de entregas para el tipo de producto "<<vproductos[productos]<<": "<<cont<<endl;

    cout<<"====================================================================================="<<endl;

    return 0;
}