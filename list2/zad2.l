%option noyywrap

%x string

%%

"--".*          {} 

\"              {BEGIN(string); ECHO; } 
<string>\"      {BEGIN(INITIAL); ECHO; }  
<string>\n      ECHO;           
<string>.       ECHO;           

.|\n            ECHO; 

%%

int main() {
    yylex();
    return 0;
}
