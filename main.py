"""
Thanks for the great tutorial!
https://nbviewer.org/gist/guocheng/1ae6c2d76461a66cfc5ec6009b5791d1
"""

"""
1. If English is the only language on the plane, ASCII is all we need.
2. But that is not the case. We need more than 256 symbols. The bigger table we need is called Unicode.
3. As the table gets bigger, we can no longer hold the contents of one symbol in a single byte (8 bits). We need 4 bytes.
4. So how does a computer figure out that four bytes represent one character?
5. If more than one byte represents a character, the bytes need to be packed as one unit. UTF-8 does this for us.
"""

"""
UTF-8 Format:
           Bits for codepoint
# Bytes      (empty spaces)        Byte 1    Byte 2   Byte 3   Byte 4
   1                7             0xxxxxxx
   2               11             110xxxxx  10xxxxxx
   3               16             1110xxxx  10xxxxxx 10xxxxxx
   4               22             11110xxx  10xxxxxx 10xxxxxx 10xxxxxx
"""

"""
In the table, the 'x' represents the number of bits we can use to
store a character. The 0's and 1's are header bits.
"""

"""
1. Here is the unicode value of '汉' in hexadecimal
"""
print(hex(ord('汉')))
"""
2. Here it is in decimal
"""
print(ord('汉'))
"""
3. Here it is in binary
"""
print(bin(ord('汉')))
"""
16 bits are necessary for packing this character!
Therefore, UTF-8 Format tells use we need at least 3 bytes.
"""
print(bin(int('汉'.encode("utf-8").hex(), 16)))
"""
Now we can write this onto the hard drive!
And when we want to read it again, simply ready it in UTF-8 format.
This is default most places.
"""
