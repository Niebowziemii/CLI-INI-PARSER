#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	char * unparsed_argument;
	unparsed_argument = (char*)malloc(strlen(argv[2])+1);
	strcpy(unparsed_argument,argv[2]);
	// printf("%s %d",unparsed_argument,strlen(unparsed_argument));
	// printf("%d",(int)unparsed_argument[3]);
	if(!strcmp(unparsed_argument,"expression")){
		char * given_expression = (char*)malloc(strlen(argv[3])+1);
		char * buff=given_expression;
		char ** operand1;
		char ** operand2;
		char * operatorr;
		strcpy(given_expression,argv[3]);
		for(int i = 0;i<strlen(given_expression); i++){
			if(!isalnum(given_expression[i])&&(int)given_expression[i]!=(int)' '&&(int)given_expression[i]!=(int)'.'){
				char illegal=given_expression[i];
				operatorr=&illegal;
				switch(illegal){
					case '+':
						if((int)given_expression[i-1]==(int)' '){
							char * wanted_operand_1 = (char*)malloc(i);
							wanted_operand_1 = strtok(buff," +");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"+ ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"+");
								operand2 = &wanted_operand_2;
							}
						}
						else{
							char * wanted_operand_1 = (char*)malloc(i+1);
							wanted_operand_1 = strtok(buff,"+");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"+ ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"+");
								operand2 = &wanted_operand_2;
							}
						}
						break;
					case '-':
						if((int)given_expression[i-1]==(int)' '){
							char * wanted_operand_1 = (char*)malloc(i);
							wanted_operand_1 = strtok(buff," -");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"- ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"-");
								operand2 = &wanted_operand_2;
							}
						}
						else{
							char * wanted_operand_1 = (char*)malloc(i+1);
							wanted_operand_1 = strtok(buff,"-");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"- ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"-");
								operand2 = &wanted_operand_2;
							}
						}
						break;
					case '*':
						if((int)given_expression[i-1]==(int)' '){
							char * wanted_operand_1 = (char*)malloc(i);
							wanted_operand_1 = strtok(buff," *");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"* ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"*");
								operand2 = &wanted_operand_2;
							}
						}
						else{
							char * wanted_operand_1 = (char*)malloc(i+1);
							wanted_operand_1 = strtok(buff,"*");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"* ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"*");
								operand2 = &wanted_operand_2;
							}
						}
						break;
					case '/':
						if((int)given_expression[i-1]==(int)' '){
							char * wanted_operand_1 = (char*)malloc(i);
							wanted_operand_1 = strtok(buff," /");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"/ ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"/");
								operand2 = &wanted_operand_2;
							}
						}
						else{
							char * wanted_operand_1 = (char*)malloc(i+1);
							wanted_operand_1 = strtok(buff,"/");
							operand1=&wanted_operand_1;
							if((int)given_expression[i+1]==(int)' '){
								char * wanted_operand_2 = (char*) malloc(strlen(given_expression)-i);
								wanted_operand_2 = strtok(NULL,"/ ");
								operand2 = &wanted_operand_2;
							}
							else{
								char * wanted_operand_2 = (char*)malloc(strlen(given_expression)-i-1);
								wanted_operand_2 = strtok(NULL,"/");
								operand2 = &wanted_operand_2;
							}
						}
						break;
					default:
						printf("expression contains illegal character. Legal characters: [a-z],[A-Z],[0-9],[<space>.*/+-]");
						return -1;
				}
			}
			else if((int)given_expression[i]==(int)' '){
				continue;
			}
		}
		// printf("%s %s %c",*operand1,*operand2,*operatorr);
		char ** section_operand_1;
		char ** key_operand_1;
		char ** section_operand_2;
		char ** key_operand_2;
		for(int i =0;i<strlen(*operand1);i++){
		if((int)(*operand1)[i]==(int)'.'){
				char * buffsection_operand_1 = (char*)malloc(i+1);
				buffsection_operand_1=strtok(*operand1,".");
				char * buffkey_operand_1 = (char*)malloc(strlen(*operand1)-i);
				buffkey_operand_1 = strtok(NULL,".");
				section_operand_1=&buffsection_operand_1;
				key_operand_1=&buffkey_operand_1;
			}
		}
		for(int i =0;i<strlen(*operand2);i++){
			if((int)(*operand2)[i]==(int)'.'){
				char * buffsection_operand_2 = (char*)malloc(i+1);
				buffsection_operand_2=strtok(*operand2,".");
				char * buffkey_operand_2 = (char*)malloc(strlen(*operand2)-i);
				buffkey_operand_2 = strtok(NULL,".");	
				section_operand_2=&buffsection_operand_2;
				key_operand_2=&buffkey_operand_2;		
				}
		}
		printf("Section 1: %s Key1: %s Operand: %c Section2: %s Operand2: %s",*section_operand_1,*key_operand_1,*operatorr,*section_operand_2,*key_operand_2);

	}
	else{
		for(int i =0;i<strlen(unparsed_argument);i++){
		if((int)unparsed_argument[i]==(int)'.'){
				char * wanted_section_name = (char*)malloc(i+1);
				wanted_section_name=strtok(unparsed_argument,".");
				char * wanted_key_name = (char*)malloc(strlen(unparsed_argument)-i);
				wanted_key_name = strtok(NULL,".");
				printf("%s %s",wanted_section_name,wanted_key_name);
		}
	}
	}
	
	return 0;


}
	// struct property{
	// 	char key[30];
	// 	char value[30];
	// };
	// struct section{
	// 	char structname[30];
	// 	struct property props[30];
	// };
	// FILE * fptr;
	// struct section dataarray[30];
	// char * linia=NULL;
	// size_t len=0;
	// int sectioncount=0;
	// int keycount[30]={0};
	// int ct=-1;
	// char * del="=";
	// char * del2=".";
	// fptr=fopen(argv[1],"r");
	// char argument[65];
	// strcpy(argument,argv[2]);
	// char * divideme = strtok(argument,del2);
	// char * keyarg = divideme;
	// divideme = strtok(NULL,del2);
	// char * valuearg = divideme;
	// divideme=NULL;
	// //printf("%s %s",keyarg,valuearg);

	// while (getline(&linia,&len,fptr)!=-1){
	// 	if(linia[0]==';')
	// 		continue;
	// 	if(strchr(linia,'[')!=NULL){
	// 		for(int i =1;i<strlen(linia)-3;i++){
	// 			if (!isalnum(linia[i])){
	// 				printf("in section name %s %c is a forbidden character fix your ini file and try again",linia,linia[i]);
	// 				return -1;
	// 			}

	// 		}
	// 		strncpy(dataarray[sectioncount].structname,linia+1,strlen(linia)-3);	
	// 		sectioncount++;
	// 		ct++;
	// 		}
	// 	if(strchr(linia,'=')!=NULL){
	// 		divideme = strtok(linia,del);
	// 		char * keytemp=divideme;
	// 		divideme = strtok(NULL,del);
	// 		char* valuetemp = divideme;
	// 		//printf("%s",keytemp);
	// 		int num=strlen(keytemp);
	// 		for(int i =0;i<num-1;i++){
	// 			if(!isalnum(keytemp[i])){
	// 				printf("in section %s in key name %s %c is a forbiden character fix your ini file and try again",dataarray[sectioncount-1].structname,keytemp,keytemp[i]);
	// 			return -1;
	// 			}
	// 		}
	// 		//printf("%s %s",keytemp,valuetemp);
			
	// 		strncpy(dataarray[sectioncount-1].props[keycount[ct]].key,keytemp,num-1);
	// 		strcpy(dataarray[sectioncount-1].props[keycount[ct]].value,valuetemp);
	// 		//printf("%s %s",dataarray[sectioncount-1].props[keycount[ct]].key,dataarray[sectioncount-1].props[keycount[ct]].value);
	// 		keycount[ct]++;


	// 	}
	// }
	// int flags=0;
	// int flagk=0;
	// for(int i =0;i<sectioncount;i++)
	// {
	// 	//printf("przed 1 ifem%ld %ld\n",strlen(dataarray[i].structname),strlen(keyarg));
	// 	if(!strcmp(dataarray[i].structname,keyarg)){
	// 		flags=1;
	// 		//printf("w 1 ifie%s %s\n",dataarray[i].structname,keyarg);
	// 		for(int j=0;j<keycount[i];j++){
	// 			//printf("przed 2 ifem%ld %ld",strlen(dataarray[i].props[j].key),strlen(valuearg));
	// 			if (!strcmp(dataarray[i].props[j].key,valuearg)){

	// 				printf("%s\n",dataarray[i].props[j].value);
	// 				flagk=1;
	// 			}
	// 			else{
	// 				flagk=0;
	// 			}
	// 		}
	// 	}
	// 	else{
	// 	flags=0;
	// 	}	
	// 	//printf("%s",dataarray[i].structname);
	// 	//for(int j=0;j<keycount[i];j++){
	// 		//printf("%s",dataarray[i].props[j].key);
	// 		//printf("%s",dataarray[i].props[j].value);}}
	// }
	// printf("%s\n",dataarray[28].props[24].value);
	
	// if(flags==0){
	// 	printf("Failed to find section [%s]\n",keyarg);
	// }
	// else if(flagk==0){
	// 	printf("Failed to find key \"%s\" in section [%s]\n",valuearg,keyarg);
	// }

	// //for(int i =0;i<sectioncount;i++){
	// //	printf("%s\n",dataarray[i].structname);
	// //	for(int j=0;j<keycount[i];j++){
	// //		printf("%s\n",dataarray[i].props[j].key);
	// //		printf("%s\n",dataarray[i].props[j].value);
	// //	}
	// //}
	// free(linia);
	// fclose(fptr);

	


