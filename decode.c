#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int decode(const char * file) 
{
    int ret = 0;
    if (file == NULL) {
        ret = -2;
        goto exit;
    }

    FILE *fp = NULL;
    if ((fp = fopen(file, "rd")) == NULL) {
        fprintf(stderr, "open file %s error\n", file);
        ret = -1;
        goto exit ;
    }
    unsigned int c;
    unsigned long int cnt = 0, cnti = 0;
    long int start = ftell(fp);
    long int end = 0;
    while ((c = fgetc(fp)) != EOF) {
        char str[512];
        unsigned int nc;
        if (c == 0x03 && 
            ((nc =fgetc(fp)) == 0xff || nc == 0xfe)) {
            cnti++;
            long int pos  = ftell(fp);
            long int sz = pos - start - 1;
            fseek(fp, start, SEEK_SET);
            fgets(str, sz, fp);
            str[sz] = '\0';
            //fprintf(stdout, "%d %d: %s\n", start, pos, str);                     
            if (nc == 0xfe) {
                pos += 2;
                cnt++;
                fprintf(stdout, "lines: %d\nitems: %d\n", cnt, cnti);
                cnti = 0;
            }
            fseek(fp, pos, SEEK_SET);
            start = pos;
        } 
    }

    if (fp != NULL)
        fclose(fp);
exit:
    return ret;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage:  %s filepath\n", argv[0]);
        return -1;
    }
    for (int i =1; i < argc; i ++) {
        fprintf(stdout, "processing file %d\n", i);
        decode(argv[i]);
    }
}

