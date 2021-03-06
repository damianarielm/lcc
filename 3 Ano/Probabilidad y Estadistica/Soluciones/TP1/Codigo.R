# Carga los datos
datos<-read.table("base5.txt",header=TRUE,sep="\t")
attach(datos)

# Variable Origen: Grafico de sectores
etiquetas <- c("Ex�tico\n63,14%    ","    Nativo/Aut�ctono\n36,86% ")
pie(table(origen), labels=etiquetas)

#Varibale Brotes: Grafico bastones
plot(table(brotes),ylim=c(0,110),space=20,xlab="Cantidad de brotes",ylab="Cantidad de �rboles")

#Variable Especie: Grafico de barras
barplot(table(ordered(especie, levels=c("Palo borracho", "Eucalipto", "�lamo", "Casuarina", "Jacarand�", "Fresno", "Acacia", "Ceibo", "Ficus"))),ylim=c(0,70),xlab="Especie",ylab="Cantidad de �rboles",col="green", names.arg = c("Palo borracho", "Eucalipto", "�lamo", "Casuarina", "Jacarand�", "Fresno", "Acacia", "Ceibo", "Ficus"))

#Variable Altura: Histograma
hist(c(altura),xlab="Altura (m)",ylab="Cantidad de �rboles",col="green",main="")

#Variable Inclinacion: Histograma
hist(inclinaci�n, col="Green", breaks = 10, xlab = "Inclinaci�n (grados)", ylab = "Cantidad de �rboles", ylim=c(0,300), main="")

#Variable Diametro: Histograma
hist(diametro, col="Green", breaks = 15, xlab = "Di�metro (cm)", ylab = "Cantidad de �rboles", ylim=c(0,70), main="", xlim = c(0,180), axes=F)
axis(1, at=seq(0,200,20))
axis(2)

boxplot(altura ~ especie)
