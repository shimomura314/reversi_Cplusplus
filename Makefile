# mingw32-make

# コンパイラの定義・コンパイルオプション
CC     = g++
CFLAGS = -Wall -Wextra -Werror

# 最終ターゲットファイル
all: othello

# 各ターゲットのビルドツール
SRCS_othello   = $(wildcard bitboard/*.cpp strategy/*.cpp)
OBJS_othello   = $(SRCS_othello:.cpp=.o)
othello: $(OBJS_othello)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# 汎用的な.cppから.oへの変換ルール
INCDIR  =  -Ibitboard -Istrategy
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# 'clean' ターゲットの定義
clean:
	-rm -f $(OBJS_othello) othello