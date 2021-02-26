# Memory dump to ASCII

## Presentation
This software aims at displaying a stack dump in ASCII readable characters. It comes from a root-me challenge where a password was stored in a buffer on the stack: dumping the stack using a format string vulnerability and then displaying it as an ASCII string allows to see the password.

Obviously, this software's work could be easily achieved by a one-liner:
```bash
echo -e $(echo $dump_string | sed -r 's/(..)(..)(..)(..)/\\x\4\\x\3\\x\2\\x\1/g')
```
But as C is the best programming language, it was always fun :)

## Compilation
The software is easily built with:
```bash
make
```

## Execution
The software is executed using:
```bash
./memory_dump_ascii <string>
```
where `<string>` should be in the following format:
```
XXXXXXXXX.XXXXXXXX. ... .XXXXXXXX
```
This is the kind of output you can get from:
```
./vulnerable_to_format_string %08x.%08x.%08x. ... .%08x
```
