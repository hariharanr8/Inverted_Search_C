#include "inverted.h"

int valid_file(char update_file[]){
    int len=strlen(update_file)-1,flag=1,word_len=0;
    char word[300];
    while(len>=0){
        if(update_file[len]=='.'){
            if(strcmp(&update_file[len],".txt")){
                flag=0;
            }
            break;
        }
        len--;
    }
    if(flag==0){
        printf("Invalid File Extention!\n");
        return FAILURE;
    }
    FILE *fp=fopen(update_file,"r");
    if(fp==NULL){
        printf("ERROR: Could not open file %s\n", update_file);
        return FAILURE;
    }
    //check file lines start and end with '#'
    while(fscanf(fp, "%299s", word) != EOF){
        word_len=strlen(word)-1;
        if(word[0]!='#' || word[word_len]!='#'){
            printf("ERROR: Invalid file Structure\n");
            printf("ERROR: The update file lines must start and end with '#' and spaces are not allowed.\n");
            fclose(fp);
            return FAILURE;
        }
    }
    fclose(fp);
    return SUCCESS;
}

void file_list_update(flist **fhead,char word[],int *f_count,int *update_file_count){
    flist *temp,*prev;
    char *tok;
    tok=strtok(word,"#;\n");
    *update_file_count=atoi(tok);
    tok=strtok(NULL,"#;\n");
    while(tok!=NULL){
        temp=*fhead,prev=NULL;
        while(temp!=NULL){
            if(strcmp(temp->fname,tok)==0){
                if(prev==NULL){
                    *fhead=temp->link;
                    free(temp);
                }
                else{
                    prev->link=temp->link;
                    free(temp);
                }
                (*f_count)--;
                break;
            }
            else{
                prev=temp;
                temp=temp->link;
            }
        }
        tok=strtok(NULL,"#;\n");
    }
}

int update_db(mnode **arr,char update_file[],flist **fhead,int *file_count,int *update_file_count){
    if(valid_file(update_file)==FAILURE){
        return FAILURE;
    }
    char *tok=NULL,word[300];
    FILE *fp=fopen(update_file,"r");
    if(fp==NULL){
        printf("ERROR: Could not open file %s\n", update_file);
        return FAILURE;
    }
    //first line of update file has file list.
    if(fscanf(fp, "%299s", word) != EOF) {
        file_list_update(fhead,word,file_count,update_file_count);
    }

    //Update file data into the table.
    while(fscanf(fp,"%299s",word)!=EOF){
        tok=strtok(word,"#;");
        //get index
        int index=atoi(tok);

        //create main_node and update
        mnode *new_main=malloc(sizeof(mnode));

        tok=strtok(NULL,"#;");
        strcpy(new_main->word,tok);//word update

        tok=strtok(NULL,"#;");
        new_main->file_count=atoi(tok);//file_count update
        new_main->m_link=NULL;
        new_main->s_link=NULL;
        if(arr[index]!=NULL){
            //point prev mlink to new mlink.
            mnode *temp=arr[index];
            while(temp->m_link!=NULL){
                temp=temp->m_link;
            }
            temp->m_link=new_main;
        }
        else{
            arr[index]=new_main;
        }
        int count=0;
        snode *tail_sub=NULL;
        while(count<new_main->file_count){
            tok=strtok(NULL,"#;");
            snode *new_sub=malloc(sizeof(snode));
            // using strdup to create duplicates memory in heap segment to store file name
            new_sub->file_name=strdup(tok);
            tok=strtok(NULL,"#;");
            new_sub->word_count=atoi(tok);
            new_sub->sub_link=NULL;
            if(count==0){
                new_main->s_link=new_sub;
            }
            else{
                tail_sub->sub_link=new_sub;
            }
            tail_sub=new_sub;
            count++;
        }
    }
    fclose(fp);
    return SUCCESS;
}