# mingw32-make

# コンパイラの定義・コンパイルオプション
CC     = g++
CFLAGS = -Wall -Wextra -Werror

# 最終ターゲットファイル
all: matching

# 各ターゲットのビルドツール
LIBDIR = -LC:/Users/shimomura/anaconda3/libs
LIBS   = -lpython39

SRCS_matching    =  $(wildcard bitboard/*.cpp strategy/*.cpp matching/*.cpp)
OBJS_matching    =  $(SRCS_matching:.cpp=.o)
matching: $(OBJS_matching)
	$(CC) -pg -o $@ $^ $(LIBDIR) $(LIBS)

# 汎用的な.cppから.oへの変換ルール
INCDIR  =  -Ibitboard -Istrategy $(shell python -m pybind11 --includes)
INCDIR  += -IC:/Users/shimomura/anaconda3/include
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c -pg $< -o $@

clean:
	-rm -f $(OBJS_matching) othello matching