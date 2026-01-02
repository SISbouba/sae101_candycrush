NAME = compile

CC = g++

RM_LIST = *.o *.out *~ 

all: 
	$(CC) -o $(NAME) *.cpp ressources/*.cpp

clean:
	$(RM) $(RM_LIST)

fclean: clean
	$(RM) $(NAME)

re : fclean all