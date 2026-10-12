
/* 
NAME:       HARIHARAN R
DATE:       10/07/2026
DESCRIPTION:Developed a highly optimized text-indexing engine in C modeled after modern 
            search engine core architectures. Built a custom structural database using a combination 
            of collision-chained lookup tables and nested sub-linked lists to map individual words across 
            multiple text files. Features automated command-line file validation, structured backup parsing 
            for incremental dynamic state reloads, and character-level case-insensitivity formatting pipelines.

*/

#include "inverted.h"

int main(int argc,char *argv[]){
    mnode *arr[27]={NULL};
    flist *fhead=NULL;
    char update_file[30];
    int f_count=0,update_file_count=0;
    if(file_validation(argc,argv,&fhead,&f_count)==FAILURE){
        return 0;
    }
    int opt,create_exe=0,update_exe=0;
    
    while(1){
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("Enter the option: ");
        if(scanf("%d",&opt) != 1) {
            while(getchar() != '\n'); // Clear buffer
            printf("ERROR: Invalid option!\n");
            printf("ERROR: Enter option 1 to 6\n");
            continue;
        }

        switch(opt)
        {
            case 1:
                if((create_exe==0) && create_db(arr,fhead,&create_exe)==SUCCESS){
                    printf("INFO: Successfully Created!\n");
                }
                else if(create_exe!=0){
                    printf("INFO: Database already created Successfully!\n");
                }
                break;
            case 2:
                display(arr);
                break;
            case 3:
                if(create_exe || update_exe){
                    char word[30];
                    printf("Enter the word: ");
                    scanf("%s",word);
                    search(word,arr);
                }
                else{
                    printf("Table is Empty!\n");
                }
                break;
            case 4:
                {
                char file[30];
                printf("Enter the file name to save the data: ");
                scanf("%s",file);
                save(arr,file,fhead,f_count+update_file_count,update_exe,update_file);
                break;
                }
            case 5:
                if(create_exe==0){
                    if(update_exe==0){
                        printf("Enter Database File_Name: ");
                        scanf("%s",update_file);
                        if(update_db(arr,update_file,&fhead,&f_count,&update_file_count)==SUCCESS){
                             printf("INFO: Updated Successfully!\n");
                            update_exe=1;
                        }
                        else{
                            printf("ERROR: Database update failed!\n");
                        }  
                    }
                    else{
                        printf("INFO: Database already updated!\n");
                    }
                }
                else{
                    printf("ERROR: Table is not empty!\n");
                }
                break;
            case 6:
                printf("Program Exit!\n");
                return 0;
            default:
                printf("ERROR: Invalid option!\n");
        }
    }
}