typedef enum { false, true } bool;

extern char * bytes_to_hex(unsigned char bytes[], int size);
extern void error(int code, char message[], char arg[]);
extern FILE * create_file(char filename[]);
extern bool file_exists(char arg[]);
extern void read_key(char filename[], unsigned char key[], int key_size);

struct content {
    long size;
    unsigned char *bytes;
};

typedef struct content Content;

extern Content read_file(char filename[]);
