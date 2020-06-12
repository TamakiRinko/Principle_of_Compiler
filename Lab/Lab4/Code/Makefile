# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test:
	./parser ../Test/Tests/A_1.cmm ../Result/oldA_1.s
	./parser ../Test/Tests/A_2.cmm ../Result/oldA_2.s
	./parser ../Test/Tests/A_3.cmm ../Result/oldA_3.s
	./parser ../Test/Tests/A_4.cmm ../Result/oldA_4.s
	./parser ../Test/Tests/A_5.cmm ../Result/oldA_5.s
	./parser ../Test/Tests/B_1.cmm ../Result/oldB_1.s
	./parser ../Test/Tests/B_2.cmm ../Result/oldB_2.s
	./parser ../Test/Tests/B_3.cmm ../Result/oldB_3.s
	./parser ../Test/Tests/C_1.cmm ../Result/oldC_1.s
	./parser ../Test/Tests/C_2.cmm ../Result/oldC_2.s
	./parser ../Test/Tests/D_1.cmm ../Result/oldD_1.s
	./parser ../Test/Tests2/A_1.cmm ../Result/newA_1.s
	./parser ../Test/Tests2/A_2.cmm ../Result/newA_2.s
	./parser ../Test/Tests2/A_3.cmm ../Result/newA_3.s
	./parser ../Test/Tests2/A_4.cmm ../Result/newA_4.s
	./parser ../Test/Tests2/A_5.cmm ../Result/newA_5.s
	./parser ../Test/Tests2/B_1.cmm ../Result/newB_1.s
	./parser ../Test/Tests2/B_2.cmm ../Result/newB_2.s
	./parser ../Test/Tests2/B_3.cmm ../Result/newB_3.s
	./parser ../Test/Tests2/C_1.cmm ../Result/newC_1.s
	./parser ../Test/Tests2/C_2.cmm ../Result/newC_2.s
	./parser ../Test/Tests2/D_1.cmm ../Result/newD_1.s

	
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
