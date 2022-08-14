# DFM Gramma

The following context free gramatic was deducted using .dfm files found on github, a basic knowledge of the delphi programming language and common sense. Matching has to be done case-insensitiv.

```
DFM := <WS>* <OBJ> <WS>*
DELPHI_IDENTIFIER := Starts with underscore or a letter and otherwise only contains numbers, letters or underscores.
DELPHI_NAME := <WS>* <DELPHI_IDENTIFIER>('.' <DELPHI_IDENTIFIER>)* <WS>*
HEX_CODE_STRING := [0-9A-Fa-f]+
HWS := (' '|'\t')*
NL := '\r'|'\n'|'\r\n'
OBJ := <WS>* ('object'|'inherited'|'inline') <WS>* (<OBJ_NAME> <WS>*  ':')? <WS>*  <OBJ_TYPE> <WS>*  ('[' <WS>*  <VALUE_INTEGER> <WS>*  ']' <WS>* )? <OBJ_PARAMS> <WS>* 'end' <WS>*
OBJ_NAME := <DELPHI_NAME> <WS>*
OBJ_PARAM := <WS>* <OBJ> <WS>*
OBJ_PARAM := <WS>* <OBJ_PARAM_NAME> <WS>* '=' <WS>* <VALUE> <WS>*
OBJ_PARAM_NAME := <WS>* <DELPHI_NAME> <WS>*
OBJ_PARAMS := <WS>* <OBJ_PARAM>* <WS>*
OBJ_TYPE := <WS>* <DELPHI_NAME> <WS>*
VALUE := <VALUE_ARRAY>
VALUE := <VALUE_BINARY>
VALUE := <VALUE_BIT>
VALUE := <VALUE_CONSTANT>
VALUE := <VALUE_DATETIME>
VALUE := <VALUE_FLOAT>
VALUE := <VALUE_INLINE_OBJECT>
VALUE := <VALUE_INTEGER>
VALUE := <VALUE_SET>
VALUE := <VALUE_STRING>
VALUE_ARRAY := <WS>* '<' <WS>* <VALUE_ARRAY_ITEMS> <WS>* '>' <WS>*
VALUE_ARRAY_ITEM  := <WS>* 'item' <WS>* <VALUE_ARRAY_ITEM_PARAM>* <WS>* 'end' <WS>*
VALUE_ARRAY_ITEM_PARAM := <WS>* <VALUE_ARRAY_ITEM_PARAM_NAME> <WS>* '=' <WS>* <VALUE> <WS>*
VALUE_ARRAY_ITEM_PARAM_NAME := <WS>* <DELPHI_NAME> <WS>*
VALUE_ARRAY_ITEMS := <WS>* <VALUE_ARRAY_ITEM>* <WS>*
VALUE_BINARY := <WS>* '{' <WS>* <HEX_CODE_STRING>* <WS>* '}' <WS>*
VALUE_BIT := 'true' | 'false'
VALUE_CONSTANT := <WS>* <DELPHI_NAME> <WS>*
VALUE_DATETIME := ('-'|'+')? (([0-9]+ '.' [0-9]*) | ([0-9]* '.' [0-9]+)) 'd'
VALUE_DATETIME := ('-'|'+')? [0-9]+ 'd'
VALUE_FLOAT := ('-'|'+')? (([0-9]+ '.' [0-9]*) | ([0-9]* '.' [0-9]+))
VALUE_INLINE_OBJECT := <WS>* '(' <WS>* ((<NL> <WS>*)* <VALUE> <WS>*)* ')' <WS>*
VALUE_INTEGER := '$' [a-fA-F0-9]+
VALUE_INTEGER := ('-'|'+')? [0-9]+
VALUE_SET := <WS>* '[' <WS>* <VALUE_SET_VALUES> <WS>* ']' <WS>*
VALUE_SET_VALUE := <VALUE_CONSTANT>
VALUE_SET_VALUE := <VALUE_DATETIME>
VALUE_SET_VALUE := <VALUE_FLOAT>
VALUE_SET_VALUE := <VALUE_INTEGER>
VALUE_SET_VALUES := <EPSILON>
VALUE_SET_VALUES := <WS>* <VALUE_SET_VALUE> <WS>* (',' <WS>* <VALUE_SET_VALUE> <WS>*)*
VALUE_STRING := <WS>* <VALUE_STRING_ELEMENT> <WS>*
VALUE_STRING_ELEMENT := <EPSILON>
VALUE_STRING_ELEMENT := <HWS>* (<VALUE_STRING_ELEMENT_CHAR> <HWS>*)+ (<VALUE_STRING_ELEMENT> <HWS>*)?
VALUE_STRING_ELEMENT := <HWS>* (<VALUE_STRING_ELEMENT_CHAR> <HWS>*)+ <WS>* '+' <WS>* <VALUE_STRING_ELEMENT> <HWS>*
VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <HWS>*
VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <HWS>* <VALUE_STRING_ELEMENT_CHAR> <HWS>* <VALUE_STRING_ELEMENT> <HWS>*)?
VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <WS>* '+' <WS>* <VALUE_STRING_ELEMENT> <HWS>*
VALUE_STRING_ELEMENT_CHAR := '#$'[0-9A-Fa-f]+
VALUE_STRING_ELEMENT_CHAR := '#'[0-9]+
VALUE_STRING_ELEMENT_STRING := <HWS>* '\'' ([^']* '\'' '\'')* '\'' <HWS>*
VALUE_STRING_ELEMENT_STRING := <HWS>* '\'' [^']* '\'' <HWS>*
WS := ('\v'|'\f'|'\n'|'\r'|'\r\n'|' '|'\t'|%xA0|%x85)*
```




