# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: boris42 <boris42@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 12:19:40 by boris42           #+#    #+#              #
#    Updated: 2017/05/02 13:53:58 by boris42          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR	= ./srcs/

NAME    = Bomberman

CXX	= g++

SRCS	= $(DIR)main.cpp \
		$(DIR)Graphic.cpp \
		$(DIR)Game.cpp \
		$(DIR)MenuManager.cpp \
		$(DIR)MenuReceiver.cpp \
		$(DIR)Inputs/PlayerInputComponent.cpp \
		$(DIR)Map.cpp \
		$(DIR)GameObject.cpp \
		$(DIR)Player.cpp \
		$(DIR)Inputs/EventReceiver.cpp \
		$(DIR)move.cpp \
		$(DIR)Bomb.cpp \
		$(DIR)Explosion.cpp \
		$(DIR)IaPlayer.cpp \
		$(DIR)Sound.cpp \
	  	$(DIR)Except.cpp


OBJ	= $(SRCS:.cpp=.o)

DONE	= "\033[34;01mdone in release mode"

BASEFLAGS += -W -Wall -Werror -std=c++11 -g
BASEFLAGS += -I./includes/ -I./includes/Inputs ##-I./irrKlang/include/
CXXFLAGS  += $(BASEFLAGS)

LDFLAGS = -lIrrlicht -Wl,-rpath,/usr/lib/ -lIrrKlang -lGL -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread

OUT	= -Werror
d	: CXXFLAGS = $(filter-out $(OUT), $(BASEFLAGS))
d	: CXXFLAGS += -g3 -O3 -Wno-unused-result
d	: DONE = "\033[33;01mdone in debug mode"

all	: $(NAME)

install :
	-@mkdir IrrLicht
	@echo "Downloading IrrLicht..."
	@wget -q "http://downloads.sourceforge.net/irrlicht/irrlicht-1.8.4.zip"
	@echo "Ok\nExtracting..."
	@unzip -q irrlicht-1.8.4.zip -d IrrLicht
	@echo "Ok"
	@rm irrlicht-1.8.4.zip
	-@mkdir /usr/include/irr
	-@cp IrrLicht/irrlicht-1.8.4/include/* /usr/include/irr/
	@echo "Making lib..."
	@make -C IrrLicht/irrlicht-1.8.4/source/Irrlicht/ > /dev/null 2>&1
	@echo "Ok"
	-@cp IrrLicht/irrlicht-1.8.4/lib/Linux/libIrrlicht.a /usr/lib/
	-@mkdir IrrKlang
	@echo "Downloading IrrKlang..."
	@wget -q "http://www.ambiera.at/downloads/irrKlang-64bit-1.5.0.zip"
	@unzip -q irrKlang-64bit-1.5.0.zip -d IrrKlang
	@echo "Ok"
	@rm irrKlang-64bit-1.5.0.zip
	-mkdir /usr/include/irr
	-cp IrrKlang/irrKlang-64bit-1.5.0/include/* /usr/include/irr/
	@echo "Ok"
	-cp IrrKlang/irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so /usr/lib/
	-cp IrrKlang/irrKlang-64bit-1.5.0/bin/linux-gcc-64/ikpFlac.so  IrrKlang/irrKlang-64bit-1.5.0/bin/linux-gcc-64/ikpMP3.so ./
$(NAME)	: $(OBJ)
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo $(DONE)

clean	:
	@$(RM) $(OBJ)
	@echo "\033[0;0m.o deleted"

fclean	: clean
	@$(RM) $(NAME)
	@echo "\033[0;0mexec deleted"

re	: fclean all

d	: fclean $(NAME)

%.o     : %.c
	@echo "\033[31;01m$< \033[0;01m-> \033[32;01m$@"
	@$(CXX) -c -o $@ $(CFLAGS) $<

%.o     : %.cpp
	@echo "\033[31;01m$< \033[0;01m-> \033[32;01m$@"
	@$(CXX) -c -o $@ $(CXXFLAGS) $<

.PHONY	: all clean fclean re d install %.o
