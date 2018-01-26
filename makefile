# Compiler
CC = g++
OPTS = -c -Wall

# Project name
PROJECT = sensorapp

# Directories
OBJDIR = sensorapp/obj
SRCDIR = sensorapp/src
BINDIR = sensorapp/bin

# Libraries
LIBS = -pthread

# Files and folders
SRCS    = $(shell find $(SRCDIR) -name '*.cpp')
SRCDIRS = $(shell find . -name '*.cpp' | dirname {} | sort | uniq | sed 's/\/$(SRCDIR)//g' )
OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS) npm
	$(CC) $(OBJS) $(LIBS) -o $(BINDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(OPTS) -c $< -o $@

npm: 
	npm install
	
clean:
	rm $(OBJDIR) -rf
	
buildrepo:
	@$(call make-repo)

# Create obj and bin directory structure
define make-repo
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef