#include <stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

void tokenise(char* inputstring, char* outputlist[] );
int countwords(char* t);

void main(int argc, char* argv[]) 
{
    while (1) 
    {
        char* command  = malloc(50 * sizeof(char));
        
        int proc;

        char* path = malloc(100 * sizeof(char));
        getcwd(path, 100);
 
        printf("%s >>> ",path);
        fgets(command, 50 * sizeof(char), stdin);
        command[strcspn(command, "\n")] = 0;  


        if( strcmp(command, "exit") == 0)
        {
            break;
        }
        else if( strlen(command)==0)
        {
            continue;
        }
       

        char* splitted[5];
        tokenise(command, splitted);



        if (strcmp(splitted[0], "cd") == 0)
        {
            if(chdir(splitted[1])!=0)
            {
                printf("cd failed\n");
            }
            continue;
        }
        if(strcmp(splitted[0], "countwords")==0)
        {
            printf("%i\n",countwords(splitted[1]));
            continue;
        }
        pid_t pid = fork();
        if (pid == 0) {
            execvp(splitted[0], splitted);
        } else {
            wait(NULL);
        }
        free(command);

}
}

void tokenise(char* inputstring, char* outputlist[] ){
    int k = 0 ;
    for(int i = 0; inputstring[i]!='\0'; i++)
        {
            
            char* temp = malloc(16 * sizeof(char));
            int j = 0;
            while(inputstring[i] != ' ' )
            {
                if("%i",inputstring[i]=='\0')
                {
                    break;
                }
                temp[j] = inputstring[i];
                j++;
                i++;
            }
            
            temp[j]='\0';
            outputlist[k] = temp;
            k++;
        }
        outputlist[k]=NULL;


}

int countwords(char* t){
    FILE* fileptr = fopen(t, "r");
    int count = 0;
    char c;
    while((c = fgetc(fileptr)) != EOF)
    {

        char c1 = fgetc(fileptr);  
        char c2 = fgetc(fileptr);

        if ((c1!='/n' && c1!=' ' && c1!= EOF ) && (c2==' ' || c2=='\n' || c2==EOF))
        {
            count++;
        }
    
        ungetc(c2, fileptr); 

    }
    fclose(fileptr);
    return count;
}


