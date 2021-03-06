#include <stdio.h>
#include <stdlib.h>

int allframes; //Number of frames to process
int freq; //Frequency of change determine how many frames should be modified after each other
int change; //If '0' first frame will be modified. If '1' first modified frame will occur after number of frame specified in 'freq' variable
int x,y; //Width and height of each frame in sequence
char *taby; //Luminance table Y
char *tabu; //Chroma table U
char *tabv; //Chroma table V
FILE *frb, *fwb; //Input and output file

void processFrames(){
    printf("\n");
    //Read and write logic
    for(int frame = 1; frame <= allframes; frame++){
        //Writing data from a file to tables
        fread(taby, (size_t) (x / 2), (size_t) (y * 2), frb);
        fread(tabu, (size_t) (x / 4), (size_t) y, frb);
        fread(tabv, (size_t) (x / 4), (size_t) y, frb);

        //Loading from tables into a file
        if(change%2==0){//If true frame will be modified
            //Writing luminance Y data to a file
            for(int i=(x*y)/2; i<x*y; i=i+x){
                for(int j=0; j<x/2; j++) {
                    fputc(taby[i+x/2+j], fwb);
                }
                for(int j=0; j<x/2; j++) {
                    fputc(taby[i + j], fwb);
                }
            }
            for(int i=0; i<(x*y)/2; i=i+x){
                for(int j=0; j<x/2; j++) {
                    fputc(taby[i+x/2+j], fwb);
                }
                for(int j=0; j<x/2; j++) {
                    fputc(taby[i+j], fwb);
                }
            }
            //Writing chrominance U data to a file
            for(int i=(x*y)/8; i<(x*y)/4; i=i+x/2){
                for(int j=0; j<x/4; j++) {
                    fputc(tabu[i+x/4+j], fwb);
                }
                for(int j=0; j<x/4; j++) {
                    fputc(tabu[i+j], fwb);
                }
            }
            for(int i = 0; i<(x*y)/8; i = i + x/2){
                for(int j=0; j<x/4; j++) {
                    fputc(tabu[i + x/4 + j], fwb);
                }
                for(int j=0; j<x/4; j++) {
                    fputc(tabu[i + j], fwb);
                }
            }
            //Writing chrominance V data to a file
            for(int i = (x*y)/8; i<(x * y) / 4; i = i + x/2){
                for(int j=0; j<x/4; j++) {
                    fputc(tabv[i + x/4 + j], fwb);
                }
                for(int j=0; j<x/4; j++) {
                    fputc(tabv[i+j], fwb);
                }
            }
            for(int i = 0; i<(x*y)/8; i = i + x/2){
                for(int j=0; j<x/4; j++) {
                    fputc(tabv[i+x/4+j], fwb);
                }
                for(int j=0; j<x/4; j++) {
                    fputc(tabv[i+j], fwb);
                }
            }
        }
        else{ //Keep original image in frame
            fwrite(taby, (size_t) (x * y), 1, fwb);
            fwrite(tabu, (size_t) ((x * y) / 4), 1, fwb);
            fwrite(tabv, (size_t) ((x * y) / 4), 1, fwb);
        }
        if(frame%freq==0) { //image change
            change++;
        }
        printf("\rCompleted processing: %d out of %d frames.", frame, allframes);
    }
    printf("\n");
}

void checkFile(FILE *file, char *name){
    if (file == NULL){ //Checking the file
        printf("\nThe %s file cannot be opened.\n", name);
        exit(1);
    }
}

void initialize(int argc, char **argv){
    printf("\n");
    if(argc == 8){
        printf("Input         : %s\n", argv[1]);
        printf("Output        : %s\n", argv[2]);
        printf("Frames        : %s\n", argv[3]);
        printf("Frequency     : %s\n", argv[4]);
        printf("Resolution X  : %s\n", argv[5]);
        printf("Resolution Y  : %s\n", argv[6]);
        printf("Start position: %s\n", argv[7]);
    }
    else{
        printf("Wrong number of arguments!\n"
               "Please provide exactly 7 arguments in the following order:\n"
               "-Input file patch,\n"
               "-Output file patch,\n"
               "-Number of frames,\n"
               "-Frequency of change,\n"
               "-Width,\n"
               "-Height,\n"
               "-Start of change(0/1).\n");
        exit(0);
    }

    frb = fopen(argv[1], "rb");//Input file
    checkFile(frb, "input");

    fwb = fopen(argv[2], "wb");//Output file
    checkFile(fwb, "output");

    allframes = atoi(argv[3]);//All frames of the file
    freq = atoi(argv[4]);//The frequency of the frame change
    change = atoi(argv[7]);//Change of frames
    x = atoi(argv[5]);//Width
    y = atoi(argv[6]);//Height

    taby = (char*) malloc((size_t) (x * y));
    tabu = (char*) malloc((size_t) ((x / 2) * (y / 2)));
    tabv = (char*) malloc((size_t) ((x / 2) * (y / 2)));
}

int main(int argc, char *argv[]){
    initialize(argc, argv);
    processFrames();
    //Closing the files
    fclose(frb);
    fclose(fwb);
    return 0;
}