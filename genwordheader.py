import sys
import codecs

def main(argc, argv):
    
    if argc < 2:
        print(f"usage: {argv[0]} wordlist.txt")
        return
    
    words_header = open("words.h", "w")
    words_source = open("words.c", "w")

    wordlist = open(argv[1], "r")
    # wordlist = codecs.open(argv[1], 'r', encoding='utf-8')

    words_source.write("""#include "words.h"

char* words[] = {
""")

    total_words = 0
    for line in wordlist.readlines():
        if len(line) > 32 or not line.isascii() or "\"" in line or "'" in line or "\\" in line:
            continue

        total_words += 1

        words_source.write(f"\"{line.strip()}\",\n")
    wordlist.close()

    words_source.write("};\n")
    words_source.close() 

    words_header.write(f"""#ifndef WORDS_H
#define WORDS_H

#define NUM_WORDS {total_words}
extern char* words[NUM_WORDS];

#endif // !WORDS_H""")   

    words_header.close()


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)