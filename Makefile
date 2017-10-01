MKDIR=mkdir


objects= $(OBJ_DIR)/main.o $(OBJ_DIR)/conjunction.o $(OBJ_DIR)/artery_MC.o $(OBJ_DIR)/artery_FV.o $(OBJ_DIR)/artery.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/generalParameters.o \
	$(OBJ_DIR)/vesselProperties.o $(OBJ_DIR)/matrix.o $(OBJ_DIR)/alger.o $(OBJ_DIR)/VECT.o $(OBJ_DIR)/network_arts_conjuncs.o \
	 $(OBJ_DIR)/stringManage.o $(OBJ_DIR)/Error.o $(OBJ_DIR)/triDiagMatrix.o 

INC_DIR=include
SRC_DIR=src
OBJ_DIR=obj

# specify the c++ compiler in your machine
CXX=g++-7 
CFLAGS=-I$(INC_DIR) -D NDEBUG -O3 -fopenmp -pthread  
LDFLAGS=-fopenmp -pthread

#CXX=icpc
#CFLAGS=-I$(INC_DIR) -D NDEBUG -O3 -openmp -pthread -liomp5
#LDFLAGS=-openmp -liomp5 -pthread

all: start bloodflow 

start:
	 - $(MKDIR) obj
	 - $(MKDIR) bin 

bloodflow: $(objects)
	$(CXX) $(LDFLAGS) -o bin/bloodflow $(objects) 

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/network_arts_conjuncs.h $(INC_DIR)/artery.h $(INC_DIR)/generalParameters.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/alger.o: $(SRC_DIR)/alger.cpp $(INC_DIR)/misc.h $(INC_DIR)/VECT.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/artery_MC.o: $(SRC_DIR)/artery_MC.cpp $(INC_DIR)/artery.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/artery_FV.o: $(SRC_DIR)/artery_FV.cpp $(INC_DIR)/artery.h $(INC_DIR)/generalParameters.h  $(INC_DIR)/vesselProperties.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/conjunction.o:$(SRC_DIR)/conjunction.cpp $(INC_DIR)/artery.h $(INC_DIR)/artery_FV.h $(INC_DIR)/artery_MC.h $(INC_DIR)/alger.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/generalParameters.o: $(SRC_DIR)/generalParameters.cpp $(INC_DIR)/misc.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/vesselProperties.o: $(SRC_DIR)/vesselProperties.cpp $(INC_DIR)/misc.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/matrix.o:$(SRC_DIR)/matrix.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/VECT.o: $(SRC_DIR)/VECT.cpp $(INC_DIR)/misc.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/network_arts_conjuncs.o:$(SRC_DIR)/network_arts_conjuncs.cpp $(INC_DIR)/artery.h $(INC_DIR)/artery_FV.h $(INC_DIR)/artery_MC.h $(INC_DIR)/alger.h $(INC_DIR)/conjunction.h $(INC_DIR)/parser.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/artery.o: $(SRC_DIR)/artery.cpp $(INC_DIR)/generalParameters.h $(INC_DIR)/misc.h $(INC_DIR)/vesselProperties.h $(INC_DIR)/VECT.h
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/stringManage.o:$(SRC_DIR)/stringManage.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/Error.o:$(SRC_DIR)/error.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR)/triDiagMatrix.o:$(SRC_DIR)/triDiagMatrix.cpp $(INC_DIR)/misc.h $(INC_DIR)/VECT.h
	$(CXX) -c -o $@ $< $(CFLAGS)
clean:
	rm -rf $(OBJ_DIR)/*.o bin/bloodflow
