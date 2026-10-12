#include "inverted.h"

void subnode_display(int index,mnode *main_temp){
    int count=0;
    snode *stemp;
    stemp=(main_temp->s_link);
    while(count<(main_temp->file_count) && stemp!=NULL){
        if(count==0){
            printf("%-6d %-18s %-10d %-20s %-10d\n",index,main_temp->word,
                main_temp->file_count,stemp->file_name,stemp->word_count);
        }
        else{
            printf("%-6s %-18s %-10s %-20s %-10d\n","","","",stemp->file_name,stemp->word_count);
        }
        count++;
        stemp=(stemp->sub_link);
    }
}

void display(mnode **arr){
    int i=0;
    mnode *mtemp;
    printf("\n=========================================================================\n");
    // Aligned Header
    printf("%-6s %-18s %-10s %-20s %-10s\n", "Index", "Word", "Filecount", "Filename", "Wordcount");
    printf("=========================================================================\n");
    while(i<SIZE){
        if(arr[i]!=NULL){
            mtemp=arr[i];
            while(mtemp!=NULL){
                subnode_display(i,mtemp);
                mtemp=mtemp->m_link;
            }
            printf("-------------------------------------------------------------------------\n");
        }
        i++;
    }
}