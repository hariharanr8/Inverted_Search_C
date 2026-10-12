#include "inverted.h"

//search file is already present or not
int search_file(char *file,flist *fhead){
    while(fhead!=NULL){
        if(strcmp(file,fhead->fname)==0){
            return FAILURE;
        }
        fhead=fhead->link;
    }
    return SUCCESS;
}

int insert_last(flist **head,char *file){
    flist *new=malloc(sizeof(flist));
    if (new == NULL) {
        return FAILURE;
    }
    new->fname=file;
    new->link=NULL;
    if(*head==NULL){
        *head=new;
        return SUCCESS;
    }
    flist *temp=*head;
    while(temp->link!=NULL){
        temp=temp->link;
    }
    temp->link=new;
    return SUCCESS;
}

int file_validation(int argc,char *argv[],flist **fhead,int *f_count){
    if(argc<2){
        printf("ERROR: Minimum one file requried!\n");
        return FAILURE;
    }
    int i=1,j=0,len;
    while(argv[i]!=NULL){
        len = strlen(argv[i])-1;
        while(len>=0){
            if(argv[i][len]=='.'){
                //extn not match
                if(strcmp(&argv[i][len],".txt")){
                    printf("ERROR: %s file has invalid extention!\n",argv[i]);
                    break;
                }
                //extn match
                else{
                    //check file is empty
                    FILE *fp=fopen(argv[i],"r");
                    if (fp == NULL) {
                        printf("ERROR: %s file does not exist or cannot be opened!\n", argv[i]);
                        break;
                    }
                    int ch;
                    if((ch=fgetc(fp))==EOF){
                        printf("ERROR: %s file is Empty!\n",argv[i]);
                        fclose(fp);
                        break;
                    }
                    //file is not empty
                    fclose(fp);
                    //check file is repeated
                    if(search_file(argv[i],*fhead)==FAILURE){
                        printf("ERROR: %s file is already exist!\n",argv[i]);
                        break;
                    }
                    //file is Unique
                    else{
                        //insert to the flist
                        if(insert_last(fhead,argv[i])==SUCCESS){
                            (*f_count)++;
                            printf("INFO: %s file is valid!\n",argv[i]);
                        }
                        else{
                            printf("ERROR: Memory allocation failed!\n");
                        }
                        
                        break;
                    }
                }
            }
            len--;
        }
        if(len==-1){
            printf("ERROR: %s file has no extension!\n", argv[i]);
        }
        i++;
    }
    return SUCCESS;
}