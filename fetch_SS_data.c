/*
    Run these commands:
    gcc fetch_SS_data.c -o spice.c -I/home/louis/Documents/IRF/cspice/include /home/louis/Documents/IRF/cspice/lib/cspice.a -L/home/louis/Documents/IRF/cspice/lib -lm
    gcc -I/home/louis/Documents/IRF/cspice/include fetch_SS_data.c -L/home/louis/Documents/IRF/cspice/lib -l:cspice.a -lm
*/

#include "SpiceUsr.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    #define ABCORR "NONE" // aberration correction
    #define FRAME "ECLIPJ2000" 
	// 2460400.5
    SpiceDouble et; // elapsed time
    SpiceDouble state[6]; // positions and velocities: [x, y, z, vx, vy, vz]
    SpiceDouble lt; // light time between object and observer

    FILE *f = fopen("BarycenterStates.txt", "w");

    if (f == NULL){
        printf("Error opening output file");
        return EXIT_FAILURE;
    }

    // Body Barycenter IDs
    // Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto
    #define N_TARGETS  10
    char observer[] = {"10"};
    char *targets[N_TARGETS] = {"10", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    // load the kernel defined separately
    furnsh_c("kernels.tm");

    for (int i=0; i<N_TARGETS; i++){
        // get data from spk file for each target body
        spkezr_c(targets[i], et, FRAME, ABCORR, observer, state, &lt);
        for (int j=0; j<6; j++){
            // print out data 
            fprintf(f, "%f ", state[j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);

    return EXIT_SUCCESS;
}
