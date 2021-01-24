#include <iostream>
#include <cstdlib>

typedef struct WavData{
	int rate;
    short channels;
    short bits;
    int datasize;
} wd_t;

wd_t* wavReader(char* filename) {
    std::cout << "File input: " << filename << std::endl;
    FILE* fp = fopen(filename, "rb");
    wd_t wav;
    wd_t* ret=&wav;
    char id[5];
    char nimp[40];
    short channels, bits;
    int rate, datasize;
    if(fp) {
        fread(&id, sizeof(char), 4, fp);
        id[4] = '\0';
        if(!strcmp(id,"RIFF")) {
            fread(&nimp, sizeof(char), 18, fp); 
            fread(&channels, sizeof(short), 1, fp);
            fread(&rate, sizeof(int), 1, fp);
            fread(&nimp, sizeof(char), 6, fp);
            fread(&bits, sizeof(short), 1, fp);
            fread(&nimp, sizeof(char), 4, fp);
            fread(&datasize, sizeof(int), 1, fp);
            std::cout << "Sample Rate : " << rate << std::endl;
            std::cout << "Channel Numbers : " << channels << std::endl;
            std::cout << "Sample Bits : " << bits << std::endl;
            std::cout << "WavData Size : " << datasize/1024 << " KB" << std::endl;
        } else {
            std::cout << "Not a valid wav file!" << std::endl;
        }
    }
    fclose(fp);
    return ret;	
}

void usage() {
    std::cout << "wavReader [option] ..." << std::endl;
    std::cout << "    -f|--file        filename of the wavefile to be read" << std::endl;
    std::cout << "    -h|--help        show this list" << std::endl;
}

int main(int argc, char* argv[]) {
    wd_t wavinfo;
    wd_t* res=&wavinfo;
    if(argc == 1)
        usage();
    for(int i=1; i<argc; i++) {
        if(!strcmp(argv[i],"-h")) {
            std::cout << "enter" << std::endl;
            usage();
        } else if(!strcmp(argv[i],"--help")) {
            std::cout << "long enter" << std::endl;
            usage();
        } else if((!strcmp(argv[i],"-f"))||(!strcmp(argv[i],"--file"))) {
            if(i==argc-1) {
                std::cout << "Error Input : Please input your wavfile's name(path)" << std::endl;
                usage();
                return -1;
            }
            res = wavReader(argv[i+1]);
        }
    }
    // usage();
    // wavReader("test.wav", "list.dat");
    return 0;
}