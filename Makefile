CC      = g++
CFLAGS  = -Wall -Wextra -Werror
TARGET  = Othello
EXT_SUFFIX = .pyd
SRCS    =  $(wildcard bitboard/*.cpp strategy/*.cpp)
OBJS    =  $(SRCS:.cpp=.o)
INCDIR  =  -Ibitboard -Istrategy $(shell python -m pybind11 --includes)
INCDIR  += -IC:/Users/shimomura/anaconda3/include
LIBDIR  =  -LC:/Users/shimomura/anaconda3/libs
LIBS    =  -lpython39

# ターゲットのビルドルール
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# 汎用的な.cppから.oへの変換ルール
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# 'all' ターゲットの定義
all: clean $(OBJS) $(TARGET)

# 'clean' ターゲットの定義
clean:
	-rm -f $(OBJS) $(TARGET)
