# About

_This is the lexical part of the course project of Compiler Principles._
_it generates DFAs for the given rules and outputs token types in the given text._


__For the homework of Software Testing and Verification.__


#### Detail

Lexial structure is defined as follows:

+	__comments:__    Comments starts with  `//` characters and ends with the end of line character.

+	__keywords:__     The keywords given in the grammar: 
           
    int real if then else while
            
+	__identifiers:__   An identifier starts with a letter and continues with a letter or digit. A keyword cannot be 

  an identifier,  and the maximum length of an identifier is 64 characters.

+	__operators:__    The followings are operators:
    
    +  -  /  *  =  ==  <  <=  >  >=  !=  

+	__delimiters:__   The followings are delimeters:
    
    (  )  {  }  ;  

+	__numbers:__     The numbers are defined as follows:

    digit      <- 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    intnumber  <- digit+                             (the maximum integer number is 231)
    exponent   <- (E|e) ( + | - | EPSILON ) digit+   (the maximum exponent value is 128)
    fraction   <- . digit+    
    realnumber <- digit+ exponent | digit+ fraction  ( exponent | EPSILON )
