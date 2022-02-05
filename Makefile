SRC=./
OUT=./build
SOURCES="main.ç"
OBJECTS=$(shell echo $(SOURCES) | tr -s '.ç' '.co')
RUN=valgrind --leak-check=full --show-leak-kinds=all
çc=./çc
all:			$(OBJECTS)
compiler:		çc
	cd ft_cedille && make compiler && cp ./çc ../
%.ce:			$(SRC)/%.ç	compiler
	mkdir -p `dirname $(OUT)/$@`
	touch .a.txt
	cp .a.txt .b.txt
	touch .b.txt
	echo "oka"
	cp -n "$<" "$(OUT)/$@" || echo ""
	$(RUN) $(çc) -I$(SRC) $(OUT)/$@ -e -compiler.c -o ./
	clang -g -I$(SRC) $(OUT)/$@-compiler.c -o \
			$(OUT)/$@-compiler -fblocks -lBlocksRuntime -luring 
	$(RUN) $(OUT)/$@-compiler\
			$(OUT)/$@ .a.txt
	cp .a.txt $(OUT)/$@
	((cmp .a.txt .b.txt) || (make $@))
%.co:			%.ce	
	rm .a.txt
	rm .b.txt
	cp $(OUT)/$< $(OUT)/$<.c 
	clang -I$(SRC)  $(OUT)/$<.c -fblocks -lBlocksRuntime -luring  && ./a.out 
	echo "yayy $@"
	rm "$(OUT)/$<"
clean:
	rm -rf çc çc.dSYM
.SUFFIXES:
.PHONY:	compiler çc
