#include "base64Table.h"
int find_index(char a){
    int i;
    for(i=0;i<strlen(base64_table);++i){
        if(a == base64_table[i])
            return i;
    }
    return -1;
}
char* encode(char* input){
    long size_of_input = strlen(input);
    char* temp = malloc(sizeof(char)*(size_of_input+1));
    if(temp == 0)
        fprintf(stderr,"memory allocation failed, check the input string");
    strcpy(temp,input);

    long output_len;
    if(size_of_input%3 == 0){
        output_len = size_of_input/3*4;
    }else{
        output_len = (size_of_input/3 + 1)*4;
    }

    char* output = malloc(sizeof(char)*output_len + 1);
    int i = 0;
    int j = 0;

    uint32_t last6 = 0x3F; //00111111
    uint32_t last2 = 0x03; //00000011
    uint32_t last4 = 0x0f; //00001111
    char group3[3];
    while(i<size_of_input){
        group3[0] = (i < size_of_input) ? temp[i++] : 0;
        group3[1] = (i < size_of_input) ? temp[i++] : 0;
        group3[2] = (i < size_of_input) ? temp[i++] : 0;

        output[j++] = base64_table[(group3[0]>>2)&last6];//first-first6
        output[j++] = base64_table[(group3[0]&last2)<<4|(group3[1]>>4)];//first-last2+second-first4
        output[j++] = base64_table[(group3[1]&last4)<<2 | group3[2]>>6];//second-last4+third-first2
        output[j++] = base64_table[group3[2] & last6];//third-last6

    }

    switch(size_of_input%3){
        case 1:
            output[j-2] = '=';
            output[j-1] = '=';
            break;
        case 2:
            output[j-1] = '=';
            break;
    }
    output[j] = '\0';
    return output;
}


char* decode(char* input){
    long size_of_input = strlen(input);
    char* temp = malloc(sizeof(char)*(size_of_input+1));
    if(temp == 0)
        fprintf(stderr,"memory allocation failed, check the input string");
    strcpy(temp,input);
    long output_len;
    if(strstr(temp,"=="))
        output_len = size_of_input/4*3 - 2;
    else if(strstr(temp,"="))
        output_len = size_of_input/4*3 - 1;
    else
        output_len = size_of_input/4*3;
    char* original = malloc(sizeof(char)*output_len + 1);
    int i;
    int j = 0;
    for(i = 0; i< size_of_input;i+=4){
        uint32_t char0 = find_index(temp[i]);
        uint32_t char1 = find_index(temp[i+1]);
        uint32_t char2 = find_index(temp[i+2]);
        uint32_t char3 = find_index(temp[i+3]);

        original[j++]= (char)(char0<<2 | char1>>4);
        original[j++]= (char)(char1<<4 | char2>>2);
        original[j++]= (char)(char2<<6 | char3);
    }
    for(i=0;i<output_len;++i){
        if(original[i] < 1 || original[i]>127){
            memmove(&original[i], &original[i + 1], output_len - i);//decode string contains terminator '\0' and remove it
            output_len -= 1;
        }
    }
    temp = (char* )realloc(original,(output_len+1)*sizeof(char));
    printf("temp:%d",strlen(temp));
    if(temp == 0){
        fprintf(stderr, "realloc failed");
        return 0;
    }
    temp[output_len+1] = '\0';
    original = temp;
    return original;
}
