all:
	# JAVA Library and Node Manager
	@cd ./libjausJava; make all install;
	@cd ./nodeManager; make all install;

	# C Libraries
	@cd ./libcimar; make all install;
	@cd ./libjausC; make all install;
	@cd ./libnodeManager; make all install;	

clean:
	# JAVA Library and Node Manager
	@cd ./libjausJava; make clean;
	@cd ./nodeManager; make clean;

	# C Libraries
	@cd ./libcimar; make clean;
	@cd ./libjausC; make clean;
	@cd ./libnodeManager; make clean;
	
	# Sample Components
	@cd ./node; make clean;

install:
	./Install
	
uninstall:
	./Uninstall	
