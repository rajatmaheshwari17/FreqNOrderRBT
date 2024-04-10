MAIN           = WordFrequency
MAIN1          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
SOURCE1        = $(MAIN1).cpp
OBJECT         = $(MAIN).o
OBJECT1        = $(MAIN1).o
ADT_TEST       = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c -g
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN1): $(OBJECT1) $(ADT_OBJECT)
	$(LINK) $(MAIN1) $(OBJECT1) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT)Test: $(ADT)Test.o $(ADT_OBJECT)
	$(LINK) $(ADT)Test $(ADT)Test.o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT1): $(SOURCE1) $(ADT_HEADER)
	$(COMPILE) $(SOURCE1)

$(ADT)Test.o: $(ADT)Test.cpp $(ADT_HEADER)
	$(COMPILE) $(ADT)Test.cpp

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN1) $(ADT_TEST) $(ADT)Test $(OBJECT) $(OBJECT1) $(ADT_TEST).o  $(ADT)Test.o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in5 junk5

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)