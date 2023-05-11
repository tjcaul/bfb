# bfb
*BrainFuck Beautifier*

**Usage**
```
bfb pattern bf
bfb pattern < bf
```

Maps a Brainfuck program into a pattern file.

**Rules**
- Characters except for `+-.,<>[]` in the bf file are
  ignored
- Only `#` characters (configurable) in the pattern
  file are replaced
- Excess bf characters are dumped at the bottom so the
  program still runs
- Excess `#` characters are replaced with `+` and `-`
  randomly, which hopefully won't break your program
  (configurable)

## Example
`demo.pat`:

```
I N T R O D U C I N G

#         ### #
#        #    #
#        #    #
#####  ###### #####
#    #   #    #    #
#    #   #    #    #
#    #   #    #    #
#####    #    #####  #

 BRAINFUCK BEAUTIFIER
```

`demo.b`:
```
>++++++++++[<++++++++++>-]< cell 0 = 100
--. decrease to 98 ('b') and print
++++. print 102 ('f')
----. print 98 ('b')
[-] zero cell 0
++++++++++. increase to 20 ('\n') and print
```

```
$ bfb demo.pat demo.b
I N T R O D U C I N G

>         +++ +
+        +    +
+        +    +
[<+++  ++++++ +>-]<
-    -   .    +    +
+    +   .    -    -
-    -   .    [    -
]++++    +    +++++  .

 BRAINFUCK BEAUTIFIER
```
