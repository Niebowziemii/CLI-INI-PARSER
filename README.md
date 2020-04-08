# console INI-Parser 
### Authors 
##### Rafał Stachowiak - creator of the command line interface
##### Franciszek Olejnik - creator of the INIParser library https://github.com/FrankOil/INIParser

## Simplicity in usage
Few steps how to use our application:
1. compile file new_approach.c
```bash
	cc -g -o new_approach new_approach.c
```
2.  execute with the following to get a value of a key in a given section:
```bash
./new_approach <ini-file-name.ini> <section_name>.<key_name>
```
3.  If you want to calculate simple expression on numbers simply try (be careful before and after the operator you must not put any white characters):
```bash
./new_approach <ini-file-name.ini> expression "<section_name_1>.<key_name_1><operator><section_name_2>.<key_name_2>"
```
you can use operators such as ``{+,-,*,/}`` to operate on numbers and ``+`` operator to concatenate strings.

### Library INIParser.h 
Assures that every error is spotted and announced.
