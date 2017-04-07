#!/usr/bin/env python2

import sys
import re

def foo(item):
    #pattern = re.compile("(O=[^,]+),")
    pattern = re.compile(r"(O=[^,]+)(,|$)")
    match = re.search(pattern, item)
    if not match:
        #print("FAILURE '%s'" % item)
        return ""
    #print(match.group(1))
    return match.group(1)

file=open(sys.argv[1])
lines = [line.strip() for line in file.readlines()]
lines = sorted(lines, key=foo)
### BEGIN BAD CODE
new = []
for i in range(0, len(lines)):
    try:
        if foo(lines[i-1]) == foo(lines[i]):
            continue
        new.append(lines[i])
    except IndexError:
        new.append(lines[i])
        continue
lines = new
### END BAD CODE

# Format in LaTeX because I'm lazy.
for i, line in enumerate(lines):
    if i % 5 == 0:
        print "\t\\begin{frame}"
        print "\t\t\\begin{itemize}"
    print "\t\t\\item %s" % line.replace("\\", "\\textbackslash ").replace("_", "\\_")
    if i % 5 == 4:
        print "\t\t\\end{itemize}"
        print "\t\\end{frame}"
if i % 5 != 4:
    print "\t\t\\end{itemize}"
    print "\t\\end{frame}"
