#Project to read PRs for JIRA/ADO tickets
#Mac/OS makefile
PRJ_NAME = pr_finder
CPPR_ROOT_INCL = /usr/local/opt/cpprestsdk/include
CPP_REST_INCL = $(CPPR_ROOT_INCL)/cpprest
CPP_PPLX_INCL = $(CPPR_ROOT_INCL)/pplx
INCLUDES = -I $(CPP_REST_INCL) -I$(CPP_PPLX_INCL) -I$(CPP_REST_INCL)/details -I/usr/local/opt/openssl/include -I/usr/local/opt/boost@1.81/include
CC_FLAGS = $(INCLUDES) 
LIB_PATHS=-L/usr/local/opt/openssl/lib -L/usr/local/opt/cpprestsdk/lib -L/usr/local/opt/boost@1.81/lib
LIBS=-lcrypto -lcpprest -lboost_program_options
L_FLAGS= $(LIB_PATHS) $(LIBS)
OBJECTS=main.o json_utils.o jira.o azdev.o utils.o
all: $(OBJECTS) ajdebug
	g++ $(L_FLAGS) $^ -o $(PRJ_NAME)
#Proyecto para mostrar el contenido JSON de cualquier ticket
ajdebug:$(OBJECTS:main.o=debug.o)
	g++ $(L_FLAGS) $^ -o $@
clean:
	rm  -f *.o $(PRJ_NAME)
%.o: %.cpp
	g++ -c $(CC_FLAGS)  -std=c++11 $^ -o $@
