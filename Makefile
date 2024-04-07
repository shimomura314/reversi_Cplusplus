# mingw32-make

# コンパイラの定義・コンパイルオプション
CC     = g++
CFLAGS = -Wall -Wextra -Werror

# 最終ターゲットファイル
all: matching
# all: othello matching

# 各ターゲットのビルドツール
# SRCS_othello   = $(wildcard bitboard/*.cpp strategy/*.cpp)
# OBJS_othello   = $(SRCS_othello:.cpp=.o)
LIBDIR = -LC:/Users/shimomura/anaconda3/libs
LIBS   = -lpython39
# othello: $(OBJS_othello)
# 	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

SRCS_matching    =  $(wildcard bitboard/*.cpp strategy/*.cpp matching/*.cpp)
OBJS_matching    =  $(SRCS_matching:.cpp=.o)
# -pgによりファイル実行時にgmon.outが生成される．
# gprof matching.exe gmon.out > gmon.txt
matching: $(OBJS_matching)
	$(CC) -pg -o $@ $^ $(LIBDIR) $(LIBS)

# 汎用的な.cppから.oへの変換ルール
INCDIR  =  -Ibitboard -Istrategy $(shell python -m pybind11 --includes)
INCDIR  += -IC:/Users/shimomura/anaconda3/include
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# 'clean' ターゲットの定義
# clean:
# 	-rm -f $(OBJS_othello) $(OBJS_matching) othello matching
clean:
	-rm -f $(OBJS_matching) othello matching
