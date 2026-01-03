# Nom de l'exécutable
EXE = compile

# Compilateur
CCPP = g++

# Liste des fichiers à supprimer lors du nettoyage
RM_LIST = *.o *.out *~ 

# Règles de compilation : construction de l'exécutable
all: 
	$(CCPP) -o $(EXE) *.cpp ressources/*.cpp

# Nettoyage de fichiers temporaires et de l'exécutable
clean:
	$(RM) $(RM_LIST)

# Nettoyage complet
fclean: clean
	$(RM) $(EXE)

re : fclean all