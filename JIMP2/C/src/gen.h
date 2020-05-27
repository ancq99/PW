
#ifndef _GEN_H_
#define _GEN_H_

char **gen_tab( FILE *in, int liczba_k, int liczba_w); //zwrace tablice na postawie pliku z kształtem trawnika
char **gen_trawnik(char **tab, int liczba_k, int liczba_w);//zwraca tablice "trawnik"
void gen_bmp_txt(char **trawnik, FILE *out, int liczba_k, int liczba_w);
void pod_out(FILE *out, int x, int y, char *typ, char *dir);

#endif
