all:
	gcc randf.c rnorm.c -o rnorm -lm
	gcc diagonal.c -o diagonal -lm
	gcc randf.c esquina.c -o esquina
	gcc randf.c espirales.c -o espirales -lm
	gcc names.c -o names
clean:
	rm rnorm; rm diagonal; rm esquina; rm espirales; \
	rm espirales.jpg; rm espirales.data; rm names
