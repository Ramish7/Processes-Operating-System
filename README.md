# Processes-Operating-System

Developing a multi-process application that will generate a value histogram for the values sitting in a set of input ascii text files, one value per line. Values can be an integers or real numbers.

To run the program type the following on the command line.
phistogram minvalue maxvalue bincount N file1 ... fileN outfile

Here, minvalue is the minimum value that exists in the given set of input files, and maxvalue is the maximum value. bincount is the number of bins in the histogram. Let w denote bin-width. Then w = (maxvalue - minvalue) / bincount. The first bin
will give the count of values in range [minvalue, minvalue+w); the second bin will give the count of values in range [minvalue+w, minvalue+2w); and so on. N is the number of input files. file1 ... fileN are the names of these input files. outfile is the output file.

The program will create another child process for each input file to generate a histogram for the values in that input file. Hence there will be N child processes working concurrently on the N input files, and at the end, N histograms will be
generated into N intermediate files. The parent process will then combine these N histograms into one histogram and will output this histogram to the output file. Each output line will contain information about a separate bin in the following format:
binnumber: count. Binnumbers will start at 1.
