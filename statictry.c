#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char **argv)
{
	struct property{
		char key[30];
		char value[30];
	};
	struct section{
		char structname[30];
		struct property props[30];
	};
	FILE * fptr;
	struct section dataarray[30];
	char * linia=NULL;
	size_t len=0;
	int sectioncount=0;
	int keycount[30]={0};
	int ct=-1;
	char * del="=";
	char * del2=".";
	fptr=fopen(argv[1],"r");
	char argument[65];
	strcpy(argument,argv[2]);
	char * divideme = strtok(argument,del2);
	char * keyarg = divideme;
	divideme = strtok(NULL,del2);
	char * valuearg = divideme;
	divideme=NULL;
	//printf("%s %s",keyarg,valuearg);

	while (getline(&linia,&len,fptr)!=-1){
		if(linia[0]==';')
			continue;
		if(strchr(linia,'[')!=NULL){
			for(int i =1;i<strlen(linia)-3;i++){
				if (!isalnum(linia[i])){
					printf("in section name %s %c is a forbidden character fix your ini file and try again",linia,linia[i]);
					return -1;
				}

			}
			strncpy(dataarray[sectioncount].structname,linia+1,strlen(linia)-3);	
			sectioncount++;
			ct++;
			}
		if(strchr(linia,'=')!=NULL){
			divideme = strtok(linia,del);
			char * keytemp=divideme;
			divideme = strtok(NULL,del);
			char* valuetemp = divideme;
			//printf("%s",keytemp);
			int num=strlen(keytemp);
			for(int i =0;i<num-1;i++){
				if(!isalnum(keytemp[i])){
					printf("in section %s in key name %s %c is a forbiden character fix your ini file and try again",dataarray[sectioncount-1].structname,keytemp,keytemp[i]);
				return -1;
				}
			}
			//printf("%s %s",keytemp,valuetemp);
			
			strncpy(dataarray[sectioncount-1].props[keycount[ct]].key,keytemp,num-1);
			strcpy(dataarray[sectioncount-1].props[keycount[ct]].value,valuetemp);
			//printf("%s %s",dataarray[sectioncount-1].props[keycount[ct]].key,dataarray[sectioncount-1].props[keycount[ct]].value);
			keycount[ct]++;


		}
	}
	int flags=0;
	int flagk=0;
	for(int i =0;i<sectioncount;i++)
	{
		//printf("przed 1 ifem%ld %ld\n",strlen(dataarray[i].structname),strlen(keyarg));
		if(!strcmp(dataarray[i].structname,keyarg)){
			flags=1;
			//printf("w 1 ifie%s %s\n",dataarray[i].structname,keyarg);
			for(int j=0;j<keycount[i];j++){
				//printf("przed 2 ifem%ld %ld",strlen(dataarray[i].props[j].key),strlen(valuearg));
				if (!strcmp(dataarray[i].props[j].key,valuearg)){

					printf("%s\n",dataarray[i].props[j].value);
					flagk=1;
				}
				else{
					flagk=0;
				}
			}
		}
		else{
		flags=0;
		}	
		//printf("%s",dataarray[i].structname);
		//for(int j=0;j<keycount[i];j++){
			//printf("%s",dataarray[i].props[j].key);
			//printf("%s",dataarray[i].props[j].value);}}
	}
	printf("%s\n",dataarray[28].props[24].value);
	
	if(flags==0){
		printf("Failed to find section [%s]\n",keyarg);
	}
	else if(flagk==0){
		printf("Failed to find key \"%s\" in section [%s]\n",valuearg,keyarg);
	}

	//for(int i =0;i<sectioncount;i++){
	//	printf("%s\n",dataarray[i].structname);
	//	for(int j=0;j<keycount[i];j++){
	//		printf("%s\n",dataarray[i].props[j].key);
	//		printf("%s\n",dataarray[i].props[j].value);
	//	}
	//}
	free(linia);
	fclose(fptr);

	



	return 0;
}
