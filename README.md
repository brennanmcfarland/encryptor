# encryptor
A rudimentary experiment in encryption given a plaintext string

NOTE: DO NOT USE THIS FOR ACTUALLY ENCRYPTING ANYTHING.  IT IS NOT SECURE FOR ACTUAL USE

A few years ago, some friends and I decided to have a private hackfest competition.  The rules: each of us would code an encryption algorithm that had to be entirely reversible (and write the implementation for reversing it) given only the output, and the input could consist only of a plaintext message and an additional string as a key.  Then, we would trade encrypted messages and binaries and attempt to break each others' code.

This program is the result of that competiton.  It mixes up the text in three stages: first, it converts the string to a 2d vector of characters and a list of their positions.  Second, it multiplies each value by a given key.  Lastly, it converts the vector to a string and intersperses each character of that string among randomly generated characters in positions determined by the fibonnacci sequence.  In the end it turns a short string into a huge textfile almost entirely of garbage, and for the record no one was able to crack it (I wrote it in C++ so it couldn't be decomplied as easily as I decompiled my opponent's algorithm in Java).  It's not useful as an actual encryption algorithm, it's a lot of fun to watch people try to crack it.
