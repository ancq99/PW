
#ifndef _PODLEWANIE_H_
#define _PODLEWANIE_H_
int test_360(char **trawnik, int x, int y, int r, int k);
int test(char **trawnik, int y, int x, int r);
void get_k_w(int x, int y);
void poj_360(char **trawnik, int j, int i, int r, int k);
void poj_180(char **trawnik, int j, int i, int r);
void kraw_zew_90(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90);
void kraw_zew_180(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90);
void kraw_wew_270(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90);
void kraw_wew_180(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90);
void kraw_360(char **trawnik, int liczba_k, int liczba_w, int r360, int r270, int r180, int r90);
void odbicia(char **trawnik, int r360, int r270, int r180, int r90);
void odbicie_poziom_g(char **trawnik);
void odbicie_poziom_d(char **trawnik);
void odbicie_pionowe_l(char **trawnik);
void odbicie_pionowe_p(char **trawnik);

#endif
