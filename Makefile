CC = gcc 
CFLAGS = -Wall -Wextra -Werror 


s21_cat : s21_cat.c 
	$(CC) $(CFLAGS) -o s21_cat s21_cat.c 

clean : 
	rm s21_cat
test :
	bash test.sh