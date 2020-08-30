#!/bin/sh

tr  A-Z a-z |                       # map uppercase to lower case
tr -cs "a-z'" "\n" |                # make one word per line
sed -e "s/^'//;s/'$//;s/'s\$//" |   # remove leading/trailing ' and 's
grep -v '^$'|                       # remove empty lines
sort | uniq -c |                    # sort and count frequencies
awk '{printf("%6d   %s\n",$1,$2)}'  # put into same format as wfreq
