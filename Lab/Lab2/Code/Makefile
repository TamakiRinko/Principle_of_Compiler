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
	./parser ../Test/A-6.0.cmm
	./parser ../Test/A-7.0.cmm
	./parser ../Test/A-8.0.cmm
	./parser ../Test/A-9.0.cmm
	./parser ../Test/A-10.0.cmm
	./parser ../Test/A-11.0.cmm
	./parser ../Test/A-12.0.cmm
	./parser ../Test/A-13.0.cmm
	./parser ../Test/A-14.0.cmm
	./parser ../Test/A-15.0.cmm
	./parser ../Test/A-16.0.cmm
	./parser ../Test/A-17.0.cmm
	./parser ../Test/A-18.0.cmm
	./parser ../Test/A-19.0.cmm
	./parser ../Test/A-20.0.cmm
	./parser ../Test/A-21.0.cmm
	./parser ../Test/A-22.0.cmm
	./parser ../Test/A-23.0.cmm
	./parser ../Test/A-24.0.cmm
	./parser ../Test/A-25.0.cmm
	./parser ../Test/B-6-1.0.cmm
	./parser ../Test/B-6-2.0.cmm
	./parser ../Test/B-6-3.0.cmm
	./parser ../Test/B-6-4.0.cmm
	./parser ../Test/B-6-5.0.cmm
	./parser ../Test/B-6-6.0.cmm
	./parser ../Test/B-6-7.0.cmm
	./parser ../Test/B-6-8.0.cmm
	./parser ../Test/B-6-9.0.cmm
	./parser ../Test/B-7-1.0.cmm
	./parser ../Test/B-7-2.0.cmm
	./parser ../Test/B-7-3.0.cmm
	./parser ../Test/B-7-4.0.cmm
	./parser ../Test/B-7-5.0.cmm
	./parser ../Test/B-7-6.0.cmm
	./parser ../Test/B-7-7.0.cmm
	./parser ../Test/B-7-8.0.cmm
	./parser ../Test/B-7-9.0.cmm
	./parser ../Test/B-8-1.0.cmm
	./parser ../Test/B-8-2.0.cmm
	./parser ../Test/B-8-3.0.cmm
	./parser ../Test/B-8-4.0.cmm
	./parser ../Test/B-8-5.0.cmm
	./parser ../Test/B-8-6.0.cmm
	./parser ../Test/B-8-7.0.cmm
	./parser ../Test/B-8-8.0.cmm
	./parser ../Test/B-8-9.0.cmm
	./parser ../Test/B-9-1.0.cmm
	./parser ../Test/B-9-2.0.cmm
	./parser ../Test/B-9-3.0.cmm
	./parser ../Test/B-9-4.0.cmm
	./parser ../Test/B-9-5.0.cmm
	./parser ../Test/B-9-6.0.cmm
	./parser ../Test/B-9-7.0.cmm
	./parser ../Test/B-9-8.0.cmm
	./parser ../Test/B-9-9.0.cmm
	./parser ../Test/B-10-1.0.cmm
	./parser ../Test/B-10-2.0.cmm
	./parser ../Test/B-10-3.0.cmm
	./parser ../Test/B-10-4.0.cmm
	./parser ../Test/B-10-5.0.cmm
	./parser ../Test/B-10-6.0.cmm
	./parser ../Test/B-10-7.0.cmm
	./parser ../Test/B-10-8.0.cmm
	./parser ../Test/B-10-9.0.cmm
	./parser ../Test/B-11-1.0.cmm
	./parser ../Test/B-11-2.0.cmm
	./parser ../Test/B-11-3.0.cmm
	./parser ../Test/B-11-4.0.cmm
	./parser ../Test/B-11-5.0.cmm
	./parser ../Test/B-11-6.0.cmm
	./parser ../Test/B-11-7.0.cmm
	./parser ../Test/B-11-8.0.cmm
	./parser ../Test/B-11-9.0.cmm
	./parser ../Test/B-12-1.0.cmm
	./parser ../Test/B-12-2.0.cmm
	./parser ../Test/B-12-3.0.cmm
	./parser ../Test/B-12-4.0.cmm
	./parser ../Test/B-12-5.0.cmm
	./parser ../Test/B-12-6.0.cmm
	./parser ../Test/B-12-7.0.cmm
	./parser ../Test/B-12-8.0.cmm
	./parser ../Test/B-12-9.0.cmm
	./parser ../Test/B-13-1.0.cmm
	./parser ../Test/B-13-2.0.cmm
	./parser ../Test/B-13-3.0.cmm
	./parser ../Test/B-13-4.0.cmm
	./parser ../Test/B-13-5.0.cmm
	./parser ../Test/B-13-6.0.cmm
	./parser ../Test/B-13-7.0.cmm
	./parser ../Test/B-13-8.0.cmm
	./parser ../Test/B-13-9.0.cmm
	./parser ../Test/B-14-1.0.cmm
	./parser ../Test/B-14-2.0.cmm
	./parser ../Test/B-14-3.0.cmm
	./parser ../Test/B-14-4.0.cmm
	./parser ../Test/B-14-5.0.cmm
	./parser ../Test/B-14-6.0.cmm
	./parser ../Test/B-14-7.0.cmm
	./parser ../Test/B-14-8.0.cmm
	./parser ../Test/B-14-9.0.cmm
	./parser ../Test/B-15-1.0.cmm
	./parser ../Test/B-15-2.0.cmm
	./parser ../Test/B-15-3.0.cmm
	./parser ../Test/B-15-4.0.cmm
	./parser ../Test/B-15-5.0.cmm
	./parser ../Test/B-15-6.0.cmm
	./parser ../Test/B-15-7.0.cmm
	./parser ../Test/B-15-8.0.cmm
	./parser ../Test/B-15-9.0.cmm
	./parser ../Test/B-16-1.0.cmm
	./parser ../Test/B-16-2.0.cmm
	./parser ../Test/B-16-3.0.cmm
	./parser ../Test/B-16-4.0.cmm
	./parser ../Test/B-16-5.0.cmm
	./parser ../Test/B-16-6.0.cmm
	./parser ../Test/B-16-7.0.cmm
	./parser ../Test/B-16-8.0.cmm
	./parser ../Test/B-16-9.0.cmm
	./parser ../Test/B-17-1.0.cmm
	./parser ../Test/B-17-2.0.cmm
	./parser ../Test/B-17-3.0.cmm
	./parser ../Test/B-17-4.0.cmm
	./parser ../Test/B-17-5.0.cmm
	./parser ../Test/B-17-6.0.cmm
	./parser ../Test/B-17-7.0.cmm
	./parser ../Test/B-17-8.0.cmm
	./parser ../Test/B-17-9.0.cmm
	./parser ../Test/B-18-1.0.cmm
	./parser ../Test/B-18-2.0.cmm
	./parser ../Test/B-18-3.0.cmm
	./parser ../Test/B-18-4.0.cmm
	./parser ../Test/B-18-5.0.cmm
	./parser ../Test/B-18-6.0.cmm
	./parser ../Test/B-18-7.0.cmm
	./parser ../Test/B-18-8.0.cmm
	./parser ../Test/B-18-9.0.cmm
	./parser ../Test/B-19-1.0.cmm
	./parser ../Test/B-19-2.0.cmm
	./parser ../Test/B-19-3.0.cmm
	./parser ../Test/B-19-4.0.cmm
	./parser ../Test/B-19-5.0.cmm
	./parser ../Test/B-19-6.0.cmm
	./parser ../Test/B-19-7.0.cmm
	./parser ../Test/B-19-8.0.cmm
	./parser ../Test/B-19-9.0.cmm
	./parser ../Test/B-20-1.0.cmm
	./parser ../Test/B-20-2.0.cmm
	./parser ../Test/B-20-3.0.cmm
	./parser ../Test/B-20-4.0.cmm
	./parser ../Test/B-20-5.0.cmm
	./parser ../Test/B-20-6.0.cmm
	./parser ../Test/B-20-7.0.cmm
	./parser ../Test/B-20-8.0.cmm
	./parser ../Test/B-20-9.0.cmm
	./parser ../Test/B-21-1.0.cmm
	./parser ../Test/B-21-2.0.cmm
	./parser ../Test/B-21-3.0.cmm
	./parser ../Test/B-21-4.0.cmm
	./parser ../Test/B-21-5.0.cmm
	./parser ../Test/B-21-6.0.cmm
	./parser ../Test/B-21-7.0.cmm
	./parser ../Test/B-21-8.0.cmm
	./parser ../Test/B-21-9.0.cmm
	./parser ../Test/B-22-1.0.cmm
	./parser ../Test/B-22-2.0.cmm
	./parser ../Test/B-22-3.0.cmm
	./parser ../Test/B-22-4.0.cmm
	./parser ../Test/B-22-5.0.cmm
	./parser ../Test/B-22-6.0.cmm
	./parser ../Test/B-22-7.0.cmm
	./parser ../Test/B-22-8.0.cmm
	./parser ../Test/B-22-9.0.cmm
	./parser ../Test/B-23-1.0.cmm
	./parser ../Test/B-23-2.0.cmm
	./parser ../Test/B-23-3.0.cmm
	./parser ../Test/B-23-4.0.cmm
	./parser ../Test/B-23-5.0.cmm
	./parser ../Test/B-23-6.0.cmm
	./parser ../Test/B-23-7.0.cmm
	./parser ../Test/B-23-8.0.cmm
	./parser ../Test/B-23-9.0.cmm
	./parser ../Test/B-24-1.0.cmm
	./parser ../Test/B-24-2.0.cmm
	./parser ../Test/B-24-3.0.cmm
	./parser ../Test/B-24-4.0.cmm
	./parser ../Test/B-24-5.0.cmm
	./parser ../Test/B-24-6.0.cmm
	./parser ../Test/B-24-7.0.cmm
	./parser ../Test/B-24-8.0.cmm
	./parser ../Test/B-24-9.0.cmm
	./parser ../Test/B-25-1.0.cmm
	./parser ../Test/B-25-2.0.cmm
	./parser ../Test/B-25-3.0.cmm
	./parser ../Test/B-25-4.0.cmm
	./parser ../Test/B-25-5.0.cmm
	./parser ../Test/B-25-6.0.cmm
	./parser ../Test/B-25-7.0.cmm
	./parser ../Test/B-25-8.0.cmm
	./parser ../Test/B-25-9.0.cmm
	./parser ../Test/C.1.cmm
	./parser ../Test/C.2.cmm
	./parser ../Test/C.3.cmm
	./parser ../Test/C.4.cmm
	./parser ../Test/C.5.cmm
	./parser ../Test/C.6.cmm
	./parser ../Test/C.7.cmm
	./parser ../Test/C.8.cmm
	./parser ../Test/C.9.cmm
	./parser ../Test/C.10.cmm
	./parser ../Test/C.11.cmm
	./parser ../Test/C.12.cmm
	./parser ../Test/C.13.cmm
	./parser ../Test/C.14.cmm
	./parser ../Test/C.15.cmm
	./parser ../Test/C.16.cmm
	./parser ../Test/C.17.cmm
	./parser ../Test/C.18.cmm
	./parser ../Test/C.19.cmm


	
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~

