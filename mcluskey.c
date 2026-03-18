#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    int arithmos;
    char *duadiko;
    int arithmos_aswn;
    int diathesimo;
}orosT;

orosT create_term(int timh, int metavlites){
      orosT ypologismos;
      ypologismos.duadiko = (char* )malloc((metavlites + 1) * sizeof(char));
      ypologismos.arithmos = timh;
      ypologismos.arithmos_aswn = 0;
      ypologismos.diathesimo = 0;
      int diairesh = timh;
      for (int i = metavlites - 1; i >= 0; i--){
          ypologismos.duadiko[i] = (diairesh % 2) + '0';
         diairesh = diairesh / 2;
         if (ypologismos.duadiko[i] == 1 + '0'){
            ypologismos.arithmos_aswn++;
         }
      }
      ypologismos.duadiko[metavlites] = '\0';
      return (ypologismos);
}

void tajinomhsh(orosT *sunarthsh, int elaxistoroi){
    orosT temp;
    for (int i = 0; i < elaxistoroi - 1; i++){
        for (int j = 0;  j < elaxistoroi - 1; j++){
            if (sunarthsh[j].arithmos_aswn > sunarthsh[j + 1].arithmos_aswn){
               temp = sunarthsh[j];
               sunarthsh[j] = sunarthsh[j + 1];
               sunarthsh[j + 1] = temp;
            }
       }
    }
}

int voithitiki(char s1[], char s2[], int len){
    int diafores = 0;
    int thesi = -1;
    for (int i = 0; i < len; i++){
        if (s1[i] != s2[i]){
            diafores++;
            thesi = i;
        }
    }   
    if (diafores == 1) return (thesi);
    return -1;
}

int exists(orosT *neos_pinakas, int k, char neo_string[]){
    for (int i = 0; i < k; i++){
            if (strcmp(neos_pinakas[i].duadiko, neo_string) == 0) return 1;
    }
    return 0;
}

orosT* sygkrish(orosT *palios_pinakas, int palio_plithos, int *neo_plithos, int metavlites){
       orosT *neos_pinakas = (orosT * )malloc(palio_plithos * palio_plithos * sizeof(orosT));
       int k = 0;
       char temp[metavlites + 1];
       for (int i = 0; i < palio_plithos; i++){
            for (int j = i + 1; j < palio_plithos; j++){
                 if (palios_pinakas[j].arithmos_aswn == palios_pinakas[i].arithmos_aswn + 1){
                    int thesi = voithitiki(palios_pinakas[i].duadiko, palios_pinakas[j].duadiko, metavlites);
                    if (thesi != -1){
                        palios_pinakas[i].diathesimo = 1;
                        palios_pinakas[j].diathesimo = 1;
                        strcpy(temp, palios_pinakas[i].duadiko);
                        temp[thesi] = '-';
                        temp[metavlites] = '\0';
                        if (exists(neos_pinakas, k, temp) == 0){
                            neos_pinakas[k].duadiko = (char* )malloc((metavlites + 1) * sizeof(char));
                            strcpy(neos_pinakas[k].duadiko, temp);
                            neos_pinakas[k].arithmos_aswn = palios_pinakas[i].arithmos_aswn;
                            neos_pinakas[k].diathesimo = 0;
                            k++;
                        }
                    }
                 }
            }
       } 
       if (k == 0){
        free(neos_pinakas);
        return (NULL);
       }
       *neo_plithos = k;
       return (neos_pinakas);
}

void collect_prime_implicants(orosT *pinakas, int plithos, orosT *final_primes, int *prime_count, int metavlites) {
    for (int i = 0; i < plithos; i++) {
        if (pinakas[i].diathesimo == 0) {
            if (exists(final_primes, *prime_count, pinakas[i].duadiko) == 0) {
                final_primes[*prime_count].duadiko = (char *)malloc((metavlites + 1) * sizeof(char));
                strcpy(final_primes[*prime_count].duadiko, pinakas[i].duadiko);
                final_primes[*prime_count].diathesimo = 0;
                (*prime_count)++;
            }
        }
    }
}

int is_covered(char *s, char *minterm_bin, int metavlites){
    for (int i = 0; i < metavlites; i++){
        if (s[i] != '-' && s[i] != minterm_bin[i]) return 0; 
    }
    return 1; 
}

void print_boolean_expr(char *duadiko, int metavlites) {
    int tipota = 1; 
    for (int i = 0; i < metavlites; i++) {
        if (duadiko[i] != '-') {
            tipota = 0;
            printf("%c", 'A' + i);
            if (duadiko[i] == '0') printf("'");
        }
    }
    if (tipota) printf("1"); 
}


void print_final_boolean(orosT *final_primes, int *selected, int sel_count, int metavlites) {
    printf("\n=== TELIKH BOOLEAN EKFRASH ===\n");
    printf("F = ");
    for (int i = 0; i < sel_count; i++) {
        if (i > 0) printf(" + ");
        print_boolean_expr(final_primes[selected[i]].duadiko, metavlites);
    }
    printf("\n");
}


void petricks_method(
    int matrix[100][100],
    int *essential_flags,
    int total_primes,
    int arithmos_minterms,
    orosT *sunarthsh,
    orosT *final_primes,
    int metavlites)
{

    int uncovered[100], unc_count = 0;
    for (int j = 0; j < arithmos_minterms; j++) {
        int covered = 0;
        for (int i = 0; i < total_primes; i++) {
            if (essential_flags[i] && matrix[i][j]) { covered = 1; break; }
        }
        if (!covered) uncovered[unc_count++] = j;
    }

    if (unc_count == 0) return; 

    int sop[1024];
    int sop_size = 0;

  
    for (int i = 0; i < total_primes; i++) {
        if (matrix[i][uncovered[0]]) {
            sop[sop_size++] = (1u << i);
        }
    }

  
    for (int u = 1; u < unc_count; u++) {
        int j = uncovered[u];

 
        unsigned int new_sum[64];
        int new_sum_size = 0;
        for (int i = 0; i < total_primes; i++) {
            if (matrix[i][j]) new_sum[new_sum_size++] = (1u << i);
        }


        unsigned int new_sop[1024];
        int new_sop_size = 0;
        for (int a = 0; a < sop_size && new_sop_size < 1024; a++) {
            for (int b = 0; b < new_sum_size && new_sop_size < 1024; b++) {
                unsigned int combined = sop[a] | new_sum[b];
              
                int dominated = 0;
                for (int c = 0; c < new_sop_size; c++) {
                    if ((new_sop[c] & combined) == new_sop[c]) {
                        dominated = 1; break;
                    }
                    if ((new_sop[c] & combined) == combined) {

                        new_sop[c] = combined;
                        dominated = 1; break;
                    }
                }
                if (!dominated) new_sop[new_sop_size++] = combined;
            }
        }
        sop_size = new_sop_size;
        memcpy(sop, new_sop, sop_size * sizeof(unsigned int));
    }


    int best = 0, best_bits = 33;
    for (int k = 0; k < sop_size; k++) {
        int bits = __builtin_popcount(sop[k]);
        if (bits < best_bits) { best_bits = bits; best = k; }
    }


    printf("\n=== PETRICK'S METHOD ===\n");
    printf("Epipleon PI gia kalypsη twn ypolipwn minterms:\n");
    for (int i = 0; i < total_primes; i++) {
        if (sop[best] & (1u << i)) {
            printf("  PI: %s = ", final_primes[i].duadiko);
            print_boolean_expr(final_primes[i].duadiko, metavlites);
            printf("\n");
        }
    }


    int selected[100];
    int sel_count = 0;

    for (int i = 0; i < total_primes; i++) {
        if (essential_flags[i]) selected[sel_count++] = i;
    }

    for (int i = 0; i < total_primes; i++) {
        if (!essential_flags[i] && (sop[best] & (1u << i))) {
            selected[sel_count++] = i;
        }
    }
    print_final_boolean(final_primes, selected, sel_count, metavlites);
}

/* ============================================================ */

int main(int argc, char* argv[]){
    int arithmos_metavlitwn, arithmos_minterms, timh;
    orosT *sunarthsh;

    printf("Arithmos Metavlitwn: ");
    scanf("%d", &arithmos_metavlitwn);
    printf("Arithmos Elaxistorwn: ");
    scanf("%d", &arithmos_minterms);
    
    sunarthsh = (orosT * )malloc(arithmos_minterms * sizeof(orosT));
    for (int i = 0; i < arithmos_minterms; i++){
        scanf("%d", &timh);
        sunarthsh[i] = create_term(timh, arithmos_metavlitwn);
    }

    tajinomhsh(sunarthsh, arithmos_minterms);

    orosT final_primes[100];
    int total_primes = 0;  
    orosT *trexwn_pinakas = sunarthsh;
    int trexon_plithos = arithmos_minterms;

    while (1) {
        int neo_plithos = 0;
        orosT *neos = sygkrish(trexwn_pinakas, trexon_plithos, &neo_plithos, arithmos_metavlitwn);
        collect_prime_implicants(trexwn_pinakas, trexon_plithos, final_primes, &total_primes, arithmos_metavlitwn);
        if (neos == NULL) break;
        trexwn_pinakas = neos;
        trexon_plithos = neo_plithos;
        tajinomhsh(trexwn_pinakas, trexon_plithos);
    }

    int matrix[100][100] = {0}; 
    for (int i = 0; i < total_primes; i++) {
        for (int j = 0; j < arithmos_minterms; j++) {
            if (is_covered(final_primes[i].duadiko, sunarthsh[j].duadiko, arithmos_metavlitwn)) {
                matrix[i][j] = 1; 
            }
        }
    }

    int essential_flags[100] = {0}; 
    for (int j = 0; j < arithmos_minterms; j++) {
        int count = 0, last_pos = -1;
        for (int i = 0; i < total_primes; i++) {
            if (matrix[i][j] == 1) {
                count++;
                last_pos = i; 
            }
        }
        if (count == 1) essential_flags[last_pos] = 1; 
    }

    printf("\n--- ESSENTIAL PRIME IMPLICANTS ---\n");
    for (int i = 0; i < total_primes; i++) {
        if (essential_flags[i] == 1) {
            printf("%s = ", final_primes[i].duadiko);
            print_boolean_expr(final_primes[i].duadiko, arithmos_metavlitwn);
            printf("\n");
        }
    }

    printf("\n=== ELENXOS KALYPSHS (Coverage Check) ===\n");
    int uncovered_count = 0;
    for (int j = 0; j < arithmos_minterms; j++) {
        int covered_by_epi = 0;
        for (int i = 0; i < total_primes; i++) {
            if (essential_flags[i] == 1 && matrix[i][j] == 1) {
                covered_by_epi = 1;
                break;
            }
        }
        if (!covered_by_epi) {
            uncovered_count++;
            printf("Minterm %d DEN kaluptetai apo tous Essential.\n", sunarthsh[j].arithmos);
            printf("   Ypopshfioi PI: ");
            for (int i = 0; i < total_primes; i++) {
                if (matrix[i][j] == 1) printf("[%s] ", final_primes[i].duadiko);
            }
            printf("\n");
        }
    }

    if (uncovered_count == 0) {

        int selected[100], sel_count = 0;
        for (int i = 0; i < total_primes; i++)
            if (essential_flags[i]) selected[sel_count++] = i;
        print_final_boolean(final_primes, selected, sel_count, arithmos_metavlitwn);
    } else {
 
        petricks_method(matrix, essential_flags, total_primes,
                        arithmos_minterms, sunarthsh, final_primes, arithmos_metavlitwn);
    }

    printf("\n=== OLOI OI PRIME IMPLICANTS ===\n");
    for (int i = 0; i < total_primes; i++) {
        printf("%s = ", final_primes[i].duadiko);
        print_boolean_expr(final_primes[i].duadiko, arithmos_metavlitwn);
        printf("\n");
    }

 
    for (int i = 0; i < total_primes; i++) free(final_primes[i].duadiko);
    for (int i = 0; i < arithmos_minterms; i++) free(sunarthsh[i].duadiko);
    free(sunarthsh);

    return 0;
}