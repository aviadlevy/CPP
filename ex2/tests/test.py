from os import listdir , system
from os.path import isfile, join
import os

FILE_DIRECTORY = "./"
input_files = [join(FILE_DIRECTORY,os.path.splitext(f)[0]) for f in listdir(FILE_DIRECTORY) if f.endswith(".in")]
for i,f in enumerate(input_files):
    my_output = system("./chess.exe < " + f + ".in > output.out");
    rescode = system("diff -B output.out " + f + ".out");
    if  rescode != 0:
        print("problem in input file:" + " -- " + f + ".in")
        print("######################## your output:########################")
        system("cat < output.out");
        print();
        print("######################## my output:########################")
        system("cat < " + f + ".out")
        break
else:
    print(" ____^^^^^____ ")
    print("(((o(*>w<*)o)))")
    print("     good!     ")           
    
