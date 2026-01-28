%{
 #include<stdio.h>
 #include<string.h>
 char *file1;
 int flag=1;
%}

%%

[0-9]+  {
	if(strcmp(yytext,"\n")==0){
	return 1;}
	else{
	printf("number");}};

%%

int yywrap()
{
   file1="file.l";
   FILE*fp=fopen(file1,"r");
   if(flag&&fp){
   yyin=fp;
   flag=0;
   return 0;
}
   else{
   return 1;
   }
   }

int main()
{
   yylex();
   return 1;
}
