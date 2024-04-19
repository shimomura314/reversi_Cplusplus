# mingw32-make

# コンパイラの定義・コンパイルオプション
CC     = emcc
CFLAGS = -Wall -Wextra -Werror -s WASM=1

# 最終ターゲットファイル
all: othello

# 各ターゲットのビルドツール
SRCS_othello   = $(wildcard bitboard/*.cpp strategy/*.cpp)
OBJS_othello   = $(SRCS_othello:.cpp=.o)
othello: $(OBJS_othello)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS) -s 'INVOKE_RUN=0' -s EXPORTED_FUNCTIONS='["_playGame","_initGame"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'

# 汎用的な.cppから.oへの変換ルール
INCDIR  =  -Ibitboard -Istrategy
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# 'clean' ターゲットの定義
clean:
	-rm -f $(OBJS_othello) othello