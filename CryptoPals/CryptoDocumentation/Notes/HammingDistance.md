# XOR Extended: Multi-byte Repeated XOR
###Great Page: https://picoctf.com/crypto_mats/
###Great Page: https://ehsandev.com/pico2014/


The easiest extension, at this point, to single-byte repeated XOR is simply to fix the "single-byte" part: rather than having a keyspace of size 28, we can have a keyspace of size 28nn, where nn is the length in bytes of our chosen key. To do this, instead of simply XOR-ing every byte of our plaintext with the same byte, we take our bytes of key — say, 0x24, 0xff and 0x42 — and use them in a cycle. That is, we XOR the first byte of the plaintext with 0x24, the second with 0xff, the third with 0x42, the fourth with 0x24, and so on. In code, we can simply say:

```
ciphertext[i] = key[i % len(key)] ^ plaintext[i]
```

If the value of nn is large enough — that is, the length of the plaintext or longer — this cipher is in fact precisely equivalent to the one-time pad. However, in general, the key must be substantially shorter — for example, it might be 16 bytes long. In that case, our keyspace has size 2128 — still much too large to bruteforce.

##Cracking Multi-Byte Repeated XOR

Multi-byte repeated XOR is substantially harder to attack than single-byte repeated XOR. To see this, note that any statistical attack (such as the one we used in our attack on the substitution cipher) will necessarily rely on knowing the length of the key — since otherwise, we do not know which properties were preserved and which were not.

On the other hand, if we do know the length of the key and we have enough ciphertext, the attack becomes simple: simply break the ciphertext into separate streams, depending on which key byte each byte of the ciphertext was encrypted with, and use our attack against single-byte repeated XOR on each stream!

This attack should rapidly find the correct subkey for each stream — using 28 time for each stream, so linear time in the length of the key overall — and therefore give us the complete key for the entire ciphertext.

Therefore, to crack multi-byte repeated XOR, we need only determine the length of the key. To do so, we will appeal to an old idea from computer science: the Hamming weight of a given sequence of bytes. The Hamming weight is simply the number of bits in the sequence that are set to 1 — in essence, it can be computed by counting the 1s after converting the bytes to binary. For example, 0x24 (in binary, 0b00100100) has a Hamming weight of 2, while 0x7ffe (in binary, 0b0111111111111110) has a Hamming weight of 14.

We notice that if two ciphertext bytes, say **cici** and **cjcj**, are a multiple of the key length apart, then their corresponding plaintext bytes were both XORed with the same key byte. Therefore, if x=ci⊕cj (where ⊕ is XOR), it is equal to the result of XORing the corresponding plaintext bytes together. If the plaintext bytes are not random — for example, if they are English text — the Hamming weight of this result should be fairly low. In comparison, since the key should be random, if **cici** and **cjcj** are not a multiple of the key length apart, then xx contains the XOR of the two key bytes — which will most likely have a fairly high Hamming weight.

If AA and BB are byte sequences of equal length, and C=A⊕BC=A⊕B, we say the Hamming weight of CC is the Hamming distance between AA and BB. In other words, the paragraph above says that the Hamming distance between two ciphertext bytes that were encrypted using the same key byte should be lower than the Hamming distance between ciphertext bytes that were encrypted using different key bytes.

We can use this fact to get a few reasonable guesses for the key length. We notice that if our guess KK is a multiple of the key length, then the "normalized Hamming distance" (normalized by dividing by KK, since we care about the average Hamming distance between bytes) between the first KK bytes of ciphertext and the second KK bytes of ciphertext should be lower than if KK is not. Therefore, if we compute this normalized Hamming distance for a few reasonable guesses for KK (say, all values of KK between 1 and 100), the ones with the lowest normalized Hamming weights are probably reasonable guesses for the real key length.

For example, consider the ciphertext (encoded in hex), encrypted using multi-byte repeating XOR, below: