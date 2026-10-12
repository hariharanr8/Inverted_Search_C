#include "inverted.h"

snode *create_snode(char *fname){
    snode *new_sub=malloc(sizeof(snode));
    if (new_sub == NULL)
        return NULL;
    new_sub->word_count=1;
    new_sub->file_name=fname;
    new_sub->sub_link=NULL;
    return new_sub;
}

mnode *create_mnode(char word[],char *fname){
    mnode *new_main=malloc(sizeof(mnode));
    if (new_main == NULL)
        return NULL;
    new_main->file_count=1;
    strcpy(new_main->word,word);
    new_main->m_link=NULL;
    new_main->s_link=create_snode(fname);
    if (new_main->s_link == NULL) {
        free(new_main);
        return NULL;
    }
    return new_main;
}

int create_db(mnode **arr,flist *fhead,int *create_exe){
    char word[30];
    int index;
    while(fhead!=NULL){
        FILE *fp=fopen(fhead->fname,"r");
        if (fp == NULL) {
            printf("ERROR: Could not open file %s\n", fhead->fname);
            fhead = fhead->link;
            continue;
        }
        //read word
        while(fscanf(fp, "%29s", word) != EOF){
            //find index
            char first_char = tolower(word[0]);
            if(first_char >= 'a' && first_char <= 'z'){
                index = first_char - 'a';
            }
            else{
                index=26;
            }
            if(arr[index]==NULL){
                arr[index]=create_mnode(word,fhead->fname);
            }
            else{
                //check word present or not
                mnode *prev=NULL;
                int present=0;
                mnode *temp=arr[index];
                while(temp!=NULL){
                    if(strcmp(temp->word,word)!=0){
                        prev=temp;
                        temp=temp->m_link;
                    }
                    else{
                        present=1;
                        break;
                    }
                }
                //word not present
                if(present==0){
                    prev->m_link=create_mnode(word,fhead->fname);
                }
                //word present
                else{
                    snode *stemp=temp->s_link;
                    snode *s_prev=NULL;
                    int file_found=0;
                    //check file found or not
                    while(stemp!=NULL){
                        if(strcmp(stemp->file_name,fhead->fname)==0){
                            file_found=1;
                            break;
                        }
                        s_prev = stemp;
                        stemp=stemp->sub_link;
                    }
                    //file is not found
                    if(file_found==0){
                        (temp->file_count)++;
                        s_prev->sub_link=create_snode(fhead->fname);
                    }
                    //file is found
                    else{
                        (stemp->word_count)++;
                    }
                }
            }
        }
        fclose(fp);
        fhead=fhead->link;
    }
    *create_exe=1;
    return SUCCESS;
}