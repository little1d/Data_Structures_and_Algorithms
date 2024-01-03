/*
 This c sources file generate user data and store it in the specified file
 The final result is output to the text file `user_table.txt`
 Author: Harrison
 Date: January 2, 2024
*/

// user_generation.c

#include "user_table_generate.h"

void generateUsers(const char *filename){
    FILE *file = fopen(filename,"w");
    if(file == NULL){
        printf("Unable to open the file");
        return ;
    }

    srand((unsigned int)time(NULL)); // Seed for random number generation

    for(int i = 0;i<10;++i){
        User user;
        user.userId = i + 1;
        int numBusiness = rand() % 2 + 1; // 1 or 2 businesses
        for(int j = 0;j < numBusiness; ++j){
            user.businessTypes[j] = rand() % 5; // Random business type
        }

        user.arrivalTime = rand() % 480; // Random time within 8 hours

        fprintf(file,"User %d, Business type:",user.userId);
        for (int j = 0; j < numBusiness; ++j) {
            fprintf(file,"%d ",user.businessTypes[j]);
        }
        fprintf(file,", Arrival Time: %d\n",user.arrivalTime);
    }

    fclose(file);
}