#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/*MUhammad Ramish Saeed
 *21503436
 *Project 1-phistogram
 */

int main(int argc, int** argv){
	
	clock_t start_time = clock();

	int minvalue = atoi(argv[1]);
	int maxvalue = atoi(argv[2]); 
	int bincount = atoi(argv[3]);

	const int numberOfInputs = atoi(argv[4]);  
	double w = (maxvalue - minvalue) / (double)bincount;

	// getting N input files
	for (int i = 0; i < numberOfInputs; i++){
		char childFile[50];
		sprintf(childFile, "intermediate%d", i);
        pid_t childProcess = fork(); 

        if (childProcess < 0) {
            printf("\nChild process not created. Exiting...");
            exit(1);
        } 
        else if (childProcess == 0){      
			FILE *fp;
		    char *line = NULL;
		    size_t len = 0;
		    ssize_t read;

		    fp = fopen(argv[5 + i], "r");
		    if (fp == NULL)
		        exit(EXIT_FAILURE);

		    // single file histogram
		    int* histogram = (int*) malloc(bincount * sizeof(int));
		    while ((read = getline(&line, &len, fp)) != -1){
		    	double num = atof(line);
		    	if(num < minvalue || num > maxvalue)
		    		continue;

		    	int place = (int)((num - minvalue) / w); //binnumber
		    	if(place >= bincount)
		    		place = bincount - 1;
		    	histogram[place]++;
		    }

		    fclose(fp);

		    fp = fopen(childFile, "w");
		    if (fp == NULL)
		        exit(EXIT_FAILURE);

		    for(int j = 0; j < bincount; j++)
		    	fprintf(fp, "%d\n", histogram[j]);

		    fclose(fp);


		    if (line)
		        free(line);
		    free(histogram);

		    exit(EXIT_SUCCESS);
        } 
        else
            wait(0); //wait for all children process to exit
    }

    //merging the intermediary files
	int* binsArray = (int*) malloc(bincount * sizeof(int));
	for(int i = 0; i < bincount; i++){
		binsArray[i] = 0;
	}

    for (int i = 0; i < numberOfInputs; i++){
		FILE *fp;
	    char *line = NULL;
	    size_t len = 0;
	    size_t read = 0;

		char childFile[50];
		sprintf(childFile, "intermediate%d", i);
	    fp = fopen(childFile, "r");
	    if (fp == NULL)
	        exit(EXIT_FAILURE);

	    int j = 0;
	    while ((read = getline(&line, &len, fp)) != -1){
	    	binsArray[j++] += atoi(line);
	        //printf("%s", line);
	    }
	    fclose(fp);
	    if (line)
	        free(line);
    }


    // outputting the output file
    FILE *fw;
    char *line = NULL;
    size_t len = 0;
    fw = fopen(argv[numberOfInputs + 5], "w");

	for(int i = 0; i < bincount; i++) {
		fprintf(fw, "%d: %d\n", (i + 1), binsArray[i]);
	}

    fclose(fw);

	free(binsArray);

	clock_t end_time = clock();

    printf("The program took: %zd milliseconds.", end_time - start_time);

	return 0;
}