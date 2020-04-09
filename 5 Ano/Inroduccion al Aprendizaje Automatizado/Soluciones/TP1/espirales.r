radios  = scan("radios")
angulos = scan("angulos")
x       = radios * cos(angulos)
y       = radios * sin(angulos)

fx = angulos / (4 * pi)
gx = (angulos + pi) / (4 * pi)
colores = ifelse((fx < radios & radios < gx) | (fx + 0.5 < radios & radios < gx + 0.5), "green", "red")

jpeg("espirales.jpg", 700, 700)
plot(x, y, col = colores)
dev.off()
