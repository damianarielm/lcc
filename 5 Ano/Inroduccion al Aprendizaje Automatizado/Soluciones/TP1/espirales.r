datos = read.csv("espirales.data", sep = ",")
datos[datos[,3] == 1, 3] = "red"
datos[datos[,3] == 0, 3] = "green"

jpeg("espirales.jpg", 700, 700)
plot(datos[,1], datos[,2], col = datos[,3])
dev.off()
