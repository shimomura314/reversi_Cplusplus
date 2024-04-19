# mingw32-make

# コンパイラの定義・コンパイルオプション
CC     = g++
CFLAGS = -Wall -Wextra -Werror

# 最終ターゲットファイル
all: matching

# 各ターゲットのビルドツール
SRCS_matching    =  $(wildcard bitboard/*.cpp strategy/*.cpp matching/*.cpp)
OBJS_matching    =  $(SRCS_matching:.cpp=.o)
matching: $(OBJS_matching)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)
# -p: prof用．ファイル実行時にmon.outが生成される．
# prof matching.exe > mon.txt
# matching: $(OBJS_matching)
# 	$(CC) -p -o $@ $^ $(LIBDIR) $(LIBS)  
# -pg: gprof用．ファイル実行時にgmon.outが生成される．
# gprof matching.exe gmon.out > gmon.txt
# matching: $(OBJS_matching)
# 	$(CC) -pg -o $@ $^ $(LIBDIR) $(LIBS)

# 汎用的な.cppから.oへの変換ルール
INCDIR  =  -Ibitboard -Istrategy $(shell python -m pybind11 --includes)
INCDIR  += -IC:/Users/shimomura/anaconda3/include
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# 'clean' ターゲットの定義
clean:
	-rm -f $(OBJS_matching) othello matching
