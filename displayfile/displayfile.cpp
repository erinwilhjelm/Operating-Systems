#include "read_file.h"

int main(int argc, char *argv[])
{

    if (argc != 2) {
   
        cout << "No file name entered";
    }
    else {
        char * ptr = read_file(argv[1]);
        if(ptr == nullptr) {
            cout <<"Error: File Note Found ";
        }
        else {
            printf("%s\n", ptr);
            free(ptr);
        }
    }


}
