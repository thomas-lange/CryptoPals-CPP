# Single Byte XOR Cypher

[Link Challenge1.3](http://www.cryptopals.com/sets/1/challenges/3)

|**Exercise:**|
|------------|
|The hex encoded string:
|
| ```1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736```
|... has been XOR'd against a single character. Find the key, decrypt the message.
|
| You can do this by hand. But don't: write code to do it for you.
|
| How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric.
| Evaluate each output and choose the one with the best score.


##Ideas
* Well actually this can be done by brute force with the already deveoloped function.
* A function will be needed to transform **hex to ascii**


##Hex to Ascii?
As HEX is simple 4 bit and ASCII 8 Bit this should be pretty straight forward:
1. Push 1. HEX into uint8 by 4 bits
2. Or with the 2. HEX
=> The result should be a 8 bit representation and as such convertable to ASCII
3. Convert 8Bit to ASCII