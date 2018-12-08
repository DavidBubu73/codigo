#include <stdio.h>
#include <stdlib.h>

unsigned char * LocalizaVectorUnsignedChar(int n);

int * Histogramar(unsigned char*, int);

int * pide_entero(int);

int  EscribeHistograma(int *, char[]);

int main()
{
    //Declaración de variables.
    int n1, n2;
    char name[51], nombre1[51], nombre2[51];
    unsigned char *list1, *list2;
    int *histo1, *histo2;
    FILE *fd;

    printf("Ingrese el nombre de su archivo: \n");

    scanf("%s", name);
    fd = fopen(name, "rb");

    if(fd == NULL)
    {
        printf("Ha ocurrido un error con la apertura de tu archivo, intentelo de nuevo.\n");
        return 0;
    }

    fread(&n1, sizeof(int), 1, fd);

    //printf("\n%d\n", n1);

    list1 = LocalizaVectorUnsignedChar(n1);

    if(list1 == NULL)
    {
        printf("Hubo un error el almacen de memoria dinamica, intenta de nuevo.\n");
        return 0;
    }


    for(int i = 0; i < n1; i++)
    {
        fread(&list1[i], sizeof(unsigned char), 1, fd);
        //printf("%u ", list1[i]);
    }


    histo1 = Histogramar(list1, n1);

    if(histo1 == NULL)
        return 0;

    //---------------------------------------------------------------Segunda lista------------------------------------------------------------------------//

    fread(&n2, sizeof(int), 1, fd);


    list2 = LocalizaVectorUnsignedChar(n2);

    if(list2 == NULL)
    {
        printf("Hubo un error el almacen de memoria dinamica, intenta de nuevo.\n");
        return 0;
    }


    for(int i = 0; i < n2; i++)
    {
        fread(&list2[i], sizeof(unsigned char), 1, fd);
        //printf("%u ", list2[i]);
    }

    histo2 = Histogramar(list2, n2);


    if(histo2 == NULL)
        return 0;

    fclose(fd);

    printf("Ingrese el nombre de su primer histograma NO OLVIDE LA EXTENSION TXT: \n");
    scanf("%s", nombre1);

    if(EscribeHistograma(histo1, nombre1) == -1)
    {
        printf("No se pudo crear tu archivo, intentelo de nuevo.\n");
        return 0;
    }

    printf("Ingrese el nombre de su segundo histograma NO OLVIDE LA EXTENSION TXT: \n");
    scanf("%s", nombre2);

    if(EscribeHistograma(histo2, nombre2) == -1)
    {
        printf("No se pudo crear tu archivo, intentelo de nuevo.\n");
        return 0;
    }

    printf("Tus datos fueron guardados con exito.\n");

    return 0;
}

unsigned char * LocalizaVectorUnsignedChar(int n)
{
    return (unsigned char *)malloc(sizeof(unsigned char) * n);
}

int * pide_entero(int n)
{
    return (int *)malloc(sizeof(int) * n);
}

int * Histogramar(unsigned char *list, int n)
{
    int *histo;
    histo = pide_entero(255);
    if(histo == NULL)
    {
        printf("Lo siento, ha ocurrido un error, vuelve a intentarlo.");
        return NULL;
    }
    int cont;
    for(int i = 0; i < 256; i++)
    {
        cont = 0;
        for(int j = 0; j < n; j++)
        {
            if(list[j] == i)
            cont++;
        }
        histo[i] = cont;
    }

    return histo;
}

int  EscribeHistograma(int *histo, char nombre[51])
{
    FILE *out;

    out = fopen(nombre, "w+");

    if(out == NULL)
        return -1;

    for(int i = 0; i < 256; i++)
    {
        fprintf(out, "%d\t%d\n", i, histo[i]);
    }

    fclose(out);

    return 0;

}
