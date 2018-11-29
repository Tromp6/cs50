// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // Structures for timing data
    struct rusage before, after;

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    // Calculate time to load dictionary
    time_load = calculate(&before, &after);

    // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check each word in text
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string

                //also erst hab ich den fehler gemacht dass ich dachte nach dem while kommt{}
                //ist der Sinn von der while einfach nur den pointer solange laufen zu lassen
                //bis das ende der linie erreicht wurde??

                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        //wieso haben wir hier ein Wort gefunden?
        //also zuerst haben wir rausgefiltert wenn es zu lang ist um ein wort
        //zu sein wenn es zahlen hat dann raus
        //aber index könnte doch auch 1 sein das bedeutet doch nicht das wir ein wort gefunden haben

        /*
            Also erst wird geprüft ob der buchstabe im alphabet ist wenn ja kommt er ins wort
            Dann wird geprüft ob das das ein String ist der zu lang ist um ein wort sein zu können
            -> falls ja wird alles rausgeworfen und der prozess startet von vorne und
            -> der pointer wird zur nächsten Linie gesetzt
            Dann wird geprüft ob es ein Wort mit zahl ist wenn ja passiert wieder dasselbe

            Wenn es ab dem 2ten durchlauf ein buchstabe hinzugefügt wird welcher kein buchstabe
            oder zahl ist dann wird das wort beendet und man hat ein wort gefunden

            Naja man tut einen ganzen text rein und wörter sind getrennt durch leerzeichen punkt
            undso dass heißt wenn das wort nicht zu lang ist und keine Zahl enthält haben wir ein
            Wort gefunden
            Denn sagen wir er überprüft den zweiten buchstaben von einem wort und der ist im alphabet
            geht er ja in die erste if und danach in keine mehr weils ja else if

        */
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Update benchmark
            time_check += calculate(&before, &after);

            // Print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Close text
    fclose(file);

    // Determine dictionary's size
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calculate time to determine dictionary's size
    time_size = calculate(&before, &after);

    // Unload dictionary
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Abort if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calculate time to unload dictionary
    time_unload = calculate(&before, &after);

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
