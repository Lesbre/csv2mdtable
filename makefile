CPP=./src
CPP_BLD=./build

markdown-table: $(CPP_BLD)/Makefile $(CPP_BLD)/*
	$(MAKE) -C $(CPP_BLD)
	mv $(CPP_BLD)/markdown-table .

$(CPP_BLD)/Makefile: CMakeLists.txt
	cmake -S . -B $(CPP_BLD)

.PHONY: clean release

clean:
	rm -rf build
	rm -f ./markdown-table

release:
	mv ./markdown-table ../../Scripts