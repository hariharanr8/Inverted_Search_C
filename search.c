#include "inverted.h"

void search(char word[],mnode **arr){
    int i=0;
    mnode *temp;
    //check array is NULL or not
    while(i<SIZE){
        if(arr[i]!=NULL){
            temp=arr[i];
            //check word is present or not
            while(temp!=NULL){
                if(strcmp(temp->word,word)==0){
                    printf("Word \"%s\" is present in %d files\n",word,temp->file_count);
                    snode *stemp=temp->s_link;
                    //print all subnode content(filename,wordcount)
                    while(stemp!=NULL){
                        printf("%s --> %d\n",stemp->file_name,stemp->word_count);
                        stemp = stemp->sub_link;
                    }
                    return;
                }
                temp=temp->m_link;
            }
        }
        i++;
    }
    printf("Word not found!\n");
    return;
}