read %r0
cmp $0, %r0
jmpl end
mul $-1, %r0
end:
print %r0
hlt
