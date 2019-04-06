# Carga los datos
datos<-read.table("base5.txt",header=TRUE,sep="\t")
attach(datos)

# Variable Origen: Grafico de sectores
etiquetas <- c("Exótico\n63,14%    ","    Nativo/Autóctono\n36,86% ")
pie(table(origen), labels=etiquetas)

#Varibale Brotes: Grafico bastones
plot(table(brotes),ylim=c(0,110),space=20,xlab="Cantidad de brotes",ylab="Cantidad de árboles")

#Variable Especie: Grafico de barras
barplot(table(ordered(especie, levels=c("Palo borracho", "Eucalipto", "Álamo", "Casuarina", "Jacarandá", "Fresno", "Acacia", "Ceibo", "Ficus"))),ylim=c(0,70),xlab="Especie",ylab="Cantidad de árboles",col="green", names.arg = c("Palo borracho", "Eucalipto", "Álamo", "Casuarina", "Jacarandá", "Fresno", "Acacia", "Ceibo", "Ficus"))

#Variable Altura: Histograma
hist(c(altura),xlab="Altura (m)",ylab="Cantidad de árboles",col="green",main="")

#Variable Inclinacion: Histograma
hist(inclinación, col="Green", breaks = 10, xlab = "Inclinación (grados)", ylab = "Cantidad de árboles", ylim=c(0,300), main="")

#Variable Diametro: Histograma
hist(diametro, col="Green", breaks = 15, xlab = "Diámetro (cm)", ylab = "Cantidad de árboles", ylim=c(0,70), main="", xlim = c(0,180), axes=F)
axis(1, at=seq(0,200,20))
axis(2)
