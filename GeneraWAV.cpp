// GeneraWAV.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265

void escribe(char * szNombre, int iTiempo, int iFrecuenciaMuestreo, int iArmonico);

int main()
{
	char szNombre[50];
	int iTiempo;
	int iFrecuenciaMuestreo;
	int iFrecuencia;

	printf("Nombre del archivo a escribir (*.wav): ");
	scanf("%s", szNombre);
	printf("Duracion del archivo de audio (seg): ");
	scanf("%i", &iTiempo);
	printf("Frecuencia de muestreo: ");
	scanf("%i", &iFrecuenciaMuestreo);
	printf("Frecuencia de sonido: ");
	scanf("%i", &iFrecuencia);

	char * szExtension = strchr(szNombre, (int) '.');

	if (strcmp(szExtension, ".wav") != 0)
	{
		printf("Extension de archivo no valida.\n");
		return -1;
	}
	if (iTiempo < 1)
	{
		printf("Argumento de tiempo no valido.\n");
		return -1;
	}
	if (iFrecuencia < 20 || iFrecuencia > 20000)
	{
		printf("Argumento de frecuencia no valido.\n");
		return -1;
	}
	if (iFrecuenciaMuestreo != 44100 && iFrecuenciaMuestreo != 22050 && iFrecuenciaMuestreo != 11025)
	{
		printf("Frecuencia de muestreo no valida.\n");
		return -1;
	}
	escribe(szNombre, iTiempo, iFrecuenciaMuestreo, iFrecuencia);

    return 0;
}

void escribe(char * szNombre, int iTiempo, int iFrecuenciaMuestreo, int iArmonico)
{
	FILE * fp;
	fp = fopen(szNombre, "wb");
	if (fp)
	{
		int iTamano = (iFrecuenciaMuestreo * iTiempo * 2) + 36;
		int iFormato = 16;
		short sPCM = 1;
		short sCanal = 1;
		int iFrecuencia = iFrecuenciaMuestreo * 2;
		char szRIFF[] = "RIFF";
		char szWave[] = "WAVEfmt ";
		short sBytes = sizeof(short);
		short sBits = sizeof(short) * 8;
		char szData[] = "data";
		fwrite(szRIFF, 4, 1, fp);
		fwrite(&iTamano, sizeof(int), 1, fp);
		fwrite(szWave, 8, 1, fp);
		fwrite(&iFormato, sizeof(int), 1, fp);
		fwrite(&sPCM, sizeof(short), 1, fp);
		fwrite(&sCanal, sizeof(short), 1, fp);
		fwrite(&iFrecuenciaMuestreo, sizeof(int), 1, fp);
		fwrite(&iFrecuencia, sizeof(int), 1, fp);
		fwrite(&sBytes, sizeof(short), 1, fp);
		fwrite(&sBits, sizeof(short), 1, fp);
		fwrite(szData, 4, 1, fp);
		fwrite(&iFrecuencia, sizeof(int), 1, fp);
		register int i = 0;
		register double dData = 0;
		short sData = 0;
		register double x = (double)iArmonico / iFrecuenciaMuestreo;
		for (i = 0; i < iTiempo * iFrecuenciaMuestreo; i++) {
			dData = 32000 * sin(2 * PI * i * x);
			sData = (short)dData;
			fwrite(&sData, sizeof(short), 1, fp);
		}
		fclose(fp);
	}
	else
	{
		printf("\nNo se ha podido crear el archivo.\n");
	}
}