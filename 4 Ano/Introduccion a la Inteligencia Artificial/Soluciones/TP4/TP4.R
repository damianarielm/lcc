library(caret)      # createDataPartition
library(rpart)      # rpart
library(rpart.plot) # rpart.plot
library(e1071)      # confusionMatrix
library(stringr)    # str_c
library(gtools)     # combinations

# Leemos el dataset original
dataSetOriginal <- read.csv("glass.data")

# Eliminamos la columna de los indices.
dataSet <- dataSetOriginal[, -1]

# Ponemos nombre a las variables
colnames(dataSet)[1]  <- "R.I"
colnames(dataSet)[2]  <- "Sodio"
colnames(dataSet)[3]  <- "Magnesio"
colnames(dataSet)[4]  <- "Aluminio"
colnames(dataSet)[5]  <- "Silicio"
colnames(dataSet)[6]  <- "Potasio"
colnames(dataSet)[7]  <- "Calcio"
colnames(dataSet)[8]  <- "Bario"
colnames(dataSet)[9]  <- "Hierro"
colnames(dataSet)[10] <- "Clase"

# Convertimos a factor la columna de las clases.
dataSet[, "Clase"] <- as.factor(dataSet[, "Clase"])

# Computamos todas las combinaciones de variables posibles.
lista <- c()
for (i in 1:9) {
    combinaciones <- combinations(9, i, names(dataSet[-10]))
    for (j in 1:nrow(combinaciones)) {
        combinacion <- str_c(combinaciones[j,], collapse = " + ")
        lista <- c(lista, paste("Clase ~ ", combinacion))
    }
}

semillas = 50
for (variables in lista) {
    # Acumuladores para elegir la mejor metrica.
    sumaGinni = 0; sumaInformation = 0

    for (seed in 0:semillas) {
        # Establecemos una semilla.
        set.seed(seed)

        # Dividimos el dataset en datos de entrenamiento y prueba.
        indices <- createDataPartition(dataSet[, "Clase"], p = .8, list = FALSE)
        entrenamiento <- dataSet[indices,]
        prueba <- dataSet[-indices,]

        # Creamos modelos a partir de los datos de entrenamiento.
        informationFit <- rpart(variables, data = entrenamiento,
                                parms = list(split = "information"))
        ginniFit <- rpart(variables, data = entrenamiento,
                          parms = list(split = "gini"))

        # Podamos los arboles.
        podaI <- prune(informationFit, cp = 0.01)
        podaG <- prune(ginniFit, cp = 0.01)

        # Probamos los modelos en los datos de prueba.
        prediccionI <- predict(informationFit, prueba, type = "class")
        prediccionG <- predict(ginniFit, prueba, type = "class")
        prediccionPodaI <- predict(podaI, prueba, type = "class")
        prediccionPodaG <- predict(podaG, prueba, type = "class")

        # Calculamos estadisticas.
        matrizI <- confusionMatrix(prediccionI, prueba[, "Clase"])
        matrizG <- confusionMatrix(prediccionG, prueba[, "Clase"])
        matrizPodaI <- confusionMatrix(prediccionPodaI, prueba[, "Clase"])
        matrizPodaG <- confusionMatrix(prediccionPodaG, prueba[, "Clase"])

        if (matrizPodaI$overall["Accuracy"] > matrizI$overall["Accuracy"]) {
            cat("ATENCION: Poda mejor que information.\n")
        }
        if (matrizPodaG$overall["Accuracy"] > matrizG$overall["Accuracy"]) {
            cat("ATENCION: Poda mejor que ginni\n")
        }

        sumaGinni <- sumaGinni + matrizG$overall["Accuracy"]
        sumaInformation <- sumaInformation + matrizI$overall["Accuracy"]

        # cat("[", Seed, "] ")
        if (matrizG$overall["Accuracy"] >= matrizI$overall["Accuracy"]) {
            # cat("Ginni Accuracy:\t\t", matrizG$overall["Accuracy"], "\n")
        } else {
            # cat("Information Accuracy:\t", matrizI$overall["Accuracy"], "\n")
        }

        # Dibujamos el arbol
        # rpart.plot(ginniFit)
    }

    promedioG = sumaGinni / (semillas + 1)
    promedioI = sumaInformation / (semillas + 1)

    # Decidimos la mejor metrica
    cat("\n")
    if (promedioG >= promedioI) {
        cat("Mejor metrica: ginni.\n")
        cat("Accuracy promedio:", promedioG, "\n")
    } else {
        cat("Mejor metrica: information.\n")
        cat("Accuracy promedio:", promedioI, "\n")
    }
    cat("Variables: ", variables, "\n")
}
