#include "inverted.h"

void validate(flist *fhead,char file[]){
    int len = strlen(file),not_found=1;
    while(len>=0){
        if(file[len]=='.'){
            not_found=0;
            //extn not match
            if(strcmp(&file[len],".txt")){
                printf("ERROR: %s file has invalid extention!\n",file);
                printf("INFO: Extention change default to .txt\n");
                strcpy(&file[len],".txt");
                break;
            }
            else{
                while(fhead != NULL){
                    if(strcmp(fhead->fname,file)==0){
                        printf("ERROR: Entered file name already exist!\n");
                        printf("INFO: default to take save.txt file\n");
                        strcpy(file,"save.txt");
                        break;
                    }
                    fhead=fhead->link;
                }
                break;
            }
        }
        len--;
    }
    if(not_found){
        printf("ERROR: There is no extention!\n");
        printf("INFO: Extention change default to .txt\n");
        strcpy(&file[strlen(file)],".txt");
    }
}

int save(mnode **arr,char *file,flist *fhead,int file_count,int update_exe,char *update_file){
    //validate file name.
    validate(fhead,file);
    //open that file to save all data.
    FILE *fp=fopen(file,"w");
    if (fp == NULL) {
        printf("ERROR: System failed to create Save file: %s\n", file);
        return FAILURE;
    }
    
    char word[300],*tok=NULL;
    if(update_exe && update_file!=NULL){
        //update files list also save in first line
        FILE *up_fp=fopen(update_file,"r");
        if(up_fp==NULL){
            printf("ERROR: Could not open file %s\n", update_file);
            fclose(fp);
            return FAILURE;
        }
        fscanf(up_fp,"%299s",word);
        fclose(up_fp);
        tok=strtok(word,"#;");
        fprintf(fp,"#%d;",file_count);
        tok=strtok(NULL,"#;");
        while(tok!=NULL){
            fprintf(fp,"%s;",tok);
            tok=strtok(NULL,"#;");
        }
    }
    else{
        fprintf(fp,"#%d;",file_count);
    }
    if(fhead!=NULL){
        while(fhead->link!=NULL){
            fprintf(fp,"%s;",fhead->fname);
            fhead=fhead->link;
        }
        fprintf(fp,"%s#\n",fhead->fname);
    }
    
    
    int i=0;
    while(i<SIZE){
        if(arr[i]!=NULL){
            mnode *mtemp=arr[i];
            while(mtemp!=NULL){
                snode *stemp=mtemp->s_link;
                fprintf(fp,"#%d;%s;%d",i,mtemp->word,mtemp->file_count);
                while(stemp!=NULL){
                    fprintf(fp,";%s;%d",stemp->file_name,stemp->word_count);
                    stemp=stemp->sub_link;
                }
                fprintf(fp,"#\n");
                mtemp=mtemp->m_link;
            }
        }
        i++;
    }
    fclose(fp);
    printf("INFO: Data Saved Successfully!\n");
    return SUCCESS;
}