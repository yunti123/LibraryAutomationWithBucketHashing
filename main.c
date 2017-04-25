/* 
 * File:   main.c
 * Author: yunti123
 *
 * Created on April 17, 2017, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 30
#define indexpath "index.txt"
#define bookpath "book.txt"
#define MAXLEN 35


typedef struct book{										// books struct
    int no;
    char author[MAXLEN];
    char name[MAXLEN];
}book;

//prototypes
int hash(int);
void sifirla(char*,char*);
book takeBook();
void insertBook();
void convert(int,char*);
void clear(char* ,char*);
void search();
void list();

//main
int main(int argc, char** argv) {
 
    //menu
    int sec ;
    do{
        printf("\n1)Insert a book\n2)Search a book\n3)List all the bookshelf\n4)Exit\n99)Sifirlama\n");
        scanf("%d",&sec);
        if(sec == 1){
            insertBook();
        }
        else if(sec == 2){
			search();
        }
        else if(sec == 3){
			list();
        }
        else if(sec == 4){
            printf("Exit\n");
        }
        else if(sec == 99){
            sifirla(indexpath,bookpath);
            printf("\nDosyalar sifirdan olusturuldu..\n");
        }
        else
            printf("Error!! Pls try again");
    }while(sec!=4);
    
    system("PAUSE");   
    return (EXIT_SUCCESS);
}


//functions

void sifirla(char* inp,char* bop){
                                                            //for reset index and book file
    FILE* in;                                               //index file
    in = fopen(inp,"w");
    fprintf(in,"Shelf number-B1-B2-B3-B4-B5\n---------------------------\n");
    
    fclose(in);
    FILE* bo;                                               //book file
    bo = fopen(bop,"w");
    fprintf(bo,"Shelf number-Author name-Book name-Author name-Book name-Author name-Book name-Author name-Book name-Author name-Book name\n");
    fclose(bo);
                                                            //insert NULL all files
    in = fopen(inp,"a");
    bo=fopen(bop,"a");
    for(int i=0;i<30;i++){
       fprintf(in,"%d-NULL-NULL-NULL-NULL-NULL\n",(i+1));
       fprintf(bo,"%d-NULL-NULL-NULL-NULL-NULL-NULL-NULL-NULL-NULL-NULL\n",(i+1));
    }
    fclose(in);
    fclose(bo);
}


int hash(int n){
    int location;
    location = n % MOD;
    return location;
}

book takeBook(){
    book b;
    char a[30];
    
    printf("\nInsert book name: ");
    scanf("%s",b.name);
    printf("\nInsert author name: ");
	scanf("%s", b.author);
	printf("\nInsert book no: ");
	do {
		scanf("%d", &b.no);
		if (b.no < 0 || b.no>149) {
			printf("\nbook key must >0 or <149\nPls Insert another book no: ");
		}
	} while (b.no < 0 || b.no>149);
    return b;
}

void insertBook(){
    FILE* inf;                                              //index file
    FILE* infT;                                             //index's temp file
	FILE* bof;												//book file
	FILE* bofT;												//books's temp file
    char* tempIn = "index.tmp";                             //index's temp files's path 
	char* tempBo = "book.tmp";								//book's temp file's path
    
	char line[250];
    char* token[6];											//token for index
	char* tokenB[11];										//token for book
	char* t;												//temp token

    int loc;
	int bucket;
    
    book b = takeBook();
	loc = hash(b.no);                                       //hashing book key


//////////////////////////////////////////////////////////////////|| Index Part ||/////////////////////////////////////////////////////////////////////////////////////
    
	inf = fopen(indexpath,"r");                             //for read the index file
    infT = fopen(tempIn,"w");                               //for write the temp file

    int satir =-1;
    int buc=0;
	int isSet;												//Boolean of set index
	int isSetName;											//Boolena of set book name
	int isSetAut;											//Boolean of set author name

	while (1) {												//start read index file
		fgets(line, sizeof(line), inf);						//read line by line
		
		
		if (satir == loc) {									
			isSet = 0;
			t = strtok(line, "-");							
				
			while (t != NULL) {								//split the line
				token[buc] = t;	
				t = strtok(NULL, "-");

				if (!strcmp(token[buc], "NULL") && !isSet) {
					itoa(b.no, token[buc], 10);
					bucket = buc;
					isSet = 1;
				}
				
				buc++;
			}
			
			char* string = (char*)malloc(sizeof(char));
			strcpy(string, "");
			
			for (int a = 0; a < 11; a++) {					//convert char[] to string
				if (a % 2 == 0) {
					int l;
					l = (a / 2);
					string = strcat(string, token[l]);
				}
				else {
					string = strcat(string, "-");
				}
			}
			fprintf(infT, "%s", string);
		}
		else {
			fprintf(infT, "%s", line);
		}


		
		satir ++;
		
		if (satir > 30)
			break;
	}														//end of write index file  
	
	fclose(inf);
	fclose(infT);
	remove(indexpath);
	rename(tempIn,indexpath);
	
	///////////////////////////////////////////////////////////////|| Book Part ||/////////////////////////////////////////////////////////////////////////////////////

	bof = fopen(bookpath, "r");								//for read the book file
	bofT = fopen(tempBo, "w");								//for write the temp file
	bucket = 1;
	satir = 0;
	buc = 0;

	while (1) {												//start read book file
		fgets(line, sizeof(line), bof);						//read line by line
		
		if (satir == loc) {									
			isSetName = 0;
			isSetAut = 0;

			t = strtok(line, "-");

			while (t != NULL) {								//splite line
				tokenB[buc] = t;
				t = strtok(NULL, "-");
				
				if (buc == ((bucket * 2) - 1) && !isSetAut) {
					tokenB[buc] = b.author;
					isSetAut = 1;
				}
				else if (buc == (bucket * 2) && !isSetName) {
					tokenB[buc] = b.name;
					isSetName = 1;
				}

				buc++;
			}
			char* stringB = (char*)malloc(sizeof(char));
			strcpy(stringB, "");
			
			for (int b = 0; b < 21; b++) {					//convert char[] to string
				if (b % 2 == 0) {
					int le;
					le = (b / 2);
					stringB = strcat(stringB, tokenB[le]);
				}
				else {
					stringB = strcat(stringB, "-");
				}
			}
			printf("%s", stringB);
			fprintf(bofT, "%s", stringB);
		}
		else {
			fprintf(bofT, "%s", line);
		}

		satir++;

		if (satir > 30)
			break;
	}														//end of write book file  

	fclose(bof);
	fclose(bofT);
	remove(bookpath);
	rename(tempBo, bookpath);

/////////////////////////////////////////////////////////////////////|| GG ||//////////////////////////////////////////////////////////////////////////////////////////
}

void search() {
	
	FILE* inf;												//index file

	inf = fopen(indexpath, "r");							//for read index file

	int loc;
	char *aras = (char*)malloc(sizeof(char));               //for book no
	int ara;												//for book no
	int bucket = 0;

	char line[250];
	char* token[6];											//token for index
	char* t;												//temp token

	int isFound = 0;										//Boolean found
	int isFirst = 1;										//Boolean is first part of line


	printf("Pls Instert the your book's no: ");
	scanf("%d", &ara);
	itoa(ara, aras, 10);


	loc = hash(ara);

	int satir = -1;
	int buc = 0;
	
	
	while (1) {												//start read index file
		fgets(line, sizeof(line), inf);						//read line by line
		
		if (satir == loc) {
			t = strtok(line, "-");

			while (t != NULL) {								//split the line
				token[buc] = t;
				t = strtok(NULL, "-");
				
				if (!strcmp(token[buc], aras) && !isFound && !isFirst) {
					bucket = buc;
					isFound = 1;
				}
				if (isFirst) {
					isFirst = 0;
				}

				buc++;
			}
		}
		satir++;

		if (isFound)										//break when the book found 
			break;

		if (satir > 30)										//break when in last shelf
			break;
		
	}														//stop read index file

	if (isFound) {											
		printf("Your book's Shelf Number:%d and on B%d \n", loc,bucket );
	}
	else
		printf("Doesnt exist\n");

	fclose(inf);
}

void list() {

	FILE* bof;												//book file

	bof = fopen(bookpath, "r");								//for read book file

	char line[250];
	char* token[11];										//token for bookk
	char* t;												//temp token

	int satir = 0;
	int buc = 0;

	while (1) {												//start read book file
		fgets(line, sizeof(line), bof);						//read line by line
		buc = 0;
		if (satir > 0) {
			t = strtok(line, "-");

			while (t != NULL) {								//split the line
				token[buc] = t;
				t = strtok(NULL, "-");
				buc++;
			}
			for (int i = 0; i < 11; i++) {
				if (i % 2 == 0) {
					printf("%s ", token[i]);
				}
			}
			printf("\n");
		}
		else {
			printf("Shelf number B1 B2 B3 B4 B5\n");
		}

		satir++;
		if (satir > 30)
			break;
	}														//finish read book file

	fclose(bof);
}

void clear(char* al,char* ver) {							//for fix fgets's '\n' issue (wrong work!! Dont use!!)
	

	int i = 0;
	while (al[i] != '\n') {
		ver[i] = al[i];
	}

}

